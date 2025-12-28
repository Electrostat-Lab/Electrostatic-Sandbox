#include <electroio/kio/ieee1284_module.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static inline void cleanup(parport_module *pmodule) {
  //TODO later
}

// routines for initializing compat mode as a host initiated mode
static inline void init_host_compat_handshakes(parport_module *pmodule) {
  // 1) set busy control to low
  pport_write_controls(pmodule, &(parport_register){
                                    .bit0 = IEEE1284_LOGIC_ON,  // nStrobe
                                    .bit1 = IEEE1284_LOGIC_ON,  // nAck
                                    .bit2 = IEEE1284_LOGIC_OFF, // Busy
                                });
  // wait T(setup)
  // 2) set nStrobe (c0) to low!
  pport_write_controls(pmodule, &(parport_register){
                                    .bit0 = IEEE1284_LOGIC_OFF,
                                    .bit1 = IEEE1284_LOGIC_ON, // retain the low logic of c1
                                    .bit2 = IEEE1284_LOGIC_OFF // retain the low logic of c2
                                });
  // wait T(busy)
  // 3) connect the busy control and set it to HIGH (PIN 11 on the first row).
  pport_write_controls(pmodule, &(parport_register){
                                    .bit0 = IEEE1284_LOGIC_OFF, // retain the low logic of c0
                                    .bit1 = IEEE1284_LOGIC_ON,
                                    .bit2 = IEEE1284_LOGIC_ON,
                                });
  // 4) set nStrobe (c0) to high!
  pport_write_controls(pmodule, &(parport_register){
                                    .bit0 = IEEE1284_LOGIC_ON,
                                    .bit1 = IEEE1284_LOGIC_ON,
                                    .bit2 = IEEE1284_LOGIC_ON, // retain the high logic of c2
                                });
  // 5) set PtrClk(Ack) to low retaining the other pins logic
  pport_write_controls(pmodule, &(parport_register){
                                    .bit0 = IEEE1284_LOGIC_ON, // retain the high logic of c0
                                    .bit1 = IEEE1284_LOGIC_OFF,
                                    .bit2 = IEEE1284_LOGIC_ON, // retain the high logic of c2
                                });
  // Now write the data
}

static inline void terminate_host_compat_handshakes(parport_module *pmodule) {
  // 6) set PtrClk(Ack) to high retaining the other pins logic
  pport_write_controls(pmodule, &(parport_register){
                                    .bit0 = IEEE1284_LOGIC_ON, // retain the high logic of c0
                                    .bit1 = IEEE1284_LOGIC_ON,
                                    .bit2 = IEEE1284_LOGIC_ON, // retain the high logic of c2
                                });
  // 6) set PtrClk(Ack) to high retaining the other pins logic
  pport_write_controls(pmodule, &(parport_register){
                                    .bit0 = IEEE1284_LOGIC_ON, // retain the high logic of c0
                                    .bit1 = IEEE1284_LOGIC_ON, // retain the high logic of c1
                                    .bit2 = IEEE1284_LOGIC_OFF,
                                });
  // Now the cycle could be repeated!
}

__int8_t init_mode(parport_module *pmodule) {
  if (pmodule == NULL) {
    return 1;
  }
  if (pmodule->pport_mode == IEEE1284_MODE_COMPAT) {
    init_host_compat_handshakes(pmodule);
  } else {
    perror("Mode not identified!\n");
  }
  return 0;
}


__int8_t terminate_mode(parport_module *pmodule) {
  if (pmodule == NULL) {
    return 1;
  }
  if (pmodule->pport_mode == IEEE1284_MODE_COMPAT) {
    terminate_host_compat_handshakes(pmodule);
  } else {
    perror("Mode not identified!\n");
  }
  return 0;
}

uint8_t pport_init_callbacks(parport_module *pport_module,
                             parport_callbacks pport_callbacks) {
  if (pport_module == NULL) {
    return 1;
  }
  pport_module->pport_callbacks.on_operation_success = pport_callbacks.on_operation_success;
  pport_module->pport_callbacks.on_operation_failure = pport_callbacks.on_operation_failure;

  if (pport_callbacks.cleanup != NULL) {
    pport_module->pport_callbacks.cleanup = pport_callbacks.cleanup;
  } else {
    pport_module->pport_callbacks.cleanup = &cleanup;
  }
  return 0;
}

int pport_open(parport_module *pmodule) {
  if (pmodule == NULL || pmodule->device == NULL || pmodule->fd > 0) {
    return 1;
  }
  pmodule->fd = open(pmodule->device, pmodule->access);
  // post-processing checks and callbacks
  if (pmodule->fd < 0) {
    if (pmodule->pport_callbacks.on_operation_failure) {
      pmodule->pport_callbacks.on_operation_failure(pmodule, errno, &pport_open);
    }
    return 1;
  }
  if (pmodule->pport_callbacks.on_operation_success) {
    pmodule->pport_callbacks.on_operation_success(pmodule, &pport_open);
  }
  return pmodule->fd;
}

__int8_t pport_close(parport_module *pmodule) {
  if (pmodule == NULL || pmodule->fd < 0) {
    return 1;
  }
  // call the pre-processing release
  pport_release(pmodule);
  __int8_t ret = close(pmodule->fd);
  // call post-processing cleanup
  if (ret == 0) {
    if (pmodule->pport_callbacks.on_operation_success != NULL) {
      pmodule->pport_callbacks.on_operation_success(pmodule, &pport_close);
    }
  } else {
    if (pmodule->pport_callbacks.on_operation_failure != NULL) {
      pmodule->pport_callbacks.on_operation_failure(pmodule, errno, &pport_close);
    }
  }
  if (pmodule->pport_callbacks.cleanup != NULL) {
    pmodule->pport_callbacks.cleanup(pmodule);
  }
  return ret;
}

__int8_t pport_release(parport_module *pmodule) {
  if (pmodule == NULL || pmodule->fd < 0) {
    return 1;
  }
  int ret = ioctl(pmodule->fd, PPRELEASE);
  if (ret < 0) {
    if (pmodule->pport_callbacks.on_operation_failure != NULL) {
      pmodule->pport_callbacks.on_operation_failure(pmodule, errno, &pport_release);
    }
  } else {
    if (pmodule->pport_callbacks.on_operation_success != NULL) {
      pmodule->pport_callbacks.on_operation_success(pmodule, &pport_release);
    }
  }
  return ret;
}

__int8_t pport_load_mode(parport_module *pmodule) {
  if (pmodule == NULL || pmodule->fd < 0 || pmodule->pport_mode == 0) {
    return 1;
  }
  int ret = ioctl(pmodule->fd, PPSETMODE, &(pmodule->pport_mode));
  if (ret < 0) {
    if (pmodule->pport_callbacks.on_operation_failure != NULL) {
      pmodule->pport_callbacks.on_operation_failure(pmodule, errno, &pport_load_mode);
    }
    pport_release(pmodule);
    pport_close(pmodule);
  } else {
    if (pmodule->pport_callbacks.on_operation_success != NULL) {
      pmodule->pport_callbacks.on_operation_success(pmodule, &pport_load_mode);
    }
  }
  return ret;
}

__int8_t pport_claim(parport_module *pmodule) {
  if (pmodule->fd < 0 || pmodule->pport_mode == 0) {
    return 1;
  }
  int ret = ioctl(pmodule->fd, PPCLAIM);
  if (ret < 0) {
    if (pmodule->pport_callbacks.on_operation_failure != NULL) {
      pmodule->pport_callbacks.on_operation_failure(pmodule, errno, &pport_claim);
    }
    pport_close(pmodule);
  } else {
    if (pmodule->pport_callbacks.on_operation_success != NULL) {
      pmodule->pport_callbacks.on_operation_success(pmodule, &pport_claim);
    }
  }
  return ret;
}

__int8_t pport_write_controls(parport_module *pmodule, parport_register *pregister) {
  if (pmodule == NULL || pmodule->fd < 0 || pregister == NULL) {
    return 1;
  }
  // conversion of the logical values to bitwise values
  // first: convert the user values into strict logic values (i.e., ON or OFF) (Logic ANDing).
  // second: bitwise left shift the converted logic values into its position in the register (Lshift).
  // third: add the positioned bits together to build the register (Bitwise ORing).
  // forth: write the byte to the control register (IO Commanding).
  pregister->bit0 = (pregister->bit0 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_0;
  pregister->bit1 = (pregister->bit1 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_1;
  pregister->bit2 = (pregister->bit2 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_2;
  pregister->bit3 = (pregister->bit3 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_3;
  pregister->bit4 = (pregister->bit4 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_4;
  pregister->bit5 = (pregister->bit5 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_5;
  pregister->bit6 = (pregister->bit6 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_6;
  pregister->bit7 = (pregister->bit7 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_7;

  pregister->memory = pregister->bit0 | pregister->bit1 | pregister->bit2 | pregister->bit3 |
                      pregister->bit4 | pregister->bit5 | pregister->bit6 | pregister->bit7;

  int ret = ioctl(pmodule->fd, PPWCONTROL, &(pregister->memory));
  if (ret < 0) {
    if (pmodule->pport_callbacks.on_operation_failure != NULL) {
      pmodule->pport_callbacks.on_operation_failure(pmodule, errno, &pport_write_controls);
    }
  } else {
    if (pmodule->pport_callbacks.on_operation_success != NULL) {
      pmodule->pport_callbacks.on_operation_success(pmodule, &pport_write_controls);
    }
  }
  return ret;
}

__int8_t pport_write_control_bit(parport_module *pmodule, uint8_t PIN, uint8_t STATE) {
  if (pmodule == NULL || pmodule->fd < 0) {
    return 1;
  }
  uint8_t control_register = (STATE && IEEE1284_LOGIC_ON) << PIN;
  int ret = ioctl(pmodule->fd, PPWCONTROL, &control_register);
  if (ret < 0) {
    if (pmodule->pport_callbacks.on_operation_failure != NULL) {
      pmodule->pport_callbacks.on_operation_failure(pmodule, errno, &pport_write_control_bit);
    }
  } else {
    if (pmodule->pport_callbacks.on_operation_success != NULL) {
      pmodule->pport_callbacks.on_operation_success(pmodule, &pport_write_control_bit);
    }
  }
  return ret;
}

__int8_t pport_read_controls(parport_module *pmodule, parport_register *pregister) {
  if (pmodule == NULL || pmodule->fd < 0 || pregister == NULL) {
    return 1;
  }
  uint8_t control_register = 0x00;
  int value = ioctl(pmodule->fd, PPRCONTROL, &control_register);
  if (value < 0) {
    // leave the parport_register memory block without invoking any side effects!
    if (pmodule->pport_callbacks.on_operation_failure != NULL) {
      pmodule->pport_callbacks.on_operation_failure(pmodule, errno, *pport_read_controls);
    }
  } else {
    // write the control values
    // conversion of the bitwise values into logical values
    pregister->bit0 = (control_register & (1 << IEEE1284_PIN_0)) && IEEE1284_LOGIC_ON;
    pregister->bit1 = (control_register & (1 << IEEE1284_PIN_1)) && IEEE1284_LOGIC_ON;
    pregister->bit2 = (control_register & (1 << IEEE1284_PIN_2)) && IEEE1284_LOGIC_ON;
    pregister->bit3 = (control_register & (1 << IEEE1284_PIN_3)) && IEEE1284_LOGIC_ON;
    pregister->bit4 = (control_register & (1 << IEEE1284_PIN_4)) && IEEE1284_LOGIC_ON;
    pregister->bit5 = (control_register & (1 << IEEE1284_PIN_5)) && IEEE1284_LOGIC_ON;
    pregister->bit6 = (control_register & (1 << IEEE1284_PIN_6)) && IEEE1284_LOGIC_ON;
    pregister->bit7 = (control_register & (1 << IEEE1284_PIN_7)) && IEEE1284_LOGIC_ON;
    pregister->memory = control_register;
    if (pmodule->pport_callbacks.on_operation_success != NULL) {
      pmodule->pport_callbacks.on_operation_success(pmodule, &pport_read_controls);
    }
  }
  return value;
}

__int8_t pport_read_control_bit(parport_module *pmodule, uint8_t PIN, uint8_t *out) {
  if (pmodule == NULL || pmodule->fd < 0 || out == NULL) {
    return 1;
  }
  int ret = ioctl(pmodule->fd, PPRCONTROL, out);
  if (ret < 0) {
    *out = 0x00;
    // leave the parport_register memory block without invoking any side effects!
    if (pmodule->pport_callbacks.on_operation_failure != NULL) {
      pmodule->pport_callbacks.on_operation_failure(pmodule, errno, &pport_read_control_bit);
    }
  } else {
    *out = *out & PIN;
    if (pmodule->pport_callbacks.on_operation_success != NULL) {
      pmodule->pport_callbacks.on_operation_success(pmodule, &pport_read_control_bit);
    }
  }
  return ret;
}

__int8_t pport_register_data_lines(parport_module *pmodule, data_line_direction dld) {
  if (pmodule == NULL || pmodule->fd < 0) {
    return 1;
  }
  int line_direction = IEEE1284_LOGIC_OFF;
  if (dld == DATA_LINE_INPUT) {
    line_direction = IEEE1284_LOGIC_ON;
  }
  int ret = ioctl(pmodule->fd, PPDATADIR, &line_direction);
  if (ret < 0) {
    if (pmodule->pport_callbacks.on_operation_failure != NULL) {
      pmodule->pport_callbacks.on_operation_failure(pmodule, errno, &pport_register_data_lines);
    }
  } else {
    if (pmodule->pport_callbacks.on_operation_success != NULL) {
      pmodule->pport_callbacks.on_operation_success(pmodule, &pport_register_data_lines);
    }
  }
  return 0;
}

__int8_t pport_write_data(parport_module *pmodule, parport_register *pregister) {
  if (pmodule == NULL || pmodule->fd < 0 || pregister == NULL) {
    return 1;
  }
  // conversion of the logical values to bitwise values
  pregister->bit0 = (pregister->bit0 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_0;
  pregister->bit1 = (pregister->bit1 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_1;
  pregister->bit2 = (pregister->bit2 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_2;
  pregister->bit3 = (pregister->bit3 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_3;
  pregister->bit4 = (pregister->bit4 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_4;
  pregister->bit5 = (pregister->bit5 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_5;
  pregister->bit6 = (pregister->bit6 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_6;
  pregister->bit7 = (pregister->bit7 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_7;

  pregister->memory = pregister->bit0 | pregister->bit1 | pregister->bit2 | pregister->bit3 |
                      pregister->bit4 | pregister->bit5 | pregister->bit6 | pregister->bit7;

  int ret = ioctl(pmodule->fd, PPWDATA, &(pregister->memory));
  if (ret < 0) {
    if (pmodule->pport_callbacks.on_operation_failure != NULL) {
      pmodule->pport_callbacks.on_operation_failure(pmodule, errno, &pport_write_data);
    }
  } else {
    if (pmodule->pport_callbacks.on_operation_success != NULL) {
      pmodule->pport_callbacks.on_operation_success(pmodule, &pport_write_data);
    }
  }
  return ret;
}

__int8_t pport_write_data_bit(parport_module *pmodule, uint8_t PIN, uint8_t STATE) {
  if (pmodule == NULL || pmodule->fd < 0) {
    return 1;
  }
  uint8_t data_register = (STATE && IEEE1284_LOGIC_ON) << PIN;
  int ret = ioctl(pmodule->fd, PPWDATA, &data_register);
  if (ret < 0) {
    if (pmodule->pport_callbacks.on_operation_failure != NULL) {
      pmodule->pport_callbacks.on_operation_failure(pmodule, errno, &pport_write_data_bit);
    }
  } else {
    if (pmodule->pport_callbacks.on_operation_success != NULL) {
      pmodule->pport_callbacks.on_operation_success(pmodule, &pport_write_data_bit);
    }
  }
  return ret;
}

__int8_t pport_read_data(parport_module *pmodule, parport_register *pregister) {
  if (pmodule == NULL || pmodule->fd < 0 || pregister == NULL) {
    return 1;
  }
  uint8_t data_register = 0x00;
  int value = ioctl(pmodule->fd, PPRDATA, &data_register);
  if (value < 0) {
    // leave the parport_register memory block without invoking any side effects!
    if (pmodule->pport_callbacks.on_operation_failure != NULL) {
      pmodule->pport_callbacks.on_operation_failure(pmodule, errno, &pport_read_data);
    }
  } else {
    // write the data values
    // conversion of the bitwise values into logical values
    pregister->bit0 = (data_register & (1 << IEEE1284_PIN_0)) && IEEE1284_LOGIC_ON;
    pregister->bit1 = (data_register & (1 << IEEE1284_PIN_1)) && IEEE1284_LOGIC_ON;
    pregister->bit2 = (data_register & (1 << IEEE1284_PIN_2)) && IEEE1284_LOGIC_ON;
    pregister->bit3 = (data_register & (1 << IEEE1284_PIN_3)) && IEEE1284_LOGIC_ON;
    pregister->bit4 = (data_register & (1 << IEEE1284_PIN_4)) && IEEE1284_LOGIC_ON;
    pregister->bit5 = (data_register & (1 << IEEE1284_PIN_5)) && IEEE1284_LOGIC_ON;
    pregister->bit6 = (data_register & (1 << IEEE1284_PIN_6)) && IEEE1284_LOGIC_ON;
    pregister->bit7 = (data_register & (1 << IEEE1284_PIN_7)) && IEEE1284_LOGIC_ON;
    pregister->memory = data_register;
    if (pmodule->pport_callbacks.on_operation_success != NULL) {
      pmodule->pport_callbacks.on_operation_success(pmodule, &pport_read_data);
    }
  }
  return value;
}

__int8_t pport_read_data_bit(parport_module *pmodule, uint8_t PIN, uint8_t *out) {
  if (pmodule == NULL || pmodule->fd < 0 || out == NULL) {
    return 1;
  }
  int ret = ioctl(pmodule->fd, PPRDATA, out);
  if (ret < 0) {
    *out = 0x00;
    // leave the parport_register memory block without invoking any side effects!
    if (pmodule->pport_callbacks.on_operation_failure != NULL) {
      pmodule->pport_callbacks.on_operation_failure(pmodule, errno, &pport_read_data_bit);
    }
  } else {
    *out = *out & PIN;
    if (pmodule->pport_callbacks.on_operation_success != NULL) {
      pmodule->pport_callbacks.on_operation_success(pmodule, &pport_read_data_bit);
    }
  }
  return ret;
}

__int8_t pport_read_status(parport_module *pmodule, parport_register *pregister) {
  if (pmodule->fd < 0 || pregister == NULL) {
    return 1;
  }
  uint8_t status_register = 0x00;
  int value = ioctl(pmodule->fd, PPRSTATUS, &status_register);
  if (value < 0) {
    // leave the parport_register memory block without invoking any side effects!
    if (pmodule->pport_callbacks.on_operation_failure != NULL) {
      pmodule->pport_callbacks.on_operation_failure(pmodule, errno, &pport_read_status);
    }
  } else {
    // write the status values
    // conversion of the bitwise values into logical values
    pregister->bit0 = (status_register & (1 << IEEE1284_PIN_0)) && IEEE1284_LOGIC_ON;
    pregister->bit1 = (status_register & (1 << IEEE1284_PIN_1)) && IEEE1284_LOGIC_ON;
    pregister->bit2 = (status_register & (1 << IEEE1284_PIN_2)) && IEEE1284_LOGIC_ON;
    pregister->bit3 = (status_register & (1 << IEEE1284_PIN_3)) && IEEE1284_LOGIC_ON;
    pregister->bit4 = (status_register & (1 << IEEE1284_PIN_4)) && IEEE1284_LOGIC_ON;
    pregister->bit5 = (status_register & (1 << IEEE1284_PIN_5)) && IEEE1284_LOGIC_ON;
    pregister->bit6 = (status_register & (1 << IEEE1284_PIN_6)) && IEEE1284_LOGIC_ON;
    pregister->bit7 = (status_register & (1 << IEEE1284_PIN_7)) && IEEE1284_LOGIC_ON;
    pregister->memory = status_register;
    if (pmodule->pport_callbacks.on_operation_success != NULL) {
      pmodule->pport_callbacks.on_operation_success(pmodule, &pport_read_status);
    }
  }
  return value;
}

__int8_t pport_read_status_bit(parport_module *pmodule, uint8_t PIN, uint8_t *out) {
  if (pmodule == NULL || pmodule->fd < 0 || out == NULL) {
    return 1;
  }
  int ret = ioctl(pmodule->fd, PPRSTATUS, out);
  if (ret < 0) {
    *out = 0x00;
    // leave the parport_register memory block without invoking any side effects!
    if (pmodule->pport_callbacks.on_operation_failure != NULL) {
      pmodule->pport_callbacks.on_operation_failure(pmodule, errno, &pport_read_status_bit);
    }
  } else {
    *out = *out & PIN;
    if (pmodule->pport_callbacks.on_operation_success != NULL) {
      pmodule->pport_callbacks.on_operation_success(pmodule, &pport_read_status_bit);
    }
  }
  return ret;
}

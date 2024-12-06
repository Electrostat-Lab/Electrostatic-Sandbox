#include <electrostatic/electroio/electrokio/ieee1284_module.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static inline void cleanup(parport_module *pmodule) {
}

// routines for initializing compat mode as a host initiated mode
static inline void init_host_compat_handshakes(parport_module *pmodule) {
  // 1) set busy control to low
  pport_write_controls(pmodule, &(parport_control){
                                    .c0 = IEEE1284_LOGIC_ON, // nStrobe
                                    .c1 = IEEE1284_LOGIC_ON, // nAck
                                    .c2 = IEEE1284_LOGIC_OFF, // Busy
                                });
  // wait T(setup)
  // 2) set nStrobe (c0) to low!
  pport_write_controls(pmodule, &(parport_control){
                                    .c0 = IEEE1284_LOGIC_OFF,
                                    .c1 = IEEE1284_LOGIC_ON, // retain the low logic of c1
                                    .c2 = IEEE1284_LOGIC_OFF // retain the low logic of c2
                                });
  // wait T(busy)
  // 3) connect the busy control and set it to HIGH (PIN 11 on the first row).
  pport_write_controls(pmodule, &(parport_control){
                                    .c0 = IEEE1284_LOGIC_OFF, // retain the low logic of c0
                                    .c1 = IEEE1284_LOGIC_ON,
                                    .c2 = IEEE1284_LOGIC_ON,
                                });
  // 4) set nStrobe (c0) to high!
  pport_write_controls(pmodule, &(parport_control){
                                    .c0 = IEEE1284_LOGIC_ON,
                                    .c1 = IEEE1284_LOGIC_ON,
                                    .c2 = IEEE1284_LOGIC_ON, // retain the high logic of c2
                                });
  // 5) set PtrClk(Ack) to low retaining the other pins logic
  pport_write_controls(pmodule, &(parport_control){
                                    .c0 = IEEE1284_LOGIC_ON, // retain the high logic of c0
                                    .c1 = IEEE1284_LOGIC_OFF,
                                    .c2 = IEEE1284_LOGIC_ON, // retain the high logic of c2
                                });
  // Now write the data
}

static inline void terminate_host_compat_handshakes(parport_module *pmodule) {
  // 6) set PtrClk(Ack) to high retaining the other pins logic
  pport_write_controls(pmodule, &(parport_control){
                                    .c0 = IEEE1284_LOGIC_ON, // retain the high logic of c0
                                    .c1 = IEEE1284_LOGIC_ON,
                                    .c2 = IEEE1284_LOGIC_ON, // retain the high logic of c2
                                });
  // 6) set PtrClk(Ack) to high retaining the other pins logic
  pport_write_controls(pmodule, &(parport_control){
                                    .c0 = IEEE1284_LOGIC_ON, // retain the high logic of c0
                                    .c1 = IEEE1284_LOGIC_ON, // retain the high logic of c1
                                    .c2 = IEEE1284_LOGIC_OFF,
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
  pport_module->pport_callbacks.on_open_success = pport_callbacks.on_open_success;
  pport_module->pport_callbacks.on_open_failure = pport_callbacks.on_open_failure;
  pport_module->pport_callbacks.on_write_success = pport_callbacks.on_write_success;
  pport_module->pport_callbacks.on_write_failure = pport_callbacks.on_write_failure;
  pport_module->pport_callbacks.on_read_success = pport_callbacks.on_read_success;
  pport_module->pport_callbacks.on_read_failure = pport_callbacks.on_read_failure;
  pport_module->pport_callbacks.on_release_success = pport_callbacks.on_release_success;
  pport_module->pport_callbacks.on_release_failure = pport_callbacks.on_release_failure;
  if (pport_callbacks.cleanup != NULL) {
    pport_module->pport_callbacks.cleanup = pport_callbacks.cleanup;
  } else {
    pport_module->pport_callbacks.cleanup = &cleanup;
  }
  pport_module->pport_callbacks.on_close_success = pport_callbacks.on_close_success;
  pport_module->pport_callbacks.on_close_failure = pport_callbacks.on_close_failure;
  return 0;
}

int pport_open(parport_module *pmodule) {
  if (pmodule == NULL || pmodule->device == NULL) {
    return 1;
  }
  pmodule->fd = open(pmodule->device, pmodule->access);
  // post-processing checks and callbacks
  if (pmodule->fd < 0) {
    if (pmodule->pport_callbacks.on_open_failure) {
      pmodule->pport_callbacks.on_open_failure(pmodule, errno);
    }
    return 1;
  }
  if (pmodule->pport_callbacks.on_open_success) {
    pmodule->pport_callbacks.on_open_success(pmodule);
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
    if (pmodule->pport_callbacks.on_close_success != NULL) {
      pmodule->pport_callbacks.on_close_success(pmodule);
    }
  } else {
    if (pmodule->pport_callbacks.on_close_failure != NULL) {
      pmodule->pport_callbacks.on_close_failure(pmodule, errno);
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
    if (pmodule->pport_callbacks.on_release_failure != NULL) {
      pmodule->pport_callbacks.on_release_failure(pmodule, errno);
    }
  } else {
    if (pmodule->pport_callbacks.on_release_success != NULL) {
      pmodule->pport_callbacks.on_release_success(pmodule);
    }
  }
  return ret;
}

__int8_t pport_load_mode(parport_module *pmodule) {
  if (pmodule->fd < 0 || pmodule->pport_mode == 0) {
    return 1;
  }
  int ret = ioctl(pmodule->fd, PPSETMODE, &(pmodule->pport_mode));
  if (ret < 0) {
    if (pmodule->pport_callbacks.on_mode_loading_failure != NULL) {
      pmodule->pport_callbacks.on_mode_loading_failure(pmodule, errno);
    }
    pport_release(pmodule);
    pport_close(pmodule);
  } else {
    if (pmodule->pport_callbacks.on_mode_loading_success != NULL) {
      pmodule->pport_callbacks.on_mode_loading_success(pmodule);
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
    if (pmodule->pport_callbacks.on_claim_failure != NULL) {
      pmodule->pport_callbacks.on_claim_failure(pmodule, errno);
    }
    pport_close(pmodule);
  } else {
    if (pmodule->pport_callbacks.on_claim_success != NULL) {
      pmodule->pport_callbacks.on_claim_success(pmodule);
    }
  }
  return ret;
}

__int8_t pport_write_controls(parport_module *pmodule, parport_control *pcontrol) {
  if (pmodule->fd < 0) {
    return 1;
  }
  // conversion of the logical values to bitwise values
  // first: convert the user values into strict logic values (i.e., ON or OFF) (Logic ANDing).
  // second: bitwise left shift the converted logic values into its position in the register (Lshift).
  // third: add the positioned bits together to build the register (Bitwise ORing).
  // forth: write the byte to the control register (IO Commanding).
  pcontrol->c0 = (pcontrol->c0 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_0;
  pcontrol->c1 = (pcontrol->c1 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_1;
  pcontrol->c2 = (pcontrol->c2 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_2;
  pcontrol->c3 = (pcontrol->c3 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_3;
  pcontrol->c4 = (pcontrol->c4 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_4;
  pcontrol->c5 = (pcontrol->c5 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_5;
  pcontrol->c6 = (pcontrol->c6 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_6;
  pcontrol->c7 = (pcontrol->c7 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_7;

  uint8_t control_register = pcontrol->c0 | pcontrol->c1 | pcontrol->c2 | pcontrol->c3 |
                             pcontrol->c4 | pcontrol->c5 | pcontrol->c6 | pcontrol->c7;

  pcontrol->c_register = control_register;

  int ret = ioctl(pmodule->fd, PPWCONTROL, &control_register);
  if (ret < 0) {
    if (pmodule->pport_callbacks.on_write_failure != NULL) {
      pmodule->pport_callbacks.on_write_failure(pmodule, errno);
    }
  } else {
    if (pmodule->pport_callbacks.on_write_success != NULL) {
      pmodule->pport_callbacks.on_write_success(pmodule);
    }
  }
  return ret;
}

__int8_t pport_read_controls(parport_module *pmodule, parport_control *pcontrol) {
  if (pmodule->fd < 0 || pcontrol == NULL) {
    return 1;
  }
  uint8_t control_register = 0x00;
  int value = ioctl(pmodule->fd, PPRCONTROL, &control_register);
  if (value < 0) {
    // leave the parport_control memory block without invoking any side effects!
    if (pmodule->pport_callbacks.on_read_failure != NULL) {
      pmodule->pport_callbacks.on_read_failure(pmodule, errno);
    }
  } else {
    // write the control values
    // conversion of the bitwise values into logical values
    pcontrol->c0 = (control_register & (1 << IEEE1284_PIN_0)) && IEEE1284_LOGIC_ON;
    pcontrol->c1 = (control_register & (1 << IEEE1284_PIN_1)) && IEEE1284_LOGIC_ON;
    pcontrol->c2 = (control_register & (1 << IEEE1284_PIN_2)) && IEEE1284_LOGIC_ON;
    pcontrol->c3 = (control_register & (1 << IEEE1284_PIN_3)) && IEEE1284_LOGIC_ON;
    pcontrol->c4 = (control_register & (1 << IEEE1284_PIN_4)) && IEEE1284_LOGIC_ON;
    pcontrol->c5 = (control_register & (1 << IEEE1284_PIN_5)) && IEEE1284_LOGIC_ON;
    pcontrol->c6 = (control_register & (1 << IEEE1284_PIN_6)) && IEEE1284_LOGIC_ON;
    pcontrol->c7 = (control_register & (1 << IEEE1284_PIN_7)) && IEEE1284_LOGIC_ON;
    pcontrol->c_register = control_register;
    if (pmodule->pport_callbacks.on_read_success != NULL) {
      pmodule->pport_callbacks.on_read_success(pmodule);
    }
  }
  return value;
}

__int8_t pport_write_data(parport_module *pmodule, parport_data *pdata) {
  if (pmodule->fd < 0) {
    return 1;
  }
  // conversion of the logical values to bitwise values
  pdata->d0 = (pdata->d0 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_0;
  pdata->d1 = (pdata->d1 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_1;
  pdata->d2 = (pdata->d2 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_2;
  pdata->d3 = (pdata->d3 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_3;
  pdata->d4 = (pdata->d4 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_4;
  pdata->d5 = (pdata->d5 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_5;
  pdata->d6 = (pdata->d6 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_6;
  pdata->d7 = (pdata->d7 && IEEE1284_LOGIC_ON) << IEEE1284_PIN_7;

  uint8_t data_register = pdata->d0 | pdata->d1 | pdata->d2 | pdata->d3 |
                          pdata->d4 | pdata->d5 | pdata->d6 | pdata->d7;

  pdata->d_register = data_register;

  int ret = ioctl(pmodule->fd, PPWDATA, &data_register);
  if (ret < 0) {
    if (pmodule->pport_callbacks.on_write_failure != NULL) {
      pmodule->pport_callbacks.on_write_failure(pmodule, errno);
    }
  } else {
    if (pmodule->pport_callbacks.on_write_success != NULL) {
      pmodule->pport_callbacks.on_write_success(pmodule);
    }
  }
  return ret;
}

__int8_t pport_read_data(parport_module *pmodule, parport_data *pdata) {
  if (pmodule->fd < 0 || pdata == NULL) {
    return 1;
  }
  uint8_t data_register = 0x00;
  int value = ioctl(pmodule->fd, PPRDATA, &data_register);
  if (value < 0) {
    // leave the parport_data memory block without invoking any side effects!
    if (pmodule->pport_callbacks.on_read_failure != NULL) {
      pmodule->pport_callbacks.on_read_failure(pmodule, errno);
    }
  } else {
    // write the data values
    // conversion of the bitwise values into logical values
    pdata->d0 = (data_register & (1 << IEEE1284_PIN_0)) && IEEE1284_LOGIC_ON;
    pdata->d1 = (data_register & (1 << IEEE1284_PIN_1)) && IEEE1284_LOGIC_ON;
    pdata->d2 = (data_register & (1 << IEEE1284_PIN_2)) && IEEE1284_LOGIC_ON;
    pdata->d3 = (data_register & (1 << IEEE1284_PIN_3)) && IEEE1284_LOGIC_ON;
    pdata->d4 = (data_register & (1 << IEEE1284_PIN_4)) && IEEE1284_LOGIC_ON;
    pdata->d5 = (data_register & (1 << IEEE1284_PIN_5)) && IEEE1284_LOGIC_ON;
    pdata->d6 = (data_register & (1 << IEEE1284_PIN_6)) && IEEE1284_LOGIC_ON;
    pdata->d7 = (data_register & (1 << IEEE1284_PIN_7)) && IEEE1284_LOGIC_ON;
    pdata->d_register = data_register;
    if (pmodule->pport_callbacks.on_read_success != NULL) {
      pmodule->pport_callbacks.on_read_success(pmodule);
    }
  }
  return value;
}

__int8_t pport_read_status(parport_module *pmodule, parport_status *pstatus) {
  if (pmodule->fd < 0 || pstatus == NULL) {
    return 1;
  }
  uint8_t status_register = 0x00;
  int value = ioctl(pmodule->fd, PPRSTATUS, &status_register);
  if (value < 0) {
    // leave the parport_status memory block without invoking any side effects!
    if (pmodule->pport_callbacks.on_read_failure != NULL) {
      pmodule->pport_callbacks.on_read_failure(pmodule, errno);
    }
  } else {
    // write the status values
    // conversion of the bitwise values into logical values
    pstatus->s0 = (status_register & (1 << IEEE1284_PIN_0)) && IEEE1284_LOGIC_ON;
    pstatus->s1 = (status_register & (1 << IEEE1284_PIN_1)) && IEEE1284_LOGIC_ON;
    pstatus->s2 = (status_register & (1 << IEEE1284_PIN_2)) && IEEE1284_LOGIC_ON;
    pstatus->s3 = (status_register & (1 << IEEE1284_PIN_3)) && IEEE1284_LOGIC_ON;
    pstatus->s4 = (status_register & (1 << IEEE1284_PIN_4)) && IEEE1284_LOGIC_ON;
    pstatus->s5 = (status_register & (1 << IEEE1284_PIN_5)) && IEEE1284_LOGIC_ON;
    pstatus->s6 = (status_register & (1 << IEEE1284_PIN_6)) && IEEE1284_LOGIC_ON;
    pstatus->s7 = (status_register & (1 << IEEE1284_PIN_7)) && IEEE1284_LOGIC_ON;
    pstatus->s_register = status_register;
    if (pmodule->pport_callbacks.on_read_success != NULL) {
      pmodule->pport_callbacks.on_read_success(pmodule);
    }
  }
  return value;
}

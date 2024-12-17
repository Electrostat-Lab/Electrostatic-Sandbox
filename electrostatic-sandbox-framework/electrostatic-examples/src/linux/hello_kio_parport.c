#include <linux/parport.h>
#include <stdio.h>
#include <fcntl.h>
#include <electrostatic/electroio/electrokio/ieee1284_module.h>

#define DEVICE "/dev/parport0"

static inline void on_open_success(parport_module *module) {
    fprintf(stdout, "Openning parallel port %s has Succeeded with %d\n", module->device, module->fd);
}

static inline void on_open_failure(parport_module *module, int err) {
    fprintf(stderr, "Openning parallel port %s has failed with %d\n", module->device, module->fd);
}

static inline void on_write_success(parport_module *module) {
    fprintf(stdout, "Write to parallel port %s Successful\n", module->device);
}

static inline void on_write_failure(parport_module *module, int err) {
    fprintf(stderr, "Write to parallel port %s Failed %d\n", module->device, err);
}

static inline void on_operation_success(parport_module *module, void *caller) {
    if (caller == &pport_open) {
        on_open_success(module);
    } else if (caller == &pport_write_data || caller == &pport_write_controls) {
        on_write_success(module);
    } else {
    }
}

static inline void on_operation_failure(parport_module *module, int err, void *caller) {
    if (caller == &pport_open) {
        on_open_failure(module, err);
    } else if (caller == &pport_write_data || caller == &pport_write_controls) {
        on_write_failure(module, err);
    } else {
    }
}


int main() {
    parport_module pmodule = {
        .device = DEVICE,
        .fd = -1, /* the start */
        .access = O_RDWR,
        .pport_mode = IEEE1284_MODE_ECP};

    parport_register data_register = {
        .bit0 = IEEE1284_LOGIC_OFF,
        .bit7 = IEEE1284_LOGIC_ON // purple pin on the breadboard (1st row)
     };

    parport_register control_register = {
        .bit0 = IEEE1284_LOGIC_ON, /*nStrobe is active LOW*/
        .bit1 = IEEE1284_LOGIC_OFF,
        .bit2 = IEEE1284_LOGIC_ON, // grey pin on breadboard (2nd row)
        .bit3 = IEEE1284_LOGIC_OFF,
        .bit4 = IEEE1284_LOGIC_OFF,
        .bit5 = IEEE1284_LOGIC_OFF,
        .bit6 = IEEE1284_LOGIC_OFF,
        .bit7 = IEEE1284_LOGIC_OFF,
    };

    pport_init_callbacks(&pmodule, (parport_callbacks){
                                       .on_operation_success = &on_operation_success,
                                       .on_operation_failure = &on_operation_failure});
    pport_open(&pmodule);
    pport_claim(&pmodule);
    pport_load_mode(&pmodule);

    pport_write_data(&pmodule, &data_register);
    pport_write_controls(&pmodule, &control_register);

    parport_register pdata_read = {};
    pport_read_data(&pmodule, &pdata_read);
    fprintf(stdout, "Data register write = %x\n", pdata_read.memory);

    pport_release(&pmodule);
    pport_close(&pmodule);
    return 0;
}

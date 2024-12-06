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

int main() {
    parport_module pmodule = {
        .device = DEVICE,
        .fd = -1, /* the start */
        .access = O_RDWR,
        .pport_mode = IEEE1284_MODE_COMPAT};

    parport_data pdata = {
        .d0 = IEEE1284_LOGIC_OFF,
        .d1 = IEEE1284_LOGIC_ON};

    pport_init_callbacks(&pmodule, (parport_callbacks) {
                                       .on_open_success = &on_open_success,
                                       .on_open_failure = &on_open_failure,
                                       .on_write_success = &on_write_success,
                                       .on_write_failure = &on_write_failure});
    pport_open(&pmodule);
    pport_claim(&pmodule);
    pport_load_mode(&pmodule);
//    init_mode(&pmodule);
    pport_write_data(&pmodule, &pdata);
    parport_data  pdata_read = {};
//    pport_read_data(&pmodule, &pdata_read);
//    fprintf(stdout, "Data register write = %x\n", pdata_read.d_register);
    pport_release(&pmodule);
    pport_close(&pmodule);
    return 0;
}

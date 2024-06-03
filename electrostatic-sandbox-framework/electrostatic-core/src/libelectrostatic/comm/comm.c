#include<electrostatic/comm/comm.h>

uint8_t init_protocol(comm_protocol* comm, comm_protocol from) {
    if (comm == NULL) {
        return -1;
    }
    comm->open = from.open;
    comm->init = from.init;
    comm->deinit = from.init;
    return 0;
}
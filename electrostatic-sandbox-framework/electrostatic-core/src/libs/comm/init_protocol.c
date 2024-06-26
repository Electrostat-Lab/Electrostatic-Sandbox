#include<electrostatic/comm/comm.h>

static device_metadata test_serial(void** args) {
    device_metadata metadata = {
    };
    printf("%s", "Test Serial!\n");
    return metadata;
}

static device_metadata test_parallel(void** args) {
    device_metadata metadata = {
    };
    printf("%s", "Test Parallel!\n");
    return metadata;
}

static comm_protocol serial_table = {
    &test_serial  
};

static comm_protocol parallel_table = {
    &test_parallel  
};

extern uint8_t init_protocol(comm_protocol *comm,
                             const comm_protocol *from) {
    if (&from == NULL) {
        return -1;
    }
    comm->open = from->open;
    comm->init = from->init;
    comm->deinit = from->deinit;
    comm->read = from->read;
    comm->write = from->write;
    comm->close = from->close;
    comm->callbacks = NULL;
    return 0;
}

extern uint8_t init_protocol_default(comm_protocol *comm, enum CommProtocol protocol, const comm_callbacks *callbacks) {
    if (protocol == SERIAL_RS232) {
	serial_table.callbacks = (comm_callbacks*) callbacks;
        return init_protocol(comm, &serial_table);
    } else if (protocol == IEEE_1284) {
	parallel_table.callbacks = callbacks;
        return init_protocol(comm, &parallel_table);
    }
}

#include <stdio.h>
#include <electrostatic/comm/comm.h>

comm_protocol serial;
comm_protocol parallel;

int main() {
    init_protocol_default(&serial, Serial);
    init_protocol_default(&parallel, Parallel);
    parallel.open(0);
    serial.open(0);
    return 0;
}

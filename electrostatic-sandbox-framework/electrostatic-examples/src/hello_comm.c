#include <stdio.h>
#include <electrostatic/comm/comm.h>

int main() {
    comm_protocol from = {
        &open
    };
    init_protocol(&serial, from);
    serial.open(0);
    return 0;
}

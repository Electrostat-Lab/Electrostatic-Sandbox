#include <stdio.h>
#include <electrostatic/comm/comm.h>

int main() {
    init_protocols_default();
    parallel.open(0);
    serial.open(0);
    return 0;
}

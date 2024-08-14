#include<linux/ModemController.h>
#include<ErrnoUtils.h>

int ModemController::setModemBitsStatus(int fd, const int* status) {
    if (fd <= 0) {
        return ERR_INVALID_PORT;
    }
    return ioctl(fd, TIOCMSET, status);
}

int ModemController::getModemBitsStatus(int fd, int* pointer) {
    if (fd <= 0) {
        return ERR_INVALID_PORT;
    }
    return ioctl(fd, TIOCMGET, pointer);
}

int ModemController::clearModemBitsStatus(int fd, const int* status) {
    if (fd <= 0) {
        return ERR_INVALID_PORT;
    }
    return ioctl(fd, TIOCMBIC, status);
}
#include <linux/TerminalDevice.h>
#include <electrostatic/util/filesystem/file_verify.h>

void TerminalDevice::getTermiosFromFd(struct termios* tty) {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
                || !is_existential(this->serialPort->path)) {
        return;
    }
    /* update the termios struct pointer with the data from the port descriptor */
    tcgetattr(this->serialPort->fd, tty);
}

int TerminalDevice::openPort() {
    if (this->serialPort == NULL || this->serialPort->path == NULL) {
        return ERR_OPERATION_FAILED;
    }
    this->serialPort->fd = open(this->serialPort->path, this->serialPort->ioFlag);
    this->serialPort->portOpened = 1;

    return serialPort->fd;
}

int TerminalDevice::fetchSerialPorts(AddressesBuffer* serialPorts) {

    DIR* dirp = opendir(DEVICES_DIR);
    
    /* sanity check the input */
    if (dirp == NULL) {
        return ERR_INVALID_DIR;
    }

    struct dirent* dp;

    /* start reading available ports */
    while ((dp = readdir(dirp)) != NULL) {

        /* allocates a tty device, must be heap allocation, as this
           device will be shared with the Java code */
        char* device = (char*) calloc(strlen(dp->d_name) + strlen(DEVICES_DIR), sizeof(char));
        device = SerialUtils::concatIntoDevice(device, dp->d_name, DEVICES_DIR);
        
        /* delete the device buffer if it's not a serial port */
        if (!SerialUtils::isSerialPort(device, O_RDONLY)) {
            BufferUtils::deleteBuffer(device);
            continue;
        }

        /* add the device to the serial ports major buffer and count up */
        serialPorts->add(device);
    } 

    /* release resources */
    closedir(dirp);
    BufferUtils::deleteBuffer(dp);

    /* throws error indicating the availability issues */
    if (*serialPorts->getAddressesCount() == 0) {
        return ERR_NO_AVAILABLE_TTY_DEVICES;
    }
    return OPERATION_SUCCEEDED;
}

int TerminalDevice::initTermios() {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
            || !is_existential(this->serialPort->path)) {
        return ERR_INVALID_PORT;
    }
    
    struct termios tty;
    TerminalDevice::getTermiosFromFd(&tty);

    /* setup tty attributes */
    tty.c_cflag &= ~(CBAUDEX | CBAUD); /* clear BAUDs */
    tty.c_cflag |= (CREAD | CS8 | CLOCAL); /* set flags */
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHOKE | ECHONL | ECHOPRT | ECHOCTL | ISIG | IEXTEN);
    tty.c_oflag &= ~(OPOST | ONLCR);
    tty.c_iflag = 0x00;

    /* define default read mode as blocking read on char at a time */
    tty.c_cc[VTIME] = BLOCKING_READ_ONE_CHAR[0];
    tty.c_cc[VMIN] = BLOCKING_READ_ONE_CHAR[1];

    /* apply attributes flag bits */
    int state = tcsetattr(this->serialPort->fd, TCSAFLUSH, &tty);

    return state;
}

int TerminalDevice::setTerminalControlFlag(TerminalFlag flag) {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
            || !is_existential(this->serialPort->path)) {
        return ERR_INVALID_PORT;
    }
    
    struct termios tty;
    TerminalDevice::getTermiosFromFd(&tty);

    tty.c_cflag = flag;
    /* sets the new terminal settings to the file descriptor with flushing any output */
    int state = tcsetattr(this->serialPort->fd, TCSAFLUSH, &tty);

    return state;
}

int TerminalDevice::setTerminalLocalFlag(TerminalFlag flag) {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
        || !is_existential(this->serialPort->path)) {
        return ERR_INVALID_PORT;
    }

    struct termios tty;
    TerminalDevice::getTermiosFromFd(&tty);

    tty.c_lflag = flag;
    int state = tcsetattr(this->serialPort->fd, TCSAFLUSH, &tty);

    return state;
}

int TerminalDevice::setTerminalInputFlag(TerminalFlag flag) {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
        || !is_existential(this->serialPort->path)) {
        return ERR_INVALID_PORT;
    }
    struct termios tty;
    TerminalDevice::getTermiosFromFd(&tty);

    tty.c_iflag = flag;
    int state = tcsetattr(this->serialPort->fd, TCSAFLUSH, &tty);

    return state;
}

int TerminalDevice::setTerminalOutputFlag(TerminalFlag flag) {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
        || !is_existential(this->serialPort->path)) {
        return ERR_INVALID_PORT;
    }
    struct termios tty;
    TerminalDevice::getTermiosFromFd(&tty);

    tty.c_oflag = flag;
    int state = tcsetattr(this->serialPort->fd, TCSAFLUSH, &tty);

    return state;
}

TerminalFlag TerminalDevice::getTerminalControlFlag() {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
        || !is_existential(this->serialPort->path)) {
        return ERR_INVALID_PORT;
    }
    struct termios tty;
    TerminalDevice::getTermiosFromFd(&tty);

    return tty.c_cflag;
}

TerminalFlag TerminalDevice::getTerminalLocalFlag() {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
        || !is_existential(this->serialPort->path)) {
        return ERR_INVALID_PORT;
    }
    struct termios tty;
    TerminalDevice::getTermiosFromFd(&tty);

    return tty.c_lflag;
}

TerminalFlag TerminalDevice::getTerminalInputFlag() {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
        || !is_existential(this->serialPort->path)) {
        return ERR_INVALID_PORT;
    }
    struct termios tty;
    TerminalDevice::getTermiosFromFd(&tty);

    return tty.c_iflag;
}

TerminalFlag TerminalDevice::getTerminalOutputFlag() {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
        || !is_existential(this->serialPort->path)) {
        return ERR_INVALID_PORT;
    }
    struct termios tty;
    TerminalDevice::getTermiosFromFd(&tty);

    return tty.c_oflag;
}

int TerminalDevice::setReadConfigurationMode(const cc_t *readConfig) {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
        || !is_existential(this->serialPort->path)) {
        return ERR_INVALID_PORT;
    }
    struct termios tty;
    TerminalDevice::getTermiosFromFd(&tty);

    tty.c_cc[VTIME] = readConfig[0];
    tty.c_cc[VMIN] = readConfig[1];
    int state = tcsetattr(this->serialPort->fd, TCSAFLUSH, &tty);

    return state;
}

void TerminalDevice::getReadConfigurationMode(cc_t *readConfig) {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
        || !is_existential(this->serialPort->path)) {
        readConfig[0] = ERR_INVALID_PORT;
        readConfig[1] = ERR_INVALID_PORT;
        return;
    }

    struct termios tty;
    TerminalDevice::getTermiosFromFd(&tty);

    readConfig[0] = tty.c_cc[VTIME];
    readConfig[1] = tty.c_cc[VMIN];
}

int TerminalDevice::setBaudRate(int baudRate) {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
        || !is_existential(this->serialPort->path)) {
        return ERR_INVALID_PORT;
    }
    struct termios tty;
    TerminalDevice::getTermiosFromFd(&tty);

    /* update the baud rate of the termios */
    cfsetspeed(&tty, baudRate);
    int state = tcsetattr(this->serialPort->fd, TCSAFLUSH, &tty);

    return state;
}

speed_t TerminalDevice::getBaudRate() {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
        || !is_existential(this->serialPort->path)) {
        return ERR_INVALID_PORT;
    }
    struct termios tty;
    TerminalDevice::getTermiosFromFd(&tty);

    int speed = cfgetospeed(&tty);

    return speed;
}

ssize_t TerminalDevice::writeData(const void* buffer, int length) {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
        || !is_existential(this->serialPort->path)) {
        return ERR_INVALID_PORT;
    }
    return write(this->serialPort->fd, buffer, length);
}

ssize_t TerminalDevice::readData(void* buffer, int length) {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
        || !is_existential(this->serialPort->path)) {
        return ERR_INVALID_PORT;
    }
    return read(this->serialPort->fd, buffer, length);
}

off_t TerminalDevice::seek(off_t offset, int whence) {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
        || !is_existential(this->serialPort->path)) {
        return ERR_INVALID_PORT;
    }
    return lseek(this->serialPort->fd, offset, whence);
}

int TerminalDevice::closePort() {
    if (this->serialPort == NULL || this->serialPort->fd <= 0
        || !is_existential(this->serialPort->path)) {
        return ERR_INVALID_PORT;
    }
    return close(this->serialPort->fd);
} 
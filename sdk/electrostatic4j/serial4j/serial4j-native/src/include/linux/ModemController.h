#ifndef _MODEM_CONTROLLER
#define _MODEM_CONTROLLER

#include<sys/ioctl.h>

namespace ModemController {
   int setModemBitsStatus(int fd, const int* status);
   int getModemBitsStatus(int fd, int* pointer);
   int clearModemBitsStatus(int fd, const int* status);
}

#endif
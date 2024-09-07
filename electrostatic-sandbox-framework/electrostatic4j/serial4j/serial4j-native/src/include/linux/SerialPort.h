#ifndef _SERIAL_PORT_H_
#define _SERIAL_PORT_H_

#include <stdint.h>
#include <jni.h>

class SerialPort {
       public:
          char *path;
          jstring jstringPath;
          int portOpened;
          int fd;
          int ioFlag;
       public:
          SerialPort() {
          }
          SerialPort(const char *path, int ioFlag): path((char *) "/dev/null"), ioFlag(-1) {
              this->path = (char *) path;
              this->ioFlag = ioFlag;
          }
          ~SerialPort() {
              this->path = NULL;
              this->jstringPath = NULL;
              this->portOpened = -1;
              this->fd = -1;
              this->ioFlag = -1;
          }
};

#endif
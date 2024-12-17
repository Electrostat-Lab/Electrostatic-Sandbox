#!/bin/bash

port="${1}"

dmesg | grep ${port}
# reset the serial port if hazardous approach are involved
# kill all the processes using the serial ports
sudo fuser -v /dev/${port}
# restart all the services
sudo systemctl restart serial-getty@${port}.service
# add the current user to the modem line and character devices groups
sudo usermod -a -G tty $(whoami)
sudo usermod -a -G lock $(whoami)
sudo usermod -a -G dialout $(whoami)
sudo usermod -a -G uucp $(whoami)
# provoke permissions
sudo chmod +rwx /dev/${port}
sudo chmod 666 /dev/${port}
sudo chown root:root /dev/${port}



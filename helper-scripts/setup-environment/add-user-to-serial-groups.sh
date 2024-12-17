#!/bin/bash

# add the user to the unix-unix communication protocol group
sudo usermod -a -G uucp $(whoami)
# add the user to the modem dialing group
sudo usermod -a -G dialout $(whoami)
# add the user to the process-device locking group for concurrency purposes
sudo usermod -a -G lock $(whoami)
# add the user to the tty group
sudo usermod -a -G tty $(whoami)
# add the user to the line printer group for parallel port programming
sudo usermod -aG lp $(whoami)
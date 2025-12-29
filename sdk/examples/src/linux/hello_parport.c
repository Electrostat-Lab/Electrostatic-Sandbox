#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/parport.h>
#include <linux/ppdev.h>
#include <sys/ioctl.h>
#include <inttypes.h>

#define DEVICE "/dev/parport0"

int main() {
    int fd;
    int mode = IEEE1284_MODE_ECP;

    // Open the parallel port device
    fd = open(DEVICE, O_RDWR);
    if (fd < 0) {
        perror("Failed to open parallel port");
        return 1;
    }

    // Claim the parallel port
    if (ioctl(fd, PPCLAIM) < 0) {
        perror("Failed to claim parallel port");
        close(fd);
        return 1;
    }

//    // Set the port mode to ECP
//    if (ioctl(fd, PPSETMODE, &mode) < 0) {
//        perror("Failed to set parallel port mode to ECP");
//        ioctl(fd, PPRELEASE);
//        close(fd);
//        return 1;
//    }
    printf("Parallel port is now in ECP mode.\n");

    // Write data to the port (for demonstration)
    unsigned char data = 0xFF; // Example data
    if (ioctl(fd, PPWDATA, &data) < 0) {
        perror("Failed to write data to parallel port");
    } else {
        printf("Data 0x%X written to parallel port.\n", data);
    }
    sleep(100);
    // Release the parallel port
    if (ioctl(fd, PPRELEASE) < 0) {
        perror("Failed to release parallel port");
    }

    // Close the device
    close(fd);
    return 0;
}

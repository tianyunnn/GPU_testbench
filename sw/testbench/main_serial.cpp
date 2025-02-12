#include <iostream>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <cerrno>
#include <string.h>

#include "fix.h"

using namespace std;

void printBits(size_t const size, void const* const ptr) {
    unsigned char* b = (unsigned char*)ptr;
    unsigned char byte;
    int i, j;

    for (i = size - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    printf("\n");
}

int main() {
    //////////////////////////////////////////////
    // Serial setup
    //////////////////////////////////////////////
    char bytes_to_send[61];
    int serial_port = open("/dev/ttyUSB1", O_RDWR);

    if (serial_port < 0) {
        printf("Error opening serial port\n");
        return -1;
    }

    struct termios options;
    options.c_cflag = B115200 | CS8 | CLOCAL;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;

    int ret;
    ret = tcflush(serial_port, TCIFLUSH);
    if (ret != 0) {
        cout << strerror(errno) << endl;
    }
    ret = tcsetattr(serial_port, TCSANOW, &options);

    float world = 1;
    float world_offset = 0;
    char render_mode = 0;
    char tex_mode = 0;
    char color1_mode = 0;
    char color2_mode = 0;

    while (true) {
        // Update values as needed
        Vec3f v0 = {float2fix(-1.66 * world + world_offset), float2fix(world), float2fix(0)};
        Vec3f v1 = {float2fix(-1.66 * world + world_offset), float2fix(-world), float2fix(0)};
        Vec3f v2 = {float2fix(1.66 * world + world_offset), float2fix(-world), float2fix(0)};
        Vec3f v3 = {float2fix(1.66 * world + world_offset), float2fix(world), float2fix(0)};

        // Pack data to send
        bytes_to_send[0] = LOW(v0.x);
        bytes_to_send[1] = HIG(v0.x);
        bytes_to_send[2] = LOW(v0.y);
        bytes_to_send[3] = HIG(v0.y);
        bytes_to_send[4] = LOW(v0.z);
        bytes_to_send[5] = HIG(v0.z);
        bytes_to_send[6] = LOW(v1.x);
        bytes_to_send[7] = HIG(v1.x);
        bytes_to_send[8] = LOW(v1.y);
        bytes_to_send[9] = HIG(v1.y);
        bytes_to_send[10] = LOW(v1.z);
        bytes_to_send[11] = HIG(v1.z);
        bytes_to_send[12] = LOW(v2.x);
        bytes_to_send[13] = HIG(v2.x);
        bytes_to_send[14] = LOW(v2.y);
        bytes_to_send[15] = HIG(v2.y);
        bytes_to_send[16] = LOW(v2.z);
        bytes_to_send[17] = HIG(v2.z);
        bytes_to_send[18] = LOW(v3.x);
        bytes_to_send[19] = HIG(v3.x);
        bytes_to_send[20] = LOW(v3.y);
        bytes_to_send[21] = HIG(v3.y);
        bytes_to_send[22] = LOW(v3.z);
        bytes_to_send[23] = HIG(v3.z);

        // Mode configuration
        bytes_to_send[24] = render_mode + tex_mode + color1_mode + color2_mode;

        int send_length = write(serial_port, bytes_to_send, 25);
        printf("Wrote %d bytes over UART\n", send_length);
        usleep(100000); // Delay for stability
    }

    fprintf(stderr, "Closing serial port...\n");
    close(serial_port);
    return 0;
}

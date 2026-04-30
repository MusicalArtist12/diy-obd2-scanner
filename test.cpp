#ifndef ARDUINO_ARCH_AVR
// to test basic functionality

#include "string.h"
#include "stdio.h"
#include "stdint.h"
#include "lib.h"

int main() {
    struct can_frame frame;


    // should result in U0158 and P0420
    __u8 data[] = { 0x06, 0x43, 0x00, 0b11000001, 0b01011000, 0x04, 0x20};

    make_frame(&frame, 0, 8, data, sizeof data);

    struct dtc_code_frame res = interpret_dtc_frame(&frame);

    if (res.count >= 1) {
        printf("%s\n", res.code_0);
    }
    if (res.count >= 2) {
        printf("%s\n", res.code_1);
    }
}

#endif
#ifndef ARDUINO_ARCH_AVR
// to test basic functionality

#include "string.h"
#include "stdio.h"
#include "stdint.h"
#include "lib.h"

int main() {
    struct can_frame frame;


    // P0303 and P0103
    __u8 data[] = { 0x10,0x08,0x43,0x03,0x03,0x01,0x03,0x02  };

    make_frame(&frame, 0x07e8, 8, data, sizeof data);

    struct dtc_code_frame res = interpret_dtc_frame(&frame);

    if (res.count >= 1) {
        printf("%s\n", res.code_0);
    }
    if (res.count >= 2) {
        printf("%s\n", res.code_1);
    }
}

#endif
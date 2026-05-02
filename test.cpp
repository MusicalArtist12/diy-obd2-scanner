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

    union can_header* header = (can_header *)data;

    union dtc_code_data* code_0;
    union dtc_code_data* code_1;
    if (header->single.type == 0) {
        code_0 = (dtc_code_data *)&header->single.data[1];
        code_1 = (dtc_code_data *)&header->single.data[3];
    }
    else if (header->single.type == 1) {
        code_0 = (dtc_code_data *)&header->first.data[1];
        code_1 = (dtc_code_data *)&header->first.data[3];
    }
    else if (header->single.type == 2) {
        code_0 = (dtc_code_data *)&header->next.data[1];
        code_1 = (dtc_code_data *)&header->next.data[3];
    }

    const char* codes = "PCBU";

    printf("code: %c%d%d%d%d\n", codes[code_0->data.cat], code_0->data.num, code_0->data.d1, code_0->data.d2, code_0->data.d3);
    printf("code: %c%d%d%d%d\n", codes[code_1->data.cat], code_1->data.num, code_1->data.d1, code_1->data.d2, code_1->data.d3);

}

#endif
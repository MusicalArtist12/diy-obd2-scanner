// https://en.wikipedia.org/wiki/OBD-II_PIDs
// https://en.wikipedia.org/wiki/CAN_bus
// https://en.wikipedia.org/wiki/Unified_Diagnostic_Services

#ifndef OBDII_LIB_H
#define OBDII_LIB_H

#include "enums.h"
#include "can.h"

// UL == unsigned 32 bit number reqired
// basically force the constants to be unsigned

const __u8 SAE_OBDII_DLC = 0x08U;
const canid_t SAE_OBDII_PID_QUERY = 0x07DFUL;
const canid_t SAE_OBDII_PID_RES = 0x07E8UL;

// util function
void make_frame(struct can_frame *frame, canid_t id, __u8 dlc, __u8* data, size_t size) {
    frame->can_id = id;
    frame->can_dlc = dlc;

    // init array
    memset(frame->data, 0, CAN_MAX_DLEN);
    // copy data
    memcpy(frame->data, data, size);
}

// only on little endian machines
union dtc_code_data {
    struct {
        __u8 b1;
        __u8 b0;
    } bytes;
    struct {
        __u8 d3: 4; // b2
        __u8 d2: 4; // b2
        __u8 d1: 4; // b1
        __u8 num: 2; // b1
        __u8 cat: 2; // b1
    } data;
};

// only on little endian machines
// basically, makes it easy to determine if single or multi frame message
union can_header {
    __u8 bytes[8];
    struct {
        __u8 len: 4;  // this will be backwards on big-endian
        __u8 type: 4; // this will be backwards on big-endian
        __u8 data[7];
    } single;
    struct {
        __u8 len_upper: 4; // this will be backwards on big-endian
        __u8 type: 4;      // this will be backwards on big-endian
        __u8 len: 8;
        __u8 data[6];
    } first;
    struct {
        __u8 idx: 4;  // this will be backwards on big-endian
        __u8 type: 4; // this will be backwards on big-endian
        __u8 data[7];
    } next;
};




#endif
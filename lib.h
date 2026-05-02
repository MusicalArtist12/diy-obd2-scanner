// https://en.wikipedia.org/wiki/OBD-II_PIDs
// https://en.wikipedia.org/wiki/CAN_bus
// https://en.wikipedia.org/wiki/Unified_Diagnostic_Services


// for testing
#ifndef CAN_H_
#define CAN_H_

typedef uint32_t __u32;
typedef uint8_t __u8;
typedef __u32 canid_t;

#define CAN_MAX_DLEN 8

struct can_frame {
               canid_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
               __u8    can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    alignas(8) __u8    data[CAN_MAX_DLEN];
};

#endif

#ifndef OBDII_LIB_H
#define OBDII_LIB_H

enum OBDII_SERVICE {
    CURR_DATA = 0x01,
    FREEZE_FRAME = 0x02,
    STORED_DTC = 0x03,
    CLEAR_DTC = 0x04,
    TEST_RES = 0x05,
    O2_MONITOR = 0x06,
    PENDING_DTC = 0x07,
    CONTROL_ONBOARD = 0x08,
    VEHICLE_INFO = 0x09,
    PERM_DTC = 0x0A
};

const __u8 SAE_OBDII_DLC = 0x08;
const __u32 SAE_OBDII_PID_QUERY = 0x07DF;
const __u32 SAE_OBDII_PID_RES = 0x7E8;

// util function
void make_frame(struct can_frame *frame, canid_t id, __u8 dlc, __u8* data, size_t size) {
    frame->can_id = id;
    frame->can_dlc = dlc;

    // init array
    memset(frame->data, 0, CAN_MAX_DLEN);
    // copy data
    memcpy(frame->data, data, size);
}

// easier to return this than a raw ptr
// keeps things on the stack
struct dtc_code_frame {
    char code_0[6]; // 5 + 1 for null
    char code_1[6];
    __u8 count;
};

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

void _parse_code(char* res, __u8 b0, __u8 b1) {
    const char* codes = "PCBU";

    union dtc_code_data code;
    code.bytes.b0 = b0;
    code.bytes.b1 = b1;

    res[0] = codes[code.data.cat];
    res[1] = code.data.num + '0';
    res[2] = code.data.d1 + '0';
    res[3] = code.data.d2 + '0';
    res[4] = code.data.d3 + '0';
}

struct dtc_code_frame interpret_dtc_frame(struct can_frame *frame) {
    struct dtc_code_frame result;

    // 1 DTC
    if (frame->data[0] >= 4) {
        _parse_code(result.code_0, frame->data[3], frame->data[4]);
        result.count = 1;
    }
    // 2 DTCs
    if (frame->data[0] >= 6) {
        _parse_code(result.code_1, frame->data[5], frame->data[6]);
        result.count = 2;
    }

    return result;
}

#endif
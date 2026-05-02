// https://en.wikipedia.org/wiki/OBD-II_PIDs
// https://en.wikipedia.org/wiki/CAN_bus
// https://en.wikipedia.org/wiki/Unified_Diagnostic_Services


#include "can.h"

#ifndef OBDII_LIB_H
#define OBDII_LIB_H

enum OBDII_SERVICE {
    CURR_DATA = 0x01U,
    FREEZE_FRAME = 0x02U,
    STORED_DTC = 0x03U,
    CLEAR_DTC = 0x04U,
    TEST_RES = 0x05U,
    O2_MONITOR = 0x06U,
    PENDING_DTC = 0x07U,
    CONTROL_ONBOARD = 0x08U,
    VEHICLE_INFO = 0x09U,
    PERM_DTC = 0x0AU
};


//https://en.wikipedia.org/wiki/OBD-II_PIDs#Service_01_-_Show_current_data
enum SERVICE_PID_BANK_1 : uint8_t {
    PIDS_SUPPORTED = 0x00U,  // what codes does the ECU support (in big endian)
    MONITOR_STATUS_SINCE_DTC_CLEARED,
    DTC_FREEZE_FRAME, // why does the freeze frame exist
    FUEL_SYS_STAT,
    CALC_ENGINE_LOAD,
    COOLANT_TEMP,
    STFT_BANK_1,
    LTFT_BANK_1,
    STFT_BANK_2,
    LTFT_BANK_2,
    FUEL_PRESSURE,
    INTAKE_MAP,
    ENGINE_SPEED,
    VEHICLE_SPEED,
    TIMING_ADV,
    INTAKE_AIR_TEMP,
    MAF_RATE,
    THROTTLE_POS,
    COMMANDED_SECONDARY_AIR_STATUS,
    O2_SENSORS_PRESENT_2_BANK,
    O2_1_TRIM_VOLTAGE,
    O2_2_TRIM_VOLTAGE,
    O2_3_TRIM_VOLTAGE,
    O2_4_TRIM_VOLTAGE,
    O2_5_TRIM_VOLTAGE,
    O2_6_TRIM_VOLTAGE,
    O2_7_TRIM_VOLTAGE,
    O2_8_TRIM_VOLTAGE,
    OBD_STANDARD,
    O2_SENSORS_PRESENT_4_BANK,
    AUX_INPUT_STATUS,
    RUNTIME
};

enum SERVICE_PID_BANK_2: uint8_t {

    PID_SUPPORTED = 0x20U, // does the ECU support this bank?
    DIST_WITH_MALF_IND_LAMP,
    FUEL_RAIL_PRESSURE,
    FUEL_RAIL_GAUGE_PRESSURE,
    O2_1_AIR_FUEL_VOLTAGE,
    O2_2_AIR_FUEL_VOLTAGE,
    O2_3_AIR_FUEL_VOLTAGE,
    O2_4_AIR_FUEL_VOLTAGE,
    O2_5_AIR_FUEL_VOLTAGE,
    O2_6_AIR_FUEL_VOLTAGE,
    O2_7_AIR_FUEL_VOLTAGE,
    O2_8_AIR_FUEL_VOLTAGE,
    COMMANDED_EGR,
    EGR_ERR,
    COMMANDED_EVAP_PURGE,
    FUEL_TANK_LEVEL,
    WARM_UPS_SINCE_CODES_CLEARED,
    DISTANCE_SINCE_CODES_CLEARED,
    EVAP_SYS_VAPOR_PRESSURE,
    ABS_BAROMETRIC_PRESSURE,
    O2_1_AIR_FUEL_AMPERAGE,
    O2_2_AIR_FUEL_AMPERAGE,
    O2_3_AIR_FUEL_AMPERAGE,
    O2_4_AIR_FUEL_AMPERAGE,
    O2_5_AIR_FUEL_AMPERAGE,
    O2_6_AIR_FUEL_AMPERAGE,
    O2_7_AIR_FUEL_AMPERAGE,
    O2_8_AIR_FUEL_AMPERAGE,
    CAT_TEMP_BANK_1_SENSOR_1,
    CAT_TEMP_BANK_2_SENSOR_1,
    CAT_TEMP_BANK_1_SENSOR_2,
    CAT_TEMP_BANK_2_SENSOR_2,
};

enum SERVICE_PID_BANK_3: uint8_t {
    PID_SUPPORTED = 0x40U, // does the ECU support this bank?
    MONITOR_STATUS_THIS_DRIVE_CYCLE,
    CONTROL_MODULE_VOLTAGE,
    ABS_LOAD_VAL,
    COMMANDED_AIR_FUEL,
    REL_THROTTLE_POS,
    AMBIENT_AIR_TEMP,
    ABS_THROTTLE_POS_B,
    ABS_THROTTLE_POS_C,
    ACCEL_PEDAL_POS_D,
    ACCEL_PEDAL_POS_E,
    ACCEL_PEDAL_POS_F,
    COMMANDED_THROTTLE_ACTUATOR,
    TIME_RUN_WITH_MIL,
    TIME_SINCE_TROUBLE_CODES_CLEARED,
    MAX_RATIO_VOLTAGE_CURRENT_INTAKE_MAP,
    MAX_MAF,
    FUEL_TYPE,
    ETHANOL_FUEL_PERCENT,
    ABS_EVAP_PRESSURE,
    EVAP_PRESSURE,
    SHORT_TERM_SECONDARY_O2_SENSOR_TRIM_1_3,
    LONG_TERM_SECONDARY_O2_SENSOR_TRIM_1_3,
    SHORT_TERM_SECONDARY_O2_SENSOR_TRIM_2_4,
    LONG_TERM_SECONDARY_O2_SENSOR_TRIM_2_4,
    ABS_FUEL_RAIL_PRESSURE,
    REL_ACCEL_PEDAL_POS,
    HYBRID_BAT_PERCENT,
    ENGINE_OIL_TEMP,
    FUEL_INJECTION_TIMING,
    ENGINE_FUEL_RATE,
    EMISSIONS_REQ_DESIGN,
};

enum SERVICE_PID_BANK_4: uint8_t {
    PID_SUPPORTED_A = 0x60U,  // does the ECU support this bank?
    DEMANDED_ENGINE_PERCENT_TORQUE,
    ACTUAL_ENGINE_PERCENT_TORQUE,
    ENGINE_REFERENCE_TORQUE,
    ENGINE_PERCENT_TORQUE_DATA,
    PRIMARY_BUS_MONITORING_STATUS
};

enum SERVICE_PID_BANK_5: uint8_t {
    PID_SUPPORTED = 0x80U,  // does the ECU support this bank?
    STATUS_DURING_DRIVE_CYCLE,
    ENGINE_RUN_TIME_TOTAL,
    ENGINE_RUN_TIME_WITH_MIL_ON,
    TIME_SINCE_DTC_CLEARED,
    MAX_VALUES_FOR_PIDS,
};

enum SERVICE_PID_BANK_6: uint8_t {
    PID_SUPPORTED_C = 0xA0U,  // does the ECU support this bank?
    TOTAL_ENGINE_RUN_TIME,
    TOTAL_IDLE_RUN_TIME,
    TOTAL_FUEL_USED
};

enum SERVICE_9_PID: uint8_t {
    S9_PIDS_SUPPORTED_A = 0x00U,
    VIN_MESSAGE_COUNT = 0x01U,   // Number of data items for VIN
    VIN,                         // Vehicle Identification Number
    CALIBRATION_ID_COUNT,
    CALIBRATION_ID,
    CALIBRATION_VERIF_IND_COUNT,
    CALIBRATION_VERIF_IND,       // CVN
    /* 0x07 - 0x08 vary by standard version */
    ECU_NAME_COUNT = 0x09U,
    ECU_NAME,
    IN_USE_MONITOR_PERF_RATIO = 0x0BU,
    ECU_SERIAL_NUMBER = 0x0CU,
    EXHAUST_REG_STANDARD = 0x0DU,
    PID_SUPPORTED_B = 0x20U
};

enum FUEL_SYS_STATUS {
    OFF,
    OPEN_LOOP_LOW_ENGINE_TEMP,
    CLOSED_LOOP_02_FEEDBACK,
    OPEN_LOOP_LOAD_OR_DECEL,
    OPEN_LOOP_FAILURE,
    CLOSED_LOOP_FAULT_FEEDBACK
};

enum COMMANDED_SECONDARY_AIR_STATUS: uint8_t {
    UPSTREAM = 1U,
    DOWNSTREAM_OF_CAT,
    FROM_OUTSIDE_ATMO_OR_OFF,
    PUMP_COMMANDED_DIAG
};
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

enum CAN_HEADER_TYPE: uint8_t {
    SINGLE,
    FIRST,
    NEXT
};

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
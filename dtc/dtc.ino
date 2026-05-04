// simple setup to read dtc codes and clear them using a button
// no laptop required!
// may or may not work perfectly

#include "mcp2515.h"
#include "lib.h"
#include "LCD1602.h"


MCP2515 mcp2515(10);
LCD lcd(8, 7, 6, 2, 3, 4, 5);

struct can_frame requestDTC;
struct can_frame respond;
struct can_frame clearDTC;

void setup() {

    byte requestDTC_data[] = { 0x01, OBDII_SERVICE::STORED_DTC };
    byte clearDTC_data[] = {0x01, OBDII_SERVICE::CLEAR_DTC };
    byte respond_data[] = { 0x30, 0x00, 0x0A };

    make_frame(&requestDTC, 0x7e0, SAE_OBDII_DLC, requestDTC_data, sizeof requestDTC_data);
    make_frame(&respond, 0x7E0, SAE_OBDII_DLC, respond_data, sizeof respond_data);
    make_frame(&clearDTC, 0x7E0, SAE_OBDII_DLC, clearDTC_data, sizeof clearDTC_data);

    mcp2515.reset();
    mcp2515.setBitrate(CAN_500KBPS);

    mcp2515.setConfigMode();
    mcp2515.setFilterMask(MCP2515::MASK0, false, CAN_SFF_MASK);
    mcp2515.setFilter(MCP2515::RXF0, false, SAE_OBDII_PID_RES);
    mcp2515.setFilter(MCP2515::RXF1, false, SAE_OBDII_PID_RES);

    mcp2515.setFilterMask(MCP2515::MASK1, false, CAN_SFF_MASK);
    mcp2515.setFilter(MCP2515::RXF2, false, SAE_OBDII_PID_RES);
    mcp2515.setFilter(MCP2515::RXF3, false, SAE_OBDII_PID_RES);
    mcp2515.setFilter(MCP2515::RXF4, false, SAE_OBDII_PID_RES);
    mcp2515.setFilter(MCP2515::RXF5, false, SAE_OBDII_PID_RES);
    mcp2515.setFilter(MCP2515::RXF5, false, SAE_OBDII_PID_RES);


    mcp2515.setNormalMode();
    mcp2515.sendMessage(&requestDTC);

    // attachInterrupt(digitalPinToInterrupt(9), irqHandler, FALLING);

    Serial.println("------- CAN Read ----------");
    Serial.println("ID  | DLC | DATA");

    //sei();

    lcd.init();
    lcd.displaySwitch(true, true, true);
    lcd.inputSet(true, false);
    lcd.clear();

    pinMode(A0, INPUT);

}

void printDTC(struct can_frame* frame) {
    union can_header* header = (can_header *)frame->data;

    union dtc_code_data* code_0;
    union dtc_code_data* code_1;

    if (header->single.type == SINGLE) {
        code_0 = (dtc_code_data *)&header->single.data[1];
        code_1 = (dtc_code_data *)&header->single.data[3];
    }
    else if (header->single.type == FIRST) {
        code_0 = (dtc_code_data *)&header->first.data[1];
        code_1 = (dtc_code_data *)&header->first.data[3];
    }
    else if (header->single.type == NEXT) {
        code_0 = (dtc_code_data *)&header->next.data[1];
        code_1 = (dtc_code_data *)&header->next.data[3];
    }

    const char* codes = "PCBU";

    lcd.writeData(codes[code_0->data.cat]);
    lcd.writeData(code_0->data.num + '0');
    lcd.writeData(code_0->data.d1 + '0');
    lcd.writeData(code_0->data.d2 + '0');
    lcd.writeData(code_0->data.d3 + '0');

    lcd.writeData(codes[code_1->data.cat]);
    lcd.writeData(code_1->data.num + '0');
    lcd.writeData(code_1->data.d1 + '0');
    lcd.writeData(code_1->data.d2 + '0');
    lcd.writeData(code_1->data.d3 + '0');


}

byte state = 0;
bool release = true;

void loop() {

    struct can_frame recieveMsg;

    if (mcp2515.readMessage(&recieveMsg) == MCP2515::ERROR_OK) {

        if ((recieveMsg.data[0] & 0xF0) == 0x10) {
            mcp2515.sendMessage(&respond);
        }

        //printFrameSerial(&recieveMsg);

        printDTC(&recieveMsg);
    }

    if (digitalRead(A0) == HIGH) {


        if (release) {
            switch (state) {
            case 0:
                state = 1;
                lcd.clear();
                lcd.writeData("3 ");
                break;
            case 1:
                state = 2;
                lcd.writeData("2 ");
                break;
            case 2:
                state = 3;
                lcd.writeData("1 ");
                break;
            case 3:
                lcd.writeData("cleared!");
                state = 4;
                mcp2515.sendMessage(&clearDTC);
                break;
            }
        }
        release = false;


    }
    else {
        release = true;
    }


}

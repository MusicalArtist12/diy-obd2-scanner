#include "mcp2515.h"
#include "lib.h"

MCP2515 mcp2515;

struct can_frame requestDTC;

volatile bool interrupt = false;

void irqHandler() {
    interrupt = true;
}

void setup() {

    byte data[2] = { 0x01, OBDII_SERVICE::STORED_DTC };

    make_frame(&requestDTC, SAE_OBDII_PID_QUERY, SAE_OBDII_DLC, data, sizeof data);

    Serial.begin(115200);

    mcp2515 = MCP2515(10); // CS pin == 10
    mcp2515.reset();
    mcp2515.setBitrate(CAN_500KBPS, MCP_16MHZ);


    mcp2515.setConfigMode();
    mcp2515.setFilterMask(MCP2515::MASK0, false, CAN_SFF_MASK);
    mcp2515.setFilter(MCP2515::RXF0, false, SAE_OBDII_PID_RES);
    mcp2515.setFilter(MCP2515::RXF1, false, SAE_OBDII_PID_RES);

    mcp2515.setFilterMask(MCP2515::MASK1, false, CAN_SFF_MASK);
    mcp2515.setFilter(MCP2515::RXF2, false, SAE_OBDII_PID_RES);
    mcp2515.setFilter(MCP2515::RXF3, false, SAE_OBDII_PID_RES);
    mcp2515.setFilter(MCP2515::RXF4, false, SAE_OBDII_PID_RES);
    mcp2515.setFilter(MCP2515::RXF5, false, SAE_OBDII_PID_RES);

    mcp2515.setNormalMode();
    mcp2515.sendMessage(&requestDTC);

    attachInterrupt(digitalPinToInterrupt(9), irqHandler, FALLING);

    Serial.println("------- CAN Read ----------");
    Serial.println("ID  | DLC | DATA");

}

void printFrame(const struct can_frame *frame) {
    Serial.print(frame->can_id, HEX); // print ID
    Serial.print(" | ");
    Serial.print(frame->can_dlc, HEX); // print DLC
    Serial.print(" | ");

    for (int i = 0; i < frame->can_dlc; i++)  {  // print the data
        Serial.print(frame->data[i], HEX);
        Serial.print(" ");
    }

    Serial.println();
}

void loop() {
    if (interrupt) {
        interrupt = false;

        uint8_t irq = mcp2515.getInterrupts();

        struct can_frame recieveMsg;


        // mask0 and rxf0-1
        if (irq & MCP2515::CANINTF_RX0IF) {
            if (mcp2515.readMessage(MCP2515::RXB0, &recieveMsg) == MCP2515::ERROR_OK) {
                printFrame(&recieveMsg);
            }
        }

        // mask1 and rxf2-5
        if (irq & MCP2515::CANINTF_RX1IF) {
            if (mcp2515.readMessage(MCP2515::RXB1, &recieveMsg) == MCP2515::ERROR_OK) {
                printFrame(&recieveMsg);
            }
        }
    }
}

#include "mcp2515.h"
#include "lib.h"

MCP2515 mcp2515(10);

struct can_frame requestDTC;
struct can_frame recieveMsg;

void setup() {

    byte data[2] = { 0x01, OBDII_SERVICE::STORED_DTC };

    make_frame(&requestDTC, SAE_OBDII_PID_QUERY, SAE_OBDII_DLC, data, sizeof data);

    Serial.begin(115200);

    mcp2515.reset();
    mcp2515.setBitrate(CAN_500KBPS);

    Serial.println("------- CAN Read ----------");
    Serial.println("ID  | DLC | DATA");

    mcp2515.setConfigMode();
    mcp2515.setFilterMask(MCP2515::MASK0, false, 0x07FF);
    mcp2515.setFilter(MCP2515::RXF0, false, SAE_OBDII_PID_RES);


    mcp2515.setNormalMode();

}



void loop() {
    mcp2515.sendMessage(&requestDTC);

    int out = mcp2515.readMessage(&recieveMsg);

    // num_data_bytes is the count filled in data[1:8]. min = 3, max = 6
    if (out == MCP2515::ERROR_OK) {
        Serial.print(recieveMsg.can_id, HEX); // print ID
        Serial.print(" | ");
        Serial.print(recieveMsg.can_dlc, HEX); // print DLC
        Serial.print(" | ");

        for (int i = 0; i < recieveMsg.can_dlc; i++)  {  // print the data
            Serial.print(recieveMsg.data[i], HEX);
            Serial.print(" ");
        }

        Serial.println();
    }

}

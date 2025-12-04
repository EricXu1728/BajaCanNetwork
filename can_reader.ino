//https://github.com/autowp/arduino-mcp2515/tree/master
#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(10);   // CS pin

void setup() {
  Serial.begin(115200);
  SPI.begin();

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);   // Match RaceCapture CAN bus speed
  mcp2515.setNormalMode();

  Serial.println("MCP2515 Receiver Ready");
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.print("ID: 0x");
    Serial.print(canMsg.can_id, HEX);

    Serial.print(" | DLC: ");
    Serial.print(canMsg.can_dlc);

    Serial.print(" | Data: ");
    for (int i = 0; i < canMsg.can_dlc; i++) {
      Serial.print(canMsg.data[i]);
      Serial.print(" ");
    }
    Serial.println();
  }
}


#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(10);   // CS pin

byte data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
bool canReady = false;

void setup() {
  Serial.begin(115200);
  delay(1000);

  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) {
    Serial.println("MCP2515 Initialized Successfully!");
    CAN0.setMode(MCP_NORMAL);
    canReady = true;
  } else {
    Serial.println("Error Initializing MCP2515...");
  }
}

void loop() {
  if (!canReady) {
    Serial.println("CAN not ready. Check MCP2515 wiring/clock.");
    delay(1000);
    return;
  }

  byte sndStat = CAN0.sendMsgBuf(0x100, 0, 8, data);

  if (sndStat == CAN_OK) {
    Serial.println("Message Sent Successfully!");
  } else {
    Serial.println("Error Sending Message...");
  }

  delay(1000);
}

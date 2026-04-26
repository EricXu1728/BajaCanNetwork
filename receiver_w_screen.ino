// CAN Receive Example
//

#include <mcp_can.h>
#include <SPI.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Common I2C address is 0x27 or 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);


long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];                        // Array to store serial string

#define CAN0_INT 2                              // Set INT to pin 2
MCP_CAN CAN0(10);                               // Set CS to pin 10


void setup()
{
  lcd.init();

  lcd.backlight();
  Serial.begin(115200);
  
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");
  
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(CAN0_INT, INPUT);                            // Configuring pin for /INT input
  
  Serial.println("MCP2515 Library Receive Example...");
}

void loop()
{
  if(!digitalRead(CAN0_INT))                         // If CAN0_INT pin is low, read receive buffer
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
    
    // if((rxId & 0x80000000) == 0x80000000)
    //   sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    // else
    //   sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
  
    // Serial.print(msgString);
  
    if((rxId & 0x40000000) == 0x40000000){    // Determine if message is a remote request frame.
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    } else{
      // Print raw bytes (your existing loop)
      for (byte i = 0; i < len; i++) {
        sprintf(msgString, " 0x%.2X", rxBuf[i]);
        Serial.print(msgString);
      }

      // Decode first 4 bytes into a float (little-endian)
      if (len >= 4) {
        uint32_t u =
          ((uint32_t)rxBuf[0]) |
          ((uint32_t)rxBuf[1] << 8) |
          ((uint32_t)rxBuf[2] << 16) |
          ((uint32_t)rxBuf[3] << 24);

        int32_t i32 = (int32_t)u;

        //Serial.print("  int32=");
        //Serial.print(i32);

        //If set Pitch*1000 on the RaceCapture side:
        float pitch = i32 / 10000.0f;
        Serial.print("  Pitch=");
        Serial.println(pitch, 3);
        lcd.setCursor(0, 1);
        lcd.print(pitch);
      } else {
        Serial.println("  (len < 4)");
      }

    }

        
    Serial.println();
  }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

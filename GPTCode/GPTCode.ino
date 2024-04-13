#include <SPI.h>
#include <mcp2515.h>
// Define the SPI pins
#define PIN_MISO 12
#define PIN_MOSI 11
#define PIN_SCK 13
#define CS_PIN 10  // Chip Select pin
// Initialize MCP2515
MCP2515 mcp2515(CS_PIN);  // CS pin 10
void setup() {
  Serial.begin(9600);
  // Initialize SPI communication with explicit pin configuration
  SPI.begin(PIN_MISO, PIN_MOSI, PIN_SCK);
  // Initialize MCP2515 module
  if (mcp2515.reset() != MCP2515_OK) {
    Serial.println("Error: MCP2515 not found");
    while (1);
  }
  // Initialize CAN controller
  if (mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ) != MCP2515_OK) {
    Serial.println("Error: Could not set bitrate");
    while (1);
  }
  // Set receive filters to accept only CAN_ID
  mcp2515.setFilterMask(MCP2515_MASK0, true);
  mcp2515.setFilter(MCP2515_FILTER0, CAN_ID);
  // Enable interrupt pin
  mcp2515.setMode(MCP2515_MODE_NORMAL);
}
void loop() {
  // Check if data is available
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    // Check if received message has the desired ID
    if (canMsg.can_id == CAN_ID) {
      // Print received data
      Serial.print("Received CAN message with ID ");
      Serial.print(canMsg.can_id, HEX);
      Serial.print(": ");
      for (int i = 0; i < canMsg.can_dlc; i++) {
        Serial.print(canMsg.data[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
    }
  }
}
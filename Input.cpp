#define RX_PIN 1   // Pin for RX (receive)
#define TX_PIN 0   // Pin for TX (transmit)

void setup() {
  // Initialize default Serial for debugging
  Serial.begin(115200); // Serial monitor (USB)

  // Initialize UART1 (TX=Pin 0, RX=Pin 1) for iBUS communication
  Serial1.begin(115200, SERIAL_8N1, RX_PIN); // UART1 for iBUS (without the TX pin)
  
  Serial.println("Starting iBUS receiver...");
}

void loop() {
  if (Serial1.available()) {  // Check if data is available in UART1
    byte data[32];           // Buffer for receiving iBUS data
    int index = 0;
    
    // Read 32 bytes of data (iBUS packet size)
    while (Serial1.available() && index < 32) {
      data[index++] = Serial1.read();
    }

    // Check for valid iBUS packet
    if (index == 32 && data[0] == 0x20 && data[1] == 0x40) {
      // Extract 6 channel values (2 bytes each)
      int channels[6];
      for (int i = 0; i < 6; i++) {
        channels[i] = data[2 + i * 2] + (data[3 + i * 2] << 8); // Little-endian
      }

      // Print channel values
      Serial.print("Channels: ");
      for (int i = 0; i < 6; i++) {
        Serial.print(channels[i]);
        Serial.print(" ");
      }
      Serial.println();
    }
  }
  
  delay(10);  // Small delay to avoid overloading the serial output
}

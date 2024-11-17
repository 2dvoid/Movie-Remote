#include <IRremote.hpp>
#define IR_RECEIVE_PIN 7

void setup()
{
  Serial.begin(115200); // // Establish serial communication
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
}

void loop() {
  if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData); // Print "old" raw data
      IrReceiver.resume(); // Enable receiving of the next value
      delay (100);
  }
}

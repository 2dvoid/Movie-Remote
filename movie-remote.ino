#include <IRremote.hpp>
#define IR_PIN 7
// Define Keycodes

//Modifier Keys:
#define META 0x08;
#define CTRL 0x01;
#define SHIFT 0x02;
#define ALT 0x04;
#define META_CTRL 0x09;
#define META_ALTR 0x0C;
// Normal Keys:
#define ENTER 0x28;

// Define the Keyboard Buffer
/* A keyboard buffer is typically 8 bytes long. The first byte holds the modifier keys (such as Ctrl, Shift, Alt). The second byte is reserved and usually set to 0. The third to eighth bytes are used for regular keys, with each byte representing one key. */
// Initially Set the buffer to 0
uint8_t buf[8] = {0};
uint8_t ircode;


void setup () {
    Serial.begin(9600);
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    delay (100);
}

void loop () {

    if (IrReceiver.decode()) {
        ircode = IrReceiver.decodedIRData.decodedRawData; 
        Serial.println (ircode);
        IrReceiver.resume();
    }


}


// Function to Send Keypress
// Argument: (Modifier_Key, Normal key)
void keypress(uint8_t mod, uint8_t key) 
{
    // Set the modifier keys in the first byte of the buffer
    buf[0] = mod;
    // Set the letter key to third byte of the buffer
    buf[2] = key;
    // Send the buffer to simulate the keypress
    Serial.write(buf, 8);
    
    // Release the keys by resetting the changed buffer and sending it again
    buf[0] = 0;
    buf[2] = 0; 
    Serial.write(buf, 8); 
    // Small Delay to ensure release is registered
    delay(50);
}



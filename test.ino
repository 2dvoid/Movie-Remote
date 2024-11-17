#include <IRremote.hpp>
#define IR_PIN 7

// Combines Ir code with its corresponding Key code
struct codemap {
    uint32_t ircode;
    uint8_t keycode;
};

// Array of codes
struct codemap code [] = {
    {F5, 0x80},
    {F9, 0x81},
    {F9, 0x81},
    {F9, 0x81}
}

// Define the Keyboard Buffer
/* A keyboard buffer is typically 8 bytes long. The first byte holds the modifier keys (such as Ctrl, Shift, Alt). The second byte is reserved and usually set to 0. The third to eighth bytes are used for regular keys, with each byte representing one key. */
// Initially Set the buffer to 0
uint8_t buf[8] = {0};

// Size of the code[] array:
const int arraysize = sizeof (code) / sizeof (codemap);

void setup () {
    Serial.begin(9600);
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    delay (100);
}

void loop () {

    if (IrReceiver.decode()) {

        uint32_t recv_code = IrReceiver.decodedIRData.decodedRawData;
        // Loop through the array and check which ir code matches the recieved ir code
        for (int i=0; i<arraysize; i++) {

            if (recv_code == code[i].ircode) {
                keypress (code[i].keycode);
                break;
            }

        }
    }

}


// Function to Send Keypress
void keypress(uint8_t key) 
{
    // Set the key to third byte of the buffer
    buf[2] = key;
    // Send the buffer to simulate the keypress
    Serial.write(buf, 8);
    
    // Release the keys by resetting the changed buffer and sending it again
    buf[2] = 0; 
    Serial.write(buf, 8); 
    // Small Delay to ensure release is registered
    delay(50);
}



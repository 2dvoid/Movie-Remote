#include <IRremote.hpp>
#define IR_PIN 7

// Combines Ir code with its corresponding Key code
struct codemap {
    uint32_t ircode;
    uint8_t keycode;
};

// Array of codes
struct codemap code [] = {
    // Ir codes and its corresponding Key code
    // Sony Remote
	{146, 0x80},    // {VOLUME_PLUS, KEY_VOLUME_UP}
	{147, 0x81},    // {VOLUME_MINUS, KEY_VOLUME_DOWN}
	{148, 0x7F},    // {MUTE, KEY_MUTE}
	{244, 0x52},    // {UP, KEY_UP_ARROW}
	{245, 0x51},    // {DOWN, KEY_DOWN_ARROW}  
	{180, 0x50},    // {LEFT, KEY_LEFT_ARROW}
	{179, 0x4f},    // {RIGHT, KEY_RIGHT_ARROW}
	{19355, 0x2f},  // {BACKWARD, KEY_LEFT_SQUARE_BRACE}
	{19356, 0x30},  // {FORWARD, KEY_RIGHT_SQUARE_BRACE}
	{229, 0x2c},    // {OK, KEY_SPACE}
	{19363, 0x2a},  // {RETURN, KEY_BACKSPACE}
	{19368, 0x06},  // {SUBTITLE, KEY_c}
	{191, 0x0d},  	 // {CHANGE_SUBTITLE, KEY_j}
	{19353, 0xe8},  // {PAUSE, KEY_MEDIA_PLAYPAUSE}
	{19354, 0xe8},  // {PLAY, KEY_MEDIA_PLAYPAUSE}
	{19352, 0xf3},  // {STOP, KEY_MEDIA_STOP}
	{145, 0xea},  // {PREVIOUS, KEY_MEDIA_PREVIOUS}
	{144, 0xeb},  // {NEXT, KEY_MEDIA_NEXT}
	{21053, 0x09},  // {FULLSCREEN, KEY_f}
	{19365, 0x14},  // {RED, KEY_q}
	{19382, 0x28}   // {OPTIONS, KEY_ENTER}
};

// Define the Keyboard Buffer
/* A keyboard buffer is typically 8 bytes long. The first byte holds the modifier keys (such as Ctrl, Shift, Alt). The second byte is reserved and usually set to 0. The third to eighth bytes are used for regular keys, with each byte representing one key. */
// Initially Set the buffer to 0
uint8_t buf[8] = {0};

// Size of the code[] array:
const int arraysize = sizeof (code) / sizeof (codemap);

void setup () {
    Serial.begin(9600);
    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
    delay (100);
}

void loop () {
    
    run();

}


void run () {
    
     if (IrReceiver.decode()) {

        uint32_t recv_code = IrReceiver.decodedIRData.decodedRawData;
        // Loop through the array to match the received IR code
        for (int i=0; i<arraysize; i++) {

            if (recv_code == code[i].ircode) {
                keypress (code[i].keycode);
                break;
            }

        }
        IrReceiver.resume();
        
    }   

}

// Function to print IR code values from a remote
void getcodes () {

    if (IrReceiver.decode()) {
        uint32_t recv_code = IrReceiver.decodedIRData.decodedRawData;
        Serial.println(recv_code);
        IrReceiver.resume(); // Enable receiving of the next value
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
    delay(50);
}

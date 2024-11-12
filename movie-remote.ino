// Define Keycodes
#define META 0x08;
#define CTRL 0x01;
#define SHIFT 0x02;
#define ALT 0x04;
#define META_CTRL 0x09;
#define META_ALTR 0x0C;
// Define the Keyboard Buffer
/* A keyboard buffer is typically 8 bytes long. The first byte holds the modifier keys (such as Ctrl, Shift, Alt). The second byte is reserved and usually set to 0. The third to eighth bytes are used for regular keys, with each byte representing one key. */
uint8_t buf[8] = {0};

void setup () {
    Serial.begin(9600);
    delay (100);
}

void loop () {
    delay (5000);
    keypress(META, 0x28);
}


void keypress(uint8_t mod, uint8_t key) 
{
    // Set the modifier keys in the first byte
    buf[0] = mod;
    // Set the letter key to third byte
    buf[2] = key;
    // Send the buffer to simulate the keypress
    Serial.write(buf, 8);
    
    // Release the keys by resetting the changed buffer and sending it again
    buf[0] = 0;
    buf[2] = 0; 
    Serial.write(buf, 8); 
    // Small Delay to ensure release is registered
    delay(200);
}



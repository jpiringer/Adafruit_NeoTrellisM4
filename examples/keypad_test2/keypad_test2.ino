#include <Adafruit_Keypad.h>
#include <Adafruit_NeoPixel.h>

#define NEO_PIN 10
#define NUM_KEYS 32

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_KEYS, NEO_PIN, NEO_GRB + NEO_KHZ800);

const byte ROWS = 4; // four rows
const byte COLS = 8; // eight columns
//define the symbols on the buttons of the keypads
byte trellisKeys[ROWS][COLS] = {
  {1,  2,  3,  4,  5,  6,  7,  8},
  {9,  10, 11, 12, 13, 14, 15, 16},
  {17, 18, 19, 20, 21, 22, 23, 24},
  {25, 26, 27, 28, 29, 30, 31, 32}
};
byte rowPins[ROWS] = {14, 15, 16, 17}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 3, 4, 5, 6, 7, 8, 9}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(trellisKeys), rowPins, colPins, ROWS, COLS); 

boolean lit[NUM_KEYS];

void setup(){
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(80);
  customKeypad.begin();
  
  Serial.begin(9600);
  Serial.println("keypad1 test!");

  for (int i=0; i<NUM_KEYS; i++) {
    lit[i] = false;
  }
}
  
void loop() {
  // put your main code here, to run repeatedly:
  customKeypad.tick();

  while (customKeypad.available()){
    keypadEvent e = customKeypad.read();
    
    if (e.bit.EVENT == KEY_JUST_PRESSED) {
      Serial.print((int)e.bit.KEY);
      Serial.println(" pressed");
      int led = e.bit.KEY-1;
      lit[led] = !lit[led];
      if (lit[led]) {
        strip.setPixelColor(led, Wheel(random(255)));
      } else {
        strip.setPixelColor(led, 0);
      }      
    }
    strip.show();
  }
  
  delay(10);
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
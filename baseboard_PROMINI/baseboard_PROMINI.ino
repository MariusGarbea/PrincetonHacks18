#include <Keypad.h>
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#define PIN 13
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial mySerial(10, 11);

const byte numRows= 4;
const byte numCols= 4;
char keymap[numRows][numCols]= {
{'A', 'B', 'C', 'D'},
{'E', 'F', 'G', 'H'},
{'I', 'J', 'K', 'L'},
{'M', 'N', 'O', 'P'}
};
int RGBmaps[16] = {15, 8, 7, 0, 14, 9, 6, 1, 13, 10, 5, 2, 12, 11, 4, 3};
byte rowPins[numRows] = {9,8,7,6};
byte colPins[numCols] = {5,4,3,12};

Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  strip.begin();
  strip.setBrightness(100);
}

void loop() {
  while(mySerial.available()) {
    char holdC = mySerial.read();
    for(int i = 0; i < 16; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
  }
  char keypressed = myKeypad.getKey();
  if (keypressed != NO_KEY) {
      Serial.println(keypressed);
      setNew(int(keypressed)-65);
  }
}

void setNew(int loc) {
  for(int i = 0; i < 16; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.setPixelColor(RGBmaps[loc], strip.Color(255, 255, 255));
  strip.show();

  mySerial.println(String(loc + 20));
}

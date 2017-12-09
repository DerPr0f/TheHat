#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 4

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(64, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
int red1 = 0;
int green1 = 0;
int blue1 = 0;
int red2 = 0;
int green2 = 0;
int blue2 = 0;
int red3 = 0;
int green3 = 0;
int blue3 = 0;
int WT = 30;
String Data = "help";

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  help();
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  // constrain the values to 0 - 255 and invert
  // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"

  // fade the red, green, and blue legs of the LED:
  if (Data == "rbc") {
    rainbowCycle(WT);
  }
  else if (Data == "rdc") {
    randomCycle(WT);
  }
  else if (Data == "rb") {
    rainbow(WT);
  }
  else if (Data == "rd") {
    randm(WT);
  }
  else if (Data == "1cw") {
    colorWipe(strip.Color(red1, green1, blue1), WT);
  }
  else if (Data == "2cw") {
    colorWipe(strip.Color(red1, green1, blue1), WT);
    colorWipe(strip.Color(red2, green2, blue2), WT);
  }
  else if (Data == "3cw") {
    colorWipe(strip.Color(red1, green1, blue1), WT);
    colorWipe(strip.Color(red2, green2, blue2), WT);
    colorWipe(strip.Color(red3, green3, blue3), WT);
  }
  else if (Data == "1tc") {
    theaterChase(strip.Color(red1, green1, blue1), WT);
  }
  else if (Data == "2tc") {
    theaterChase(strip.Color(red1, green1, blue1), WT);
    theaterChase(strip.Color(red2, green2, blue2), WT);
  }
  else if (Data == "3tc") {
    theaterChase(strip.Color(red1, green1, blue1), WT);
    theaterChase(strip.Color(red2, green2, blue2), WT);
    theaterChase(strip.Color(red3, green3, blue3), WT);
  }
  else if (Data == "tcr") {
    theaterChaseRainbow(WT);
  }
  else if (Data == "fio") {
    FadeInOut(red1, green1, blue1, WT);
  }
  else if (Data == "rl")  {
    RunningLights(red1, green1, blue1, WT);
  }
  // print the three numbers in one string as hexadecimal:
  if (Data != "help") {
  /*  Serial.print("C1:  ");
    Serial.print(red1, HEX);
    Serial.print(green1, HEX);
    Serial.print(blue1, HEX);
    Serial.print("  C2:  ");
    Serial.print(red2, HEX);
    Serial.print(green2, HEX);
    Serial.print(blue2, HEX);
    Serial.print("  C3:  ");
    Serial.print(red3, HEX);
    Serial.print(green3, HEX);
    Serial.print(blue3, HEX);
    Serial.print("  Waittime:  ");
    Serial.print(WT); */
    Serial.print("  String:  ");
    Serial.println(Data);
  }

  /*  colorWipe(strip.Color(255, 0, 0), 50); // Red
    colorWipe(strip.Color(0, 255, 0), 50); // Green
    colorWipe(strip.Color(0, 0, 255), 50); // Blue
    //colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
    // Send a theater pixel chase in...
    theaterChase(strip.Color(127, 127, 127), 50); // White
    theaterChase(strip.Color(127, 0, 0), 50); // Red
    theaterChase(strip.Color(0, 0, 127), 50); // Blue

    rainbow(20);
    rainbowCycle(20);
    theaterChaseRainbow(50); */
}

void serialEvent() {
  while (Serial.available()) {
    Data = Serial.readStringUntil(',');
    WT = Serial.parseInt();
    if (Serial.read() == '\n') {
      return;
    }
    if (Data == "help")  {
      help();
    }
    // look for the next valid integer in the incoming serial stream:
    red1 = Serial.parseInt();
    // do it again:
    green1 = Serial.parseInt();
    // do it again:
    blue1 = Serial.parseInt();
    if (Serial.read() == '\n') {
      return;
    }
    red2 = Serial.parseInt();
    // do it again:
    green2 = Serial.parseInt();
    // do it again:
    blue2 = Serial.parseInt();
    if (Serial.read() == '\n') {
      return;
    }
    red3 = Serial.parseInt();
    // do it again:
    green3 = Serial.parseInt();
    // do it again:
    blue3 = Serial.parseInt();
    if (Serial.read() == '\n') {
      return;
    }
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
void randm(uint8_t wait) {
  uint16_t i;
  for (i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, random(0, 255), random(0, 255), random(0, 255));
  }
  strip.show();
  delay(wait);
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void randomCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, random(0, 150), random(0, 150), random(0, 150));
    }
    strip.show();
    delay(wait);
  }
}

void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

void FadeInOut(int red, int green, int blue, int wait) {
  for (int k = 0; k < 256; k = k + 1) {
    int r = (k / 256.0) * red;
    int g = (k / 256.0) * green;
    int b = (k / 256.0) * blue;
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, r, g, b);
    }
    strip.show();
    delay(wait / 50);
  }
  for (int k = 255; k >= 0; k = k - 1) {
    int r = (k / 256.0) * red;
    int g = (k / 256.0) * green;
    int b = (k / 256.0) * blue;
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, r, g, b);
    }
    strip.show();
    delay(wait / 50);
  }
}

void RunningLights(int red, int green, int blue, int WaveDelay) {
  int Position = 0;
  for (int i = 0; i < strip.numPixels() * 2; i++)
  {
    Position++; // = 0; //Position + Rate;
    for (int i = 0; i < strip.numPixels(); i++) {
      // sine wave, 3 offset waves make a rainbow!
      //float level = sin(i+Position) * 127 + 128;
      //setPixel(i,level,0,0);
      //float level = sin(i+Position) * 127 + 128;
      strip.setPixelColor(i, ((sin(i + Position) * 127 + 128) / 255)*red,
                          ((sin(i + Position) * 127 + 128) / 255)*green,
                          ((sin(i + Position) * 127 + 128) / 255)*blue);
    }
    strip.show();
    delay(WaveDelay);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
void help()   {
  Serial.println("Commands: [command],[waittime],[red1],[green1],[blue1],[red2],[green2],[blue2],[red3],[green3],[blue3]");
  Serial.println("Rainbows: rbc (RainbowCycle) , rb (Rainbow)");
  Serial.println("Random: rdc (RandomCycle) , rd (Random)");
  Serial.println("ColorWipe: 1cw (one color), 2cw (two colors), 3cw (three colors)");
  Serial.println("TheaterChase: 1tc (one color), 2tc (two colors), 3tc (three colors), tcr (rainbow)");
  Serial.println("Fade In Out: fio (one color)");
  Serial.println("Running Lights: rl (one Color)");
}

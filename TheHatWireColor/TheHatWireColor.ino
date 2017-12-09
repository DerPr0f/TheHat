#include <Adafruit_NeoPixel.h>
#include <Wire.h>
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
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

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
String Data = "hel";
String Wt;
String Red1;
String Green1;
String Blue1;
String Red2;
String Green2;
String Blue2;
String Red3;
String Green3;
String Blue3;

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event

  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  //help();
}

void loop() {
  if (Data == "rbc") {
    rainbowCycle(WT, red1);
  }
  else if (Data == "rb") {
    rainbow(WT, red1);
  }
  else if (Data == "rd") {
    randm(WT, red1);
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
    theaterChaseRainbow(WT, red1);
  }
  else if (Data == "fio") {
    FadeInOut(red1, green1, blue1, WT);
  }
  else if (Data == "rl")  {
    RunningLights(red1, green1, blue1, WT);
  }
  else if (Data == "ss")  {
    singleScan(red1, green1, blue1, WT);
  }
  else if (Data == "ds")  {
    dualScan(red1, green1, blue1, WT);
  }
  else if (Data == "1tw") {
    twinkle(red1, green1, blue1, WT);
  }
  else if (Data == "2tw") {
    twinkle(red1, green1, blue1, WT);
    twinkle(red2, green2, blue2, WT);
  }
  else if (Data == "3tw") {
    twinkle(red1, green1, blue1, WT);
    twinkle(red2, green2, blue2, WT);
    twinkle(red3, green3, blue3, WT);
  }
  else if (Data == "twr")  {
    twinkleRandom(WT, red1);
  }
  else if (Data == "sp")  {
    sparkle(red1, green1, blue1, red2, green2, blue2, WT);
  }
  // print the three numbers in one string as hexadecimal:
  if (Data != "help" && Serial.available()) {
    Serial.print("C1:  ");
    Serial.print(red1, DEC);
    Serial.print(" ");
    Serial.print(green1, DEC);
    Serial.print(" ");
    Serial.print(blue1, DEC);
    Serial.print("  C2:  ");
    Serial.print(red2, DEC);
    Serial.print(" ");
    Serial.print(green2, DEC);
    Serial.print(" ");
    Serial.print(blue2, DEC);
    Serial.print("  C3:  ");
    Serial.print(red3, DEC);
    Serial.print(" ");
    Serial.print(green3, DEC);
    Serial.print(" ");
    Serial.print(blue3, DEC);
    Serial.print("  Waittime:  ");
    Serial.print(WT);
    Serial.print("  String:  ");
    Serial.println(Data);
  }
}

void receiveEvent() {
  while (1 < Wire.available()) {
    Data = "";
    Wt = "";
    Red1 = "";
    Green1 = "";
    Blue1 = "";
    Red2 = "";
    Green2 = "";
    Blue2 = "";
    Red3 = "";
    Green3 = "";
    Blue3 = "";
    //Data
    for (int I = 0; I <= 3; I++)  {
      char In = Wire.read();
      if (In == ',')  {
        //WT
        for (int I = 0; I <= 3; I++)  {
          char In = Wire.read();
          if (In == ',')  {
            //red1
            for (int I = 0; I <= 3; I++)  {
              char In = Wire.read();
              if (In == ',')  {
                //green1
                for (int I = 0; I <= 3; I++)  {
                  char In = Wire.read();
                  if (In == ',')  {
                    //blue1
                    for (int I = 0; I <= 3; I++)  {
                      char In = Wire.read();
                      if (In == ',')  {
                        //red2
                        for (int I = 0; I <= 3; I++)  {
                          char In = Wire.read();
                          if (In == ',')  {
                            //green2
                            for (int I = 0; I <= 3; I++)  {
                              char In = Wire.read();
                              if (In == ',')  {
                                //blue2
                                for (int I = 0; I <= 3; I++)  {
                                  char In = Wire.read();
                                  if (In == ',')  {
                                    //red3
                                    for (int I = 0; I <= 3; I++)  {
                                      char In = Wire.read();
                                      if (In == ',')  {
                                        //green3
                                        for (int I = 0; I <= 3; I++)  {
                                          char In = Wire.read();
                                          if (In == ',')  {
                                            //blue3
                                            for (int I = 0; I <= 3; I++)  {
                                              char In = Wire.read();
                                              if (In == '.')  {
                                                return;
                                              } else
                                                Blue3 = String(Blue3 + In);
                                              blue3 = Blue3.toInt();
                                            }
                                          }
                                          else if (In == '.')  {
                                            return;
                                          } else
                                            Green3 = String(Green3 + In);
                                          green3 = Green3.toInt();
                                        }
                                      }
                                      else if (In == '.')  {
                                        return;
                                      } else
                                        Red3 = String(Red3 + In);
                                      red3 = Red3.toInt();
                                    }
                                  }
                                  else if (In == '.')  {
                                    return;
                                  } else
                                    Blue2 = String(Blue2 + In);
                                  blue2 = Blue2.toInt();
                                }
                              }
                              else if (In == '.')  {
                                return;
                              } else
                                Green2 = String(Green2 + In);
                              green2 = Green2.toInt();
                            }
                          }
                          else if (In == '.')  {
                            return;
                          } else
                            Red2 = String(Red2 + In);
                          red2 = Red2.toInt();
                        }
                      }
                      else if (In == '.')  {
                        return;
                      } else
                        Blue1 = String(Blue1 + In);
                      blue1 = Blue1.toInt();
                    }
                  }
                  else if (In == '.')  {
                    return;
                  } else
                    Green1 = String(Green1 + In);
                  green1 = Green1.toInt();
                }
              }
              else if (In == '.')  {
                return;
              } else
                Red1 = String(Red1 + In);
              red1 = Red1.toInt();
            }
          }
          else if (In == '.')  {
            return;
          } else
            Wt = String(Wt + In);
          WT = Wt.toInt();
        }
      }
      else if (In == '.')  {
        return;
      }
      Data = String(Data + In);
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

void rainbow(uint8_t wait, int bright) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255, bright));
    }
    strip.show();
    delay(wait);
  }
}
void randm(uint8_t wait, int bright) {
  uint16_t i;
  for (i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, random(0, bright), random(0, bright), random(0, bright));
  }
  strip.show();
  delay(wait);
}

void rainbowCycle(uint8_t wait, int bright) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255, bright));
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
void theaterChaseRainbow(uint8_t wait, int bright) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255, bright)); //turn every third pixel on
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

void singleScan(int r, int g, int b, int Delay) {
  int x;
  for (int i = 0; i < strip.numPixels() * 2; i++) {
    if (x > (strip.numPixels() * 2) - 2) {
      x = 0;
    }
    x++;
    int j = x - (strip.numPixels() - 1);
    j = abs(j);
    strip.clear();
    strip.setPixelColor(abs(j), r, g, b);
    strip.show();
    delay(Delay);
  }
}
void dualScan(int r, int g, int b, int Delay) {
  int x;
  for (int i = 0; i < strip.numPixels() * 2; i++) {
    if (x > (strip.numPixels() * 2) - 2) {
      x = 0;
    }
    x++;
    int j = x - (strip.numPixels() - 1);
    j = abs(j);
    strip.clear();
    strip.setPixelColor(abs(j), r, g, b);
    strip.setPixelColor(strip.numPixels() - (j + 1), r, g, b);
    strip.show();
    delay(Delay * 10);
  }
}

void twinkle(int r, int g, int b, int Delay) {
  strip.clear();
  for (int i = random(strip.numPixels() / 5, strip.numPixels() / 2); i > 1; i--) {
    strip.setPixelColor(random(strip.numPixels()), r, g, b);
    strip.show();
    delay(Delay * 10);
  }
}

void twinkleRandom(int Delay, int bright) {
  twinkle(random(0, bright), random(0, bright), random(0, bright), Delay);
}

void sparkle(int r, int g, int b, int rf, int gf, int bf, int Delay) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, r, g, b);
  }
  if (random(10) < 2) {
    for (int i = 0; i < max(1, strip.numPixels() / 3); i++) {
      strip.setPixelColor(random(strip.numPixels()), rf, gf, bf);
    }
    delay(20);
  } else {
    delay(Delay);
  }
  strip.show();
}

uint32_t Wheel(byte WheelPos, int bright) {
  int light = 255 / bright;
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(round((255 - WheelPos * 3) / light), 0, round((WheelPos * 3) / light));
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, round((WheelPos * 3) / light), round((255 - WheelPos * 3) / light));
  }
  WheelPos -= 170;
  return strip.Color(round((WheelPos * 3) / light), round((255 - WheelPos * 3) / light), 0);
}

void help()   {
  Serial.println("Commands: [command],[waittime],[red1],[green1],[blue1],[red2],[green2],[blue2],[red3],[green3],[blue3]");
  Serial.println("Rainbows: rbc (RainbowCycle) , rb (Rainbow)");
  Serial.println("Random: rdc (RandomCycle)");
  Serial.println("ColorWipe: 1cw (one color), 2cw (two colors), 3cw (three colors)");
  Serial.println("TheaterChase: 1tc (one color), 2tc (two colors), 3tc (three colors), tcr (rainbow)");
  Serial.println("Fade In Out: fio (one color)");
  Serial.println("Running Lights: rl (one Color)");
}

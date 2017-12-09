//This code works only completely with another I2C-connected Arduino with my programm "TheHatWireColor".
//
//Command for the I2C-lights: s,[command],[waittime],[red1],[green1],[blue1],[red2],[green2],[blue2],[red3],[green3],[blue3]
//Command for matrix-lights: tc,[command],[waittime],[red1],[green1],[blue1],[red2],[green2],[blue2],[red3],[green3],[blue3]
//Command for matrix-text: t,[text]|[red1],[green1],[blue1]
//Lighteffects (sc or tc):
//rbc,w,b. = RainbowCycle
//rb,w,b. = Rainbow
//rd,w,b. = Random
//(1-3)cw,w,c1(,c2,c3). = ColorWipe
//(1-3)tc,w,c1(,c2,c3). = TheaterChase
//tcr,w,b. = TheaterChaseRainbow
//fio,w,c1. = FadeInOut
//rl,w,c1. = RunningLights
//ss,w,c1. = SingleScan
//ds,w,c1. = DualScan
//(1-3)tw,w,c1(,c2,c3). = Twinkle
//twr,w,b. = TwinkleRandom
//sp,w,c1,c2. = Sparkle
//Texteffects (written with the definer, because Data defines the text here):
//t,Data|r,g,b. = Running text
//tr,Data|b. = Running text with random colors
//ts,Data|r,g,b. = Static letter
//tsr,Data|b,w. = Static letter with random colors
//tsrl,Data|b,w. = Random letters with random colors

#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 4

SoftwareSerial mySerial(10, 11); // RX, TX

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB            + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(64, PIN, NEO_GRB + NEO_KHZ800);

String InOut;
String SortO;
int red1 = 10;
int green1 = 0;
int blue1 = 0;
int red2 = 0;
int green2 = 0;
int blue2 = 0;
int red3 = 0;
int green3 = 0;
int blue3 = 0;
int WT = 30;
String Data;
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
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
  Serial.println("Funzt");
  mySerial.begin(38400);
  mySerial.println("Wer das liest, kann ab jetzt erzaehlen, dass er sein Handy mit einem Hut verbunden hat!");
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(matrix.Color(200, 200, 200));
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mySerial.available()) {
    mySerialEvent();
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
    Serial.print(Data);
    Serial.print("  SortOut:  ");
    Serial.print(SortO);
  }
  if (SortO == "tc")  {
    Serial.println("tc");
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
  }
  else if (SortO == "t" || SortO == "tt") {
    Serial.println("tt");
    Text(Data, matrix.Color(red1, green1, blue1));
  }
  else if (SortO == "tr") {
    Serial.println("tr");
    TextRandom(Data, red1);
  }
  else if (SortO == "ts") {
    Serial.println("ts");
    StaticText(Data, matrix.Color(red1, green1, blue1), 100);
  }
  else if (SortO == "tsr") {
    Serial.println("tsr");
    StaticTextRandom(Data, red1, green1);
  }
  else if (SortO == "tsrl") {
    Serial.println("tsr");
    StaticTextRandomLetter(Data, red1, green1);
  }

  else if (SortO == "r" || SortO == "reset") {
    Serial.println("r");
    colorWipe(strip.Color(0, 0, 0), 0);
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write("1cw,0,0,0,0.");        // sends five bytes
    Wire.endTransmission();    // stop transmitting
  }
}

void mySerialEvent()  {
  String SortB = SortO;
  String Sort = mySerial.readStringUntil(',');
  if (Sort != "s" || Sort != "sc" || Sort != "c") {
    SortO = Sort;
  }
  Serial.println(SortO);
  if (Sort == "s" || Sort == "sc" || Sort == "c") {
    Serial.println("Haeee");
    InOut = mySerial.readString();
    Serial.println(InOut);
    char buffer[50];
    InOut.toCharArray(buffer, 50);
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write(buffer);        // sends five bytes
    Wire.endTransmission();    // stop transmitting
    SortO = SortB;
  }
  else if (Sort == "tc") {
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
      char In = mySerial.read();
      if (In == ',')  {
        //WT
        for (int I = 0; I <= 3; I++)  {
          char In = mySerial.read();
          if (In == ',')  {
            //red1
            for (int I = 0; I <= 3; I++)  {
              char In = mySerial.read();
              if (In == ',')  {
                //green1
                for (int I = 0; I <= 3; I++)  {
                  char In = mySerial.read();
                  if (In == ',')  {
                    //blue1
                    for (int I = 0; I <= 3; I++)  {
                      char In = mySerial.read();
                      if (In == ',')  {
                        //red2
                        for (int I = 0; I <= 3; I++)  {
                          char In = mySerial.read();
                          if (In == ',')  {
                            //green2
                            for (int I = 0; I <= 3; I++)  {
                              char In = mySerial.read();
                              if (In == ',')  {
                                //blue2
                                for (int I = 0; I <= 3; I++)  {
                                  char In = mySerial.read();
                                  if (In == ',')  {
                                    //red3
                                    for (int I = 0; I <= 3; I++)  {
                                      char In = mySerial.read();
                                      if (In == ',')  {
                                        //green3
                                        for (int I = 0; I <= 3; I++)  {
                                          char In = mySerial.read();
                                          if (In == ',')  {
                                            //blue3
                                            for (int I = 0; I <= 3; I++)  {
                                              char In = mySerial.read();
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
  else if (Sort == "t" || Sort == "tt" || Sort == "ts" || Sort == "tr" || Sort == "tsr" || Sort == "tsrl") {
    Data = "";
    Wt = "";
    Red1 = "";
    Green1 = "";
    Blue1 = "";
    //Data
    for (int I = 0; I <= 100; I++)  {
      char In = mySerial.read();
      if (In == '|')  {
        //red1
        for (int I = 0; I <= 3; I++)  {
          char In = mySerial.read();
          if (In == ',')  {
            //green1
            for (int I = 0; I <= 3; I++)  {
              char In = mySerial.read();
              if (In == ',')  {
                //blue1
                for (int I = 0; I <= 3; I++)  {
                  char In = mySerial.read();
                  if (In == '.')  {
                    return;
                  }
                  Blue1 = String(Blue1 + In);
                  blue1 = Blue1.toInt();
                }
              }
              else if (In == '.')  {
                return;
              }
              Green1 = String(Green1 + In);
              green1 = Green1.toInt();
            }
          }
          else if (In == '.')  {
            return;
          }
          Red1 = String(Red1 + In);
          red1 = Red1.toInt();
        }
      }
      else if (In == -1)  {
        return;
      }
      Data = String(Data + In);
    }
  }
  //  else if (Sort == "help")  {
  //    help();
  //  }
}

int x    = matrix.width();
int pass = 0;

void Text(String Input, uint32_t c) {
  int maxDi;
  maxDi = Input.length() * 6;
  for (int I = 0; I <= maxDi; I++)  {
    matrix.setTextColor(c);
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(Input);
    if (--x < -maxDi) {
      x = matrix.width();
    }
    matrix.show();
    delay(100);
  }
}

void TextRandom(String Input, int bright) {
  int maxDi;
  maxDi = Input.length() * 6;
  for (int I = 0; I <= maxDi; I++)  {
    matrix.setTextColor(matrix.Color(random(0, bright), random(0, bright), random(0, bright)));
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(Input);
    if (--x < -maxDi) {
      x = matrix.width();
    }
    matrix.show();
    delay(100);
  }
}

//void TextRandom(String Input, int bright) {
//  Text(Input, matrix.Color(random(0, bright), random(0, bright), random(0, bright)));
//}

void StaticText(String Input, uint32_t c, int wait) {
  matrix.setTextColor(c);
  matrix.fillScreen(0);
  matrix.setCursor(1, 0);
  matrix.print(Input);
  matrix.show();
  delay(wait);
}

void StaticTextRandom(String Input, int bright, int wait) {
  StaticText(Input, matrix.Color(random(0, bright), random(0, bright), random(0, bright)), wait);
}

void StaticTextRandomLetter(String Input, int bright, int wait) {
  String Zeug = "";
  char Letter = random(33, 126);
  Zeug = String(Zeug + Letter);
  StaticText(Zeug, matrix.Color(random(0, bright), random(0, bright), random(0, bright)), wait);
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

void help() {
  mySerial.println("rbc,w,b = RainbowCycle");
  mySerial.println("rb,w,b = Rainbow");
  mySerial.println("rd,w,b = Random");
  mySerial.println("(1-3)cw,w,c1(,c2,c3) = ColorWipe");
  mySerial.println("(1-3)tc,w,c1(,c2,c3) = TheaterChase");
  mySerial.println("tcr,w,b = TheaterChaseRainbow");
  mySerial.println("fio,w,c1 = FadeInOut");
  mySerial.println("rl,w,c1 = RunningLights");
  mySerial.println("ss,w,c1 = SingleScan");
  mySerial.println("ds,w,c1 = DualScan");
  mySerial.println("(1-3)tw,w,c1(,c2,c3) = Twinkle");
  mySerial.println("twr,w,b = TwinkleRandom");
  mySerial.println("sp,w,c1,c2 = Sparkle");
}


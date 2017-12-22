/***************************************************
  This is a library for the Adafruit 1.8" SPI display.

This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
The 1.8" TFT shield
  ----> https://www.adafruit.com/product/802
The 1.44" TFT breakout
  ----> https://www.adafruit.com/product/2088
as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <Fonts/FreeSerif18pt7b.h>

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    7  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to -1!
#define TFT_DC     9

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
#define VT_PIN A0 
#define AT_PIN A1
int h=0;
int prevh = 0;
int hi=0;
int prevhi = 0;
unsigned long tpmasurare;  // variabila pentru memorare timp masurare (in ms)
float sumatensiune = 0.;   // valoare insumare tensiune pentru calcul medie
//float sumatensiunei = 0.; 
float sumacurent = 0.; // valoare insumare curent pentru calcul medie

int trcurent = 0;
int trtensiune = 0;
//int trtensiunei = 0;

float current = 0.;   // valoare curent
float tensiune = 0.; // valoare tensiune
//float tensiunei = 0.;
int tempPin = A2;  //LM35
int val;

//float p = 3.1415926;

void setup(void) {
  Serial.begin(9600);
  Serial.print("Hello! ST7735 TFT Test");
analogReference(INTERNAL); // punem referinta interna de 1,1V;
  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  // Use this initializer (uncomment) if you're using a 1.44" TFT
  //tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab

  // Use this initializer (uncomment) if you're using a 0.96" 180x60 TFT
  //tft.initR(INITR_MINI160x80);   // initialize a ST7735S chip, mini display

  Serial.println("Initialized");

  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(3);

  pinMode(6, INPUT); 
digitalWrite(6, HIGH);
tft.setCursor(120, 15);
tft.setTextColor(ST7735_YELLOW);
  tft.print("U-out");
  tft.setCursor(120, 50);
  tft.setTextColor(ST7735_GREEN);
  tft.print("I-out");
   tft.setCursor(20, 121);
  tft.setTextColor(ST7735_RED);
  tft.print("Temperatura cooler");
tft.drawRect(1,1,159,31,ST7735_YELLOW);
tft.drawRect(1,37,159,32,ST7735_GREEN);  
  
 // time = millis() - time;

//  Serial.println(time, DEC);
//  delay(500);

  // large block of text
 /// tft.fillScreen(ST7735_BLACK);
 // testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ST7735_WHITE);
//  delay(1000);

  // tft print function!
////  tftPrintTest();
 // delay(4000);

  // a single pixel
 // tft.drawPixel(tft.width()/2, tft.height()/2, ST7735_GREEN);
 // delay(500);

  // line draw test
 // testlines(ST7735_YELLOW);
 // delay(500);

  // optimized lines
 // testfastlines(ST7735_RED, ST7735_BLUE);
//  delay(500);

 // testdrawrects(ST7735_GREEN);
 // delay(500);
//
  //testfillrects(ST7735_YELLOW, ST7735_MAGENTA);
  //delay(500);

 // tft.fillScreen(ST7735_BLACK);
 // testfillcircles(10, ST7735_BLUE);
 // testdrawcircles(10, ST7735_WHITE);
 // delay(500);

 // testroundrects();
 // delay(500);

 // testtriangles();
 // delay(500);

 // mediabuttons();
  //delay(500);

 // Serial.println("done");
 // delay(1000);
}

void loop() {
 sumatensiune = 0;
// sumatensiunei = 0;
  sumacurent = 0;
    for (int i=1; i <= 20; i++)
  {
 trtensiune = analogRead(VT_PIN);
 //..trtensiunei = analogRead(VTi_PIN);
 sumatensiune = sumatensiune + trtensiune;
  trcurent = analogRead(AT_PIN);

  sumacurent = sumacurent + trcurent;
delay (20);  // pauza de 20ms intre masuratori
    }

// calculam valorile medii
sumacurent = sumacurent/20.;
sumatensiune = sumatensiune/20.;
//sumatensiunei = sumatensiunei/20.;
  //tensiune = (sumatensiune * (5.0 / 1023.0) * 5.0)/.5;
  tensiune=(float)(67.1+.974)/.974*1.06*sumatensiune/1023;
 // tensiunei=(float)(67.3+.98)/.98*5*sumatensiunei/1024;
 // voltage=tensiune
 // current = (sumacurent * (5.0 / 1023.0))/0.02;
 current=(float)1.06/0.05*sumacurent/1023;
 // current=curent
  
//  float watts = 18.3-voltage * current;
 // sumatensiune=sumatensiune+voltage;
 // sumacurent=sumacurent+current;
delay(20);
  val = analogRead(tempPin);
//float mv = ( val/1023.0)*1100; 
float mv=val/9.31;
//float cel = mv/10;
float cel = mv;  
 delay(200); 
 tft.setCursor(10, 110);
  tft.setTextColor(ST7735_RED);
  tft.setFont(&FreeSerif18pt7b);
  tft.setTextSize(1);
  tft.fillRect(0,90,95,30,ST7735_BLACK);
   
  tft.println(cel); 
   tft.setCursor(105, 115);
    tft.print("C");
     tft.drawCircle(100, 95, 3, ST7735_RED);
  //tft.setFont();
  
  tft.setCursor(3, 28);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(1);
  
  tft.fillRect(2,2,90,28,ST7735_BLACK);
  tft.println(tensiune+.2);
   tft.setCursor(90, 28);
   tft.print("V");
//tft.setFont();

  tft.setCursor(15, 65);
  tft.setTextColor(ST7735_GREEN);
  tft.fillRect(3,40,90,27,ST7735_BLACK);
  tft.setTextSize(1);
  tft.println(current/2);
  tft.setCursor(90, 65);
   tft.print("A");
tft.setFont();
  
   if (cel > 45)
  {digitalWrite(2, HIGH); 
  tft.setCursor(20, 75);
 tft.setTextColor(ST7735_WHITE);
   tft.fillRect(0,73,125,15,ST7735_BLACK);
  tft.print("Ventilator pornit");
 
  }
   else

   tft.fillRect(0,73,125,15,ST7735_BLACK);

  if (cel < 35)
  digitalWrite(2, LOW);
  
  delay(500);
  
 
}
/*void loop() {
  tft.invertDisplay(true);
  delay(500);
  tft.invertDisplay(false);
  delay(500);
}

void testlines(uint16_t color) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, 0, x, tft.height()-1, color);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, 0, tft.width()-1, y, color);
  }

  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, 0, 0, y, color);
  }

  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, tft.height()-1, x, 0, color);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
  }

  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
  }
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  tft.fillScreen(ST7735_BLACK);
  int color = 0xF800;
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(t = 0 ; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects() {
  tft.fillScreen(ST7735_BLACK);
  int color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = tft.width()-2;
    int h = tft.height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(ST7735_GREEN);
  tft.print(p, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST7735_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST7735_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST7735_WHITE);
  tft.print(" seconds.");
}

void mediabuttons() {
  // play
  tft.fillScreen(ST7735_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST7735_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);
}
*/

#include "ssd1306.h"
#include <Wire.h>
#include <SPI.h>

const unsigned char PROGMEM logo_bmp[32]=
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};

SSD1306* SSD1306::instance = NULL;

SSD1306* SSD1306::getInstance(void)
{
  if (instance == NULL)
  {
    instance = new SSD1306();
  }
  return instance;
}

SSD1306::SSD1306(void)
{
  // OLED display width, in pixels
  screen.width  = SSD1306_LCDWIDTH ;
  // OLED display height, in pixels
  screen.height = SSD1306_LCDHEIGHT ;
  
  logo.width  = 16U;
  logo.height = 16U;

  // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
  display = new Adafruit_SSD1306(screen.width, screen.height, &Wire, -1);
}

SSD1306::~SSD1306(void)
{
  free(display);
  free(instance);
}

bool SSD1306::init(void)
{
  bool initialized = false;

  Serial.println(logo.width);
  Serial.println("SSD1306 init has been started");

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  // Address 0x3C for 128x32
  if( (display->begin(SSD1306_SWITCHCAPVCC, 0x3C)) == false)
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
    //this->~SSD1306();
    return initialized;
  }

  Serial.println("SSD1306 display");

  // Show initial display buffer contents on the screen, the library initializes this with an Adafruit splash screen.
  display->display();
  delay(2000);

    welcomePage();

  // Show the display buffer on the screen. You MUST call display() after drawing commands to make them visible on screen!
  display->display();
  delay(2000);

  Serial.println(F("SSD1306 allocation successful"));
  initialized = true;
  return initialized;
}

void SSD1306::welcomePage(void)
{
  display->clearDisplay();
  display->setCursor(0,0);
  display->setTextSize(2);
  display->setTextColor(WHITE);

  display->print("Smart boi");
  display->display();
  delay(1000);

  display->startscrollleft(0x00, 0x0F);
  delay(4400);
  display->stopscroll();  
}

void SSD1306::mainPage(float t, float h)
{
  display->clearDisplay();
  display->setCursor(0,0);
  display->setTextSize(1);

  display->println(F(""));
  display->print(F("Temperature: "));
  display->println(t);
  display->print(F("Humidity: "));
  display->print(h);

  display->display();
}

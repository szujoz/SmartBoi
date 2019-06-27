#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
typedef struct ScreenItem
{
  uint8_t height;
  uint8_t width;
} ScreenItem;

class SSD1306
{
  public:
    static SSD1306* getInstance(void);
  
  private:
    static SSD1306*  instance;
  
    ScreenItem       screen;
    ScreenItem       logo;
    Adafruit_SSD1306 *display;

    static const unsigned char PROGMEM logo_bmp[32];

    SSD1306(void);

  public:
    ~SSD1306(void);

    bool init(void);
    void welcomePage(void);
    void mainPage(float t, float h);
};

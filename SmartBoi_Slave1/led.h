enum LED_STATE
{
  eLED_OFF  = 0,
  eLED_ON
};

class LED
{
  private:
    int       pin;
    LED_STATE state;

  public:
    LED(int Pin);
    void init(void);
    
    int  getPin(void);
    void turnON(void);
    void turnOFF(void);
    void toggle(void);
};

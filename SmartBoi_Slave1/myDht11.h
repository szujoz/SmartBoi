#include <Arduino.h>

///KY015 DHT11 Temperature and humidity sensor 
class DHT11
{
  private:
      int   pin;
      float temperature;
      float humidity;

      uint8_t readData(void);

  public:
      DHT11(int Pin);
      void init(void);
      
      int getPin(void);

      void process(void);
};

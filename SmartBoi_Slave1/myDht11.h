#include <Arduino.h>

///KY015 DHT11 Temperature and humidity sensor
#include <DHT.h>
#include <DHT_U.h>

class DHT_11
{
  private:
      static DHT_11* instance;

      DHT*  dht11;
      int   pin;
      float temperature;
      float humidity;
      float humiture;

      DHT_11(const int Pin);

  public:
      static DHT_11* getInstance(const int Pin);

      ~DHT_11(void);
      
      void init(void);

      int getPin(void);
      float getTempr(void);
      float getHumid(void);

      void process(void);
};

#include "myDht11.h"

DHT_11* DHT_11::instance = NULL;

DHT_11::DHT_11(int Pin)
{
  pin          = Pin;
  temperature  = 0.0f;
  humidity     = 0.0f;
  humiture     = 0.0f;

  dht11 = new DHT(Pin, DHT11);
}

DHT_11* DHT_11::getInstance(const int Pin)
{
  if (instance == NULL)
  {
    instance = new DHT_11(Pin);
  }

  return instance;
}

DHT_11::~DHT_11(void)
{
  free(dht11);
  free(instance);
}

void DHT_11::init(void)
{
  dht11->begin();
}

int DHT_11::getPin(void)
{
  return pin;
}

float DHT_11::getTempr(void)
{
  return temperature;
}

float DHT_11::getHumid(void)
{
  return humidity;
}

/// TODO debug
void DHT_11::process(void)
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht11->readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht11->readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht11->readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht11->computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht11->computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  temperature = t;
  humidity = h;
  humiture = hic;
}

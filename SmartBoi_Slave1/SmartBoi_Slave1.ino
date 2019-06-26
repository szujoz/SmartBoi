#include <DHT.h>
#include <DHT_U.h>
#include "led.h"
#include "ssd1306.h"

// General infos
#define topologyId      (1U)
#define unitName        ("Beka")
#define temprSensorPin  (14U)     // D5
#define ledStatusPin    (16U)     // D0

// Components
DHT dht(temprSensorPin, DHT11);
//DHT11    sensor(temprSensorPin);
LED      statusLed(ledStatusPin);
SSD1306* lcd;

void setup()
{
  // Serial communication
  Serial.begin(115200);
  Serial.println();
  Serial.print(unitName);
  Serial.print(" [Slave ID: ");
  Serial.print(topologyId);
  Serial.println("] is starting up");

  delay(1000);

  //sensor.init(); 
  dht.begin();
  statusLed.init();
  lcd->getInstance();
}

void loop()
{
  statusLed.toggle();
  //sensor.process();
  Serial.println("ping");
  delay(1000);

    // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

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
}

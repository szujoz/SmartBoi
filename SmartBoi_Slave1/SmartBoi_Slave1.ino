#include "dht11.h"
#include "led.h"

// General infos
#define topologyId      (1U)
#define unitName        ("Beka")
#define temprSensorPin  (15U)     // D8
#define ledStatusPin    (13U)     // D7

// Components
DHT11 sensor(temprSensorPin);
LED   statusLed(ledStatusPin);

void setup()
{
  // Serial communication
  Serial.begin(115200);
  Serial.println();
  Serial.print(unitName);
  Serial.print(" [Slave ID: ");
  Serial.print(topologyId);
  Serial.println("] is starting up");

  sensor.init(); 
  statusLed.init();
}

void loop()
{
  statusLed.toggle();
  sensor.process();
  Serial.println("ping");
  delay(1000);
}

#include "myDht11.h"
#include "led.h"
#include "ssd1306.h"

// General infos
#define TOPOLOGY_ID      (1U)
#define UNIT_NAME        ("Beka")
#define DHT11_SENS_PIN   (14U)     // D5
#define LED_STATUS_PIN   (16U)     // D0

// Components
SSD1306* lcd      = SSD1306::getInstance();
DHT_11*  sensDHT  = DHT_11::getInstance(DHT11_SENS_PIN);
LED      statusLed(LED_STATUS_PIN);

void setup()
{
  // Serial communication
  Serial.begin(115200);
  Serial.println();
  Serial.print(UNIT_NAME);
  Serial.print(" [Slave ID: ");
  Serial.print(TOPOLOGY_ID);
  Serial.println("] is starting up");

  delay(200);

  Serial.println("Initialize modules");
  statusLed.init();
  lcd->init();
  sensDHT->init();

  Serial.println("Program setup is finished");
}

void loop()
{
  statusLed.toggle();
  sensDHT->process();
  lcd->mainPage(sensDHT->getTempr(),sensDHT->getHumid());
  Serial.println("ping");
  delay(1000);
}

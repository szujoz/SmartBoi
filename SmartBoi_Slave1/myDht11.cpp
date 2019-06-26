#include "myDht11.h"

DHT11::DHT11(int Pin)
{
  pin          = Pin;
  temperature  = 0.0f;
  humidity     = 0.0f;
}

void DHT11::init(void)
{
  pinMode(pin, OUTPUT);
  // Bus down, send start signal.
  digitalWrite(pin, LOW);
  // Delay greater than 18ms, so DHT11 start signal can be detected.
  delay(30); 
}

int DHT11::getPin(void)
{
  return pin;
}

/// TODO debug
void DHT11::process(void)
{
  uint8_t data[5];
  
  digitalWrite(pin, LOW); // bus down, send start signal
  delay(30); // delay greater than 18ms, so DHT11 start signal can be detected
 
  digitalWrite(pin, HIGH);
  delayMicroseconds(40); // Wait for DHT11 response
 
  pinMode(pin, INPUT);
  /// TODO timeout
  /*for(int i = 0; i < 200; i++)
  {
    if (digitalRead(pin) == HIGH)   break;
  }*/
  while (digitalRead(pin) == HIGH);
  delayMicroseconds(80); // DHT11 response, pulled the bus 80us
  if (digitalRead(pin) == LOW);
    delayMicroseconds(80); // DHT11 80us after the bus pulled to start sending data

  /// TODO 5th is crc?
  for (int i = 0; i < 4; i ++) // receive temperature and humidity data, the parity bit is not considered
    data[i] = readData();

  humidity    = ((float)data[0]) + ((float)((int)data[1])/100.0f);
  temperature = ((float)data[2]) + ((float)((int)data[3])/100.0f);

  Serial.print(data[0]);
  Serial.print("  ");
  Serial.print(data[1]);
  Serial.print("  ");
  Serial.print(data[2]);
  Serial.print("  ");
  Serial.print(data[3]);
  Serial.print("  Derived: ");
  Serial.print(temperature);
  Serial.print(" ");
  Serial.println(humidity);
 
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH); // send data once after releasing the bus, wait for the host to open the next Start signal
}

///TODO debug
uint8_t DHT11::readData(void)
{
  uint8_t data;

  for (int i = 0; i < 8; i ++)
  {
    if (digitalRead(pin) == LOW)
    {
      while (digitalRead(pin) == LOW);     // wait for 50us
        delayMicroseconds(30);             // determine the duration of the high level to determine the data is '0 'or '1'
      
      if (digitalRead(pin) == HIGH)
        data |= (1 << (7-i));               // high front and low in the post

      while (digitalRead (pin) == HIGH);    // data '1 ', wait for the next one receiver
     }
  }
  
  return data;
}

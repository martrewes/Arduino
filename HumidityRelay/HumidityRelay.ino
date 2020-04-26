#include <SimpleDHT.h>

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
int pinRelay = 4;
SimpleDHT11 dht11;

void setup() {
  Serial.begin(9600);

pinMode(pinRelay, OUTPUT);
digitalWrite(pinRelay, LOW);
}
void loop() {
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    return;
  }
  
  Serial.println("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" %");
  
  if ((int)humidity > 80) {
    Serial.print("Over Humid, activated relay");
    digitalWrite(pinRelay, HIGH);
  }
  
  if ((int)humidity < 60){
    Serial.println("Humidity normal, relay off");
    digitalWrite(pinRelay, LOW);
  }
  
  // DHT11 sampling rate is 1hz
  delay(2000);
}

#include <SimpleDHT.h>
#include <LiquidCrystal.h>

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
LiquidCrystal lcd(8, 7, 5, 4, 3, 2);

int pinDHT11 = 10;
int pinRelay = 11;
const char *txtState = "Relay Deactivate";

SimpleDHT11 dht11;



void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
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
  lcd.clear();
  Serial.println("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" %");
  lcd.print("Tm: "); lcd.print((int)temperature);lcd.print("*C "); lcd.print("Hu: ");  lcd.print((int)humidity); lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print(txtState);
  
  if ((int)humidity > 60) {
    Serial.print("Over Humid, activated relay");
    digitalWrite(pinRelay, HIGH);
    txtState = "Relay Activated";
  }
  
  if ((int)humidity < 50){
    Serial.println("Humidity normal, relay off");
    digitalWrite(pinRelay, LOW);
    txtState = "Relay Deactivate";
  }
  
  // DHT11 sampling rate is 1hz
  delay(2000);
}

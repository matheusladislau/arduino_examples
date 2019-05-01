#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp180;

void setup() {
  Serial.begin(9600);
  if (!bmp180.begin()) {
    Serial.println("Sensor nao encontrado !!");
    while (1) {}
  }
}
   
void loop(){
   Serial.print("Temperatura : ");
   Serial.print(bmp180.readTemperature(),1);
   Serial.println(" C");

  Serial.print("Pressao : ");
  Serial.print(bmp180.readPressure());  
  Serial.println(" Pa");
    
  delay(3000);
  Serial.println("");
}

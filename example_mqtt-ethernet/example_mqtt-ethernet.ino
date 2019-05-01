#include <SPI.h>
#include <PubSubClient.h>
#include <Ethernet.h>

// Variables
float tempC;
String pubstring;
unsigned long time;
char message_buffer[100];

// Network Settings
// MAC address of ethernet shield
// Look for it on a sticket at the bottom of the shield. 
// Old Arduino Ethernet Shields or clones may not have a dedicated MAC address. Set any hex values here.
byte MAC_ADDRESS[] = {  0x78, 0x45, 0xC4, 0xAA, 0xE5, 0x6F };

// IP address of MQTT server
byte MQTT_SERVER[] = {85,119,83,194};
byte ip[] = {192,168,1,115};
EthernetClient ethClient;
PubSubClient client;


void setup()
{  
  // Initilize serial link for debugging
  Serial.begin(9600);
  
  Ethernet.begin(MAC_ADDRESS,ip);
  //Ethernet.begin(MAC_ADDRESS);
  
  Serial.print("Local IP=");
  Serial.println(Ethernet.localIP());
  client  = PubSubClient("mqtt_server.com", 12131, callback, ethClient);
  Serial.print("conectado ao mqtt");
  }

void loop()
{
  if (!client.connected())
  {
    Serial.println("conectando usuario");
    client.connect("clientID", "user", "password");
    //client.connect("sfo-arduino");
    client.publish("teste", "I'm alive!");
  }
 // else{  
  
  if (millis() > (time + 5000)) {
    time = millis();
    tempC = 10;
    pubstring = String(tempC);
    pubstring.toCharArray(message_buffer, pubstring.length() + 1);
    client.publish("arduino/temperature",message_buffer);
    //Serial.println("published!");
    //Serial.println(message_buffer);
}
    
  // MQTT client loop processing
  client.loop();
}

// Handles messages arrived on subscribed topic(s)
void callback(char* topic, byte* payload, unsigned int length) {
}

#include "UbidotsEsp32Mqtt.h"

const char* WIFI_SSID = "----";           // Put here your Wi-Fi SSID
const char* WIFI_PASS = "----";           // Put here your Wi-Fi password

const char* UBIDOTS_TOKEN = "TOEKN";  // Put here your Ubidots TOKEN
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

int counter=0;
long var1=0;
long var2=0;
long var3=0;
long var4=0;
long randomNumber;
  
void setup() {

  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS); 
}

void loop() {
  
  randomNumber = 1.0/(random(1,100));
 
  counter = counter;
  var1 = 1555 + 100*randomNumber; //simulacion de la altitud
  var2 = 27 + 10*randomNumber; //simulacion de la temperatura
  var3 = 30 + 10*randomNumber; //simulacion de la humedad
  var4 = 1024 + 100*randomNumber; //simulacion presion

  ubidots.add("counter", counter);
  ubidots.add("Var1", counter);  // Change for your variable name
  ubidots.add("Var2", counter);
  ubidots.add("Var3", counter);
  ubidots.add("Var4", counter);
  
  bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id

  counter++;
  delay(5000);
}

#include "UbidotsEsp32Mqtt.h"
#include <nRF24L01.h>
#include <RF24.h>

const char *UBIDOTS_TOKEN = "BBFF-rpFsDqYybIZLSdQmZbbiYnlTG1oqoJ";  // Put here your Ubidots TOKEN
const char *WIFI_SSID = "RED_PC";      // Put here your Wi-Fi SSID
const char *WIFI_PASS = "3173192494";      // Put here your Wi-Fi password
const char *DEVICE_LABEL = "esp32_iot";   // Put here your Device label to which data  will be published
const char *VARIABLE_LABEL1 = "Counter";
const char *VARIABLE_LABEL2 = "var1";
const char *VARIABLE_LABEL3 = "var2";
const char *VARIABLE_LABEL4 = "var3";
const char *VARIABLE_LABEL5 = "var4";// Put here your Variable label to which data  will be published

const int PUBLISH_FREQUENCY = 5000; // Update rate in milliseconds

unsigned long timer;

bool stade = HIGH;

Ubidots ubidots(UBIDOTS_TOKEN);

RF24 radio(4, 5); 
const uint64_t address = 0xE8E8F0F0E1LL;

struct MyData 
{
  int counter;
  float var1;
  float var2;
  float var3;
  float var4;
};

MyData data;


void setup()
{
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_250KBPS);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver

  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setup();
  ubidots.reconnect();

  delay(1000);
  Serial.println('Receiver NFR24 + Ubidtos');
  timer = millis();
}

void loop()
{
  if (!ubidots.connected())
  {
    ubidots.reconnect();
  }

  if ( (millis() - timer) > PUBLISH_FREQUENCY) // triggers the routine every 5 seconds
  {

    if ( radio.available() ) 
    {
      radio.read(&data, sizeof(MyData));
     
      digitalWrite(2, stade);
      stade = !stade;

      Serial.print("Receiver: ");
      Serial.print(data.counter);
      Serial.print(" ");
      Serial.print(data.var1);
      Serial.print(" ");
      Serial.print(data.var2);
      Serial.print(" ");
      Serial.print(data.var3);
      Serial.print(" ");
      Serial.println(data.var4);
      
      ubidots.add(VARIABLE_LABEL1, data.counter);
      ubidots.add(VARIABLE_LABEL2, data.var1);
      ubidots.add(VARIABLE_LABEL3, data.var2);
      ubidots.add(VARIABLE_LABEL4, data.var3);
      ubidots.add(VARIABLE_LABEL5, data.var4);
      ubidots.publish(DEVICE_LABEL);
      
      timer = millis();
     }
  }
  ubidots.loop();

}

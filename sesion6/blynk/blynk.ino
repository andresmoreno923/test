/*************************************************************

  You can use this sketch as a debug tool that prints all incoming values
  sent by a widget connected to a Virtual Pin 1 in the Blynk App.

  App project setup:
    Slider widget (0...100) on V1
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLLPqqHa-W"
#define BLYNK_DEVICE_NAME "relees"
#define BLYNK_AUTH_TOKEN "DVzfmjDJfIxuP6f1IR8pfZAKE3P63Ozv"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

const byte relee1 = 2;
const byte relee2 = 33;
const byte relee3 = 25;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "RED_PC";
char pass[] = "andres1992";

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin 1
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.print("V1 : ");
  Serial.println(pinValue);
  digitalWrite(relee1,pinValue);
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.print("V2 : ");
  Serial.println(pinValue);
  digitalWrite(relee2,pinValue);
}

BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.print("V3 : ");
  Serial.println(pinValue);
  digitalWrite(relee3,pinValue);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  delay(100);

  pinMode(relee1,OUTPUT);
  pinMode(relee2,OUTPUT);
  pinMode(relee3,OUTPUT);


  digitalWrite(relee1,HIGH);
  digitalWrite(relee2,HIGH);
  digitalWrite(relee3,HIGH);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
}

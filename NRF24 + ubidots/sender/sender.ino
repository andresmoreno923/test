#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(4, 5);
const uint64_t address = 0xE8E8F0F0E1LL;

int counter;
float var1;
float var2;
float var3;
float var4;

long randomNumber;

bool stade = HIGH;

struct MyData {
  int counter;
  float var1;
  float var2;
  float var3;
  float var4;
};
MyData data;

void setup() {

  pinMode(2, OUTPUT);
  Serial.begin(115200);

  radio.begin();                   //Starting the Wireless communication
  radio.openWritingPipe(address);  //Setting the address where we will send the data
  radio.setPALevel(RF24_250KBPS);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();           //This sets the module as transmitter
}

void loop() {

  digitalWrite(2, stade);
  stade = !stade;
  randomNumber = random(1, 100);

  var1 = (1555 + (1.0 / 10.0) * randomNumber);
  var2 = (27 + (10.0 / 100) * randomNumber);
  var3 = (30 + (10.0 / 100) * randomNumber); 
  var4 = (1024 + (1.0 / 10) * randomNumber);

  data.counter = counter;
  data.var1 = var1;  //simulacion de la altitud
  data.var2 = var2;     //simulacion de la temperatura
  data.var3 = var3;    //simulacion de la humedad
  data.var4 = var4;    //simulacion presion

  radio.write(&data, sizeof(MyData));
  
  Serial.print("Sender: ");
  Serial.print(counter);
  Serial.print(" ");
  Serial.print(var1);
  Serial.print(" ");
  Serial.print(var2);
  Serial.print(" ");
  Serial.print(var3);
  Serial.print(" ");
  Serial.println(var4);
  

  counter++;
  delay(5000);
}
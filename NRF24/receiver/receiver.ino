/* Prueba distancia NRF24L01 programa del Receptor
    Module // Arduino UNO,NANO
    GND    ->   GND
    Vcc    ->   3.3V Fuente Externa
    CE     ->   D9
    CSN    ->   D10
    CLK    ->   D13
    MOSI   ->   D11
    MISO   ->   D12
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>      // debe descargar la libreria RF24.h

const uint64_t pipeIn = 0xE8E8F0F0E1LL;     //Mismo codigo en el RX y TX

RF24 radio(4,5);  // asigna pines para CSN y CE

struct Received_data {
  byte ch1;
};

int ch1_value = 0;
Received_data received_data;

void setup()
{
  pinMode(2, OUTPUT);        // salida digital 7 para el buzzer
  Serial.begin(9600);
  received_data.ch1 = 127;   // canal 127
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);   // configura 250KBPS
  radio.openReadingPipe(1,pipeIn);
  radio.startListening();

}
unsigned long last_Time = 0;
void receive_the_data() // funcion que recive el dato y lo almacena en la variable  receive_data
{
  while ( radio.available() ) {
  radio.read(&received_data, sizeof(Received_data));
  last_Time = millis(); 
}
}
void loop()
{
  receive_the_data();
  ch1_value = map(received_data.ch1,0,255,1000,2000); // convierte el dato recivido a un valor entre 1000 y 2000
  Serial.println(ch1_value);      // escribe el valor en el monitor serial                    
  if (ch1_value <=1100){          // si el valor es alto o bajo 
    digitalWrite(2,1);       // activa buzzer
  }
  else{
    digitalWrite(2,0);       // apaga el buzzer
  }
  //delay(100);          // espera 100ms antes de leer el proximoo dato
}

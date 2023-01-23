#include <WiFi.h>
#include <WebServer.h>


/*Put your SSID & Password*/

const char* ssid = "HUAWEI Mate 10uuuuuuuuyuuyu";  // Enter SSID here
const char* password = "1b3635642c6f";  //Enter Password here

WebServer server(80);

long randomNumber;      

float Temperature = 32.0;
float Humidity = 80.0;
 
void setup() {

  Serial.begin(115200);
  delay(100);
        

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

}


void loop() {
  
  server.handleClient();
  
} 

void handle_OnConnect() {

  randomNumber = random(1, 100);
  Temperature = (27 + (10.0 / 100) * randomNumber);
  Humidity = (80 + (10.0 / 100) * randomNumber);
  server.send(200, "text/html", SendHTML(Temperature,Humidity)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat,float Humiditystat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>ESP32 Weather Report</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-tolor: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-sp: 50px;} h1 {coize: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>ESP32 Weather Report</h1>\n";
  
  ptr +="<p>Temperature: ";
  ptr +=Temperaturestat;
  ptr +="°C</p>";
  ptr +="<p>Humidity: ";
  ptr +=Humiditystat;
  ptr +="%</p>";
  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";

  Serial.println(ptr);
  return ptr;
}
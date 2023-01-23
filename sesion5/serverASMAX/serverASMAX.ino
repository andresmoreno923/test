
// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

float BPM, SpO2;

#define REPORTING_PERIOD_MS     1000

// Replace with your network credentials
const char* ssid = "RED_PC";
const char* password = "andres1992";

PulseOximeter pox;
uint32_t tsLastReport = 0;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readVAR1() {
  return String(BPM);
}

String readVAR2() {
  return String(SpO2);
}

void onBeatDetected() {
    Serial.println("♥ Beat!");
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <div align="center"><img src="https://seeklogo.com/images/U/universidad-autonoma-benito-juarez-de-oaxaca-logo-EC6287843D-seeklogo.com.png"></div>
  <h2>ESP32 max30100</h2>
  <p>
    <i class="fa fa-heart" style="font-size:48px;color:red"></i>
    <span class="dht-labels">Ritmo Cardiaco</span> 
    <span id="var1">%VAR1%</span>
    <sup class="units">BPM</sup>
  </p>
  <p>
    <i class="fa-solid fa-mask-ventilator" style="font-size:48px;color:red"></i>
    <span class="dht-labels">Saturacion</span>
    <span id="var2">%VAR2%</span>
    <sup class="units">&percnt;</sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("var1").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/var1", true);
  xhttp.send();
}, 1000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("var2").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/var2", true);
  xhttp.send();
}, 1000 ) ;
</script>
</html>)rawliteral";

// Replaces placeholder with DHT values
String processor(const String& var){
  //Serial.println(var);
  if(var == "VAR1"){
    return readVAR1();
  }
  else if(var == "VAR2"){
    return readVAR2();
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  delay(100);


    WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/var1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readVAR1().c_str());
  });
  server.on("/var2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readVAR2().c_str());
  });

  // Start server
  server.begin();

    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
        pox.setOnBeatDetectedCallback(onBeatDetected);
    }

  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
}
 
void loop(){
  
    pox.update();
    BPM = pox.getHeartRate();
    SpO2 = pox.getSpO2();

    if (millis() - tsLastReport > REPORTING_PERIOD_MS)
    {

      Serial.print("BPM: ");
      Serial.println(BPM);

      Serial.print("SpO2: ");
      Serial.print(SpO2);
      Serial.println("%");

      Serial.println("*********************************");
      Serial.println();

      tsLastReport = millis();
    }
}
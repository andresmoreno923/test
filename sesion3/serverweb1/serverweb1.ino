
#include <WiFi.h>
 
//Nombre de la red
const char* nombre = "RED_PC";
 
//Password
const char* password = "3173192494";

IPAddress ip(192, 168, 137, 200); // IP estática
IPAddress gateway(192, 168, 137, 1); // Puerta de enlace.
IPAddress subnet(255, 255, 255, 0);// Red.
 
//Puerto (dejar en 80 por defecto)
WiFiServer server(80);
 
int ledPin = 2;
int value = LOW;
   
void setup() {
  Serial.begin(115200);
  delay(50); //Hay que dejar un margen de tiempo
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Conectar a la red WiFi
  WiFi.config(ip, gateway, subnet); // Configura IP estática

  WiFi.beg1in(nombre, password);
  
  while (WiFi.status() != WL_CONNECTED)
    delay(100); //aqui tambien hay que dejar un margen de tiempo
  Serial.println("Conectado a la red WiFi");
  
  // Iniciar el servidor
  server.begin();
  Serial.println("Se ha iniciado el servidor");
  
  // Escribir la direccion IP
  Serial.print("IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");
  
}
  
void loop() {
  // Comprobar si se ha conectado algun cliente
  WiFiClient client = server.available();
   
  if (client) {
    Serial.println("Nueva conexion");


  String request = client.readStringUntil('\r'); // Leo hasta retorno de carro
  Serial.println(request); //Imprimo la petición
  client.flush(); //Limpio el buffer
 
  // Interpreto lo que he recibido
 
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, 10);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, 0);
    value = LOW;
  }
    
    // Escribir las cabeceras HTML
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
   
    //Escribir el contenido que vamos a visualizar
    client.println("<html>");
    client.println("<img src='https://seeklogo.com/images/D/diseno-industrial-uis-logo-B812CF8DE9-seeklogo.com.png' width='200' height='98'>");
    
    client.println("<img src='https://upload.wikimedia.org/wikipedia/commons/2/2c/Logouis.png' width='201' height='98'>");

    client.println("");
    client.println("<br><br>");
    client.print("Natalia castellanos - Catherine Arciniegas");
    client.println("<br><br>");

    

    client.println("<iframe width='560' height='315' src='https://www.youtube.com/embed/h5z99EYHY4I' title='YouTube video player' frameborder='0' allow='accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture' allowfullscreen></iframe>");
    
    //client.println("<iframe width='560' height='315' src='https://www.youtube.com/embed/OVhmdLVVS-U' frameborder='0' allow='accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture' allowfullscreen></iframe>");
    
    client.println("<p><audio src='https://uccf7fdeb318e7e645b564c7d3d3.dl.dropboxusercontent.com/cd/0/get/A0Ahf--I4DWNNPS8pfH47BiAdEPprwB-VVkAQXq5wW22jPZiDYtzIqzfu9ZTC9VT-NOY9yAsdKEKv7UjalRLVXOpbnhO7_uyNnOF5cs8TGPdiuTddpah5aaJIFWIyYg_wi4/file?dl=1#' preload='auto' controls='controls'></audio></p>");
    client.println("<br><br>");
    
    client.print("El Vibrador  esta:  ");
 
  if(value == HIGH) {
    client.print("ON");
  } else {
    client.print("OFF");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Encender </button></a>"); // Los botones con enlace
  client.println("<a href=\"/LED=OFF\"\"><button>Apagar </button></a><br />");  
    client.println("</html>");
     
  }
}

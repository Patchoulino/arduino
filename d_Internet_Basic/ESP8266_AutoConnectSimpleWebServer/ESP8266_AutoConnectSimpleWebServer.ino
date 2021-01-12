/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

MDNSResponder mdns;

ESP8266WebServer server(80);

String webPage = "";

const int gpio0_pin = 0;
const int gpio1_pin = LED_BUILTIN;
const int gpio2_pin = 2;

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void setup(void){
  webPage += "<h1>ESP8266 Web Server</h1><p>Socket #0 <a href=\"socket0On\"><button>ON</button></a>&nbsp;<a href=\"socket0Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #1 <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #2 <a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>";
    
  // preparing GPIOs
  pinMode(gpio0_pin, OUTPUT);
  digitalWrite(gpio0_pin, LOW);
  pinMode(gpio1_pin, OUTPUT);
  digitalWrite(gpio1_pin, LOW);
  pinMode(gpio2_pin, OUTPUT);
  digitalWrite(gpio2_pin, LOW);
  
  delay(1000);
  Serial.begin(115200);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  if(!wifiManager.autoConnect("Arduino_virus")) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  } 
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  
  server.on("/socket0On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio0_pin, HIGH);
    delay(1000);
  });
  server.on("/socket0Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio0_pin, LOW);
    delay(1000); 
  });
  server.on("/socket1On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio1_pin, HIGH);
    delay(1000);
  });
  server.on("/socket1Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio1_pin, LOW);
    delay(1000); 
  });
  server.on("/socket2On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, HIGH);
    delay(1000);
  });
  server.on("/socket2Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, LOW);
    delay(1000); 
  });
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
} 

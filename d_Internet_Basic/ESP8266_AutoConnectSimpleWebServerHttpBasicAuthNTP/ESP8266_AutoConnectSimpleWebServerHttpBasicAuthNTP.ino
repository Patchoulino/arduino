/*********
  This is just a recompilation of various examples for the ESP8266:
  
  AutoConnect                https://github.com/tzapu/WiFiManager
  
  SimpleWebServer            https://github.com/esp8266/Arduino
  HttpBasicAuthentification

  NTPtimeESP                 https://github.com/SensorsIot/NTPtimeESP
  
  Gerardo Abraham Aguilar López
  abagl@outlook.com
*********/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
//WiFiManager
#include <DNSServer.h>
#include <WiFiManager.h> 
//HttpBasicAuth
#include <ArduinoOTA.h>
//NTP
#include <NTPtimeESP.h>
#define DEBUG_ON

MDNSResponder mdns;
ESP8266WebServer server(80);

NTPtime NTPch("mx.pool.ntp.org");   // Choose server pool as required

strDateTime dateTime;

const char* www_username = "user";
const char* www_password = "pass";

String webPage = "";

const int gpio0_pin = 0;
const int gpio2_pin = 2;

void refreshWebPage () {
  webPage = "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";
  webPage += "<h1>ESP8266 Web Server</h1>";
  webPage += "<p>Socket #0 <a href=\"socket0On\"><button>ON</button></a>&nbsp;<a href=\"socket0Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #0 <a href=\"socket0Toggle\"><button>Toggle</button></a>&nbsp;</p>";
  webPage += "<p>Status: "; webPage += String(digitalRead(gpio0_pin));  webPage += "</p>";
  webPage += "<p>Socket #2 <a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #2 <a href=\"socket2Toggle\"><button>Toggle</button></a>&nbsp;</p>";
  webPage += "<p>Status: "; webPage += String(digitalRead(gpio2_pin));  webPage += "</p>";
  server.send(200, "text/html", webPage);
}

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void setup(void){
  pinMode(gpio0_pin, OUTPUT);
  digitalWrite(gpio0_pin, LOW);
  pinMode(gpio2_pin, OUTPUT);
  digitalWrite(gpio2_pin, LOW);
  
  delay(1000);
  Serial.begin(9600);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  if(!wifiManager.autoConnect("IoT_Virus")) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  } 
  
  ArduinoOTA.begin();
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      refreshWebPage();
    }
  });
  
  server.on("/socket0On", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      digitalWrite(gpio0_pin, HIGH);
      refreshWebPage();
    }
  });
  server.on("/socket0Off", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      digitalWrite(gpio0_pin, LOW);
      refreshWebPage();
    }
  });
  server.on("/socket0Toggle", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      digitalWrite(gpio0_pin, !digitalRead(gpio0_pin));
      refreshWebPage();
    }
  });
  server.on("/socket2On", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      digitalWrite(gpio2_pin, HIGH);
      refreshWebPage();
    }
  });
  server.on("/socket2Off", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      digitalWrite(gpio2_pin, LOW);
      refreshWebPage();
    }
  });
  server.on("/socket2Toggle", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      digitalWrite(gpio2_pin, !digitalRead(gpio2_pin));
      refreshWebPage();
    }
  });
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){

    // first parameter: Time zone in floating point (for India); second parameter: 1 for European summer time; 2 for US daylight saving time; 0 for no DST adjustment; (contributed by viewwer, not tested by me)
  dateTime = NTPch.getNTPtime(-6.0, 0);

  // check dateTime.valid before using the returned time
  // Use "setSendInterval" or "setRecvTimeout" if required
  if(dateTime.valid){
    NTPch.printDateTime(dateTime);

    byte actualHour = dateTime.hour;
    byte actualMinute = dateTime.minute;
    byte actualsecond = dateTime.second;
    int actualyear = dateTime.year;
    byte actualMonth = dateTime.month;
    byte actualday =dateTime.day;
    byte actualdayofWeek = dateTime.dayofWeek;
  }

  if((dateTime.minute % 2) == 0){
    digitalWrite(gpio2_pin, 0);
  }
  else{
    digitalWrite(gpio2_pin, 1);
  }
  
  server.handleClient();
} 


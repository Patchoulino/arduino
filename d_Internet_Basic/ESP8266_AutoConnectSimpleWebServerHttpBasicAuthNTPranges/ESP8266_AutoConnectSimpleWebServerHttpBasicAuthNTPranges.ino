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

byte upper_threshold = 19;
byte lower_threshold = 8;

//  <a href=\"upper_19\"><button>19:00</button></a> //button
//  &nbsp                                           //tab space
void refreshWebPage () {
  webPage = "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";
  webPage += "<h1>ESP8266 Web Server</h1>";
  webPage += "<p>Upper Threshold: "; webPage += String(upper_threshold);  webPage += "</p>";
  webPage += "<p><a href=\"upper_19\"><button>19:00</button></a><a href=\"upper_20\"><button>20:00</button></a><a href=\"upper_21\"><button>21:00</button></a><a href=\"upper_22\"><button>22:00</button></a><a href=\"upper_23\"><button>23:00</button></a><a href=\"upper_00\"><button>00:00</button></a></p>";
  webPage += "<p>Lower Threshold: "; webPage += String(lower_threshold);  webPage += "</p>";
  webPage += "<p><a href=\"lower_05\"><button>05:00</button></a><a href=\"lower_06\"><button>06:00</button></a><a href=\"lower_07\"><button>07:00</button></a><a href=\"lower_08\"><button>08:00</button></a><a href=\"lower_09\"><button>09:00</button></a><a href=\"lower_10\"><button>10:00</button></a></p>";
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
  
  server.on("/upper_19", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      upper_threshold = 19;
      refreshWebPage();
    }
  });
  server.on("/upper_20", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      upper_threshold = 20;
      refreshWebPage();
    }
  });
  server.on("/upper_21", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      upper_threshold = 21;
      refreshWebPage();
    }
  });
  server.on("/upper_22", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      upper_threshold = 22;
      refreshWebPage();
    }
  });
  server.on("/upper_23", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      upper_threshold = 23;
      refreshWebPage();
    }
  });
  server.on("/upper_00", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      upper_threshold = 0;
      refreshWebPage();
    }
  });

  server.on("/lower_05", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      lower_threshold = 5;
      refreshWebPage();
    }
  });
  server.on("/lower_06", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      lower_threshold = 6;
      refreshWebPage();
    }
  });
  server.on("/lower_07", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      lower_threshold = 7;
      refreshWebPage();
    }
  });
  server.on("/lower_08", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      lower_threshold = 8;
      refreshWebPage();
    }
  });
  server.on("/lower_09", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      lower_threshold = 9;
      refreshWebPage();
    }
  });
  server.on("/lower_10", [](){
    if(!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
      ArduinoOTA.handle();
    }
    else {
      lower_threshold = 10;
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
    /*NTPch.printDateTime(dateTime);
    byte actualHour = dateTime.hour;
    byte actualMinute = dateTime.minute;
    byte actualsecond = dateTime.second;
    int actualyear = dateTime.year;
    byte actualMonth = dateTime.month;
    byte actualday =dateTime.day;
    byte actualdayofWeek = dateTime.dayofWeek;*/
    if((dateTime.hour < upper_threshold) && (dateTime.hour > lower_threshold)){
      digitalWrite(gpio2_pin, LOW);
    }
    else{
      digitalWrite(gpio2_pin, HIGH);
    }
  }
  
  server.handleClient();
} 


/* RGB web server with ESP8266
 *  Editing the version for users
* analogWrite with values received from web page
*Sasidhar P
* WiFi router that creates a fixed domain: http://rgb
* web page returns POST request with 3 RGB parameters http://192.168.1.1/
* 
*/

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include "webpage.h"
#include "WiFiLogin.h"
//#include "timeSetting.h"
#include "brightness.h"
#include "updateTime.h"
#include "requestCommand.h"
//#include "scheduleCommand.h" //now included in requestcommand.h
//#include "getUserName.h"

const char *ssid = "Capstone333";
const char *password = "87654321";
const byte DNS_PORT = 53;
const int redLED = 0;   //D3
const int greenLED = 4; //D2
const int blueLED = 5;  //D1

int userChk = 0;
//const char * puser="";
const char * ppuser="";

IPAddress apIP(192, 168, 1, 1);
//DNSServer dnsServer;
ESP8266WebServer webServer(80);
HTTPClient http;    //Declare object of class HTTPClient


//////////////////////for timesetting////////////////////////////////////////////////////////////////////////////
unsigned long timeNow = 0;
unsigned long timeLast = 0;
unsigned long tsec =0;

/*alarm setting*/
 int ahours =0;
  int aminutes = 0;
  int aday = 0;
  int asec=0;
  bool schMode = false;

//////////////////////////////////////////////////////////////////////////////////////////////////
///////////req comand/////////


//////////rea command//////

void handleColors() {
// Serial.println("handle root..");
String red = webServer.arg(0); // read RGB arguments
String green = webServer.arg(1);
String blue = webServer.arg(2);

if((red != "") && (green != "") && (blue != ""))
{
  analogWrite(redLED, 1023 - red.toInt());
  analogWrite(greenLED, 1023 - green.toInt());
  analogWrite(blueLED, 1023 - blue.toInt());
}


Serial.print("Red: ");
Serial.println(red.toInt()); 
Serial.print("Green: ");
Serial.println(green.toInt()); 
Serial.print("Blue: ");
Serial.println(blue.toInt()); 
Serial.println();

webServer.send(200, "text/html", webpage);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void handleWifiLogin(){
//String ip = (String)WiFi.localIP();
  //  Serial.println(ip);
    //webServer.send(200, "text/html", ip);
    
if(  webServer.hasArg("username") ||  webServer.hasArg("password") || webServer.arg("username") != NULL || webServer.arg("password") != NULL) {
    
Serial.println("after if in wifilogin");
String username = webServer.arg("username"); 
String password = webServer.arg("password");

Serial.println(username);
Serial.println(password);

    Serial.print("Connecting to ");
    Serial.println(webServer.arg("username"));
    String ssid2 =  webServer.arg("username");
    String password2 = webServer.arg("password");


    //WiFi.disconnect();
     char cssid[ssid2.length()+1];
     char cpass[password2.length()+1];
     ssid2.toCharArray(cssid, ssid2.length()+1);
     password2.toCharArray(cpass, password2.length()+1);
      
      //WiFi.disconnect(); //forgets any old wifi
  
    Serial.println(cssid);
    Serial.println(cpass);
     WiFi.softAPdisconnect();

     WiFi.begin(cssid, cpass); Serial.print("Connecting");
     
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  
    Serial.println(WiFi.localIP());
    //if(dnsServer.start(DNS_PORT, "rgb", WiFi.localIP())){
      //Serial.println("In Wifi login dns started");
    //}
    //Serial.println("New Wifi connected and now try rgb in your WiFi");
    analogWrite(blueLED,1023);delay(500);analogWrite(blueLED,0);delay(500);analogWrite(blueLED,1023);delay(500);analogWrite(blueLED,0);delay(500);
    analogWrite(blueLED,1023);analogWrite(blueLED,0);delay(500);
    webServer.send(200, "text/html", "New Wifi connected");
if (WiFi.status() == WL_CONNECTED){
updateTime(); }
    
}
  webServer.send(200, "text/html", WiFiLogin);
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void scheduleMode(){
//  int ahours =0;
//  int aminutes = 0;
  if( webServer.hasArg("hours") ||  webServer.hasArg("minutes") ||  webServer.hasArg("day") ||  webServer.hasArg("seconds") || webServer.hasArg("mon")|| webServer.arg("hours") != NULL || webServer.arg("minutes") != NULL|| webServer.arg("day") != NULL || webServer.arg("seconds") != NULL|| webServer.arg("mon") != NULL)
  {
    
    ahours = (webServer.arg("hours")).toInt();
    aminutes = webServer.arg("minutes").toInt();
    aday = webServer.arg("day").toInt();
    asec = webServer.arg("seconds").toInt();

    Serial.println("Alarm wait");
//    Serial.println(hours); Serial.println(minutes);
    //Serial.println(ahours);Serial.println(aminutes);

   schMode = true;
   fade(blueLED);
  fade(greenLED);

  
    webServer.send(200, "text/html", SchedulePage);
  }

  webServer.send(200, "text/html", SchedulePage);
  
}

void initTime(){
//  if(  webServer.hasArg("hours") ||  webServer.hasArg("minutes") ||  webServer.hasArg("day") ||  webServer.hasArg("seconds")|| webServer.arg("hours") != NULL || webServer.arg("minutes") != NULL|| webServer.arg("day") != NULL || webServer.arg("seconds") != NULL){
//    hours = (webServer.arg("hours")).toInt();
//    minutes = webServer.arg("minutes").toInt();
//    dayNum = webServer.arg("day").toInt();
//    seconds = webServer.arg("seconds").toInt();
//    timeSet();
    webServer.send(200, "text/html", String(pday)+":"+String(phour)+":"+String(pmin)+":"+String(psec));
  }
//
//  else{
//    
//  webServer.send(200, "text/html", initTimeWebPage+setTime3);
//  }
//}
//////////////////////////////////////////////////////////////////////////////////////////////////
void setBright(){

  webServer.send(200, "text/html", brightness);
  
}

void incBright(){
   if(ledbrightness<=950)
     ledbrightness+=50;
      analogWrite(blueLED,ledbrightness);
      analogWrite(redLED,ledbrightness);
      analogWrite(greenLED,ledbrightness);
  webServer.send(200, "text/html", brightness);
}

void decBright(){
  if(ledbrightness>=50)
     ledbrightness-=50; 
     analogWrite(blueLED,ledbrightness);
      analogWrite(redLED,ledbrightness);
      analogWrite(greenLED,ledbrightness);
  webServer.send(200, "text/html", brightness);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
void handleRoot(){
  webServer.send(200, "text/html", rootPage);
}
//////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {

pinMode(redLED, OUTPUT);
pinMode(greenLED, OUTPUT);
pinMode(blueLED, OUTPUT);

analogWrite(redLED, 0);
analogWrite(greenLED, 0);
analogWrite(blueLED, 0);

delay(1000);
Serial.begin(115200);
Serial.println();

WiFi.mode(WIFI_AP);
WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
WiFi.softAP(ssid,password);
//WiFi.config(staticIP,gateway,subnet);

// if DNSServer is started with "*" for domain name, it will reply with provided IP to all DNS request
//if(dnsServer.start(DNS_PORT, "rgb", apIP)){
//  Serial.println("Dns in setup started");
//}

webServer.on("/",handleRoot);
webServer.on("/rgb", handleColors);
webServer.on("/wifilogin", handleWifiLogin);
webServer.on("/alarm",scheduleMode);
webServer.on("/inittime",initTime);

webServer.on("/brightness",setBright);
webServer.on("/brightnessinc",incBright);
webServer.on("/brightnessdec",decBright);
webServer.begin();

testRGB();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {

//dnsServer.processNextRequest();

/////////// dcm server connection in loop ////////////////////

 


///////////--- end of dcm server connection in loop ---///////////////////

///////////////////// time setting ///////////////////////////
//timeNow = millis()/1000;
//tsec = timeNow - timeLast;
//timeLast = timeNow;
////Serial.print("tsec : ");Serial.println(tsec);
//
//if(tsec == 1) {psec = psec +1; Serial.println(tsec); /*Serial.println(psec);*/}
//
//if(psec == 60) { pmin = pmin +1; psec =0;}
//
//if(pmin == 60) { phour = phour + 1; pmin =0;}
//
//if(phour == 24) { pday = pday +1; phour = 0; updateTime();}

/////////////////////time setting ////////////////////////////

/////////////// FIFO commands eating from database //////////////
if (WiFi.status() == WL_CONNECTED) {
  //getUserName();  Serial.print("in loop the value if puser is: ");Serial.println(String(puser));
requestCommand(); //access httprc values from requestCommand.h file
updateTime();
//Serial.print("CIDi;");Serial.print(cidi); Serial.print("inti;");Serial.print(intensityi);
if(cidi == 1 ) { //brightness mode
  Serial.print("in cidi 1 ");
  analogWrite(redLED, 1023-intensityi); // R off
   analogWrite(greenLED, 1023-intensityi); // G off
  analogWrite(blueLED, 1023-intensityi); // B off
  
}

if(cidi == 2) { //rgb mode
  Serial.print("in cidi 2 ");
  analogWrite(redLED, 1023-redi); // R off
analogWrite(greenLED, 1023-greeni); // G off
analogWrite(blueLED, 1023-bluei); 
  
}
}
////////////////FIFO commands ate /////////////////
/////////////schedule visit//////////////
if (WiFi.status() == WL_CONNECTED) {
  //getUserName();
  deScheduleCommand();
scheduleCommand();
if(hourssc== phour&& minutessc == pmin) {
  
  if(statussc == 0) {Serial.print("alarm status 0");fade(greenLED);analogWrite(redLED, 1023); analogWrite(greenLED, 1023); analogWrite(blueLED, 1023);deScheduleCommand();}
  if(statussc==1){Serial.print("alarm status 1");fade(blueLED);analogWrite(redLED, 0); analogWrite(greenLED, 0); analogWrite(blueLED, 0);deScheduleCommand();}}

  
    
}
////////////schedule visit///////////
webServer.handleClient();



if(schMode == true && ahours == phour && aminutes == pmin && aday == pday && asec == psec){
  Serial.println("Alarm Alarm !! ");
    fade(greenLED);
    fade(blueLED);
    schMode = false;
  
  
}

Serial.println("Loop completed");
}//loop completed
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void testRGB() { // fade in and out of Red, Green, Blue

analogWrite(redLED, 0); // R off
analogWrite(greenLED, 0); // G off
analogWrite(blueLED, 0); // B off

fade(redLED); // R
fade(greenLED); // G
fade(blueLED); // B
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void fade(int pin) {

for (int u = 0; u < 1024; u++) {
analogWrite(pin, u);
delay(1);
}
for (int u = 0; u < 1024; u++) {
analogWrite(pin, 1023 - u);
delay(1);
}
}

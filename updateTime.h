unsigned long int pyear = 0;
unsigned long int pmonth = 0;
unsigned long int pday = 0;
unsigned long int phour = 0;
unsigned long int pmin = 0;
unsigned long int psec = 0;
String payload = "";

void updateTime(){
  HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://ec2-13-211-121-155.ap-southeast-2.compute.amazonaws.com/timeSet.php?pass=123");      //Specify request destination ?s1=1&s2=1&pass=123
   http.addHeader("Content-Type", "text/plain");  //Specify content-type header
 
   int httpCode = http.POST("Message from ESP8266");   //Send the request
    payload = http.getString();                  //Get the response payload
   //strcpy(payloadt,payload);
  //char JSONMessage[256] = payload;
  
payload.trim();
payload.remove(payload.length()-1);
payload.remove(0,1);
  //Serial.print("..");
//Serial.print(payload);Serial.print("..");
  StaticJsonBuffer<300> JSONBuffer;
  JsonObject&  parsed= JSONBuffer.parseObject(payload);

  if (!parsed.success()) {
 
  Serial.println("Parsing failed");
  return;
 
}

//[{"year":"2018","month":"04","day":"04","hour":"10","min":"53","sec":"06"}]
const char * olyear = parsed["year"];
const char * olmonth= parsed["month"];
const char * olday= parsed["day"];
const char * olhour = parsed["hour"];
const char * olmin = parsed["min"];
const char * olsec = parsed["sec"];

 pyear = atol(olyear);//olyear.toInt(); 
 pmonth = atol(olmonth);
 pday = atol(olday);
 phour = atol(olhour);
 pmin = atol(olmin);
 psec = atol(olsec);





  
   //Serial.println(httpCode);   //Print HTTP return code
   //Serial.println(payload);    //Print request response payload

Serial.print("yyyy|mon|da|hh:mm:ss ");
Serial.print(pyear);Serial.print("|");Serial.print(pmonth);Serial.print("|");Serial.print(pday);Serial.print("|");Serial.print(phour);Serial.print(":");Serial.print(pmin);Serial.print(":");Serial.println(psec);

}

String SchedulePage= ""
"<p> Enter Alarm Time</p> "
"<form action=\"/alarm\" method=\"POST\">"
//"<input type=\"text\" name=\"day\" placeholder=\"day\">"
/*"<select name=\"dayow\">"
    "<option value=\"0\">Sunday</option>"
    "<option value=\"1\">Monday</option>"
    "<option value=\"2\">Tuesday</option>"
    "<option value=\"3\">Wednesday</option>"
    "<option value=\"4\">Thursday</option>"
    "<option value=\"5\">Friday</option>"
    "<option value=\"6\">Saturday</option>"
    
 " </select>"*/
"</br><input type=\"text\" name=\"hours\" placeholder=\"Hours\">"
"</br><input type=\"text\" name=\"minutes\" placeholder=\"Minutes\">"

//"</br><input type=\"text\" name=\"month\" placeholder=\"Month\">"
"</br><input type=\"text\" name=\"seconds\" placeholder=\"seconds\">"
"</br><input type=\"text\" name=\"day\" placeholder=\"day\">"

"</br><input type=\"submit\" value=\"Set alarm\"></form></br>";



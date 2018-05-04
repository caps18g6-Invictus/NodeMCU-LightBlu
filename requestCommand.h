#include "getUserName.h"

String payloadrc = "";
int idcommandsi = 0;
int cidi = 0;
int intensityi = 0;
int yeari = 0;
int dayi = 0;
int monthi = 0;
int hoursi = 0;
int minutesi = 0;
int secondsi = 0;
int redi = 0;
int greeni = 0;
int bluei = 0;

void requestCommand(){
  getUserName();
  Serial.print("in request command the value if puser is");Serial.println(String(puser));
  HTTPClient httprc;    //Declare object of class HTTPClient
 
   httprc.begin("http://ec2-13-211-121-155.ap-southeast-2.compute.amazonaws.com/usercommand.php?pass=123&trun=1&username="+ String(puser)+"&devid="+String(dId));      //Specify request destination ?s1=1&s2=1&pass=123
   httprc.addHeader("Content-Type", "text/plain");  //Specify content-type header
 
   int httpCode = httprc.POST("Message");   //Send the request
    payloadrc = httprc.getString();                  //Get the response payload
  // strcpy(payloadrc,payload);
  //char JSONMessage[256] = payload;
  
payloadrc.trim();
payloadrc.remove(payloadrc.length()-1);
payloadrc.remove(0,1);
 Serial.print("..in RC");
Serial.print(payloadrc);Serial.print(".. RC");
  StaticJsonBuffer<600> JSONBuffer;
  JsonObject&  parsed= JSONBuffer.parseObject(payloadrc);

  if (!parsed.success()) {
 
  Serial.println("~RC");
  return;
 
}
//Serial.print("in request command cidi1 : ");
const char * idcommands = parsed["idcommands"];
const char * cid = parsed["cid"];
const char * intensity = parsed["intensity"];
const char * year = parsed["year"];
const char * day = parsed["day"];
const char * month = parsed["month"];
const char * hours = parsed["hours"];
const char * minutes = parsed["minutes"];
const char * seconds = parsed["seconds"];
const char * red= parsed["red"];
const char * green = parsed["green"];
const char * blue = parsed["blue"];
//Serial.print("in request command cidi2 : ");

 idcommandsi = atoi(idcommands);
 cidi = atoi(cid);
 intensityi = atoi(intensity);
 yeari = atoi(year);
 dayi = atoi(day);
 monthi = atoi(month);
 hoursi = atoi(hours);
 minutesi = atoi(minutes);
 secondsi = atoi(seconds);
 redi = atoi(red);
 greeni = atoi(green);
 bluei = atoi(blue);


 //Serial.print("in request command cidi : ");Serial.print(cidi);
}

//======================================schedule command file copied here==========================================================

//#include "getUserName.h"
String payloadsc = "";
int schaidsc = 0;
int statussc = 0;
int yearsc = 0;

int daysc = 0;
int monthsc = 0;
int hourssc = 0;
int minutessc = 0;
int secondssc = 0;


void scheduleCommand(){
  getUserName();
  HTTPClient httpsc;    //Declare object of class HTTPClient
 Serial.print("in r schedule command the value if puser is: ");Serial.println(String(puser));
  Serial.print("in r schedule command the value if device id is: ");Serial.println(String(dId));
   httpsc.begin("http://ec2-13-211-121-155.ap-southeast-2.compute.amazonaws.com/usersched.php?pass=123&trun=1&username="+ String(puser)+"&devid="+String(dId));      //Specify request destination ?s1=1&s2=1&pass=123
   httpsc.addHeader("Content-Type", "text/plain");  //Specify content-type header
 
   int httpCode = httpsc.POST("Message");   //Send the request
    payloadsc = httpsc.getString();                  //Get the response payload
   //strcpy(payloadt,payload);
  //char JSONMessage[256] = payload;
  
payloadsc.trim();
payloadsc.remove(payloadsc.length()-1);
payloadsc.remove(0,1);
//  Serial.print("..");
//Serial.print(payloadsc);Serial.print("..");
  StaticJsonBuffer<500> JSONBuffer;
  JsonObject&  parsed= JSONBuffer.parseObject(payloadsc);

  if (!parsed.success()) {
 
  Serial.println("~SC");
  return;
 
}

else{

const char * schaid = parsed["schaid"];
const char * statusc = parsed["status"];
const char * timec = parsed["time"];
const char * year = parsed["year"];
const char * day = parsed["day"];
const char * month = parsed["month"];
const char * hours = parsed["hours"];
const char * minutes = parsed["minutes"];
const char * seconds = parsed["seconds"];



 schaidsc = atoi(schaid);
 statussc = atoi(statusc);
 
 yearsc = atoi(year);
 daysc = atoi(day);
 monthsc = atoi(month);
 hourssc= atoi(hours);
 minutessc = atoi(minutes);
 secondssc = atoi(seconds);



 Serial.print("in schedule command status : ");Serial.print(hourssc);Serial.print(minutessc); Serial.print(" Status is: ");Serial.println(statussc);//Serial.print(daysc);
}
 
}

void deScheduleCommand(){
  getUserName();
  HTTPClient httpsc;    //Declare object of class HTTPClient
 
   httpsc.begin("http://ec2-13-211-121-155.ap-southeast-2.compute.amazonaws.com/usersched.php?pass=123&trun=3&username="+ String(puser)+"&devid="+String(dId));      
   httpsc.addHeader("Content-Type", "text/plain");  //Specify content-type header
 
   int httpCode = httpsc.POST("Message");   //Send the request
    payloadsc = httpsc.getString(); 
}





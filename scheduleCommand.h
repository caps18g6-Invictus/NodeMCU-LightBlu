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
  HTTPClient httpsc;    //Declare object of class HTTPClient
 Serial.print("in schedule command the value if puser is");Serial.println(String(puser));
  Serial.print("in schedule command the value if did is");Serial.println(String(dId));
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
Serial.print("in schedule command cidi1 : ");
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



 Serial.print("in schedule command status : ");Serial.print(hourssc);Serial.println(minutessc); Serial.print(" ");Serial.print(statussc);//Serial.print(daysc);
}
 
}

void deScheduleCommand(){
  HTTPClient httpsc;    //Declare object of class HTTPClient
 
   httpsc.begin("http://ec2-13-211-121-155.ap-southeast-2.compute.amazonaws.com/usersched.php?pass=123&trun=3");      
   httpsc.addHeader("Content-Type", "text/plain");  //Specify content-type header
 
   int httpCode = httpsc.POST("Message");   //Send the request
    payloadsc = httpsc.getString(); 
}




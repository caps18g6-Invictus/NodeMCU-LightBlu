String payloadgu = "";
const char * puser="";
int dId = 333;

void getUserName(){
  HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://ec2-13-211-121-155.ap-southeast-2.compute.amazonaws.com/getuser.php?trun=1&devid="+String(dId));      //Specify request destination ?s1=1&s2=1&pass=123
   http.addHeader("Content-Type", "text/plain");  //Specify content-type header
 
   int httpCode = http.POST("Message from ESP8266");   //Send the request
    payloadgu = http.getString();                  //Get the response payload
   //strcpy(payloadt,payload);
  //char JSONMessage[256] = payload;
  
payloadgu.trim();
payloadgu.remove(payloadgu.length()-1);
payloadgu.remove(0,1);
  //Serial.print("..");
//Serial.print(payloadgu);Serial.print("..");
  StaticJsonBuffer<300> JSONBuffer;
  JsonObject&  parsed= JSONBuffer.parseObject(payloadgu);

  if (!parsed.success()) {Serial.println("Parsing failed in getUserName"); return;}


puser = parsed["username"];
 
   //Serial.println(httpCode);   //Print HTTP return code
   //Serial.println(payload);    //Print request response payload
//puser = pusergu;
Serial.print("Device being used by username :  ");
Serial.println(puser);

}

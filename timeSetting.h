unsigned long timeNow = 0;
unsigned long timeLast = 0;

String daysOfWeek[7] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
String toDay = "";
int dayNum = 0;
//Time start Settings:

int startingHour = 12; // set your starting hour here, not below at int hour. This ensures accurate daily correction of time

int seconds = 0;
int minutes = 17;
int hours = startingHour;
int days = 0;
String setTime3 = "initiating ";
//Accuracy settings

 int ahours =0;
  int aminutes = 0;
  int aday = 0;
  bool schMode = false;

int dailyErrorFast = 0; // set the average number of milliseconds your microcontroller's time is fast on a daily basis
int dailyErrorBehind = 0; // set the average number of milliseconds your microcontroller's time is behind on a daily basis

int correctedToday = 1; // do not change this variable, one means that the time has already been corrected today for the error in your boards crystal. This is true for the first day because you just set the time when you uploaded the sketch.  


 
void timeSet(){

  timeNow = millis()/1000; // the number of milliseconds that have passed since boot
seconds = timeNow - timeLast;//the number of seconds that have passed since the last time 60 seconds was reached.

  

if (seconds == 60) {
  timeLast = timeNow;
  minutes = minutes + 1;
}

//if one minute has passed, start counting milliseconds from zero again and add one minute to the clock.

if (minutes == 60){ 
  minutes = 0;
  hours = hours + 1;
}

// if one hour has passed, start counting minutes from zero and add one hour to the clock

if (hours == 24){
  hours = 0;
  days = days + 1;
  
  dayNum = dayNum + 1;
  //strcpy(toDay , daysOfWeek[dayNum]);
  if(dayNum > 6){
    dayNum =0;
  }
  }

  //if 24 hours have passed , add one day

if (hours ==(24 - startingHour) && correctedToday == 0){
  delay(dailyErrorFast*1000);
  seconds = seconds + dailyErrorBehind;
  correctedToday = 1;
}

//every time 24 hours have passed since the initial starting time and it has not been reset this day before, add milliseconds or delay the progran with some milliseconds. 
//Change these varialbes according to the error of your board. 
// The only way to find out how far off your boards internal clock is, is by uploading this sketch at exactly the same time as the real time, letting it run for a few days 
// and then determine how many seconds slow/fast your boards internal clock is on a daily average. (24 hours).

if (hours == 24 - startingHour + 2) { 
  correctedToday = 0;
}

//let the sketch know that a new day has started for what concerns correction, if this line was not here the arduiono
// would continue to correct for an entire hour that is 24 - startingHour. 



//Serial.print("The time is:           ");
//Serial.print(days);
//Serial.print(":");
//Serial.print(hours);
//Serial.print(":");
//Serial.print(minutes);
//Serial.print(":"); 
//Serial.println(seconds); 


String setTime = "The time is ";
String setTime0 = setTime + daysOfWeek[dayNum] + " ";
String setTime1 = setTime0 + hours + " :";
String setTime2 = setTime1 + minutes + " :";
 setTime3 = setTime2 + seconds + " ";

}

String SchedulePage= ""
"<p> Enter Alarm Time</p> "
"<form action=\"/alarm\" method=\"POST\">"
//"<input type=\"text\" name=\"day\" placeholder=\"day\">"
"<select name=\"day\">"
    "<option value=\"0\">Sunday</option>"
    "<option value=\"1\">Monday</option>"
    "<option value=\"2\">Tuesday</option>"
    "<option value=\"3\">Wednesday</option>"
    "<option value=\"4\">Thursday</option>"
    "<option value=\"5\">Friday</option>"
    "<option value=\"6\">Saturday</option>"
    
 " </select>"
"</br><input type=\"text\" name=\"hours\" placeholder=\"Hours\">"
"</br><input type=\"text\" name=\"minutes\" placeholder=\"Minutes\">"
"</br><input type=\"text\" name=\"day\" placeholder=\"Seconds\">"
"</br><input type=\"text\" name=\"month\" placeholder=\"Month\">"

"</br><input type=\"submit\" value=\"Set alarm\"></form></br>";



String initTimeWebPage = ""
"<p> Enter time</p> "
"<form action=\"/inittime\" method=\"POST\">"
"<select name=\"day\">"
    "<option value=\"0\">Sunday</option>"
    "<option value=\"1\">Monday</option>"
    "<option value=\"2\">Tuesday</option>"
    "<option value=\"3\">Wednesday</option>"
    "<option value=\"4\">Thursday</option>"
    "<option value=\"5\">Friday</option>"
    "<option value=\"6\">Saturday</option>"
    
 " </select>"
"</br><input type=\"text\" name=\"hours\" placeholder=\"Hours\">"
"</br><input type=\"text\" name=\"minutes\" placeholder=\"Minutes\">"
"</br><input type=\"text\" name=\"seconds\" placeholder=\"Seconds\">"
"</br><input type=\"submit\" value=\"Set Time\"></form></br>";

//String initTimeWebPage = initTimeWebPage0 + setTime3;

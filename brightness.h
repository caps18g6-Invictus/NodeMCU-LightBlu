  int ledbrightness=0;
  String brightness0 = ""
"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
"<html>\r\n"
"<head>\r\n"
"<title>BRIGHTNESS</title>\r\n"
"<h1 align=\"center\" >CHANGE BRIGHTNESS</h1>\r\n"
"</head>\r\n"
"<body bgcolor=\"yellow\">\r\n"
"<div align=\"center\" >\r\n"
"<label align=\"center\" >\r\n"
"PRESENT BRIGHTNESS LEVEL : ";
String brightness1 = brightness0 + ledbrightness;
String brightness = brightness1 +
"</label>\r\n<br />\r\n<br />\r\n"
"<a href=\"/brightnessinc\">\r\n<button>   +   </button>\r\n</a><br />\r\n<br />\r\n"
"<a href=\"/brightnessdec\">\r\n<button>   -  </button></a>\r\n<br />\r\n<br />\r\n"
"<a href=\"/main\">\r\n<button>HOME</button>\r\n</a>\r\n<br />\r\n<br />\r\n"
"</div>\r\n"
"</body>\r\n"
"</html>\r\n";

//  brightness+=ledbrightness;
  //brightness+=


  String rootPage = ""
  "<html>\r\n"
"<head>\r\n"
"<title>Interface</title>\r\n"
"<h1 align=\"center\" >Interface</h1>\r\n"
"</head>\r\n"
"<body bgcolor=\"yellow\">\r\n"
"<div align=\"center\" >\r\n"
"<label align=\"center\" >\r\n"
"PRESENT BRIGHTNESS LEVEL : "
"</label>\r\n<br />\r\n<br />\r\n"
"<a href=\"/wifilogin\">\r\n<button>   Configure Wifi   </button>\r\n</a><br />\r\n<br />\r\n"
"<a href=\"/inittime\">\r\n<button>   Set Device Time  </button>\r\n</a><br />\r\n<br />\r\n"
"<a href=\"/alarm\">\r\n<button>   Set Schedule   </button>\r\n</a><br />\r\n<br />\r\n"
"<a href=\"/brightness\">\r\n<button>   Brightness White Mode   </button>\r\n</a><br />\r\n<br />\r\n"
"<a href=\"/rgb\">\r\n<button>   color Selection   </button>\r\n</a><br />\r\n<br />\r\n"
"</div>\r\n"
"</body>\r\n"
"</html>\r\n";

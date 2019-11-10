#include <SPI.h>
#include <Ethernet.h>
 byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x78, 0xE0 }; // <------- PUT YOUR MAC Address Here
 byte ip[]= { 192, 168, 8, 112}; //                    <------- PUT YOUR IP Address Here
 byte gateway[] = { 192, 168, 8, 1 }; //               <------- PUT YOUR ROUTERS IP Address to which your shield is connected Here
 byte subnet[] = { 255, 255, 255, 0 }; //                <------- It will be as it is in most of the cases
EthernetServer server(80); //                           <------- It's Defaulf Server Port for Ethernet Shield
String readString;
void setup()
{
  pinMode(6, OUTPUT); // Pin Assignment through which relay will be controlled
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
 
  //start Ethernet

  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
 //enable serial data print
  Serial.begin(9600);
}
void loop()
{  // Create a client connection
  EthernetClient client = server.available();
 if (client) {
      while (client.connected()) {
      if (client.available()) {
        char c = client.read();
       if (readString.length() < 100) {
          readString += c;
          Serial.print(c);
        }
        //if HTTP request has ended
        if (c == '\n') {
         
           Serial.println(readString); //print to serial monitor for debugin
          client.println("<HTML>");
          client.println("<HEAD>");         
          client.println("<Style>");
          client.println("a:link,a:visited {");
          client.println("Color:white;");
          client.println("padding:14px 25px;");
          client.println("text-align:center;");
          client.println("border-top:5px solid;");
          client.println("border-bottom:5px solid;");
          client.println("border-right:5px solid;");
          client.println("border-left:5px solid;");
          client.println("display:inline-block;");          
          client.println("background-color:#fe0077;");
          client.println("}");
          client.println("a:hover,a:active {");
          client.println("background-color:#C10A5F;");
          client.println("}");
          client.println("</Style>");        
          client.println("</HEAD>");
          client.println("<body bgcolor=\"#242424\">");
          client.println("<div align=\"center\">");
            
          // Relay Control Code
          client.println("<br />");
          client.println("<a href=\"/?r1on\"\"> Turn On Light 1</a>");
          client.println("<a href=\"/?r1off\"\">Turn Off Light 1</a><br />");
          client.println("<br />");        
          client.println("<a href=\"/?r2on\"\">Turn On Light 2</a>");
          client.println("<a href=\"/?r2off\"\">Turn Off Light 2</a><br />");
          client.println("<br />");
          client.println("<a href=\"/?r3on\"\">Turn On Light 3</a>");
          client.println("<a href=\"/?r3off\"\">Turn Off Light 3</a><br />");
          client.println("<br />");
           client.println("<a href=\"/?r4on\"\">Turn On Light 4</a>");
          client.println("<a href=\"/?r4off\"\">Turn Off Light 4</a><br />");
         client.println("<br />");
          // control arduino pin via ethernet Start //
          if (readString.indexOf("?r1on") > 0) //checks for on
          {
            digitalWrite(6, LOW);    // set pin 6 high
                    
            client.println("<br />");
          }
          else {
           if (readString.indexOf("?r1off") > 0) //checks for off
            {
              digitalWrite(6, HIGH);    // set pin 6 low
                           
              client.println("<br />");
           }
          }
         if (readString.indexOf("?r2on") > 0) //checks for on
          {

            digitalWrite(7, LOW);    // set pin 7 high
            
            client.println("<br />");
          }
         else {

            if (readString.indexOf("?r2off") > 0) //checks for off
            {
              digitalWrite(7, HIGH);    // set pin 7 low
             
              client.println("<br />");
            }
          }
          if (readString.indexOf("?r3on") > 0) //checks for on
          {
            digitalWrite(8, LOW);    // set pin 8 high
         
           client.println("<br />");
          }
          else {

            if (readString.indexOf("?r3off") > 0) //checks for off
            {
              digitalWrite(8, HIGH);    // set pin 8 low
                           
              client.println("<br />");
            }
          }
          if (readString.indexOf("?r4on") > 0) //checks for on
          {
            digitalWrite(9, LOW);    // set pin 9 high
            
            
            client.println("<br />");
          }
          else {
            if (readString.indexOf("?r4off") > 0) //checks for of
            {
              digitalWrite(9, HIGH);    // set pin 9 low
                      
              
              client.println("<br />");
            }
          }
          client.println("<hr/>");
          client.println("<hr/>");
          
          // control arduino pin via ethernet End //
          
          // Relay Status Display
          
          client.println("<center>");           
          client.println("<table border=\"2\">");
          client.println("<tr>");
          if (digitalRead(6))
          {//green
            client.print("<td><font color =\"green\"><h3> Light 1 is OFF </h4></td>");
          }
          else
          {
            client.print("<td><font color =\"Red\"><h3> Light 1 is ON </h4></td>");
          }
          client.println("<br />");
          if (digitalRead(7))
          {
            client.print("<td><font color =\"green\"><h3> Light 2 is OFF </h4></td>");
          }
          else
          {
            client.print("<td><font color =\"Red\"><h3> Light 2 is ON</h4></td>");
          }
          client.println("</tr>");
          client.println("<tr>");
          if (digitalRead(8))
          {
            client.print("<td><font color =\"green\"><h3> Light 3 is OFF </h4></td>");
          }
          else
          {
            client.print("<td><font color =\"Red\"><h3> Light 3 is ON </h4></td>");
          }
          if (digitalRead(9))
          {
            client.print("<td><font color =\"green\"><h3> Light 4 is OFF </h4></td>");
          }
          else
          {
            client.print("<td><font color =\"Red\"><h3>Light 4 is ON </h4></td>");
          }
          client.println("</tr>");
          client.println("</table>");
          client.println("</center>");
          //clearing string for next read
          readString = "";
          client.println("</body>");
          client.println("</HTML>");
          delay(1);
          //stopping client
          client.stop();
        }
      }
    }


  }


}


#include <ESP8266WiFi.h>

const char* ssid = "";
const char* password = "";
const char* host = "";                                    
WiFiServer server(5001);


void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.print("Connecting ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.print("Server started: ");
  Serial.println(WiFi.localIP());

  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);

  digitalWrite(14,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  digitalWrite(15,LOW);

}

void loop() { 
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }

  String req = client.readStringUntil('\r');
  client.flush();
  if (req.indexOf("") != -10) {

//================================================== GOF
    if (req.indexOf("/GOF") != -1)
    {
      Serial.println("You clicked: Forward 1");
      digitalWrite(12, HIGH);
      digitalWrite(15, HIGH);
      delay(1000);
      digitalWrite(12, LOW);
      digitalWrite(15, LOW);
    }

//================================================== STOP
    if (req.indexOf("/STOP") != -1)
    {
      Serial.println("You clicked: STOP");
      digitalWrite(14,LOW);
      digitalWrite(12,LOW);
      digitalWrite(13,LOW);
      digitalWrite(15,LOW);
      
    }

//================================================== GOB
    if (req.indexOf("/GOB") != -1)
    {
      Serial.println("You clicked: Backward");
      digitalWrite(14,HIGH);
      digitalWrite(12,LOW);
      
      digitalWrite(13,HIGH);
      digitalWrite(15,LOW);
    }

//================================================== LEFT
    if (req.indexOf("/LEFT") != -1)
    {
      Serial.println("You clicked: LEFT");
      digitalWrite(15,HIGH);
    }
    
//================================================== RIGHT
    if (req.indexOf("/RIGHT") != -1)
    {
      Serial.println("You clicked: RIGHT");
      digitalWrite(12,HIGH);
    }
    
  }

  else {
    Serial.println("invalid request");
   client.stop();
    return;
  }
  myservo.write(pos);
  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<br>";
  s += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
  s += "<input type=\"button\" name=\"bl\" value=\"Forward\" onclick=\"location.href='/GOF'\">";
  s += "&nbsp;&nbsp;";
  s += "<input type=\"button\" name=\"bl\" value=\"Stop\" onclick=\"location.href='/STOP'\">";
  s += "&nbsp;&nbsp;";
  s += "<input type=\"button\" name=\"bl\" value=\"Backward\" onclick=\"location.href='/GOB'\">";
  s += "<br><br>";
  s += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
  s += "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
  s += "<input type=\"button\" name=\"bl\" value=\"LEFT\" onclick=\"location.href='/LEFT'\">";
  s += "&nbsp;&nbsp;";
  s += "<input type=\"button\" name=\"bl\" value=\"RIGHT\" onclick=\"location.href='/RIGHT'\">";
  s += "<br><br>";
  s += "</html>\n";
  client.flush();
  client.print(s);
  delay(1);


  
}

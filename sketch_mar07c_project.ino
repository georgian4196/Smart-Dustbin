#include <Servo.h>
#include <WiFi.h>

WiFiClient client;

String MakerIFTTT_Key ;
String MakerIFTTT_Event;
char *append_str(char *here, String s) {  int i=0; while (*here++ = s[i]){i++;};return here-1;}
char *append_ul(char *here, unsigned long u) { char buf[20]; return append_str(here, ultoa(u, buf, 10));}
char post_rqst[256];char *p;char *content_length_here;char *json_start;int compi;
static const int servoPin = 4;

Servo servo1;

#define TRIGGER 2
#define ECHO  27

#define TRIGGER1 13
#define ECHO1  14

long duration;
long distance;

long duration1;
long distance1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);

  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin("Nokia","Nokia12345678qwe");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");
  }
  Serial.println("Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));

  
  servo1.attach(servoPin);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(TRIGGER1, OUTPUT);
  pinMode(ECHO1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;

  if (distance <= 4) {

    Serial.println("Too Close.");

    for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
        servo1.write(posDegrees);
        //Serial.println(posDegrees);
        delay(20);
    }
    delay(5222);
    for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        //Serial.println(posDegrees);
        delay(20);
    }
    }

    else {
      Serial.printf("Centimeters recorded:"); 
      Serial.println("distance");
    }
    delay(500);

  digitalWrite(TRIGGER1, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER1, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIGGER1, LOW);
  duration = pulseIn(ECHO1, HIGH);
  distance = (duration/2) / 29.1;

 if (distance <= 4) {

    Serial.println("bhar gya hai.");
//http server to send massage to mqtt

    if (client.connect("maker.ifttt.com",80)) {
     Serial.println("MQTT");
    MakerIFTTT_Key ="dxKqzmr77ZoWhBaWxgxwVa5PCEKK0Vj5HTBYQEuN8Fm";
    MakerIFTTT_Event ="dustbin";
    p = post_rqst;
    p = append_str(p, "POST /trigger/");
    p = append_str(p, MakerIFTTT_Event);
    p = append_str(p, "/with/key/");
    p = append_str(p, MakerIFTTT_Key);
    p = append_str(p, " HTTP/1.1\r\n");
    p = append_str(p, "Host: maker.ifttt.com\r\n");
    p = append_str(p, "Content-Type: application/json\r\n");
    p = append_str(p, "Content-Length: ");
    content_length_here = p;
    p = append_str(p, "NN\r\n");
    p = append_str(p, "\r\n");
    json_start = p;
    p = append_str(p, "{\"value1\":\"");
    p = append_str(p, "+917002549361");
    p = append_str(p, "\",\"value2\":\"");
    p = append_str(p, "bhej rha hu");
    p = append_str(p, "\",\"value3\":\"");
    p = append_str(p, "");
    p = append_str(p, "\"}");

    compi= strlen(json_start);
    content_length_here[0] = '0' + (compi/10);
    content_length_here[1] = '0' + (compi%10);
    client.print(post_rqst);
    }
    }

    else {
      Serial.printf("Centimeters recorded:"); 
      Serial.println("distance");
    }
}

#include <WiFi.h>
#include<ThingSpeak.h>
#include<WiFiClient.h>
#include<ESP32Servo.h>

const char* ssid="Wokwi-GUEST";
const char* password="";

long channelID=2805605;
const char* writeAPIKey="9K67ZCTFLIQMPAED";


const int trigPin1=16;
const int echoPin1=17;
const int trigPin2=25;
const int echoPin2=26;
const int thresholdDist=50;

WiFiClient client;
int mesdist(int trigpin, int echopin);

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  WiFi.begin(ssid,password);

 while(WiFi.status()!=WL_CONNECTED){
  delay(1000);
  Serial.println("wifi connecting....");
 }
 Serial.println("wifi connected ");

 ThingSpeak.begin(client);
}

void loop() {
  int parkingstat;
 
  int dist1=mesdist(trigPin1,echoPin1);
  int dist2=mesdist(trigPin2,echoPin2);

  if(dist1 <thresholdDist && dist2 < thresholdDist){
    parkingstat=0;
}
  else{
    parkingstat=1;
  }
  ThingSpeak.setField(1,parkingstat);
  int x=ThingSpeak.writeFields(channelID,writeAPIKey);
  if(x==200){
  Serial.println("send data sucssesfully");
  }
  else{
    Serial.println("error in sending");
  }
  delay(8000);
}
int mesdist(int trigpin,int echopin){

  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  long duration = pulseIn(echopin, HIGH);

  // Calculate the distance (duration in microseconds / 58 = cm)
  float distance = duration * 0.034 / 2;

  return distance;
  
}
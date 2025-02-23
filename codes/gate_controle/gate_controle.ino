#include <WiFi.h>
#include <ThingSpeak.h>
#include <ESP32Servo.h>
#include <HTTPClient.h>

const int trigPin1=16;
const int echoPin1=17;
const int trigPin2=25;
const int echoPin2=26;
int Tdist=200;
int mesdist(int trigpin, int echopin);


const char *ssid = "Wokwi-GUEST";
const char *password = "";
WiFiClient client;

unsigned long channelID = 2805605;
const char *readAPIKey = "W2N7HIKM621EXJO7";
int gateServoPin = 5;  // Servo pin for the gate
Servo gateServo;       // Servo to control gate


void setup() {
  Serial.begin(115200);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  ThingSpeak.begin(client);
  gateServo.attach(gateServoPin);
  gateServo.write(0);
}

void loop() {
  int parkingStatus;
  int dist1=mesdist(trigPin1,echoPin1);
  int dist2=mesdist(trigPin2,echoPin2);
  // Get the latest status (last two entries)
  String readUrl = "https://api.thingspeak.com/channels/" + String(channelID) + "/fields/1.json?api_key=" + String(readAPIKey) + "&results=1";

  HTTPClient http;
  http.begin(readUrl); // Connect to ThingSpeak API

  int httpCode = http.GET();
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println("Received payload: ");
    Serial.println(payload);

    // Parse the JSON response to get the most recent parking status
    int feedstart=payload.indexOf("feeds");
    int start = payload.indexOf("\"field1\":\"",feedstart) + 10;  // Field 1 value
    int end = payload.indexOf("\"", start);
    String statusString = payload.substring(start, end);
    Serial.println(statusString);
    parkingStatus = statusString.toInt();
   

    // Control gate based on parking status


    }

   else {
    Serial.println("Error in HTTP request");
  }
  Serial.println(dist1);
  Serial.println(dist2);
  http.end();  // Close the HTTP connection
   Serial.println(parkingStatus);
  if(parkingStatus == 0) { // Slot occupied
      gateServo.write(90);
      Serial.println("door is closed");  // Close the gate
    } 
  if(parkingStatus==1){
    if((dist1<Tdist||dist2<Tdist)) { // Slot free
      gateServo.write(0);  
      Serial.println("gate is open");// Open the gate
    }
    else{
    gateServo.write(90);
    Serial.println("door is closed");
  }
}


  delay(8000); // Check status every 10 seconds
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
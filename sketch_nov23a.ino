    //#include <dht.h>

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL7F6IFH8G"
#define BLYNK_DEVICE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN "D39B19jzbD8YHJ8FIpHIUKTeFNyD_Z8-"
#include <BlynkSimpleEsp32.h>
#include <WiFi.h>

const char* ssid = "iZoom";
const char* pass = "Zoom1234";
const char* auth = "D39B19jzbD8YHJ8FIpHIUKTeFNyD_Z8-";

const int thrs_mq2 = 400;
const int thrs_moist = 300;
 
#define led 15
#define fan 27
#define mq2 36
#define moist 35
#define pir 34
#define buzz 25
#define light 26

//#define dht1 14
//dht DHT;
//#define DHTTYPE DHT11
//DHT dht(dht1, DHTTYPE);

int moist_read, mq2_read, pir_read;
//float  dht_h, dh_t;


void setup(){
  Serial.begin(115200);
  Blynk.begin(auth,ssid,pass);
  pinMode(led,OUTPUT);
  pinMode(fan,OUTPUT);
  pinMode(light,OUTPUT);
  pinMode(buzz,OUTPUT);
  pinMode(pir,INPUT);
  pinMode(mq2,INPUT);
  pinMode(moist,INPUT);
  //pinMode(dht1, INPUT);

  //display.print("Smart Home");
  
}
BLYNK_WRITE(V4){
  int button=param.asInt();
  digitalWrite(fan, button);
}

BLYNK_WRITE(V5){
  int button=param.asInt();
  digitalWrite(light, button);
}

void loop(){
  //DHT.read11(dht1);
  pir_read = 0;
  mq2_read = analogRead(mq2);
  moist_read = analogRead(moist);
  pir_read = digitalRead(pir);
  //dht_h = DHT.humidity;
  //dht_t = DHT.temperature;

  Serial.println(mq2_read);
  Serial.println(moist_read);
  Serial.println(pir_read);
  //Serial.println(dht_h);
  //Serial.println(dht_t);

  if( mq2_read > thrs_mq2 ){
    digitalWrite(buzz, HIGH); 
  }
  else{
    digitalWrite(buzz, LOW); 
  }

  if( moist_read < thrs_moist ){
     digitalWrite(buzz, HIGH);
  }
  else{
    digitalWrite(buzz, LOW);
  }

  if( pir == HIGH ){
    pir_read = 1;
    digitalWrite(buzz, HIGH);
    Serial.println("Motion Detected");
  }
  else if ( pir == LOW ){
    pir_read = 0;
    digitalWrite(buzz, LOW);
    Serial.println("No Motion");
  }
  Blynk.virtualWrite(V0,mq2_read);
  Blynk.virtualWrite(V1,moist_read);
  Blynk.virtualWrite(V2,pir_read);

Blynk.run();

  //if (isnan(dht_h) || isnan(dht_t)) {
   // Serial.println("Failed to read from DHT sensor!");
    //return;
  //}
}

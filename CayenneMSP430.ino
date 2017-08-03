// MQTT Coupled with Cayenne 

#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

//---common among cayenne devices---------//
char ssid[] =      "MY WIFI";
char password[] =  "MY PASSWORD";
char server[] =    "mqtt.mydevices.com";
String user =      "MY USERID";
char MQTTpass[] =  "MY MQTT PASSWORD";
String clientID =  "MY CLIENT ID";
//----unique to application -------------//
int reconnections = 0;
float t; //temperature variable
float h; //humidity variable
float batteryVoltage;
WiFiClient wifiClient;

//---utilize for smart delay-------------//
unsigned long Millis0 = 0;
const long interval = 10000;

void callback(char* topic, byte* payload, unsigned int length);
PubSubClient client(server,1883, callback, wifiClient);

void setup()
{
  //---common---------------------//
  Wire.begin(); //begin i2C
  Serial.begin(115200);
  connectWifi();
  reconnectMQTT();
  subscribeAll();
  //---unique for application-----//
  pinMode(28,OUTPUT);
  digitalWrite(28,LOW);
  pinMode(29,OUTPUT);
  digitalWrite(29,LOW);
  pinMode(30,OUTPUT);
  digitalWrite(30,LOW);
}

//-----------------------------------------------------------//
//----------------------MAIN LOOP ---------------------------//
//-----------------------------------------------------------//

void loop()
{
  if ( WiFi.status() != WL_CONNECTED) {
    connectWifi();                  // Reconnect WIFI if disconnected
    reconnections++;
  }
   
  if (!client.connected()) {
  reconnectMQTT();                // Reconnect MQTT if disconnected
  subscribeAll();
  }
  
  client.poll();                  // Check if any message were received
  delay(100);

  unsigned long Millis1 = millis();
  if (Millis1 - Millis0 >= interval) { //inside this statement just runs every "interval"
    Millis0 = Millis1;
    long rssi = WiFi.RSSI();  
    publishRSSI(rssi,0);           // publish signal strength
    }

}

//-----------------------------------------------------------//
//--------------Configure Subscriptions----------------------//
//-----------------------------------------------------------//

void subscribeAll()   // subscribe to channels corresponding to controls on Cayenne Dashboard
{
    channelSubscribe(21); 
    channelSubscribe(22);
    channelSubscribe(23);
}

//-----------------------------------------------------------//
//-----------------Callback Routines-------------------------//
//-----------------------------------------------------------//


void callback(char* topic, byte* payload, unsigned int length) {
  char cTopic[101];                                    //make the topic array
  memcpy (cTopic,topic,101);
  char cPayload[length-1];                             //make the payload array
  memcpy(cPayload,payload,length);      
  String sPayload = String(cPayload);                
  String topicString = String(cTopic);
  int chan = getChannel(topicString);                  //store the channel of the cmd
  float cmdVal = getValue(sPayload,length);            //store cmd value
  switch (chan) {
      case 21: {                                       //Routine for ch21 cmd
              int i = (int)cmdVal;
              String str = String(cmdVal);
              Serial.println(i);                  
              makeAgree(str,28);              // write the value to the pin
              publishBin(str,21);             // confirm LOW or HIGH on channel 21
              break;
              }
     case 22: {                                        //routine for ch22 cmd
              publishFloat(String(cmdVal)+1,22);       //confirm float value on channel 22
              break;
              }
     default: {
              // do nothing
              break;
              }
    }
  
}

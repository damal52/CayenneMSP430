void channelSubscribe(int channel)  //subscribe to a channel
{
  String topic =  String("v1/" + user + "/things/" + clientID + "/cmd/" + channel);
  char topicChar[topic.length()+1];
  topic.toCharArray(topicChar,topic.length()+1);  
  if(client.subscribe(topicChar)) {
        Serial.print("Subscription successful for ch");
        Serial.println(channel);
  }
}

int getChannel(String myTopicString)  //parse the channel from the cmd topic
{
  int ind1 = myTopicString.indexOf('/');            //find location of first delimiter
  int ind2 = myTopicString.indexOf('/', ind1+1 );   //find location of second delimiter
  int ind3 = myTopicString.indexOf('/', ind2+1 );   //find location of third delimiter
  int ind4 = myTopicString.indexOf('/', ind3+1 );   //find location of fourth delimiter
  int ind5 = myTopicString.indexOf('/', ind4+1 );   //find location of fifth delimiter
  String myChan = myTopicString.substring(ind5+1,100);   //captures second data String
  Serial.println(myChan); 
  int chan = myChan.toInt();
  return(chan);
}  

long getDecimal(float val)
{
  int intPart = int(val);
  long decPart = 100*(val-intPart); //I am multiplying by 1000 assuming that the foat values will have a maximum of 3 decimal places. 
                                    //Change to match the number of decimal places you need
  if(decPart>0)return(decPart);           //return the decimal part of float number if it is available 
  else if(decPart<0)return((-1)*decPart); //if negative, multiply by -1
  else if(decPart=0)return(00);           //return 0 if decimal part of float number is not available
}

float getValue(String payloadString, int length)  //parse the channel from the cmd topic
{
  int ind1 = payloadString.indexOf(',');            //find location of first delimiter
  String cmdValue = payloadString.substring(ind1+1,length);   //captures second data String
  Serial.println(cmdValue); 
  float cmdValueF = cmdValue.toFloat();
  return(cmdValueF);
}  

void makeAgree(String value, int pin)
{
  int myInt = value.toInt();
  if (myInt == 1){
    digitalWrite(pin,HIGH);
  }
  else {
    digitalWrite(pin,LOW);
  }
}

void publishBin(String value, int channel)  //publish a binary value
{
  String topic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String valueString = String("digital_sensor="+String(value));
  Serial.println(valueString);  //debugging effort
  char valueChar[valueString.length()+1];
  valueString.toCharArray(valueChar,valueString.length()+1);
  char topicChar[topic.length()+1];
  topic.toCharArray(topicChar,topic.length()+1);
  client.publish(topicChar,valueChar);
}

void publishCelsius(float value, int channel)
{
  String pubTopic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String myTempString = "temp,c="+String(int(value))+ "."+String(getDecimal(value));
  Serial.println(myTempString);
  char myTempChar[myTempString.length()+1];
  myTempString.toCharArray(myTempChar,myTempString.length()+1);
  char pubTopicChar[pubTopic.length()+1];
  pubTopic.toCharArray(pubTopicChar,pubTopic.length()+1);
  client.publish(pubTopicChar,myTempChar);
}

void publishFloat(String value, int channel)  //publish a float value
{
  String topic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String valueString = String("analog_actuator="+String(value));
  Serial.println(valueString);  //debugging effort
  char valueChar[valueString.length()+1];
  valueString.toCharArray(valueChar,valueString.length()+1);
  char topicChar[topic.length()+1];
  topic.toCharArray(topicChar,topic.length()+1);
  client.publish(topicChar,valueChar);
}

void publishHumidity(float value, int channel)
{
  String pubTopic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String myHumString = "rel_hum,p="+String(int(h))+ "."+String(getDecimal(h));
  Serial.println(myHumString);
  char myHumChar[myHumString.length()+1];
  myHumString.toCharArray(myHumChar,myHumString.length()+1);
  char pubTopicChar[pubTopic.length()+1];
  pubTopic.toCharArray(pubTopicChar,pubTopic.length()+1);
  client.publish(pubTopicChar,myHumChar);
}

void publishRSSI(float value, int channel) //publish an RSSI float value
{
  String pubTopic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String myRssi = String("rssi,dbm="+String(value));
  //Serial.println(myRssi);
  char cRssi[myRssi.length()+1];
  myRssi.toCharArray(cRssi,myRssi.length()+1);
  char pubTopicChar[pubTopic.length()+1];
  pubTopic.toCharArray(pubTopicChar,pubTopic.length()+1);
  client.publish(pubTopicChar,cRssi);
}

void publishCount(int value, int channel)
{
  String pubTopic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String myCount = String("counter,Analog="+String(value));
  Serial.println(myCount);
  char myCountChar[myCount.length()+1];
  myCount.toCharArray(myCountChar,myCount.length()+1);
  char pubTopicChar[pubTopic.length()+1];
  pubTopic.toCharArray(pubTopicChar,pubTopic.length()+1);
  client.publish(pubTopicChar,myCountChar);
}

void publishVoltage(float value, int channel)
{
  String topic =  String("v1/" + user + "/things/" + clientID + "/data/" + channel);
  String valueString = String("voltage,v="+String(value));
  Serial.println(valueString);
  char valueChar[valueString.length()+1];
  valueString.toCharArray(valueChar,valueString.length()+1);
  char topicChar[topic.length()+1];
  topic.toCharArray(topicChar,topic.length()+1);
  client.publish(topicChar,valueChar);
}

void reconnectMQTT(void)
{
  Serial.println("Disconnected. Reconnecting....");
  char clientIDx[clientID.length()+1];
  char userx[user.length()+1];
  clientID.toCharArray(clientIDx,clientID.length()+1);
  user.toCharArray(userx,user.length()+1);
    if(!client.connect(clientIDx, userx, MQTTpass)) {
      Serial.println("Connection failed");
    } else {
      Serial.println("Connection success");
    }
}

float readBatt(int pin) {
  int x = analogRead(pin); // pins that work: 24,25,26,27,28,6,2, DON'T WORK: 23
  float maxVoltage = 3.30; // max scale of analog input
  float voltageDiv = 5.73; // voltage divider circuit
  float battVoltage = ((x)/4096.00*maxVoltage*voltageDiv);
  return(battVoltage);
}




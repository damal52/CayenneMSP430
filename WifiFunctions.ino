void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void connectWifi() {
Serial.print("Attempting to connect to Network named: "+ String(ssid));
  WiFi.begin(ssid, password);
  int delays = 0;
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
    delays++;
    if (delays >50){
    WiFi.begin(ssid,password);
    delays=0;
    }
  }
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");  
  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);  
  }
  Serial.println("\nIP Address obtained"); // We are connected and have an IP address.
  printWifiStatus();  // Print the WiFi status.
}

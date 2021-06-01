void getWeatherData() //client function to send/receive GET request data.
{
  result = "";
  if (client.connect(weatherHost, 80))
  {
    //starts client connection, checks for connection
    client.println("GET /data/2.5/weather?id=" + CityID + "&units=metric&APPID=" + APIKEY);
    client.println("Host: api.openweathermap.org");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
  }
  else
  {
    Serial.println("connection failed");  //error message if no client connect
    Serial.println();
  }

  while (client.connected() && !client.available())
    delay(1); //waits for data
  while (client.connected() || client.available())
  {
    //connected or data available
    char c = client.read(); //gets byte from ethernet buffer
    result = result + c;
  }

  client.stop();  //stop client
  result.replace('[', ' ');
  result.replace(']', ' ');
  //Serial.println(result); //debug otput json response  
  char jsonArray[result.length() + 1];
  result.toCharArray(jsonArray, sizeof(jsonArray));
  jsonArray[result.length() + 1] = '\0';
  DynamicJsonBuffer json_buf;
  JsonObject &root = json_buf.parseObject(jsonArray);

  if (!root.success())
  {
    Serial.println("parseObject() failed");
  }

  float temperature = root["main"]["temp"];
  float humidity = root["main"]["humidity"];
  String weather = root["weather"]["main"];
  String description = root["weather"]["description"];
  weatherDescription = description;
  Temperature = temperature;
  Humidity = humidity;
}

void getTimeNTP()
{
  while(!timeClient.update()){timeClient.forceUpdate();}
  hh = timeClient.getHours();
  mm = timeClient.getMinutes();
  ss = timeClient.getSeconds();
  date_time = timeClient.getFormattedDate();
  index_date = date_time.indexOf("T");
  date = date_time.substring(0, index_date);
}

void getDHT(){
  DHTTemperature = dht.readTemperature(); // получить значение температуры
  DHTHumidity = dht.readHumidity();       // получить значение влажности
  hic = dht.computeHeatIndex(DHTTemperature, DHTHumidity, false); //Индекс температуры
}

void displayConditions(float Temperature, float Humidity, String &description)
{
  lcd.clear();  //Printing Temperature
  lcd.print("T:");
  lcd.print(Temperature, 1);
  lcd.print((char) 223);
  lcd.print("C ");

  lcd.print(" H:"); //Printing Humidity
  lcd.print(Humidity, 0);
  lcd.print(" %");

  lcd.setCursor(0, 1);
  lcd.print(description);
}

void printTime(int value) {
  getTimeNTP();
  lcd.clear();
  printNumber(hh/10,0 + value);printNumber(hh%10,2 + value);
  lcd.setCursor(4 + value, 0);lcd.print("\x2E");lcd.setCursor(4 + value, 1);lcd.print("\x2E");
  printNumber(mm/10,5 + value);printNumber(mm%10,7 + value);
  //lcd.setCursor(9 + value, 0);lcd.print("\x2E");lcd.setCursor(9 + value, 1);lcd.print("\x2E");
  //printNumber(ss/10,10 + value);printNumber(ss%10,12 + value);
  
  //lcd.setCursor(4, 0);
  //lcd.print(date);
}

void printDHT(){ 
  String hicstat = "";
  
  getDHT();
  while(isnan(DHTTemperature) || isnan(DHTHumidity) || isnan(hic) || hic < 0 || DHTHumidity > 100) { 
    getDHT();
    delay(5);
  }
  
  if(hic < 30){
    hicstat = "Good";
  }else if(hic < 40){
    hicstat = "Normal";
  }else if(hic < 45){
    hicstat = "Bad";
  }else if(hic > 45){
    hicstat = "DANGER";
  }
  
  lcd.clear();  //Printing Temperature
  lcd.print("T:");
  lcd.print(DHTTemperature, 1);
  lcd.print((char) 223);
  lcd.print("C ");

  lcd.print(" H:"); //Printing Humidity
  lcd.print(DHTHumidity, 0);
  lcd.print(" %");
  
  lcd.setCursor(0,1);
  lcd.print("Hic:"); //Printing Humidity
  lcd.print(hic);
  lcd.print(" ");
  lcd.print(hicstat);

  
}

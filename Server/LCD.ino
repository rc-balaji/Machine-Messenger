#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

WiFiClient wifiClient;
PubSubClient client(wifiClient);
const char* ssid = "AB7";
const char* password = "07070707";
const char* mqtt_server = "broker.hivemq.com";

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Maximum length of the message buffer
const int MAX_MESSAGE_LENGTH = 16;

// Buffer to store the received message
char receivedMessage[MAX_MESSAGE_LENGTH];

void setup_wifi() {
  delay(10);
  Serial.println();

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  // Clear the LCD display
  lcd.clear();
  
  // Construct the message from the payload
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.println(message);

  // Copy the message to the buffer
  //  Serial.println(message);

  DynamicJsonDocument jsonDoc(256);
  deserializeJson(jsonDoc, message);

  Serial.println(jsonDoc["message"].as<String>());

  // lcd.print();
//  Display the message continuously scrolling from right to left
  // for (int i = 0; i < strlen(receivedMessage) + 16; i++) {
    int i =0;
  while(true){
  lcd.setCursor(i, 0);
  lcd.print(jsonDoc["message"].as<String>());
  delay(500);
  lcd.clear();
  if(i==16){
      break;
  }
  i+=1;
}

}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "lcdClient";
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      lcd.clear();

      lcd.print("Connected");
      delay(1300);
      lcd.clear();
      lcd.print("Read to use");
      delay(800);
      lcd.clear();
      lcd.print("wait for message!!!");
      
      client.subscribe("Sami");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.print("Connecting.....");
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();
}

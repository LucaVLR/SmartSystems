#include <Wire.h>
#include <WiFi.h>              // Standard ESP32 Library
#include <PubSubClient.h>      // https://github.com/knolleary/pubsubclient (install with library Manager)
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// WIFI Credentials 
#define WIFI_SSID "Android" // Fill wifi SSID between quotes
#define WIFI_PASS "password" // Fill wifi pass between quotes
#define MQTT_SERVER = "mqtt.luytsm.be";

// WIFI and MQTT class instances
WiFiClient espClient;
PubSubClient client(espClient);

// Dashboard data
String drv_mode, drv_direction;
byte drv_speed = 0;

// Display width and height, pixels
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// SSD1306 display pins connected using SPI
#define OLED_MOSI   23
#define OLED_CLK   18
#define OLED_DC    4
#define OLED_CS    5
#define OLED_RESET 0

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// PWM Settings
#define PWM_FREQUENCY 500
#define PWM_RESOLUTION 8
#define PWM_MAX_DC 255

// Motor PWM Pin declarations
byte MOTOR_PHA[2] = {34, 32};
byte MOTOR_EN[2] = {35, 33};
byte MOTOR_CHANNELS[2] = {0, 1};

// Sensor byte array
byte sense[3];

// Ultrasonic distance edge value
#define BUMP 5

#define ADJUST_LEFT 0
#define ADJUST_RIGHT 1
#define MOTOR_BACKWARDS -1
#define MOTOR_STOP 0
#define MOTOR_FORWARD 1

#define drivingSpeed 128

void setup() {
  Serial.begin(115200);
  
  // init of the PWM Pins
  for (int i = 0; i < 2; i++) {
    ledcSetup(MOTOR_CHANNELS[i], PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(MOTOR_EN[i], MOTOR_CHANNELS[i]);
  }

  Wire.begin();

  // wifi init 
  setup_wifi();

  //mqtt init 
  client.setServer(MQTT_SERVER, 1883);
  client.setCallback(callback);
}

void loop() {
  // every loop checks if there is a connection with the MQTT server if not
  // reconnect 
  if (!client.connected()) {
    reconnect();
  }
  // every loop we will run the MQTT loop and trigger the callback function if neccesary 
  client.loop();

  if(drv_mode == "manueel")
    manueel();
    
  if (drv_mode == "automatisch")
    automatisch();
}

void manueel() {
  drv_speed = map(drv_speed, 0, 100, 0, 255); // map % to u_byte

  if(drv_direction == "stop")
    driveMotors(MOTOR_STOP, 0, MOTOR_STOP, 0);

  else if(drv_direction == "vooruit")
    driveMotors(MOTOR_FORWARD, drv_speed, MOTOR_FORWARD, drv_speed);

  else if(drv_direction == "links")
    driveMotors(MOTOR_BACKWARDS, drv_speed, MOTOR_FORWARD, drv_speed);

  else if(drv_direction == "rechts")
    driveMotors(MOTOR_FORWARD, drv_speed, MOTOR_BACKWARDS, drv_speed);

  else if(drv_direction == "achteruit")
    driveMotors(MOTOR_BACKWARDS, drv_speed, MOTOR_BACKWARDS, drv_speed);

  else if(drv_direction == "links-vooruit")
    driveMotors(MOTOR_FORWARD, drv_speed/2, MOTOR_FORWARD, drv_speed);

  else if(drv_direction == "rechts-vooruit")
    driveMotors(MOTOR_FORWARD, drv_speed, MOTOR_FORWARD, drv_speed/2);

  else if(drv_direction == "links-achter")
    driveMotors(MOTOR_BACKWARDS, drv_speed/2, MOTOR_BACKWARDS, drv_speed);

  else if(drv_direction == "rechts-achter")
    driveMotors(MOTOR_BACKWARDS, drv_speed, MOTOR_BACKWARDS, drv_speed/2);
}

void automatisch() {
  Wire.requestFrom(0xAA, 3);
  byte x = 0;
  while(Wire.available()) {
    sense[x] = Wire.read();
    x++;
  }

  if(sense[0] == BUMP)
    driveMotors(MOTOR_STOP, 0, MOTOR_STOP, 0);
    
  else {
    switch(sense[2]) {
      case 0b00000001 ... 0b00000111:
        driveMotors(MOTOR_FORWARD, drv_speed, MOTOR_FORWARD, drv_speed/2);
        break;

      case 0b00011100 ... 0b00111000:
        driveMotors(MOTOR_FORWARD, drv_speed, MOTOR_FORWARD, drv_speed);
        break;
      
      case 0b10000000 ... 0b01110000:
        driveMotors(MOTOR_FORWARD, drv_speed/2, MOTOR_FORWARD, drv_speed);
        break;
    }
  }
}

void driveMotors(int leftMotorDirection, int leftMotorSpeed, int rightMotorDirection, int rightMotorSpeed) {
  switch(leftMotorDirection) {
    case MOTOR_FORWARD:
      digitalWrite(MOTOR_PHA[0], LOW);
      break;
      
    case MOTOR_BACKWARDS:
      digitalWrite(MOTOR_PHA[0], HIGH);
      break;

    case MOTOR_STOP:
      digitalWrite(MOTOR_PHA[0], LOW);
      break;
  }

  switch(rightMotorDirection) {
    case MOTOR_FORWARD:
      digitalWrite(MOTOR_PHA[1], HIGH);
      break;
      
    case MOTOR_BACKWARDS:
      digitalWrite(MOTOR_PHA[1], LOW);
      break;

    case MOTOR_STOP:
      digitalWrite(MOTOR_PHA[1], LOW);
      break;
  }

  ledcWrite(MOTOR_CHANNELS[0], leftMotorSpeed);
  ledcWrite(MOTOR_CHANNELS[1], rightMotorSpeed);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  //Display that we still are trying to connect 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Normaly the wifi will connect very fast. If it hangs reset the controller with EN button
  // This needs to be done after the controller is programmed

  // Print connection information
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Function to (re)connect to the MQTT server
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8261Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("mode");
      client.subscribe("dir");
      client.subscribe("speed");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

//This function is called when MQTT receives a message 
void callback(char* topic, byte* message, unsigned int length) {
  String data;
  
  for (int i = 0; i < length; i++)
    data += (char)message[i];

  if(String(topic) == "mode")
    drv_mode = data;
  
  else if (String(topic) == "speed")
    drv_speed = data.toInt();
    
  else if (String(topic) == "dir")
    drv_direction = data;
    
  else
    return;
}

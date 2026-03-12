#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

// placeholder pin 1 for pins
// i dont have an esp for pin reference

#define en1Pin 1
#define en2Pin 1
#define in1Pin 1
#define in2Pin 1
#define in3Pin 1
#define in4Pin 1

int speed = 255;
bool out1 = true;
bool out2 = false;
bool reversed = false;

typedef struct command_struct {
  bool rev;
  int command;
} command_struct;

command_struct command_data;

int currComand = 0;

void setup() {
  Serial.begin(115200);
  pinMode(en1Pin, OUTPUT);
  pinMode(en2Pin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}

void setSpeed(int newSpeed) { speed = newSpeed; }

void goForward() {
  digitalWrite(in1Pin, out1);
  digitalWrite(in2Pin, out2);
  digitalWrite(in3Pin, out1);
  digitalWrite(in4Pin, out2);
}

void goLeft() {
  digitalWrite(in1Pin, out1);
  digitalWrite(in2Pin, out2);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
}

void goRight() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, out1);
  digitalWrite(in4Pin, out2);
}

void stop() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
}

void reverse() { reversed = true; }

void forward() { reversed = false; }

void reverseCheck() {
  if (reversed) {
    bool out1 = false;
    bool out2 = true;
  } else {
    bool out1 = true;
    bool out2 = false;
  }
}

void updateCarMovement() {
  switch (currComand) {
  case 0:
    stop();
    break;
  case 1:
    goForward();
    break;
  case 2:
    goLeft();
    break;
  case 3:
    goRight();
    break;
  }
}

void loop() {
  analogWrite(en1Pin, speed);
  analogWrite(en2Pin, speed);

  reverseCheck();
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&command_data, incomingData, sizeof(command_data));
  Serial.print("reverse: ");
  Serial.println(command_data.rev);
  Serial.print("command: ");
  Serial.println(command_data.command);
  Serial.println();
  currComand = command_data.command;
  if (command_data.rev) {
    reverse();
  } else {
    forward();
  }
}
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#define jsVrY 1
#define jsVrX 1

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // temp

typedef struct command_struct {
  bool rev;
  int command;
} command_struct;

command_struct command_data;

esp_now_peer_info_t peerInfo;

int currComand = 0;
bool reversed = false;

int jsx;
int jsy;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0],
           mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success"
                                                : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  pinMode(jsVrX, INPUT);
  pinMode(jsVrY, INPUT);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(esp_now_send_cb_t(OnDataSent));

  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
}

void loop() {

  jsx = analogRead(jsVrX);
  jsy = analogRead(jsVrY);

  if (jsy < 480) {
    reversed = true;
  } else {
    reversed = false;
  }
  if ((jsy < 400 || jsy > 600) && (jsx > 400 || jsx < 600)) {
    currComand = 1;
  } else if (jsx < 400) {
    currComand = 2;
  } else if (jsx > 600) {
    currComand = 3;
  } else {
    currComand = 0;
  }

  command_data.command = currComand;
  command_data.rev = reversed;
  esp_err_t result =
      esp_now_send(0, (uint8_t *)&command_data, sizeof(command_struct));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }
}
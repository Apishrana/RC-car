#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

void setup() {
  Serial.begin(115200);
  Serial.print('mac addres of this esp is : ');
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  uint8_t baseMac[6];
  esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
  Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n", baseMac[0], baseMac[1],
                baseMac[2], baseMac[3], baseMac[4], baseMac[5]);
}

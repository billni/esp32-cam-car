#include <EEPROM.h>

#ifndef _SMART_CONFIG_
#define _SMART_CONFIG_

#define EEPROM_SIZE 1024
struct WifiPwd {
  char ssid[32];
  char pwd[64];
};


void saveConfig(WifiPwd *wifipwd) {
  EEPROM.begin(EEPROM_SIZE);
  uint8_t *p = (uint8_t*)(wifipwd);
  for (int i = 0; i < sizeof(*wifipwd); i++) {
    EEPROM.write(i, *(p + i));
  }
  EEPROM.commit();
  delete wifipwd;
}

WifiPwd* loadConfigs() {
  WifiPwd *pvalue  = new WifiPwd;
  EEPROM.begin(EEPROM_SIZE);
  uint8_t *p = (uint8_t*)(pvalue);
  for (int i = 0; i < sizeof(*pvalue); i++) {
    *(p + i) = EEPROM.read(i);
  }
  EEPROM.commit();
  return pvalue;
}

void clearConfig() {
  EEPROM.begin(EEPROM_SIZE);
  for (int i = 0; i < 96; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}

#endif

/*
Copyright (C) AC SOFTWARE SP. Z O.O.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

//**********************************************************************************
//      DEFINICJE ZMIENNYCH  ----  SKONFIGUROWAĆ PRZED KOMPILACJĄ
//**********************************************************************************

#define DS_PIN 13                 // ESP8266 pin D7 - pin do ktorego sa podpięte DS18B20
#define WIFI_MAC {0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0x62}     //MAC adres - trzeba pamiętać żeby każde urządzenie miało inny MAC-adres
#define WIFI_SSID "xxxxxxx"             // Nazwa sieci Wi-Fi (w cudzysłowiu)
#define WIFI_PASS "xxxxxxxxxxxxxxx"    // Hasło do sieci Wi-Fi (w cudzysłowiu)
#define SUPLA_SERV "svrxxxx.supla.org"    // Serwer SUPLA (w cudzysłowiu)
#define SUPLA_MAIL "xxxxxxx@xxxxxxxxxxx.xx"               // Mail użytkownika (w cudzysłowiu)
#define SUPLA_GUID {0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX}      //SUPLA GUID, zalogować się do supla i wejść na stronę: https://www.supla.org/arduino/get-guid skopiować GID
#define SUPLA_AUTHKEY {0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX,0xXX}   //SUPLA AUTHKEY, zalogować się do supla i wejść na stronę: https://www.supla.org/arduino/get-authkey skopiować AUTHKEY


#define DS18B20_ID1 {0x28,0x79,0x87,0x07,0xD6,0x01,0x3C,0x1D}
#define DS18B20_ID2 {0x28,0x79,0x87,0x07,0xD6,0x01,0x3C,0x1D}
#define DS18B20_ID3 {0x28,0x79,0x87,0x07,0xD6,0x01,0x3C,0x1D}
#define DS18B20_ID4 {0x28,0x79,0x87,0x07,0xD6,0x01,0x3C,0x1D}

//**********************************************************************************


#include <SuplaDevice.h>

/*
 * This example requires Dallas Temperature Control library installed. 
 * https://github.com/milesburton/Arduino-Temperature-Control-Library
 */
// Add include to DS sensor
#include <supla/sensor/DS18B20.h>


// Choose proper network interface for your card:
#ifdef ARDUINO_ARCH_AVR
  // Arduino Mega with EthernetShield W5100:
  #include <supla/network/ethernet_shield.h>
  // Ethernet MAC address
  uint8_t mac[6] = WIFI_MAC;
  Supla::EthernetShield ethernet(mac);

  // Arduino Mega with ENC28J60:
  // #include <supla/network/ENC28J60.h>
  // Supla::ENC28J60 ethernet(mac);
#elif defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
  // ESP8266 and ESP32 based board:
  #include <supla/network/esp_wifi.h>
  Supla::ESPWifi wifi(WIFI_SSID, WIFI_PASS);
#endif

void setup() {

  Serial.begin(115200);

  // Replace the falowing GUID with value that you can retrieve from https://www.supla.org/arduino/get-guid
  char GUID[SUPLA_GUID_SIZE] = SUPLA_GUID;

  // Replace the following AUTHKEY with value that you can retrieve from: https://www.supla.org/arduino/get-authkey
  char AUTHKEY[SUPLA_AUTHKEY_SIZE] = SUPLA_AUTHKEY;

  /*
   * Having your device already registered at cloud.supla.org,
   * you want to change CHANNEL sequence or remove any of them,
   * then you must also remove the device itself from cloud.supla.org.
   * Otherwise you will get "Channel conflict!" error.
   */

  // CHANNEL0-3 - Thermometer DS18B20
  // 4 DS18B20 thermometers at pin 23. DS address can be omitted when there is only one device at a pin
  DeviceAddress ds1addr = DS18B20_ID1;
  DeviceAddress ds2addr = DS18B20_ID2;
  DeviceAddress ds3addr = DS18B20_ID3;
  DeviceAddress ds4addr = DS18B20_ID4;

  new Supla::Sensor::DS18B20(DS_PIN, ds1addr);
  new Supla::Sensor::DS18B20(DS_PIN, ds2addr);
  new Supla::Sensor::DS18B20(DS_PIN, ds3addr);
  new Supla::Sensor::DS18B20(DS_PIN, ds4addr);


  /*
   * SuplaDevice Initialization.
   * Server address, LocationID and LocationPassword are available at https://cloud.supla.org 
   * If you do not have an account, you can create it at https://cloud.supla.org/account/create
   * SUPLA and SUPLA CLOUD are free of charge
   * 
   */

  SuplaDevice.begin(GUID,              // Global Unique Identifier 
                    SUPLA_SERV,  // SUPLA server address
                    SUPLA_MAIL,   // Email address used to login to Supla Cloud
                    AUTHKEY);          // Authorization key
    
}

void loop() {
  SuplaDevice.iterate();
}

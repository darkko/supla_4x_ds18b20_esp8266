# supla_4x_ds18b20_esp8266
Urządzenie do pomiaru 4 temperatur za pomocą ESP8266 i wysyłania danych na serwer SUPLA

Przed wgraniem programu do ESP8266 trzeba wykonać następujące działania:
- odczytać ID sensorów DS18B20
- zakładamy konto na SUPLA
- pobieramy SUPLA GUID - zalogować się do SUPLA i wejść na stronę: https://www.supla.org/arduino/get-guid skopiować GID
- pobieramy SUPL AUTHKEY - zalogować się do SUPLA i wejść na stronę: https://www.supla.org/arduino/get-authkey skopiować AUTHKEY
- uruchamiamy Arduino IDE
- trzeba dodać bibliotekę: SuplaDevice do Arduino IDE
- w preferencjach dodać w linii "Dodatkowe adresy URL do menadżera płytek": http://arduino.esp8266.com/stable/package_esp8266com_index.json (jeśli nie ma tego dodanego).
- otworzyć plik .ini w Arduino IDE
- uzupełnić zmienne konfiguracyjne
- wgrać kprogram na płytkę ESP8266

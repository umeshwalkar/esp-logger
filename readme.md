# ESP Logger for Arduino IDE
ESP Logger is an Arduino library designed to standardize the basic operations on log files on ESP8266/ESP32 SoC.

### Features
1. Support to SPIFFS (the internal Flash) and SD card.
2. Methods to monitor log dimension, to avoid collision with other files
3. Support to multiple log files to store different information.
4. The data are retrive in the order they are gathered. that means in FIFO manner.
5. Full control on when and how flush your data.
6. Agnostic with respect to data format, the atomic measurement unit is *Record*
   
### Assumption
* flash memory is reliable, the data corruption is not managed.
* Fixed length log record.

### Installation
This is a regular Arduino library, so installiation is straightforward from Library Manager. If you desire the lastest Github version, you can download this repo and copy the entire folder in your Arduino Library directory. More info at [Arduino Library](https://www.arduino.cc/en/Guide/Libraries).

### API and Examples
After installing, you can see the examples to understand how easy is mastering this library. For advacend usages (and advanced users), the full library specifications can be found directy in *commented* header (*.h) files.
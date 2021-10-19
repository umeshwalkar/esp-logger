#ifndef ESP_LOGGER_SPIFFS_H
#define ESP_LOGGER_SPIFFS_H

#include "esp-logger.h"

/**
 * For further details look at the base class Logger
 */
class EspLoggerSPIFFS : public EspLogger{
  public:
  
  EspLoggerSPIFFS(String file, unsigned int packetSize, unsigned int maxNumOfPackets);

  bool begin();

  //bool append(String message, bool timestamp = true);

  //void reset();
  
  //bool flush();

  //unsigned int getActualSize();
  bool getCount(unsigned int *pTotalLogs);
  bool clear();
  bool push(const uint8_t *data);
  bool pop( uint8_t *data);
  bool get( uint8_t *data, unsigned int logNum);
//  bool reset();
};


#endif //END ESP_LOGGER_SPIFFS_H

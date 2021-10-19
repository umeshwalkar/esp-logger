#ifndef ESP_LOGGER_H
#define ESP_LOGGER_H

#include <Arduino.h>

#define DEBUG_ESP_LOGGER

//#ifdef DEBUG_ESP_PORT
//#define DEBUG_OUTPUT DEBUG_ESP_PORT
//#else
//#define DEBUG_OUTPUT Serial
//#endif

//#define ESP_LOG_NO_ERROR        0
//#define ESP_LOG_FILE_OPEN_ERROR 1

/**
   This class is responsible for a log file.
*/
class EspLogger {
  public:
    EspLogger(String file, unsigned int packetSize, unsigned int maxNumOfPackets);

    /**
       Start the Filesystem, call this before starting to append or
       flush, return true is case of success, false otherwise

       Actually this is just a wrapper for concrete begin(..) method
    */
    virtual bool begin() = 0;

    virtual bool getCount(unsigned int *pTotalLogs) = 0;
    virtual bool clear() = 0;
    virtual bool push(const uint8_t *data) = 0;
    virtual bool pop( uint8_t *data) = 0;
    virtual bool get( uint8_t *data, unsigned int logNum) = 0;
//    virtual bool reset() = 0;

    virtual ~EspLogger();

  protected:

    /**
      Actual log file
    */
    String filePath;

    /**
      size of one packet to be rocord
    */
    unsigned int onePacketSize;

    /**
      size of total number of packets to be rocord
    */
    unsigned int maxPackets;

    unsigned int last_error_code;

    /*typedef union {
      uint8_t Array[6];

      struct {
        uint16_t Current;
        uint16_t Start;
        uint16_t End;
      };
    } LOG_INFO;*/
};
#endif  //END ESP_LOGGER_H

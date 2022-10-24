#ifndef SERIAL_DEBUG_H
#define SERIAL_DEBUG_H

#include <Arduino.h>
#include <stdint.h>

typedef String DebugString;

class SerialDebug
{
    public:

        typedef enum
        {
            baud_9600 = 0,
            baud_19200,
            baud_38400,
            baud_57600,
            baud_115200,
            baud_921600
        }baudrate;

        typedef enum
        {
            error = 0,
            info,
            verbose,
            debug, 
            error_info,
            error_verbose,
            error_debug,
            info_verbose,
            info_debug,
            verbose_debug,
            all
        }debug_level;


        SerialDebug(baudrate Baudrate, bool LogEnabled);
        void init();
        void setDebugLevel(debug_level DebugLevel = all);
        void setLogStatus(bool Enable);
        void setTimePrint(bool Enable);
        void logError(DebugString Message, bool NewLine = true);
        void logInfo(DebugString Message, bool NewLine = true);
        void logVerbose(DebugString Message, bool NewLine = true);
        void logDebug(DebugString Message, bool NewLine = true);

    private:

        debug_level _debugLevel;
        bool _serialItitialized = false;
        bool _logEnabled = false;
        bool _enableTimePrint = false;
        uint32_t _baudRate = 9600;
        DebugString _timeLog();
        DebugString _buildMsg(DebugString Msg, DebugString Level);
};


extern SerialDebug Debug;

#endif
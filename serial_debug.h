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
            ard_1_serial = 0,
            ard_mega_serial_1,
            ard_mega_serial_2,
            ard_mega_serial_3,
        }serial_used;

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


        SerialDebug(serial_used SerialUsed, baudrate Baudrate, bool LogEnabled);
        void setDebugLevel(debug_level DebugLevel);
        void setLogStatus(bool Enable);
        void setTimePrint(bool Enable);
        void logError(DebugString Message, bool NewLine = true);
        void logInfo(DebugString Message, bool NewLine = true);
        void logVerbose(DebugString Message, bool NewLine = true);
        void logDebug(DebugString Message, bool NewLine = true);

    private:

        HardwareSerial *_debugSerial;
        debug_level _debugLevel;
        bool _logEnabled = false;
        bool _enableTimePrint = false;
        DebugString _timeLog();
        DebugString _buildMsg(DebugString Msg, DebugString Level);
};

#endif
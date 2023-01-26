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
            error_info_debug,
            error_info_verbose,
            all
        }debug_level;

        /**
         * @brief Construct a new Serial Debug object
         * 
         * @param baudrate Baudrate 
         * @param bool LogEnabled 
         */
        SerialDebug(baudrate Baudrate, bool LogEnabled);

        /**
         * @brief Initialize all the variables for the log
         * 
         */
        void init();

        /**
         * @brief Set the Debug Level 
         * 
         * @param debug_level DebugLevel 
         */
        void setDebugLevel(debug_level DebugLevel = all);

        /**
         * @brief Set the Log Status 
         * 
         * @param bool Enable 
         */
        void setLogStatus(bool Enable);

        /**
         * @brief Set the Time Print 
         * 
         * @param bool Enable 
         */
        void setTimePrint(bool Enable);

        /**
         * @brief 
         * 
         * @param DebugString Message 
         * @param bool NewLine
         */
        void logError(DebugString Message, bool NewLine = true);

        /**
         * @brief 
         * 
         * @param DebugString Message 
         * @param bool NewLine
         */
        void logInfo(DebugString Message, bool NewLine = true);
        
        /**
         * @brief 
         * 
         * @param DebugString Message 
         * @param bool NewLine
         */
        void logVerbose(DebugString Message, bool NewLine = true);

        /**
         * @brief 
         * 
         * @param DebugString Message 
         * @param bool NewLine
         */
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
#ifndef SERIAL_LOG_H
#define SERIAL_LOG_H

#include <Arduino.h>
#include <stdint.h>

typedef String LogString;

class Logger
{
    public:
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
        }log_level;

        /**
         * @brief Set the Print Call Back function thats print the message
         * 
         * @param void (*PrintCB)(const char *Message) 
         */
        void setPrintCallBack(void (*PrintCB)(const char *Message));

        /**
         * @brief Set the Module Name of the logger
         * 
         * @param LogString ModuleName 
         */
        void setModuleName(LogString ModuleName);

        /**
         * @brief Set the RootLogger Level 
         * 
         * @param log_level DebugLevel 
         */
        void setDebugLevel(log_level LogLevel = all);

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
         * @param LogString Message 
         * @param bool NewLine
         */
        void logError(LogString Message, bool NewLine = true);

        /**
         * @brief 
         * 
         * @param LogString Message 
         * @param bool NewLine
         */
        void logInfo(LogString Message, bool NewLine = true);
        
        /**
         * @brief 
         * 
         * @param LogString Message 
         * @param bool NewLine
         */
        void logVerbose(LogString Message, bool NewLine = true);

        /**
         * @brief 
         * 
         * @param LogString Message 
         * @param bool NewLine
         */
        void logDebug(LogString Message, bool NewLine = true);   

    private:
        log_level _logLevel;
        bool _logEnabled = false;
        bool _enableTimePrint = false;
        LogString _moduleName = "root";
        void (*_printCB)(const char *Message);
        LogString _buildMsg(LogString OrigMsg, LogString Level, bool NewLine);

};

class ArduinoLogger : public Logger
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

        /**
         * @brief Construct a new Serial RootLogger object
         * 
         * @param baudrate Baudrate 
         * @param bool LogEnabled 
         */
        ArduinoLogger(baudrate Baudrate, log_level Level, bool LogEnabled, bool TimeprintEnable);

        /**
         * @brief Initialize the serial (REQUIRED)
         * 
         */
        void init();


    private:

        bool _serialItitialized = false;
        uint32_t _baudRate = 9600;
};

class ArduinoBranchLogger : public Logger
{
    public:

        ArduinoBranchLogger(LogString BranchName, log_level Level, bool LogEnable, bool TimeprintEnable);

        /**
         * @brief Set the Branch Name of the log
         * 
         * @param LogString BranchName 
         */
        void setBranchName(LogString BranchName);


    private:
        LogString _moduleName = "";
};

extern ArduinoLogger RootLogger;

#endif
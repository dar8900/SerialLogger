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
         * @brief Set the RootLogger Level 
         * 
         * @param log_level DebugLevel 
         */
        void setDebugLevel(log_level LogLevel = all) = 0;

        /**
         * @brief Set the Log Status 
         * 
         * @param bool Enable 
         */
        void setLogStatus(bool Enable) = 0;

        /**
         * @brief Set the Time Print 
         * 
         * @param bool Enable 
         */
        void setTimePrint(bool Enable) = 0;
        
        /**
         * @brief 
         * 
         * @param LogString Message 
         * @param bool NewLine
         */
        void logError(LogString Message, bool NewLine = true) = 0;

        /**
         * @brief 
         * 
         * @param LogString Message 
         * @param bool NewLine
         */
        void logInfo(LogString Message, bool NewLine = true) = 0;
        
        /**
         * @brief 
         * 
         * @param LogString Message 
         * @param bool NewLine
         */
        void logVerbose(LogString Message, bool NewLine = true) = 0;

        /**
         * @brief 
         * 
         * @param LogString Message 
         * @param bool NewLine
         */
        void logDebug(LogString Message, bool NewLine = true) = 0;   


};

class MasterLogger : public Logger
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
        MasterLogger(baudrate Baudrate = 115200, log_level Level, bool LogEnabled = true, bool TimeprintEnable);

        /**
         * @brief Initialize the serial (REQUIRED)
         * 
         */
        void init();

        /**
         * @brief Set the RootLogger Level 
         * 
         * @param log_level DebugLevel 
         */
        void setDebugLevel(log_level DebugLevel = all);

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
        bool _serialItitialized = false;
        bool _logEnabled = false;
        bool _enableTimePrint = false;
        uint32_t _baudRate = 9600;
        LogString _buildMsg(LogString OrigMsg, LogString Level, bool NewLine);
};

class BranchLogger : public Logger
{
    public:

        BranchLogger(LogString BranchName, log_level Level, bool LogEnable, bool TimeprintEnable);

        /**
         * @brief Set the Branch Name of the log
         * 
         * @param LogString BranchName 
         */
        void setBranchName(LogString BranchName);

        /**
         * @brief Set the RootLogger Level 
         * 
         * @param log_level DebugLevel 
         */
        void setDebugLevel(log_level DebugLevel = all);

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
        LogString _moduleName = "";
        LogString _buildMsg(LogString OrigMsg, log_level Level, bool NewLine);
};

extern MasterLogger RootLogger;

#endif
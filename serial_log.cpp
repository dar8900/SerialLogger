#include "serial_log.h"

#ifdef ESP8266
#define DebugSerial Serial
#elif ESP32
#define DebugSerial Serial
#else

#if defined(UBRRH) || defined(UBRR0H)
#define DebugSerial Serial
#endif
#if defined(UBRR1H)
#define DebugSerial Serial1
#endif
#endif

static void PrintSerialMessage(const char *Message)
{
#ifndef ARDUINO_AVR_ATTINYX5	
	DebugSerial.print(Message);
#endif
}

void Logger::setPrintCallBack(void (*PrintCB)(const char *Message))
{
	if(PrintCB){
		_printCB = PrintCB;
	}
}

void Logger::setModuleName(LogString ModuleName)
{
	_moduleName = ModuleName;
}

void Logger::setDebugLevel(log_level LogLevel)
{
	_logLevel = LogLevel;
}

void Logger::setLogStatus(bool Enable)
{
	_logEnabled = Enable;
}

void Logger::setTimePrint(bool Enable)
{
	_enableTimePrint = Enable;
}

LogString Logger::_buildMsg(LogString Msg, LogString Level, bool NewLine)
{
	LogString Time = "";
	if (_enableTimePrint)
	{
		LogString TimePrint = "";
		uint32_t LogTime = millis();
		if (LogTime <= 1000)
		{
			TimePrint = String(LogTime) + "ms";
		}
		else
		{
			LogTime /= 1000;
			TimePrint = String(LogTime) + "s";
		}
		Time = TimePrint + " ";
	}
	Msg = Time + Level + "\t" + _moduleName + "\t" + Msg + (NewLine ? "\n" : "");
	return Msg;
}

void Logger::logError(LogString Message, bool NewLine)
{
	if (_logEnabled && (_logLevel == error ||
						_logLevel == error_debug ||
						_logLevel == error_info ||
						_logLevel == error_verbose ||
						_logLevel == error_info_debug ||
						_logLevel == error_info_verbose ||
						_logLevel == all))
	{
		Message = _buildMsg(Message, "[ERROR]", NewLine);
		_printCB(Message.c_str());
	}
}

void Logger::logInfo(LogString Message, bool NewLine)
{
	if (_logEnabled && (_logLevel == info ||
						_logLevel == error_info ||
						_logLevel == info_debug ||
						_logLevel == info_verbose ||
						_logLevel == error_info_debug ||
						_logLevel == all))
	{
		Message = _buildMsg(Message, "[INFO]", NewLine);
		_printCB(Message.c_str());
	}
}

void Logger::logVerbose(LogString Message, bool NewLine)
{
	if (_logEnabled && (_logLevel == verbose ||
						_logLevel == error_verbose ||
						_logLevel == verbose_debug ||
						_logLevel == info_verbose ||
						_logLevel == error_info_verbose ||
						_logLevel == all))
	{
		Message = _buildMsg(Message, "[VERB]", NewLine);
		_printCB(Message.c_str());
	}
}

void Logger::logDebug(LogString Message, bool NewLine)
{
	if (_logEnabled && (_logLevel == debug ||
						_logLevel == error_debug ||
						_logLevel == info_debug ||
						_logLevel == verbose_debug ||
						_logLevel == error_info_debug ||
						_logLevel == all))
	{
		Message = _buildMsg(Message, "[DEBUG]", NewLine);
		_printCB(Message.c_str());
	}
}


ArduinoLogger::ArduinoLogger(baudrate Baudrate, log_level Level, bool LogEnabled, bool TimeprintEnable)
{
	switch (Baudrate)
	{
	case baud_9600:
		_baudRate = 9600;
		break;
	case baud_19200:
		_baudRate = 19200;
		break;
	case baud_38400:
		_baudRate = 38400;
		break;
	case baud_57600:
		_baudRate = 5760;
		break;
	case baud_115200:
		_baudRate = 115200;
		break;
	case baud_921600:
		_baudRate = 921600;
		break;
	default:
		break;
	}
	setDebugLevel(Level);
	setLogStatus(LogEnabled);
	setTimePrint(TimeprintEnable);
}

void ArduinoLogger::init()
{
	if (!_serialItitialized)
	{
#ifndef ARDUINO_AVR_ATTINYX5		
		DebugSerial.begin(_baudRate);
#endif		
	}
	_serialItitialized = true;
	setPrintCallBack(PrintSerialMessage);
}

ArduinoBranchLogger::ArduinoBranchLogger(LogString BranchName, log_level Level, bool LogEnable, bool TimeprintEnable)
{
	setDebugLevel(Level);
	setLogStatus(LogEnable);
	setTimePrint(TimeprintEnable);
	setBranchName(BranchName);
	setPrintCallBack(PrintSerialMessage);
}

void ArduinoBranchLogger::setBranchName(LogString BranchName)
{
	setModuleName(BranchName);
}


ArduinoLogger RootLogger(ArduinoLogger::baudrate::baud_115200, Logger::log_level::all, true, false);
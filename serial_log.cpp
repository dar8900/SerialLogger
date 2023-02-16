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

MasterLogger::MasterLogger(baudrate Baudrate, log_level Level, bool LogEnabled, bool TimeprintEnable)
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

void MasterLogger::init()
{
	if (!_serialItitialized)
	{
		DebugSerial.begin(_baudRate);
	}
	_serialItitialized = true;
}

void MasterLogger::setDebugLevel(log_level LogLevel)
{
	_logLevel = LogLevel;
}

void MasterLogger::setLogStatus(bool Enable)
{
	_logEnabled = Enable;
}

void MasterLogger::setTimePrint(bool Enable)
{
	_enableTimePrint = Enable;
}

LogString MasterLogger::_buildMsg(LogString Msg, LogString Level, bool NewLine)
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
	Msg = Time + Level + "\t" + "root - " + Msg + (NewLine ? "\n" : "");
	return Msg;
}

void MasterLogger::logError(LogString Message, bool NewLine)
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
		DebugSerial.print(Message);
	}
}

void MasterLogger::logInfo(LogString Message, bool NewLine)
{
	if (_logEnabled && (_logLevel == info ||
						_logLevel == error_info ||
						_logLevel == info_debug ||
						_logLevel == info_verbose ||
						_logLevel == error_info_debug ||
						_logLevel == all))
	{
		Message = _buildMsg(Message, "[INFO]", NewLine);
		DebugSerial.print(Message);
	}
}

void MasterLogger::logVerbose(LogString Message, bool NewLine)
{
	if (_logEnabled && (_logLevel == verbose ||
						_logLevel == error_verbose ||
						_logLevel == verbose_debug ||
						_logLevel == info_verbose ||
						_logLevel == error_info_verbose ||
						_logLevel == all))
	{
		Message = _buildMsg(Message, "[VERB]", NewLine);
		DebugSerial.print(Message);
	}
}

void MasterLogger::logDebug(LogString Message, bool NewLine)
{
	if (_logEnabled && (_logLevel == debug ||
						_logLevel == error_debug ||
						_logLevel == info_debug ||
						_logLevel == verbose_debug ||
						_logLevel == error_info_debug ||
						_logLevel == all))
	{
		Message = _buildMsg(Message, "[DEBUG]", NewLine);
		DebugSerial.print(Message);
	}
}

LogString BranchLogger::_buildMsg(LogString Msg, LogString Level, bool NewLine)
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

	Msg = Time + Level + "\t" + _moduleName + " - " + Msg + (NewLine ? "\n" : "");
	return Msg;
}

BranchLogger::BranchLogger(LogString BranchName, log_level Level, bool LogEnable, bool TimeprintEnable)
{
	setDebugLevel(Level);
	setLogStatus(LogEnable);
	setTimePrint(TimeprintEnable);
	setBranchName(BranchName);
}

void BranchLogger::setBranchName(LogString BranchName)
{
	_moduleName = BranchName;
}

void BranchLogger::setDebugLevel(log_level LogLevel)
{
	_logLevel = LogLevel;
}

void BranchLogger::setLogStatus(bool Enable)
{
	_logEnabled = Enable;
}

void BranchLogger::setTimePrint(bool Enable)
{
	_enableTimePrint = Enable;
}

void BranchLogger::logError(LogString Message, bool NewLine)
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
		DebugSerial.print(Message);
	}
}

void BranchLogger::logInfo(LogString Message, bool NewLine)
{
	if (_logEnabled && (_logLevel == info ||
						_logLevel == error_info ||
						_logLevel == info_debug ||
						_logLevel == info_verbose ||
						_logLevel == error_info_debug ||
						_logLevel == all))
	{
		Message = _buildMsg(Message, "[INFO]", NewLine);
		DebugSerial.print(Message);
	}
}

void BranchLogger::logVerbose(LogString Message, bool NewLine)
{
	if (_logEnabled && (_logLevel == verbose ||
						_logLevel == error_verbose ||
						_logLevel == verbose_debug ||
						_logLevel == info_verbose ||
						_logLevel == error_info_verbose ||
						_logLevel == all))
	{
		Message = _buildMsg(Message, "[VERB]", NewLine);
		DebugSerial.print(Message);
	}
}

void BranchLogger::logDebug(LogString Message, bool NewLine)
{
	if (_logEnabled && (_logLevel == debug ||
						_logLevel == error_debug ||
						_logLevel == info_debug ||
						_logLevel == verbose_debug ||
						_logLevel == error_info_debug ||
						_logLevel == all))
	{
		Message = _buildMsg(Message, "[DEBUG]", NewLine);
		DebugSerial.print(Message);
	}
}

MasterLogger RootLogger(MasterLogger::baudrate::baud_115200, Logger::log_level::all, true, false);
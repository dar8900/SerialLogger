#include "serial_debug.h"


#if defined(UBRRH) || defined(UBRR0H)
  #define DebugSerial	Serial
#endif
#if defined(UBRR1H)
  #define DebugSerial	Serial1
#endif


SerialDebug::SerialDebug(baudrate Baudrate, bool LogEnabled)
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
	_logEnabled = LogEnabled;
}

DebugString SerialDebug::_timeLog()
{
	DebugString TimePrint = "";
	uint32_t DebugTime = millis();
	if(DebugTime <= 1000)
	{
		TimePrint = String(DebugTime) + "ms";
	}
	else
	{
		DebugTime /= 1000;
		TimePrint = String(DebugTime) + "s";
	}
	return TimePrint;
}

void SerialDebug::init()
{
	DebugSerial.begin(_baudRate);
	_serialItitialized = true;
}

void SerialDebug::setDebugLevel(debug_level DebugLevel)
{
	_debugLevel = DebugLevel;
}

void SerialDebug::setLogStatus(bool Enable)
{
	if(!_serialItitialized)
	{
		init();
	}
	_logEnabled = Enable;
}

void SerialDebug::setTimePrint(bool Enable)
{
	_enableTimePrint = Enable;
}

DebugString SerialDebug::_buildMsg(DebugString Msg, DebugString Level)
{
	DebugString Time = "";
	if(_enableTimePrint)
	{
		Time = _timeLog() + " ";
	}
	Msg = Time + Level + "\t" + Msg;
	return Msg;
}

void SerialDebug::logError(DebugString Message, bool NewLine)
{
	if(_logEnabled)
	{
		if(_debugLevel == error || 
			_debugLevel == error_debug ||
			_debugLevel == error_info ||
			_debugLevel == error_verbose ||
			_debugLevel == error_info_debug ||
			_debugLevel == error_info_verbose ||
			_debugLevel == all)
		{
			Message = _buildMsg(Message, "[ERROR]");
			if(NewLine)
			{
				DebugSerial.println(Message);
			}
			else
			{
				DebugSerial.print(Message);
			}
		}
	}
}

void SerialDebug::logInfo(DebugString Message, bool NewLine)
{
	if(_logEnabled)
	{	
		if(_debugLevel == info ||
			_debugLevel == error_info ||
			_debugLevel == info_debug ||
			_debugLevel == info_verbose ||
			_debugLevel == error_info_debug ||
			_debugLevel == all)
		{
			Message = _buildMsg(Message, "[INFO]");
			if(NewLine)
			{
				DebugSerial.println(Message);
			}
			else
			{
				DebugSerial.print(Message);
			}
		}
	}
}

void SerialDebug::logVerbose(DebugString Message, bool NewLine)
{
	if(_logEnabled)
	{
		if(_debugLevel == verbose ||
			_debugLevel == error_verbose ||
			_debugLevel == verbose_debug ||
			_debugLevel == info_verbose ||
			_debugLevel == error_info_verbose ||
			_debugLevel == all)
		{
			Message = _buildMsg(Message, "[VERB]");
			if(NewLine)
			{
				DebugSerial.println(Message);
			}
			else
			{
				DebugSerial.print(Message);
			}
		}
	}
}

void SerialDebug::logDebug(DebugString Message, bool NewLine)
{
	if(_logEnabled)
	{
		if(_debugLevel == debug ||
			_debugLevel == error_debug ||
			_debugLevel == info_debug ||
			_debugLevel == verbose_debug ||
			_debugLevel == error_info_debug ||
			_debugLevel == all)
		{
			Message = _buildMsg(Message, "[DEBUG]");
			if(NewLine)
			{
				DebugSerial.println(Message);
			}
			else
			{
				DebugSerial.print(Message);
			}
		}
	}
}

SerialDebug Debug(SerialDebug::baudrate::baud_115200, true);
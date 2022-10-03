#include "serial_debug.h"

SerialDebug::SerialDebug(serial_used SerialUsed, baudrate Baudrate, bool LogEnabled) : _logEnabled(LogEnabled)
{
    switch (_debugSerial)
    {
        case ard_1_serial:
			_debugSerial = Serial;
			break;
		case ard_mega_serial_1:
			_debugSerial = Serial1;
			break;
		case ard_mega_serial_2:
			_debugSerial = Serial2;
			break;
		case ard_mega_serial_3:
			_debugSerial = Serial3;
			break;
		default:
			_debugSerial = Serial;
        	break;
    }

	switch (Baudrate)
	{
		case baud_9600:
			_debugSerial.begin(9600);
			break;
		case baud_19200:
			_debugSerial.begin(19200);
			break;
		case baud_38400:
			_debugSerial.begin(38400);
			break;
		case baud_57600:
			_debugSerial.begin(5760);
			break;
		case baud_115200:
			_debugSerial.begin(115200);
			break;
		case baud_921600:
			_debugSerial.begin(921600);
			break;
		default:
			break;
	}
	
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

void SerialDebug::setDebugLevel(debug_level DebugLevel)
{
	_debugLevel = DebugLevel;
}

void SerialDebug::setLogStatus(bool Enable)
{
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
		Time = _timeLog + " ";
	}
	Msg = Time + Level + "\t" + Msg;
	return Msg;
}

void SerialDebug::logError(DebugString Message)
{
	if(_logEnabled)
	{
		if(_debugLevel == error || 
			_debugLevel == error_debug ||
			_debugLevel == error_info ||
			_debugLevel == error_verbose ||
			_debugLevel == all)
		{
			Message = _buildMsg(Message, "[ERROR]");
			_debugSerial.print(Message);
		}
	}
}

void SerialDebug::logInfo(DebugString Message)
{
	if(_logEnabled)
	{	
		if(_debugLevel == info ||
			_debugLevel == error_info ||
			_debugLevel == info_debug ||
			_debugLevel == info_verbose ||
			_debugLevel == all)
		{
			Message = _buildMsg(Message, "[INFO]");
			_debugSerial.print(Message);
		}
	}
}

void SerialDebug::logVerbose(DebugString Message)
{
	if(_logEnabled)
	{
		if(_debugLevel == verbose ||
			_debugLevel == error_verbose ||
			_debugLevel == verbose_debug ||
			_debugLevel == info_verbose ||
			_debugLevel == all)
		{
			Message = _buildMsg(Message, "[VERB]");
			_debugSerial.print(Message);
		}
	}
}

void SerialDebug::logDebug(DebugString Message)
{
	if(_logEnabled)
	{
		if(_debugLevel == debug ||
			_debugLevel == error_debug ||
			_debugLevel == info_debug ||
			_debugLevel == verbose_debug ||
			_debugLevel == all)
		{
			Message = _buildMsg(Message, "[DEBUG]");
			_debugSerial.print(Message);
		}
	}
}

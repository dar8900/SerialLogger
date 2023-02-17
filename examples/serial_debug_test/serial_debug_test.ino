#include "serial_debug.h"

void setup()
{
	RootLogger.init();
	RootLogger.setDebugLevel(ArduinoLogger::log_level::all);	
}

void loop()
{
	RootLogger.logError("Error");
	RootLogger.logInfo("Info");
	RootLogger.logVerbose("Verb");
	RootLogger.logDebug("Debug");
	delay(1000);
}
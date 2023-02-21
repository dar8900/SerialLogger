#include <serial_log.h>
#include "main.h"

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
	test_func();
	delay(1000);
}
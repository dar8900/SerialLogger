#include "serial_debug.h"

void setup()
{
	Debug.init();
	Debug.setTimePrint(true);
	Debug.setDebugLevel(SerialDebug::debug_level::all);	
}

void loop()
{
	Debug.logError("Error");
	Debug.logInfo("Info");
	Debug.logVerbose("Verb");
	Debug.logDebug("Debug");
	delay(1000);
}
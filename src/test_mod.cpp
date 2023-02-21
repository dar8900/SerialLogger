#include <serial_log.h>
#include "main.h"

ArduinoBranchLogger BranchLogger("test_mod", Logger::log_level::error_info_debug, true, false);


void test_func()
{
	BranchLogger.logInfo("Test info log");
}
# ARDUINO SERIAL LOG

##  Library to print debug serial message in arduino environment

# USAGE

## Initialize the library with the Baudrate setted and optionally enable the debug print
``` c++
SerialDebug(baudrate Baudrate, bool LogEnabled);
```
## Initialize all the variables, mandatory
``` c++
void init();
```
## Set the debug level
``` c++
void setDebugLevel(debug_level DebugLevel = all);
```

## Enable/disable the logging
``` c++
void setLogStatus(bool Enable);
```

## Show the time passed in the log
``` c++
void setTimePrint(bool Enable);
```

## Log only errors log
``` c++
void logError(DebugString Message, bool NewLine = true);
```

## Log only info log
``` c++
void logInfo(DebugString Message, bool NewLine = true);
```

## Log only verbose log
``` c++
void logVerbose(DebugString Message, bool NewLine = true);
```

## Log only debug log
``` c++
void logDebug(DebugString Message, bool NewLine = true);
```


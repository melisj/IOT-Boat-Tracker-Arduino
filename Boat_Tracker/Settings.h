// Hardcoded boat
const String BOAT_NAME = "viermineen";

// Button Setup
#define BUTTON_PIN D1
bool buttonPressed = false;

// Init the network data
//const String networkName = "TELE2-A7E7F3_2.4G";
//const String password = "36D49969D4C3";
const String networkName = "NokiaPower";
const String password = "arduinoenzo";

// Domain main
const String domainName = "boattracker.duckdns.org";
const String ipBackupName = "192.168.43.4"; 

// Connection for the weather API and calibration of the position
const String weatherUrl = "http://" + ipBackupName + "/arduino/weather?boat_name=" + BOAT_NAME;
const String calibrateUrl = "http://" + ipBackupName + "/arduino/calibrate";

// Delays
const int secondDelayForWeather = 60;

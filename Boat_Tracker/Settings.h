// Hardcoded boat
const String BOAT_NAME = "viermineen";

// Button Setup
#define BUTTON_PIN D1
bool buttonPressed = false;

// Init the network data
const String networkName = "TELE2-A7E7F3_2.4G";
const String password = "36D49969D4C3";
//const String networkName = "NokiaPower";
//const String password = "arduinoenzo";

// Domain main
const String domainName = "boattracker.duckdns.org";
const String ipBackupName = "192.168.43.4"; 

// Connection for the weather API and calibration of the position
const String weatherUrl = "http://" + domainName + "/arduino/weather?boat_name=" + BOAT_NAME;
const String calibrateUrl = "http://" + domainName + "/arduino/calibrate";

// Delays
const int secondDelayForWeather = 60;

// Sound notes
#define NOTE_A 50
#define NOTE_B 100
#define NOTE_C 200
#define NOTE_D 400
#define NOTE_E 800
#define NOTE_F 1600
#define NOTE_G 3200
#define NOTE_H 6400

// Setup the speaker
#define BUZZER_PIN_1 D5
#define BUZZER_PIN_2 D6
bool soundSwitch;

// Sound to play
const int allNotes[] = {NOTE_A, NOTE_B, NOTE_C, NOTE_D, NOTE_E, NOTE_F, NOTE_G, NOTE_H};
const int asciiValueA = (int)'A';
const int asciiValueDash= (int)'-';

// Max length of 32 audio tones
const String introAudio = "[F100/-100/F100/-100/F100/E100/-100/D100/D100/D100/]";
const String connectionAudio = "[D100/-100/F100/-100/G100/F100/E100/]";
const String succesRequest = "[D100/E100/-100/D100/-100/-100/B100/]";

class AudioObject {
  public:
    int currentSequenceLength = 0;
    int currentSequenceNotes[32];
    int currentSequenceTimes[32];
};

// Setup the led
#define LED_COUNT 3
#define LED_PIN D2
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN);

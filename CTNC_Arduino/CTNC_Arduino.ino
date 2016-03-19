
#include <SoftwareSerial.h>
SoftwareSerial esp(10, 11); // RX, TX
HardwareSerial & dbg = Serial;

String gEspResponse = "";
String gEspSoftwareVersion = "";

// Port configuration
uint8_t gpio[10] = {
  /* 0  */ A0,
  /* 1  */ 2,
  /* 2  */ 3,
  /* 3  */ 12,
  /* 4  */ 13,
  /* 5  */ A1,
  /* 6  */ 4,
  /* 7  */ 5,
  /* 8  */ 6,
  /* 9  */ 7
};

void setup() {
  uint8_t loopIndex;

  for(loopIndex = 0; loopIndex < 10; loopIndex++) {
    pinMode(gpio[loopIndex], OUTPUT);
    digitalWrite(gpio[loopIndex], LOW);
  }

  dbg.begin(9600);           // Serial monitor
  esp.begin(9600);             // ESP8266

  
  dbg.println("Initialized both the serials");
}

void loop() {
  //dbg.println("Loop is running");  
  checkAndProcessWebRequest();
}

// Function checks and processes the in coming get request for web server
int checkAndProcessWebRequest()
{
  int ipdIndex = 0;
  int startIndex = 0;
  int endIndex = 0;

  // Get any pending web request
  readSerial();
  
  // Start the web server for every ESP reboot 
  if (0 == gEspResponse.indexOf("&&")) {
    //dbg.println("Got some command for me!!!");
    if (2 == gEspResponse.indexOf("SIO")) {
      dbg.println("Got SIO command " + gEspResponse);

      uint8_t gpioIndex = gEspResponse.substring(5,6).toInt();
      uint8_t gpioValue = gEspResponse.substring(6,7).toInt();

      dbg.print("Setting up GPIO: ");
      dbg.print(gpio[gpioIndex]);
      dbg.print(" Value: ");
      dbg.println(gpioValue);
      digitalWrite(gpio[gpioIndex], gpioValue);
    }
  }
}

int readSerial()
{
  int j = 0;
  char lastChar = 0;

  // Reset the global data
  gEspResponse = "";
  
  int leftBytes = esp.available();
  while (leftBytes > 0) {
    char inChar = esp.read();
    byte byteReceived = (byte)inChar;
    //dbg.println("Data: Avlb - " + esp.available() +  byteReceived + inChar);

    if (byteReceived >= 32 && byteReceived <= 126) gEspResponse += inChar;
    //dbg.println(" Response: " + gEspResponse);

    delay(1); // Allow ESP to put some more data
    leftBytes = esp.available();

    if ('?' == inChar) break;
  }

  //if (!gEspResponse.equals("")) dbg.println("ESP Response: " + gEspResponse);
  return 0;
}



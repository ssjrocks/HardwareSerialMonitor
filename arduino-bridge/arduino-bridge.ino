// amateur project to display pc stats on a nextion via an arduino
//must use mega for now .. cant get this nextion library to work with software serial for now ... so recieves hardware monitor input on Serial and outputs nextion commands on Serial1


#include "EasyNextionLibrary.h"  // Include EasyNextionLibrary


//#include <SoftwareSerial.h>

// SoftwareSerial mySerial(2, 3); // RX, TX not gonna work
EasyNex myNex(Serial1); // Create an object of EasyNex class with the name < myNex >

    
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];      
char messageFromPC[numChars] = {0};
int ctem = 0;
int cload = 0;
int gtem = 0;
int gload = 0;
int angle = 0;
int angle2 = 0;
int gclock = 0;
int gmem = 0;
int sclock = 0;
int cclock = 0;
boolean newData = false;



void setup() {
              Serial.begin(9600);
              myNex.begin(9600); // Begin the object with a baud rate of 9600
              }


void loop() {
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        sendParsedData();
        newData = false;
    }
}




void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}



void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,"|");      // get the first part - the string
    ctem = atoi(strtokIndx);     // convert this part to an integer
 
    strtokIndx = strtok(NULL, "|"); // this continues where the previous call left off
    cload = atoi(strtokIndx);     // convert this part to an integer

    strtokIndx = strtok(NULL, "|");
    gtem = atoi(strtokIndx);     // convert this part to an integer
    
    strtokIndx = strtok(NULL, "|"); // this continues where the previous call left off
    gload = atoi(strtokIndx);     // convert this part to an integer

    strtokIndx = strtok(NULL, "|");
    gclock = atoi(strtokIndx);     // convert this part to an integer
        
    strtokIndx = strtok(NULL, "|"); // this continues where the previous call left off
    cclock = atoi(strtokIndx);     // convert this part to an integer

}


//wild bill angle mapping solution
int maparc(int value){
  int result;
  if (value > 16)
    result = map(value,16,100,0,225);
  else if(value==0)
    result = 315;
  else
    result = map(value,1,15,316,360);
  return result;
}


//============

void sendParsedData() {


   myNex.writeNum("ctem.val", ctem);
   myNex.writeNum("ctem2.val", ctem);
   myNex.writeNum("cload2.val", cload);
   myNex.writeNum("cload.val", maparc(cload));
   myNex.writeNum("gtem.val", gtem);
   myNex.writeNum("gtem2.val", gtem);
   myNex.writeNum("gload2.val", gload);
   myNex.writeNum("gload.val", maparc(gload));
   myNex.writeNum("gclock.val", gclock);
   myNex.writeNum("cclock.val", cclock);

}

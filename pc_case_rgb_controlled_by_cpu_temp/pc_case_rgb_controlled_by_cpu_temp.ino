// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>


#define PIN            4                           // Which pin on the Arduino is connected to the NeoPixels?


#define NUMPIXELS      195                        // How many NeoPixels are attached to the Arduino?
int ctem = 0;
int ro = 0;
int go = 0;
int green = 0;
int red=0;
boolean newData = false;
const byte numChars = 32; 
char tempChars[numChars];   
char receivedChars[numChars];


                                                  // When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
                                                  // Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
                                                 // example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  pixels.begin();                                 // This initializes the NeoPixel library.
  pixels.show();  
  for (int p = 0; p < NUMPIXELS; p++) {
      pixels.setPixelColor(p, 0, 255, 0);       // full bright green color.
  }
}


void loop() {
  checkdata();// check for new input
//   
if (ctem > 80){
  ro = 255;
  go = 1;
  
}
  for (int i=0; i<go; i++) {
    for (int p = 0; p < NUMPIXELS; p++) {
    //    go = map(temp,15,80,255,0);
      red = map(i, 0, go,0, ro);
      pixels.setPixelColor(p, red,i,0); 
      }
      pixels.show(); delay(1); 
  
  //Serial.println("brighter");
 // Serial.println(ctem);
//Serial.println(i);
 // Serial.println(green);
      }
 
  checkdata();// check for new input
  for (int i=go; i>0; i--) { 
   for (int p = 0; p < NUMPIXELS; p++) {

    red = map(i, 0, go,0, ro);
    pixels.setPixelColor(p, red,i,0);
    }
    pixels.show(); delay(1);

  //Serial.println("dimmer");  
 // Serial.println(ctem);
//  Serial.println(i);
 // Serial.println(green);
    }

  

// for (int p = 0; p < NUMPIXELS; p++) {pixels.setPixelColor(p, ro,go,0); }
// pixels.show();

//loop from 3 to 155 and back setting strip brightness as we go
//  for (int i=3; i<155; i++) { pixels.setBrightness(i); pixels.show(); delay(5); }
//  for (int i=155; i>3; i--) { pixels.setBrightness(i); pixels.show(); delay(5); }

                                                //debugging
 // Serial.println(ctem);
 // Serial.println(ro);
// Serial.println(go);
            }

void checkdata(){
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
                                                // this temporary copy is necessary to protect the original data
                                                //   because strtok() used in parseData() replaces the commas with \0
    parseData();
    mapcolor(ctem);                             // map new color to the temp
  //  updatecolor();                              // set new color of strip
    newData = false;
    }
    //not needed   updatecolor();               // fallback? incase no new data?
}


//void updatecolor() {                           // update strip color with temperature
 // for (int p = 0; p < NUMPIXELS; p++) {
//pixels.setPixelColor(p, ro, go, 0);       // full bright green color.
 // }
//pixels.show();
//}


void mapcolor(int temp) {                     // map temp to color value
    ro = map(temp,30,80,0,255);
    go = map(temp,30,80,255,0);
    
}


void parseData() {                            // split the data into its parts
  char * strtokIndx;                          // this is used by strtok() as an index
  strtokIndx = strtok(tempChars,"|");         // get the first part - the string
  ctem = atoi(strtokIndx);                    // convert this part to an integer
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
                receivedChars[ndx] = '\0';        // terminate the string
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

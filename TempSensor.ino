 // Include Libraries
#include "Arduino.h"
#include "Buzzer.h"
#include "Adafruit_NeoPixel.h"
#include "Fan.h"


// Pin Definitions
#define BUZZER_PIN_SIG	2
#define LEDRGB_PIN_DIN	3
#define PCFAN_PIN_COIL1	5
#define TMP36_PIN_VOUT	A3



// Global variables and defines
#define LedRGB_NUMOFLEDS 1
// object initialization
Buzzer buzzer(BUZZER_PIN_SIG);
Adafruit_NeoPixel LedRGB(LEDRGB_PIN_DIN);
Fan PCFan(PCFAN_PIN_COIL1);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    LedRGB.begin(); // This initializes the NeoPixel library.
    LedRGB.show(); // Initialize all leds to 'off'
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // Buzzer - Test Code
    // The buzzer will turn on and off for 500ms (0.5 sec)
    buzzer.on();       // 1. turns on
    delay(500);             // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    buzzer.off();      // 3. turns off.
    delay(500);             // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }
    else if(menuOption == '2') {
    // LED - RGB Addressable, PTH, 5mm Diffused (5 Pack) - Test Code
    for(int i=0 ; i <= LedRGB_NUMOFLEDS ; i++){
    for (int k = 0 ; k <= 255 ; k++) {
    // set leds Color to RGB values, from 0,0,0 up to 255,255,255
    LedRGB.setPixelColor(i, LedRGB.Color(255-k,k,100)); // turn on green color on led #i.
    if (i > 0)
    LedRGB.setPixelColor(i-1, LedRGB.Color(0,0,0)); // turn off last led
    LedRGB.show(); //update led color to the hardware.
    delay(1);
    }
    }

    }
    else if(menuOption == '3') {
    // PC Fan 12V - Test Code
    // The PC Fan will turn on for 2000ms and off for 4000ms (4 sec)
    PCFan.on(); // 1. turns on
    delay(2000);       // 2. waits 2000 milliseconds (2 sec).
    PCFan.off();// 3. turns off
    delay(4000);       // 4. waits 4000 milliseconds (4 sec).

    }
    else if(menuOption == '4')
    {
    // Disclaimer: The This Analog Temprature Sensor can measure -40 to 150C. It is very percise and doesn't need calibration is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Buzzer"));
    Serial.println(F("(2) LED - RGB Addressable, PTH, 5mm Diffused (5 Pack)"));
    Serial.println(F("(3) PC Fan 12V"));
    Serial.println(F("(4) This Analog Temprature Sensor can measure -40 to 150C. It is very percise and doesn't need calibration"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing Buzzer"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing LED - RGB Addressable, PTH, 5mm Diffused (5 Pack)"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing PC Fan 12V"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing This Analog Temprature Sensor can measure -40 to 150C. It is very percise and doesn't need calibration - note that this component doesn't have a test code"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

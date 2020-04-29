/* ENGR 152
 *  Maker Competition
 *  LCD I2C Test
 *  Last edited by Kyler Howard, 4-17-20
 *  
 *  Pin Setup for LCD:
 *  GND to Ground
 *  VCC to 5V
 *  SDA to A4
 *  SCL to A5
 *  
 *  I2C found at 0x27
 *  
 *  Pin Setup for Joystick:
 *  GND to Ground
 *  +5V to 5V
 *  VRx to A0
 *  VRy to A1
 *  SW to A2
 *  
 *  Make an array of (char *name) from readDir (probably) called "files"     
 *    find out how many files are in folder
 *    set that number as size of array (subtract one because array starts at 0)
 *    loop through folder again and fill array with file names. for loop - buttons example
 *  display files[0] on LCD, using the cursor with while loop
 *    if move down, increment i with i++, display files[i]...
 *    if move up, subtract one i--, display files[i]...
 *    if i == max value, i = 0
 *    if i < 0, i = max value - 1
 *    if button selected, set toPlay = files[i] 
 *    leave while loop, and add delay
*/

//================================================================================
//                 Declare Global Variables & Header Files
//================================================================================

// including required libraries to run the I2C LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <FatReader.h>
#include <WaveHC.h>
#include "remind.h"

FatVolume Vol;    // This holds the information for the partition on the card
FatReader Root;   // This holds the information for the filesystem on the card
FatReader F;      // This holds the information for the file we're playing
WaveHC Wave;      // This is the only wave (audio) object, since we will only play one at a time


// starting the LCD at the I2C address and the parameters the microprocessor needs
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int Button = 9;

// somehow have to find size of dir. Maybe readDir. for now it's an example. Somewhere in the Wave setup function it does this!

int dirSize = 5;
String *files;



// declaring analog pins
int XJoystick = A0;              // x-axis of joystick
int YJoystick = A1;              // y-axis of joystick
int JoystickButton = A2;         // joystick button treat as digital

// Custom Function Variables and Parameters
int DebounceDelay = 500;         // Delay set for debounce time - delay time after a button is pressed
int Up = 400;                    // Trigger value for moving joystick up - neutral is about 511
int Down = 500;                  // Trigger value for moving joystick down - neutral is about 511
int Left = 400;                  // Trigger value for moving joystick left - neutral is about 511
int Right = 600;                 // Trigger value for moving joystick right - neutral is about 511

long previousTime = 0;


//=========================================================================
//                                Setup
//=========================================================================
void setup() {

  // starting the serial monitor at 9600 bpm
  Serial.begin(9600);

  // Starting the LCD
  lcd.begin(16,2);
  lcd.backlight();
  lcd.clear();  
  lcd.print("Choose Reminder:");

  // setting the I/O pins
  pinMode (Button, INPUT_PULLUP);
  pinMode (XJoystick, INPUT);
  pinMode (YJoystick, INPUT);
  pinMode (JoystickButton, INPUT_PULLUP);

  // setup the wave shield

  Root = waveSetup();

  Serial.println(" ");

  // attempting to fill the array
  byte i;
  dirSize = getFiles(Root);
  Serial.println("dirSize: " + String(dirSize));
  files = new String[dirSize];
  for (i=0; i < dirSize; i++){
    files[i] = i;
    Serial.println(files[i]);

  }

  Serial.println(" ");
  Serial.println("Starting Menu!");

 
}

//================================================================================
//                               Main Loop
//================================================================================

void loop(){

  
  // a while loop to record input from the joystick
  char i=0;
  while(true){
    

    lcd.setCursor(2,1);

    lcd.print(files[i]);

  // a millis() based time to have a blinking cursor
    unsigned long currentTime = millis();
    if((currentTime - previousTime) >= 300) {

      lcd.setCursor(0,1);
      lcd.print(">");     
    }
  
    if((currentTime - previousTime) >= 600) {
      lcd.setCursor(0,1);

      lcd.print(" "); 
      previousTime = currentTime;
    }
      
    if(analogRead(XJoystick) > Right || analogRead(YJoystick) > Down){
      
      i++;

      Serial.println("Moved right/down");
      
      if(i == dirSize){
        
        i = 0;
        Serial.println("cycle to start");
        
      }

      delay(500);
      
    }

    if(analogRead(XJoystick) < Left || analogRead(YJoystick) < Up){
      
      i--;

      Serial.println("Moved left/up");
      
      if(i < 0){
      
        i = (dirSize - 1);
        Serial.println("cycle to end");
      
      }

      delay(500);
      
    }
   
    
  }
  
}

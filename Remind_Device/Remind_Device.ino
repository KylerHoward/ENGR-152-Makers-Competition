/* ENGR 152
 *  Maker Competition
 *  Remind Device
 *  Last edited by Kyler Howard and Jackson Pope
*/

//================================================================================
//                 Declare Global Variables & Header Files
//================================================================================

// including required libraries to run the I2C LCD and then the Wave Shield
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WaveHC.h>
#include <WaveUtil.h>

// starting the LCD at the I2C address and the parameters the microprocessor needs
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// sets constant state variables from 1 to 7
const int STATE_GENERAL_WAIT = 1;
const int STATE_LCD_ON = 2;
const int STATE_FILE_WAIT = 3;
const int STATE_AUDIO_SELECT = 4;
const int STATE_SPEAKER_PLAY = 5;
const int STATE_ACKNOWLEDGE_WAIT = 6;
const int STATE_MOTION_OFF = 7;
const int n = 8;

// declaring digital pins
int IndicatorLED = 8;            // Indicator LED output
int ConfirmationButton = 9;      //acknowledge button? Input
int MotionSensor = 11;           // Motion sensor input

// declaring analog pins
int XJoystick = A0;              // x-axis of joystick
int YJoystick = A1;              // y-axis of joystick
int JoystickButton = A2;         // joystick button treat as digital

// declare variable data holders
int SpeakerCount;                // For WAVE shield  -  not sure what it does
int CurrentState;                // Holds State of State machine
int AudioSelectState;            // Holds state value for audio selection
int AudioFilePreset;             // Holds which audio file to play
int PreviousMillis;              // Holds millis since joystick was moved for mini state machine

// Custom Function Variables and Parameters
int DebounceDelay = 500;         // Delay set for debounce time - delay time after a button is pressed
int Down = 700;                  // Trigger value for moving joystick down - neutral is about 511
int Up = 300;                    // Trigger value for moving joystick up - neutral is about 511
int Left = 300;                  // Trigger value for moving joystick left - neutral is about 511
int Right = 700;                 // Trigger value for moving joystick right - neutral is about 511





//================================================================================
//                         Main Initializing Function
//================================================================================

void setup() {

  // Starting the LCD at 16 columns and 2 rows
  lcd.begin(16,2);

  // start serial monitor at 9600 bpm
  Serial.begin(9600);

  // set the currentState to STATE_GENERAL_WAIT
  CurrentState = STATE_GENERAL_WAIT;
  Serial.println("STATE_GENERAL_WAIT");


  // Set pin modes for digital pins
  pinMode (IndicatorLED, OUTPUT);
  pinMode (ConfirmationButton, INPUT_PULLUP);    // Logic is INVERTED!
  pinMode (MotionSensor, INPUT_PULLUP);          // Logic is INVERTED!
  
  // Set pin modes for analog pins
  pinMode (XJoystick, INPUT);
  pinMode (YJoystick, INPUT);
  pinMode (JoystickButton, INPUT_PULLUP);

  //Turn on indicator LED
  digitalWrite (IndicatorLED, HIGH);
  
}





//================================================================================
//                               Main Loop
//================================================================================

void loop() { 

  // State machine will Print out which state it moves to. Helps with troubleshooting
  // Starts state machine
  switch(CurrentState){
      
    //=============================
    //    State One
    //=============================

    // starts state one of state machine
    case STATE_GENERAL_WAIT:

      lcd.noBacklight();

      // If the joystick is moved or button is pressed
      if(analogRead(XJoystick) > Right || analogRead(XJoystick) < Left || analogRead(YJoystick) < Up || analogRead(YJoystick) > Down || digitalRead(JoystickButton) == LOW || digitalRead(ConfirmationButton) == LOW) {
       
        // move to STATE_LCD_ON
        CurrentState = STATE_LCD_ON;
        Serial.println("STATE_LCD_ON");
        
        Debounce();
      }
     
      // If motion is sensed, set the speaker counter to 1 and move to STATE_SPEAKER_PLAY
      // Logic is reversed for pullup input
      if(digitalRead(MotionSensor) == LOW){
        
        //Set speaer count to 1
        SpeakerCount = 1;
        
        //Go to STATE_SPEAKER_PLAY
        CurrentState = STATE_SPEAKER_PLAY;
        Serial.println("STATE_SPEAKER_PLAY");
        
      }      

      // end the case
      break;

      // this state now appears to work with no issues!
  
      
    //=============================
    //    State Two
    //=============================

    // starts state two of state machine
    case STATE_LCD_ON:
      
      lcd.backlight();
      
      //reset LCD screen
      lcd.clear();
      
      // Print first audio file
      lcd.print("audio file 1");      // Is this supposed to be a variable, or just a placeholder until enough wave testing has been done?
      
      // Set audio file select state to the first page
      int AudioFile = 1;
      
      // Move to STATE_FILE_WAIT
      CurrentState = STATE_FILE_WAIT;
      Serial.println("STATE_FILE_WAIT");
      
      // Set timer for mini state machine to 0
      PreviousMillis = millis();

      // end the case
      break;

      
      
    //=============================
    //    State Three
    //=============================

    // starts state three of state machine
    case STATE_FILE_WAIT:
      
      // Watch dog for state machine
      // If joystick is moved
      if(analogRead(XJoystick) > Right || analogRead(XJoystick) < Left || analogRead(YJoystick) > Up || analogRead(YJoystick) < Down) {
        PreviousMillis = millis();
      }
      
      // If no input for 30 seconds, go back to general wait state
      if(millis() - PreviousMillis > 30000) {
        
        // Move to general wait state
        CurrentState = STATE_GENERAL_WAIT;
        Serial.println("STATE_GENERAL_WAIT");
      }
      
      //---------------------------
      //   Mini State Machine
      //---------------------------
      
      // Selection menu for choosing which audio file you want to play
      // The # of cases will depend on the # of audio files we have
      switch(AudioSelectState){
        
        //---------------------------
        //    mini state n
        //---------------------------
        
        // Template for audio selction state machine 
        case n:
                    
          // It joystick is moved right or down
          if(analogRead(XJoystick) > Right || analogRead(YJoystick) < Down) {
          
            //move to the next audio file
            AudioSelectState = n + 1;
            
            // Print the next file's name on LCD screen
            lcd.print("audio file n + 1");      // Again, is this supposed to be a variable or waiting for Wave testing?
            
            Debounce();
          }
          
          // If joystick is moved left or up
          if(analogRead(XJoystick) > Left || analogRead(YJoystick) < Up) {
            
            //move to previous audio file
            AudioSelectState = n - 1;
            
            // Print the previous audio file
            lcd.print("Audio file n - 1");      // Again, is this supposed to be a variable or waiting for Wave testing?
            
            Debounce();
          }
          
          // If joystick button is pressed
          if(digitalRead(JoystickButton) == LOW)  {
            
            // Set the audio file of current state to preset audio 
            //AudioFilePreset = Audio file n;   // no variables set before for Audio file n. I'll let you put that where you want and then get rid of commenting out this
            
            // Move to general waiting state
            CurrentState = STATE_AUDIO_SELECT;
            Serial.println("STATE_AUDIO_SELECT");
          }
      }

      // end the case
      break;
     
         

    //=============================
    //    State Four
    //=============================

    // starts state four of state machine
    case STATE_AUDIO_SELECT:

      // Declare audio file as speaker output
      // Wait 30 seconds
      // Turn off LCD screen
      // Return to STATE_GENERAL_WAIT
        
      // end the case    
      break;
      
      

    //=============================
    //    State Five
    //=============================

    // starts state five of state machine
    case STATE_SPEAKER_PLAY:

      // Play the selected audio file out of the speaker
      // Move to STATE_ACKNOWLEDGE_WAIT
      
      // end the case
      break;


    //=============================
    //    State Six
    //=============================

    // starts state six of state machine
    case STATE_ACKNOWLEDGE_WAIT:

      // If the acknowledge button is pressed, move to STATE_MOTION_OFF
      // If the acknowledge button is not pressed within 10 seconds, increase the speaker counter by 1 and move to STATE_SPEAKER_PLAY.
      // If the counter is above 12, go to STATE_GENERAL_WAIT

      // end the case
      break;

    //=============================
    //    State Seven
    //=============================

    // starts state seven of state machine
    case STATE_MOTION_OFF:

      // Turn off motion sensor
      // If there is not button input in 30 minutes, move to STATE_GENERAL_WAIT
      // If there is a button input, move to STATE_LCD_ON

      // end the case
      break;

     
  }
    
}                                    // Go back to the beginning of the loop


//===========================================
//             Custom Functions
//===========================================

void Debounce (void) {
  delay(DebounceDelay);
}

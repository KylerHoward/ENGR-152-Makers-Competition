/* ENGR 152
 *  Maker Competition
 *  Remind Device
 *  Last edited by Kyler Howard, 4-17-20
*/

//================================================================================
//                 Declare Global Variables & Header Files
//================================================================================

// including required libraries to run the I2C LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

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

// setting other variables
int IndicatorLED = 8;
int ConfirmationButton = 9;
int ConfirmationButtonState = 1;

// TO DO: button state variable, joystick state variable, motion sensor state variable, speaker count variable, and whatever WAVE needs

// sets the currentState to STATE_WELCOME

int currentState = 1;
//================================================================================
//                         Main Initializing Function
//================================================================================

void setup() {

  // Starting the LCD at 16 columns and 2 rows
  lcd.begin(16,2);

  // clearing the LCD and putting the cursor at 0,0
  lcd.clear();


  // start serial monitor at 9600 bpm
  Serial.begin(9600);

  // set the currentState to STATE_WELCOME
  currentState = STATE_GENERAL_WAIT;

  // MAKE THE LED TURN ON
  pinMode (IndicatorLED, OUTPUT);

  digitalWrite (IndicatorLED, HIGH);

  pinMode (ConfirmationButton, INPUT_PULLUP);



  lcd.print("~~TESTING~~");
  
  
}


//================================================================================
//                               Main Loop
//================================================================================

void loop() { 

  // Starts state machine
  switch(currentState){
  
    //=============================
    //    State One
    //=============================

    // starts state one of state machine
    case STATE_GENERAL_WAIT:

      // If the joystick or button is pressed, move to STATE_LCD_ON
      // If the motion detector is sensed, set the speaker counter to 1 and move to STATE_SPEAKER_PLAY
      
      ConfirmationButtonState = digitalRead(ConfirmationButton);
      
      if (ConfirmationButtonState == LOW){

        Serial.print("Button Pushed");
      }

      // end the case
      break;


    //=============================
    //    State Two
    //=============================

    // starts state two of state machine
    case STATE_LCD_ON:

      // Turn on LCD screen
      // Display Audio Files
      // Move to STATE_FILE_WAIT

      // end the case
      break;

    //=============================
    //    State Three
    //=============================

    // starts state three of state machine
    case STATE_FILE_WAIT:

      // If the joystick is moved, move the LCD readout to reflect this
      // If a file is selected using the joystick, move to STATE_AUDIO_SELECT
      // IF no user input for 30 seconds, turn off the LCD screen, and move to STATE_GENERAL_WAIT

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

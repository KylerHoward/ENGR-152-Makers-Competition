/* ENGR 152
 *  Maker Competition
 *  Remind Device
 *  Last edited by Jackson Pope, 4-18-20
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

// declaring digital pins
int IndicatorLED = 8;            // Indicator LED output
int ConfirmationButton = 9;      //acknowledge button? Input
int MotionSensor = 11;           // Motion sensor input

// declaring analog pins
int XJoystick = A0;              // x-axis of joystick
int YJoystick = A1;              // y-axis of joystick
int JoystickButton = A2;         // joystick button treat as digital
int LCDPowerPin = A3;            // Power for LCD screen

// declare variable data holders
int SpeakerCount;                // For WAVE shield  -  not sure what it does
int CurrentState;                // Holds State of State machine
int AudioSelectState;            // Holds state value for audio selection
int AudioFilePreset;             // Holds which audio file to play
int PreviousMillis;              // Holds millis since joystick was moved for mini state machine

// Custom Function Variables and Parameters
int DebounceDelay = 500;         // Delay set for debounce time - delay time after a button is pressed
int Up = 700;                    // Trigger value for moving joystick up
int Down = 300;                  // Trigger value for moving joystick down
int Left = 300;                  // Trigger value for moving joystick left
int Right = 700;                 // Trigger value for moving joystick right





//================================================================================
//                         Main Initializing Function
//================================================================================

void setup() {

  // Starting the LCD at 16 columns and 2 rows
  lcd.begin(16,2);

  // clearing the LCD and putting the cursor at 0,0
  lcd.clear();
  lcd.setCursor(0,0);

  // start serial monitor at 9600 bpm
  Serial.begin(9600);

  // set the currentState to STATE_GENERAL_WAIT
  CurrentState = STATE_GENERAL_WAIT;

  // Set pin modes for digital pins
  pinMode (IndicatorLED, OUTPUT);
  pinMode (ConfirmationButton, INPUT_PULLUP);    // Logic is INVERTED!
  pinMode (MotionSensor, INPUT_PULLUP);          // Logic is INVERTED!
  
  // Set pin modes for analog pins
  pinMode (XJoystick, INPUT);
  pinMode (YJoystick, INPUT);
  pinMode (JoystickButton, INPUT);
  pinMode (LCDPowerPin, OUTPUT);

  //Turn on indicator LED
  digitalWrite (IndicatorLED, HIGH);

  // Print initializing message on LCD Screen
  lcd.print("~~TESTING~~");
}





//================================================================================
//                               Main Loop
//================================================================================

void loop() { 

  // State machine will Print out which state it moves to. Helps with troubleshooting
  // Starts state machine
  switch(currentState){
  
      
    //=============================
    //    State One
    //=============================

    // starts state one of state machine
    case STATE_GENERAL_WAIT:
      
      // Print trouble shooting information 
        // If button is pressed, print button pushed. - note: logic is inverted because of pullup input
        if (digitalRead(ConfirmationButton) == LOW){
          Serial.println("Button Pushed");
        }
      
        // If Joystick is moved, Print the analog value of Joystick inputs 
        if(analogRead(XJoystick) > Right || analogRead(XJoystick) < Left || analogRead(YJoystick) > Up || analogRead(YJoystick) < Down) {
          
          // Print "Joystick moved"
          Serial.println("Joystick Moved");
          
          //print x-axis: (analog reading of x)
          Serial.print("x-axis: ");
          Serial.println(analogRead(XJoystick));
          
          //print y-axis: (analog reading of y)
          Serial.print("y-axis: ");
          Serial.println(analogRead(YJoystick));
        }


      // If the joystick is moved or button is pressed
      if(analogRead(XJoystick) > Right || analogRead(XJoystick) < Left || analogRead(YJoystick) > Up || analogRead(YJoystick) < Down || digitalRead(JoystickButton) == LOW) {
       
        // move to STATE_LCD_ON
        CurrentState = STATE_LCD_ON;
        Serial.Println("STATE_LCD_ON");
        
        Debounce();
      }
      
      // If motion is sensed, set the speaker counter to 1 and move to STATE_SPEAKER_PLAY
      // Logic is reversed for pullup input
      if(digitalRead(MotionSensor) == LOW){
        
        //Set speaer counter to 1
        SpeakerCounter = 1;
        
        //Go to STATE_SPEAKER_PLAY
        CurrentState = STATE_SPEAKER_PLAY;
        Serial.Println("STATE_SPEAKER_PLAY");
      }      

      // end the case
      break;

      
      
    //=============================
    //    State Two
    //=============================

    // starts state two of state machine
    case STATE_LCD_ON:
      
      // Turn LCD on
      digitalWrite(LCDPowerPin, HIGH);
      
      //reset LCD screen
      lcd.clear();
      lcd.setCursor(0,0);
      
      // Print first audio file
      lcd.print(audio file 1);
      
      // Set audio file select state to the first page
      AudioFile = 1;
      
      // Move to STATE_FILE_WAIT
      CurrentState = STATE_FILE_WAIT;
      Serial.Println("STATE_FILE_WAIT");
      
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
        Serial.Println("STATE_GENERAL_WAIT");
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
            lcd.print(audio file n + 1);
            
            Debounce();
          }
          
          // If joystick is moved left or up
          if(analogRead(XJoystick) > Left || analogRead(YJoystick) < Up) {
            
            //move to previous audio file
            AudioSelectState = n - 1;
            
            // Print the previous audio file
            lcd.print(sudio file n - 1);
            
            Debounce();
          }
          
          // If joystick button is pressed
          if(digitalRead(JoystickButton) == LOW)  {
            
            // Set the audio file of current state to preset audio 
            AudioFilePreset = Audio file n;
            
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

void Debounce(void) {
  delay(DebounceDelay);
}

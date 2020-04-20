/* ENGR 152
 *  Maker Competition
 *  Joystick Test
 *  Last edited by Kyler Howard and Jackson Pope
 *  
 *  Pin Setup for Joystick:
 *  GND to Ground
 *  +5V to 5V
 *  VRx to A0
 *  VRy to A1
 *  SW to A2
*/

//================================================================================
//                 Declare Global Variables & Header Files
//================================================================================

int LED = 8;

// declaring analog pins
int XJoystick = A0;              // x-axis of joystick
int YJoystick = A1;              // y-axis of joystick
int JoystickButton = A2;         // joystick button treat as digital

// Custom Function Variables and Parameters
int DebounceDelay = 500;         // Delay set for debounce time - delay time after a button is pressed
int Up = 600;                    // Trigger value for moving joystick up - neutral is about 511
int Down = 400;                  // Trigger value for moving joystick down - neutral is about 511
int Left = 400;                  // Trigger value for moving joystick left - neutral is about 511
int Right = 600;                 // Trigger value for moving joystick right - neutral is about 511

//=========================================================================
//                                Setup
//=========================================================================
void setup() {

  // start serial monitor at 9600 bpm
  Serial.begin(9600);

  pinMode (LED, OUTPUT);

  // Set pin modes for analog pins
  pinMode (XJoystick, INPUT);
  pinMode (YJoystick, INPUT);
  pinMode (JoystickButton, INPUT_PULLUP);
 
}

//================================================================================
//                               Main Loop
//================================================================================

void loop(){

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

    digitalWrite (LED, HIGH);

    delay(500);
  }

  if(digitalRead(JoystickButton) == LOW){

    Serial.print("Button Pressed");
    
    digitalWrite (LED, HIGH);

    delay(500);

  }

  digitalWrite (LED, LOW);

}

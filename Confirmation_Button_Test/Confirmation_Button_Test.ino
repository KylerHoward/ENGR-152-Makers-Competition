/* ENGR 152
 *  Maker Competition
 *  Remind Device
 *  Last edited by Kyler Howard and Jackson Pope
*/

int ConfirmationButton = 9;

void setup() {
  // put your setup code here, to run once:
 Serial.begin (9600);
 pinMode (ConfirmationButton, INPUT_PULLUP);
Serial.println ("Test");


}

void loop() {
  
  if (digitalRead(ConfirmationButton)== LOW){

    Serial.println("Button Pushed");

    delay(500);
    
  }
}

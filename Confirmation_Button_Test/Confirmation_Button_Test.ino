/* ENGR 152
 *  Maker Competition
 *  Remind Device
 *  Last edited by Kyler Howard, 4-18-20
*/

int ConfirmationButton = 9;
int ConfirmationButtonState = digitalRead(ConfirmationButton);

void setup() {
  // put your setup code here, to run once:
 Serial.begin (9600);
 pinMode (ConfirmationButton, INPUT_PULLUP);
Serial.print ("Test");


}

void loop() {
  // put your main code here, to run repeatedly:
  ConfirmationButtonState = digitalRead(ConfirmationButton);
  
  if (ConfirmationButtonState == LOW){

    Serial.print("Button Pushed");
  }
}

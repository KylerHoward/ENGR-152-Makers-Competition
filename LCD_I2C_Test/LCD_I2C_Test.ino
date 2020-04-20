/* ENGR 152
 *  Maker Competition
 *  LCD I2C Test
 *  Last edited by Kyler Howard, 4-17-20
 *  
 *  Pin Setup for LCD:
 *  GND to Ground
 *  VCC to A3
 *  SDA to A4
 *  SCL to A5
 *  
 *  I2C found at 0x27
*/

//================================================================================
//                 Declare Global Variables & Header Files
//================================================================================

// including required libraries to run the I2C LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// starting the LCD at the I2C address and the parameters the microprocessor needs
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int LCDPowerPin = A3;            // Power for LCD screen

//=========================================================================
//                                Setup
//=========================================================================
void setup() {

  // setting the LCDPowerPin as the output
  pinMode (LCDPowerPin, OUTPUT);

  // turning the LCD on
  digitalWrite (LCDPowerPin, HIGH);

  // Starting the LCD at 16 columns and 2 rows
  lcd.begin(16,2);

  // clearing the LCD and putting the cursor at 0,0
  lcd.clear();

  // printing "Hello World!" to the LCD
  lcd.print("Hello World!");      
  
  /* when using pin A3 to power the LCD, it does not display "Hello World!"
   * when directly plugging into the 5V rail, it works. We will have to figure this out...
   */
 
}

//================================================================================
//                               Main Loop
//================================================================================

void loop(){

  
  
}

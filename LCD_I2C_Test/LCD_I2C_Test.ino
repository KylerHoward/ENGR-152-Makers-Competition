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
*/

//================================================================================
//                 Declare Global Variables & Header Files
//================================================================================

// including required libraries to run the I2C LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// starting the LCD at the I2C address and the parameters the microprocessor needs
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//=========================================================================
//                                Setup
//=========================================================================
void setup() {

  // Starting the LCD at 16 columns and 2 rows
  lcd.begin(16,2);

  // clearing the LCD and putting the cursor at 0,0
  lcd.clear();

  // printing "Hello World!" to the LCD
  lcd.print("Hello World!");
 
}

//================================================================================
//                               Main Loop
//================================================================================

void loop(){

}

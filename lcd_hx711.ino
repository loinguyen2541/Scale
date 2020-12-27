#include <LCD5110_Graph.h>
#include <math.h>
#include <string.h>
#include "HX711.h"

LCD5110 lcd(3, 4, 5, 7, 6);

extern uint8_t TinyFont[];
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];

int count = 0;

const int LOADCELL_DOUT_PIN = 13;
const int LOADCELL_SCK_PIN = 12;

HX711 scale;

void setup()
{
    lcd.InitLCD();
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    scale.set_scale(-59300);                      // this value is obtained by calibrating the scale with known weights; see the README for details
    scale.tare();  
}

void loop()
{
    float num = scale.get_units(15) *6;
    if(num <= 0)
    num = 0;
    displayWeight(num);

    delay(500);
}

String convertToString(float number)
{
    float num2 = floorf(number * 10) / 10;
    String text = "";
    text += num2;
    String result = text.substring(0, text.length() - 1);
    return result;
}

void displayWeight(float weight)
{
    lcd.clrScr();
    lcd.update();

    lcd.setFont(MediumNumbers);
    String text = convertToString(weight);
    lcd.print(text, CENTER, 15);
    lcd.update();
}

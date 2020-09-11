#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

String inputString = "";            // String for buffering the message
boolean stringComplete = false;     // Indicates if the string is complete
byte cpuTemp = 0;
byte cpuTempNew = 0;
byte gpuTemp = 0;
byte gpuTempNew = 0;
byte i = 0;
byte j = 0;

void serialEvent() {
    while (Serial.available()) {
        char inChar = (char)Serial.read();
        if (inChar == 'S') {
            stringComplete = true;
        }
        inputString += inChar;
    }
}

void setup() {
    // Setup LCD
    lcd.begin(16,2);
 
    // Setup serial
    Serial.begin(9600);
    inputString.reserve(200);
}

void loop() {
    serialEvent();
    if (stringComplete) {
  
        if(inputString.length() == 8){
          
            // CPU
            // C AND S are here to make it work with simplecode.py
            int cpuStringStart = inputString.indexOf("C");
            int cpuStringLimit = inputString.indexOf("S");
            cpuTempNew = inputString.substring(cpuStringStart + 1, cpuStringLimit).toInt();
            
            if(cpuTempNew != cpuTemp || j == 3){
                cpuTemp = cpuTempNew;
                lcd.setCursor(0, 0);
                lcd.print("CPU:" + String(cpuTemp) + "C");
                j++;
            }
        
            // GPU
            int gpuStringStart = inputString.indexOf("G");
            int gpuStringLimit = inputString.indexOf("P");
            gpuTempNew = inputString.substring(gpuStringStart + 1, gpuStringLimit).toInt();
        
            if(gpuTempNew != gpuTemp || i == 3 ){
                gpuTemp = gpuTempNew;
                lcd.setCursor(0, 1);
                lcd.print("GPU:" + String(gpuTemp) + "C");
                i++;
            }
  
        }
        else if(inputString.length() == 6){
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Error");
        }
        inputString = "";
        stringComplete = false;
    }
}

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Display Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// 74HC595 Shift Register Pins
const int latchPin = 12; // ST_CP
const int clockPin = 13; // SH_CP
const int dataPin = 11;  // DS

// Peripherals
const int buzzerPin = 5; // PD5

// 7-Segment Common Cathode Lookup Table (0-9)
const byte segDigits[10] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

// Global variable to store the reset reason
bool wasHardwareReset = false;

void setup() {
  // 1. Immediately check the MCU Status Register before it gets cleared
  // EXTRF is bit 1 of MCUSR. If it's set, the reset pin was pressed.
  if (MCUSR & (1 << EXTRF)) {
    wasHardwareReset = true;
  }
  // Clear the status register flags to reset the detection for next time
  MCUSR = 0;

  // Initialize pins
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;); 
  }
  
  // Run the customized sequence
  runSequence();
}

void loop() {
  // Idle state; wait for the hardware reset pin to interrupt execution
}

void runSequence() {
  display.setTextColor(SSD1306_WHITE);

  // STEP A: If triggered by the button, display "RESET" first
  if (wasHardwareReset) {
    display.clearDisplay();
    display.setTextSize(2);      
    display.setCursor(35, 24);   
    display.print("RESET");
    display.display();
    delay(1000); // Show "RESET" for 1 second before continuing
  }

  // STEP B: Display "START"
  display.clearDisplay();
  display.setTextSize(2);      
  display.setCursor(35, 24);   
  display.print("START");
  display.display();
  delay(1500); 

  // STEP C: Switch OLED to "LOADING..." and begin countdown
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(5, 24); // Adjusted X cursor slightly left to fit longer text
  display.print("LOADING...");
  display.display();

  // 7-Segment Countdown (9 down to 0)
  for (int i = 9; i >= 0; i--) {
    // Write to shift register
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, segDigits[i]);
    digitalWrite(latchPin, HIGH);
    
    // Countdown beep
    digitalWrite(buzzerPin, HIGH);
    delay(150);
    digitalWrite(buzzerPin, LOW);
    
    delay(850); // Keep "LOADING..." active while waiting for next second tick
  }

  // STEP D: Display "END" & Sound the continuous final alarm
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(45, 24);
  display.print("END");
  display.display();

  // Continuous final alarm for 2.5 seconds
  digitalWrite(buzzerPin, HIGH);
  delay(2500);
  digitalWrite(buzzerPin, LOW);
}
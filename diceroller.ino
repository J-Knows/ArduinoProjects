#include "SevSeg.h"

SevSeg sevseg; // Creates sevseg object

const int pin_nums[] = {12, 13, 4, 3, 2, 11, 10, 5}; // Declare and initialize the array
const int numLength = sizeof(pin_nums) / sizeof(pin_nums[0]); // Calculate the number of elements in the array
const int buttonPin = 9; // Pin for the button

bool displayNumber = false; // State variable to toggle between cycling and displaying a number
int randomNumber = 0; // Variable to store the random number

void setup() {
  // Set each pin as an OUTPUT
  for (int i = 0; i < numLength; i++) {
    pinMode(pin_nums[i], OUTPUT);
  }

  // Initialize SevSeg
  byte segmentPins[] = {12, 13, 4, 3, 2, 11, 10, 5};
  byte numDigits = 1;
  byte digitPins[] = {}; // No digit pins for a single digit display
  bool resistorsOnSegments = true;
  byte hardwareConfig = COMMON_CATHODE;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);

  // Set up the button pin
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    // Toggle the display state
    displayNumber = !displayNumber;

    if (displayNumber) {
      // Generate a random number between 1 and 6
      randomNumber = random(1, 7);
      sevseg.setNumber(randomNumber);
      Serial.print("hi");
     
    }

    // Wait until the button is released
    while (digitalRead(buttonPin) == LOW) {
      // Do nothing
    }

    // Add a delay to avoid multiple readings
    delay(200);
  }

  if (displayNumber) {
    // Display the random number indefinitely
    sevseg.refreshDisplay();
  } else {
    // Cycle through the pin_nums array to turn on each segment
    for (int i = 0; i < numLength; i++) {
      digitalWrite(pin_nums[i], HIGH); // Turn on the pin
      delay(30); // Small delay
      digitalWrite(pin_nums[i], LOW); // Turn off the pin
    }
  }
}
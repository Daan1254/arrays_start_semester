#include <Arduino.h>

const int PIN_LED_RED = 4;    // The Number of the red LED pin.
const int PIN_LED_GREEN = 5;  // The Number of the green LED pin.
const int PIN_LED_BLUE = 6;   // The Number of the blue LED pin.
const int PIN_LED_YELLOW = 7; // The Number of the yellow LED pin.
const int PIN_BUTTON_1 = 8;   // The number of the button 1 (KEY1) pin.
const int PIN_BUTTON_2 = 9;   // The number of the button 2 (KEY2) pin.

int buttonArray[4] = {0,0,0,0};  // Initialize array to hold button pins
unsigned int arrayIndex = 0;       // Track the index for adding elements

const int interval = 100;
unsigned int prevMillis = 0;

byte prevButtonState = HIGH;

void readButton(int BUTTON_PIN) {
    const byte buttonState = digitalRead(BUTTON_PIN);

    if (buttonState == prevButtonState) return;
    if (buttonArray[3] != 0) return;

    Serial.println(BUTTON_PIN == PIN_BUTTON_1 ? PIN_LED_RED : PIN_LED_GREEN);
    buttonArray[arrayIndex] = BUTTON_PIN == PIN_BUTTON_1 ? PIN_LED_RED : PIN_LED_GREEN;
    arrayIndex++; // Increment the index after adding a button pin
    
    Serial.println("array:");
    for (unsigned int i = 0; i < arrayIndex; i++) {
        Serial.println(buttonArray[i]);
    }
}

void playLeds() {
    for (unsigned int i = 0; i < arrayIndex; i++) {
        digitalWrite(buttonArray[i], HIGH);
        delay(500);
        digitalWrite(buttonArray[i], LOW);
        delay(500);
    }

    memset(buttonArray, 0, sizeof(buttonArray));
    arrayIndex = 0;
}

void setup() {
    Serial.begin(9600);
    
    pinMode(PIN_LED_RED, OUTPUT);
    pinMode(PIN_LED_GREEN, OUTPUT);

    pinMode(PIN_BUTTON_1, INPUT_PULLUP);
    pinMode(PIN_BUTTON_2, INPUT_PULLUP);
}

void loop() {
    const unsigned currentMillis = millis();

    if (currentMillis - prevMillis >= interval) {
        readButton(PIN_BUTTON_1);
        readButton(PIN_BUTTON_2);
        prevMillis = currentMillis;
    }

    if (buttonArray[3] != 0) {
        playLeds();
    }
}

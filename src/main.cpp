#include <Arduino.h>

const int PIN_LED_RED = 4;    // The Number of the red LED pin.
const int PIN_LED_GREEN = 5;  // The Number of the green LED pin.
const int PIN_LED_BLUE = 6;   // The Number of the blue LED pin.
const int PIN_LED_YELLOW = 7; // The Number of the yellow LED pin.
const int PIN_BUTTON_1 = 8;   // The number of the button 1 (KEY1) pin.
const int PIN_BUTTON_2 = 9;   // The number of the button 2 (KEY2) pin.

void setup() {
    Serial.begin(9600);
    const int array[5] = {1, 3, 5, 7, 9};

    int som = 0;

   for (unsigned int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        som = som + array[i];
        Serial.println(array[i]);
    }

    Serial.print("Som: ");
    Serial.println(som);
}

void loop() {
}
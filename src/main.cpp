#include <Arduino.h>

struct ButtonState {
    byte pin;
    byte prevState;
    byte state;
    int value;
};

const int PIN_LED_RED = 4;    // The Number of the red LED pin.
const int PIN_LED_GREEN = 5;  // The Number of the green LED pin.
const int PIN_LED_BLUE = 6;   // The Number of the blue LED pin.
const int PIN_LED_YELLOW = 7; // The Number of the yellow LED pin.
const int PIN_BUTTON_1 = 8;   // The number of the button 1 (KEY1) pin.
const int PIN_BUTTON_2 = 9;   // The number of the button 2 (KEY2) pin.

bool shouldRetry = true;
int pincode[4] = {1,1,2,2};
int currentPincode[4] = {0,0,0,0};
int arrayIndex = 0;

const int interval = 100;
unsigned int prevMillis = 0;

ButtonState buttonStates[2] = {{PIN_BUTTON_1, HIGH, HIGH, 1}, {PIN_BUTTON_2, HIGH, HIGH, 2}};


void reset() {
    memset(currentPincode, 0, sizeof(currentPincode));
}

void readButtons() {
    for (int i = 0; i < 2; i++) {
        ButtonState& button = buttonStates[i];
        byte currentState = digitalRead(button.pin);

        if (currentState != button.prevState) {
            button.prevState = currentState;
            button.state = currentState;

            byte newState = digitalRead(button.pin);
            if (newState == button.state) {
                // Only register a button press if the button was previously in a LOW state (pressed)
                if (button.state == LOW) {
                    currentPincode[arrayIndex] = button.value;
                    arrayIndex++;
                }
            }
        }
    }
}

void wrong() {
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(PIN_LED_RED, LOW);
        delay(500);
        digitalWrite(PIN_LED_RED, HIGH);
        delay(500);
    }

    shouldRetry = true;
}

void success() {
    digitalWrite(PIN_LED_RED, LOW);
    digitalWrite(PIN_LED_GREEN, HIGH);
}

void checkAnswers() {
    bool correct = true;
    for (unsigned int i = 0; i < sizeof(pincode) / sizeof(pincode[0]); i++) {
        if (currentPincode[i] != pincode[i]) {
            correct = false;
            break;
        }
    }

    if (correct) {
        Serial.println("Kluis open.");
        success();
    } else {
        Serial.println("Code onjuist");
        wrong();
    }

    arrayIndex = 0;
    memset(currentPincode, 0, sizeof(currentPincode));
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

    if (shouldRetry) {
        reset();
        Serial.println("Voer pincode in...");
        digitalWrite(PIN_LED_RED, HIGH);
        shouldRetry = false;
    }

    if (currentMillis - prevMillis >= interval) {
        readButtons();
        prevMillis = currentMillis;
    }

    if (currentPincode[3] != 0) {
        checkAnswers();
    }
}
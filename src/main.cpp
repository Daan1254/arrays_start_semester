#include <Arduino.h>
#include <pitches.h>

struct ButtonState {
    byte pin;
    byte prevState;
    byte state;
};

const int PIN_LED_RED = 4;
const int PIN_LED_GREEN = 5;
const int PIN_LED_BLUE = 6;
const int PIN_LED_YELLOW = 7;
const int PIN_BUTTON_1 = 8;
const int PIN_BUTTON_2 = 9;
const int PIN_BUZZER = 3;

int tones[4] = {NOTE_C4, NOTE_G3, NOTE_C4, NOTE_G3};
int toneAnswers[4] = {0, 0, 0, 0};
unsigned int arrayIndex = 0;

const int interval = 100;
unsigned int prevMillis = 0;

ButtonState buttonStates[2] = {{PIN_BUTTON_1, HIGH, HIGH}, {PIN_BUTTON_2, HIGH, HIGH}};

bool shouldBuzz = true;

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
                    toneAnswers[arrayIndex] = button.pin == PIN_BUTTON_2 ? NOTE_C4 : NOTE_G3;
                    arrayIndex++;
                }
            }
        }
    }
}

void checkAnswers() {
    bool correct = true;

    for (unsigned int i = 0; i < sizeof(tones) / sizeof(tones[0]); i++) {
        if (toneAnswers[i] != tones[i]) {
            correct = false;
            break;
        }
    }

    if (correct) {
        Serial.println("Congratulations! You got it right!");
    } else {
        Serial.println("Oops! Wrong sequence. Try again!");
    }

    arrayIndex = 0;
    memset(toneAnswers, 0, sizeof(toneAnswers));
}

void setup() {
    Serial.begin(9600);

    pinMode(PIN_LED_RED, OUTPUT);
    pinMode(PIN_LED_GREEN, OUTPUT);
    pinMode(PIN_BUTTON_1, INPUT_PULLUP);
    pinMode(PIN_BUTTON_2, INPUT_PULLUP);
    pinMode(PIN_BUZZER, OUTPUT);

    Serial.println("Left: high tone || Right: low tone");
}

void loop() {
    const unsigned currentMillis = millis();

    if (currentMillis - prevMillis >= interval) {
        readButtons();
        prevMillis = currentMillis;
    }

    if (shouldBuzz) {
        shouldBuzz = false;
        for (unsigned int i = 0; i < sizeof(tones) / sizeof(tones[0]); i++) {
            tone(PIN_BUZZER, tones[i], 1000);
            delay(1100);
        }
    }

    if (toneAnswers[3] != 0) {
        checkAnswers();
    }
}

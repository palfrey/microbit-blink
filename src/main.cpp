#define MICROBIT_DBG 1
#include <MicroBit.h>
#include "MicroBitImage.h"

MicroBit uBit;
MicroBitImage lshift("1,0,1,1,1\n1,0,0,1,1\n1,0,1,0,1\n1,0,0,0,0\n1,1,1,1,1\n");
Ticker *ticker = NULL;

typedef enum {
    ALWAYS_ON = 1,
    CYCLING,
    TILT
} Mode;

Mode currentMode = ALWAYS_ON;

void changeBrightness() {
    int brightness = uBit.display.getBrightness();
    brightness += 50;
    if (brightness > 255)
        brightness -= 255;
    uBit.display.print(lshift);
    uBit.display.setBrightness(brightness);
}

void onGesture(MicroBitEvent e) {
    uBit.display.printChar(e.value + '0');
}

void setMode() {
    if (ticker)
    {
        ticker->detach();
        ticker = NULL;
    }
    uBit.messageBus.ignore(MICROBIT_ID_GESTURE, MICROBIT_EVT_ANY, onGesture);

    switch(currentMode) {
        case ALWAYS_ON:
            uBit.display.print(lshift);
            uBit.display.setBrightness(255);
            break;
        case CYCLING:
            uBit.display.print(lshift);
            uBit.display.setBrightness(10);
            ticker = new Ticker();
            ticker->attach_us(changeBrightness, 250 * 1000);
            break;
        case TILT:
            uBit.display.setBrightness(255);
            uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_EVT_ANY, onGesture);
            onGesture(MicroBitEvent(MICROBIT_ID_GESTURE, uBit.accelerometer.getGesture()));
            break;
    }
}

void onButtonA(MicroBitEvent e) {
    switch (currentMode) {
        case ALWAYS_ON:
            currentMode = TILT;
            break;
        case CYCLING:
            currentMode = ALWAYS_ON;
            break;
        case TILT:
            currentMode = CYCLING;
            break;
    }
    setMode();
}

void onButtonB(MicroBitEvent e) {
    switch (currentMode) {
        case ALWAYS_ON:
            currentMode = CYCLING;
            break;
        case CYCLING:
            currentMode = TILT;
            break;
        case TILT:
            currentMode = ALWAYS_ON;
            break;
    }
    setMode();
}

int main() {
    // Initialise the micro:bit runtime.
    uBit.init();
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonA);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonB);
    setMode();
    // If main exits, there may still be other fibers running or registered event handlers etc.
    // Simply release this fiber, which will mean we enter the scheduler. Worse case, we then
    // sit in the idle task forever, in a power efficient sleep.
    release_fiber();
    return 0;
}

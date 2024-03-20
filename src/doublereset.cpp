#include "doublereset.h"


DoubleReset::DoubleReset(Preferences *preferences)
{
    this->timeout = DR_TIMEOUT * 1000;
    this->doubleResetDetected = false;
    this->waitingForDoubleReset = false;
    this->preferences = preferences;
    preferences->begin("DR", false); // false for read/write
};

bool DoubleReset::detectDoubleReset()
{
    doubleResetDetected = detectRecentlyResetFlag();

    if (doubleResetDetected) {
        #if (DOUBLERESET_DEBUG)
            Serial.println("doubleResetDetected");
        #endif

        clearRecentlyResetFlag();
    } else {
        #if (DOUBLERESET_DEBUG)
            Serial.println("No doubleResetDetected");
        #endif

        setRecentlyResetFlag();
        waitingForDoubleReset = true;
    }

    return doubleResetDetected;

};
    
bool DoubleReset::waitingForDRD()
{
    return waitingForDoubleReset;
}

void DoubleReset::loop()
{
    if (waitingForDoubleReset && millis() > timeout) {
        #if (DOUBLERESET_DEBUG)
            Serial.println("Stop doubleResetDetecting");
        #endif

        stop();
    }
};

void DoubleReset::stop()
{
    clearRecentlyResetFlag();
    waitingForDoubleReset = false;
};

bool DoubleReset::detectRecentlyResetFlag()
{
    DOUBLERESETDETECTOR_FLAG = preferences->getInt("Flag", DOUBLERESETDETECTOR_FLAG_CLEAR);
    doubleResetDetectorFlag = DOUBLERESETDETECTOR_FLAG;

    #if (DOUBLERESET_DEBUG)
        Serial.printf("Preferences Flag read = %d\n", DOUBLERESETDETECTOR_FLAG);
    #endif

    doubleResetDetected = (doubleResetDetectorFlag == DOUBLERESETDETECTOR_FLAG_SET);
    return doubleResetDetected;
};

void DoubleReset::setRecentlyResetFlag()
{
    doubleResetDetectorFlag = DOUBLERESETDETECTOR_FLAG_SET;
    DOUBLERESETDETECTOR_FLAG = DOUBLERESETDETECTOR_FLAG_SET;

    preferences->putInt("Flag", DOUBLERESETDETECTOR_FLAG);
    #if (DOUBLERESET_DEBUG)
        Serial.println("Saving Prefernces flag SET");
    #endif
};


void DoubleReset::clearRecentlyResetFlag()
{
    doubleResetDetectorFlag = DOUBLERESETDETECTOR_FLAG_CLEAR;
    DOUBLERESETDETECTOR_FLAG = DOUBLERESETDETECTOR_FLAG_CLEAR;

    preferences->putInt("Flag", DOUBLERESETDETECTOR_FLAG);
    #if (DOUBLERESET_DEBUG)
        Serial.println("Saving Prefernces flag CLEAR");
    #endif

};


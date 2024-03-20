#ifndef DOUBLERESET_H
#define DOUBLERESET_H

#include <Preferences.h>

// Debuf flag add Serial.print debug information
#define DOUBLERESET_DEBUG   false

// Number of seconds after reset during which a 
// subsequent reset will be considered a double reset.
#define DR_TIMEOUT 5


#define DOUBLERESETDETECTOR_FLAG_SET    1234
#define DOUBLERESETDETECTOR_FLAG_CLEAR  4321

class DoubleReset
{
  public:
    DoubleReset(Preferences *preferences);
    bool detectDoubleReset();
    bool waitingForDRD();
    void loop();
    void stop();

    bool doubleResetDetected;

  private:
    int DOUBLERESETDETECTOR_FLAG;
    unsigned long timeout;
    bool waitingForDoubleReset;
    Preferences *preferences;

    bool detectRecentlyResetFlag();
    void setRecentlyResetFlag();
    void clearRecentlyResetFlag();

    int doubleResetDetectorFlag;
};

#endif

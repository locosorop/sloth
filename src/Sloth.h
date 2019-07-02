// Sloth.h
#ifndef SLOTH_H
#define SLOTH_H

#include <EventDelay.h>

class Sloth
{
private:
  unsigned int awakeTime;
  unsigned int sleepTime;
  int downTime;
  int whineTime;
  int awakeChecks;
  int sleepChecks;
  int defaultSleepChecksValue;
  int defaultAwakeChecksValue;
  bool whine;
  bool asleep;
  EventDelay d_whine;
  EventDelay d_down;
  EventDelay d_awake;
  EventDelay d_sleep;

public:
  Sloth();
  void setup();
  void setAwakeTime(int);
  void setSleepTime(int);
  void setDownTime(int);
  void setWhineTime(int);
  void setAwakeChecks(int);
  void setSleepChecks(int);
  bool getAwake();
  bool getAsleep();
  void updateControl();
};

#endif /* SLOTH_H */
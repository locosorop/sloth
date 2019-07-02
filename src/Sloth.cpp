#include "Sloth.h"
#include <Arduino.h>
#include <EventDelay.h>

Sloth::Sloth()
{
  awakeTime = 65535;
  sleepTime = 65535;
  downTime = 10000;
  whineTime = 5000;
  awakeChecks = 10;
  sleepChecks = 0;
  whine = true;
  asleep = false;

  EventDelay d_whine(whineTime); // Does this work?
  EventDelay d_down(downTime);
  EventDelay d_awake(awakeTime);
  EventDelay d_sleep(sleepTime);
}

void Sloth::setup()
{
  d_whine.start();
  d_awake.start();
}

void Sloth::setAwakeTime(int un)
{
  if (un > -1 && un < 65536)
  {
    awakeTime = un;
  }
}

void Sloth::setSleepTime(int un)
{
  if (un > -1 && un < 65536)
  {
    sleepTime = un;
  }
}

void Sloth::setDownTime(int n)
{
  downTime = n;
}

void Sloth::setWhineTime(int n)
{
  whineTime = n;
}

void Sloth::setAwakeChecks(int n)
{
  defaultAwakeChecksValue = n;
}

void Sloth::setSleepChecks(int n)
{
  defaultSleepChecksValue = n;
}

bool Sloth::getAwake()
{
  return !asleep;
}

bool Sloth::getAsleep()
{
  return asleep;
}

void Sloth::updateControl()
{
  // Sleep check
  if (getAwake() && d_awake.ready())
  {
    Serial.println();
    if (sleepChecks < 0)
    {
      Serial.println("[going to sleep]");
      sleepChecks = defaultSleepChecksValue;
      asleep = true;
      Serial.println("d_sleep start " + (String)sleepTime);
      d_sleep.start();
    }
    else
    {
      Serial.println("[skip sleeping]");
      sleepChecks--;
      Serial.println("sleepChecks " + (String)sleepChecks);
      d_awake.start();
    }
  }
  // Wakeup check
  if (getAsleep() && d_sleep.ready())
  {
    Serial.println();
    if (awakeChecks < 0)
    {
      Serial.println("[waking up]");
      awakeChecks = defaultAwakeChecksValue;
      asleep = false;
      Serial.println("d_awake start " + (String)awakeTime);
      d_awake.start();
    }
    else
    {
      Serial.println("[skip waking up]");
      awakeChecks--;
      Serial.println("awakeChecks " + (String)awakeChecks);
      d_sleep.start();
    }
  }
  // Silence reactivation
  if (getAwake() && whine && d_whine.ready())
  {
    Serial.println();
    Serial.println("[start whining]");
    whine = true;
    int randomWhineTime = (int)random(500, 10000);
    Serial.println("d_whine start " + (String)randomWhineTime);
    d_whine.start(randomWhineTime);
  }
}
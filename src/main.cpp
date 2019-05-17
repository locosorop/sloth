#include <Arduino.h>
#include <MozziGuts.h>
#include <SampleHuffman.h>
#include <EventDelay.h>
#include "./audio/whine_sounddata.h"

#define HEART_PIN 13

SampleHuffman whineSound(WHINE_SOUNDDATA, WHINE_HUFFMAN, WHINE_SOUNDDATA_BITS);
int t_shortest = 50;
int t_short = 80;
int t_long = 500;
int t_longest = 800;
EventDelay d_shortest(t_shortest);
EventDelay d_short(t_short);
EventDelay d_long(t_long);
EventDelay d_longest(t_longest);
int heartbeatAdjustment = 0;
int event = 0;
int whineTime = 5000; // 5 seconds (approx)
EventDelay d_whine(whineTime);
int downTime = 10000; // 10 seconds (approx)
EventDelay d_down(downTime);
unsigned int awakeTime = 65535;
EventDelay d_awake(awakeTime);
unsigned int sleepTime = 65535;
EventDelay d_sleep(sleepTime);
int awakeChecks = 10; // multiplier for awakeTime
int sleepChecks = 10; // multiplier for sleepTime
bool whine = true;
bool asleep = false;

void setup()
{
  while (!Serial)
  {
    ;
  }
  Serial.println("LoCoSoRoP");
  pinMode(HEART_PIN, OUTPUT);
  whineSound.setLoopingOn();
  startMozzi();
  randomSeed(analogRead(0));
  Serial.begin(9600);
  d_whine.start();
  d_awake.start();
}

void updateControl()
{
  // Sleep check
  if (!asleep && d_awake.ready())
  {
    Serial.println();
    if (sleepChecks < 0)
    {
      Serial.println("[going to sleep]");
      sleepChecks = 10;
      asleep = true;
      heartbeatAdjustment = 80;
      Serial.println("d_sleep start " + (String)sleepTime);
      Serial.println("heartbeatAdjustment " + (String)heartbeatAdjustment);
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
  if (asleep && d_sleep.ready())
  {
    Serial.println();
    if (awakeChecks < 0)
    {
      Serial.println("[waking up]");
      awakeChecks = 10;
      asleep = false;
      heartbeatAdjustment = 0;
      Serial.println("d_awake start " + (String)awakeTime);
      Serial.println("heartbeatAdjustment " + (String)heartbeatAdjustment);
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
  if (!asleep && whine && d_whine.ready())
  {
    Serial.println();
    Serial.println("[stop whining]");
    whine = false;
    int randomDownTime = (int)random(10000, 60000);
    Serial.println("d_down start " + (String)randomDownTime);
    d_down.start(randomDownTime);
    heartbeatAdjustment = (int)random(0, 10);
    Serial.println("heartbeatAdjustment " + (String)heartbeatAdjustment);
  }
  // Whine sound reactivation
  if (!asleep && !whine && d_down.ready())
  {
    Serial.println();
    Serial.println("[start whining]");
    whine = true;
    int randomWhineTime = (int)random(5000, 10000);
    Serial.println("d_whine start " + (String)randomWhineTime);
    d_whine.start(randomWhineTime);
    whineSound.start();
    heartbeatAdjustment = (int)random(-50, 0);
    Serial.println("heartbeatAdjustment " + (String)heartbeatAdjustment);
  }
  if (event == 0)
  {
    digitalWrite(HEART_PIN, HIGH);
    d_short.start(t_short + heartbeatAdjustment);
    // Serial.print("0");
    Serial.print("-");
    event = 1;
  }
  if (event == 1 && d_short.ready())
  {
    digitalWrite(HEART_PIN, LOW);
    d_long.start(t_long + heartbeatAdjustment);
    // Serial.print("1");
    Serial.print("_");
    event = 2;
  }
  if (event == 2 && d_long.ready())
  {
    digitalWrite(HEART_PIN, HIGH);
    d_shortest.start(t_short + heartbeatAdjustment);
    // Serial.print("2");
    Serial.print("-");
    event = 3;
  }
  if (event == 3 && d_shortest.ready())
  {
    digitalWrite(HEART_PIN, LOW);
    d_longest.start(t_longest + heartbeatAdjustment);
    // Serial.print("3");
    Serial.print("_");
    event = 4;
  }
  if (event == 4 && d_longest.ready())
  {
    d_short.start(t_short + heartbeatAdjustment);
    // Serial.print("4");
    Serial.print("*");
    event = 0;
  }
}

int updateAudio()
{
  if (whine)
  {
    return whineSound.next();
  }
}

void loop()
{
  audioHook();
}
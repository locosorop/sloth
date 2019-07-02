#include <Arduino.h>
#include <MozziGuts.h>

#define HEART_PIN 13

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    ;
  }
  Serial.println("LoCoSoRoP - All rights reserved.");
  // Set up random seed
  randomSeed(analogRead(0));
  // TODO: Set up heartbeat

  // TODO: Set up soundController

  // TODO: Set up timer

  // Start Mozzi
  startMozzi();
}

// Mozzi control hook
void updateControl()
{
  ;
}

// Mozzi audio hook
int updateAudio()
{
  ;
}

// Use mozzi hooks so loop stays instant
void loop()
{
  audioHook();
}
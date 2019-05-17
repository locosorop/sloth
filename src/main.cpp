#include <Arduino.h>
#include <MozziGuts.h>
#include <SampleHuffman.h>
#include <EventDelay.h>
#include "./audio/whine_sounddata.h"

#define HEART_PIN 13

SampleHuffman whineSound(WHINE_SOUNDDATA, WHINE_HUFFMAN, WHINE_SOUNDDATA_BITS);
EventDelay d_shortest(50);
EventDelay d_short(80);
EventDelay d_long(500);
EventDelay d_longest(800);
int event = 0;
int whineTime = 10000; // 10 seconds (approx)
EventDelay d_whine(whineTime);
int downTime = 20000; // 20 seconds (approx)
EventDelay d_down(downTime);
int whine = true;

void setup()
{
  pinMode(HEART_PIN, OUTPUT);
  whineSound.setLoopingOn();
  startMozzi();
  randomSeed(analogRead(0));
  Serial.begin(9600);
  while (!Serial)
  {
    // Wait...
  }
  d_whine.start();
}

void updateControl()
{
  if (whine && d_whine.ready())
  {
    whine = false;
    int randomDownTime = (int)random(10000, 60000);
    Serial.println("d_down start " + (String)randomDownTime);
    d_down.start(randomDownTime);
  }
  if (!whine && d_down.ready())
  {
    whine = true;
    int randomWhineTime = (int)random(5000, 30000);
    Serial.println("d_whine start " + (String)randomWhineTime);
    d_whine.start(randomWhineTime);
  }
  if (event == 0)
  {
    digitalWrite(HEART_PIN, HIGH);
    d_short.start();
    Serial.println("0");
    event = 1;
  }
  if (event == 1 && d_short.ready())
  {
    digitalWrite(HEART_PIN, LOW);
    d_long.start();
    Serial.println("1");
    event = 2;
  }
  if (event == 2 && d_long.ready())
  {
    digitalWrite(HEART_PIN, HIGH);
    d_shortest.start();
    Serial.println("2");
    event = 3;
  }
  if (event == 3 && d_shortest.ready())
  {
    digitalWrite(HEART_PIN, LOW);
    d_longest.start();
    Serial.println("3");
    event = 4;
  }
  if (event == 4 && d_longest.ready())
  {
    d_short.start();
    Serial.println("4");
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
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

void setup()
{
  pinMode(HEART_PIN, OUTPUT);
  whineSound.setLoopingOn();
  startMozzi();
  Serial.begin(9600);
  while (!Serial)
  {
    // Wait...
  }
}

void updateControl()
{
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
  return whineSound.next();
}

void loop()
{
  audioHook();
}
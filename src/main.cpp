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
  // Silence reactivation
  if (whine && d_whine.ready())
  {
    Serial.println();
    whine = false;
    int randomDownTime = (int)random(10000, 60000);
    Serial.println("d_down start " + (String)randomDownTime);
    d_down.start(randomDownTime);
    heartbeatAdjustment = (int)random(0, 10);
    Serial.println("heartbeatAdjustment " + (String)heartbeatAdjustment);
  }
  // Whine sound reactivation
  if (!whine && d_down.ready())
  {
    Serial.println();
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
    Serial.print("0");
    event = 1;
  }
  if (event == 1 && d_short.ready())
  {
    digitalWrite(HEART_PIN, LOW);
    d_long.start(t_long + heartbeatAdjustment);
    Serial.print("1");
    event = 2;
  }
  if (event == 2 && d_long.ready())
  {
    digitalWrite(HEART_PIN, HIGH);
    d_shortest.start(t_short + heartbeatAdjustment);
    Serial.print("2");
    event = 3;
  }
  if (event == 3 && d_shortest.ready())
  {
    digitalWrite(HEART_PIN, LOW);
    d_longest.start(t_longest + heartbeatAdjustment);
    Serial.print("3");
    event = 4;
  }
  if (event == 4 && d_longest.ready())
  {
    d_short.start(t_short + heartbeatAdjustment);
    Serial.print("4");
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
/**
 * Testing STM32 & Mozzi
 * Official Mozzi Example from https://github.com/sensorium/Mozzi/tree/master/examples/08.Samples/SampleHuffman_Umpah
 */
#include <STM32ADC.h>
#include <MozziGuts.h>
#include <SampleHuffman.h>
#include "umpah_huff.h"

SampleHuffman umpah(UMPAH_SOUNDDATA,UMPAH_HUFFMAN,UMPAH_SOUNDDATA_BITS);

void setup() {
  umpah.setLoopingOn();
  startMozzi();
}


void updateControl(){
}


int updateAudio(){
  return umpah.next();
}


void loop() {
  audioHook();
}
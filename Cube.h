#ifndef Cube_h
#define Cube_h

#include "Arduino.h"

class Cube {
public:
  // Initialization
  Cube();
  void reset();           // turn off all led's 
  
  // Modifiers
  void setMode(int m);    // change the mode and reset
    // Mode 0
    void ledOn(int x, int y, int z);
    void ledOff(int x, int y, int z);
    // Mode 1
    void columnOn(int x, int y);
    void columnOff(int x, int y);
    void layerOn(int z);
    void layerOff(int z);
         
  // Utilities 
  void run(unsigned long time, int delay_time);
  void mode0(int delay_time);
  void mode1(int delay_time);
  
  // Helper Functions
  void dropLED(int x, int y);  // helper for raindrops pattern
  void raiseLED(int x, int y); // helper for raindrops pattern
  void innerRingOn(int z);     // helper for opposingRings
  void innerRingOff(int z);    // helper for opposingRings
  void outerRingOn(int z);     // helper for opposingRings
  void outerRingOff(int z);    // helper for opposingRings
  void spiralIn(int z);
  void spiralOut(int z);
  
  
  // Patterns
  void bouncingRings(int cycles); // outer ring of LEDs lights in up and down pattern
  void floatingBox(int moves);    // 2x2x2 mini cube moves randomly throughout the cube
  void pinwheel(int rotations);   // vertical wall of LEDs rotates in center of cube
  void raindrops(int count);      // LEDs drop up and down the cube at random
  void randomWalk();              // all LEDs start in center and move randomly until all leave cube
  void ascension();               // more LEDs light up starting from lower edge up to opposite edge
  void opposingRings(int cycles); // inner and outer rings move up and down in opposing directions
  void wave(int cycles);          // LEDs do the wave
  void spell(String phrase);      // spells out a string of characters sliding through the cube
  
    
private:
  // member variables
  int mode_;              // 0 for individual LED basis, 1 for column and row control
  boolean leds_[5][5][5]; // on/off values for leds in mode 0
  boolean columns_[25];   // on/off values for columns in mode 1
  

};

#endif



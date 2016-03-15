#include "Cube.h"

Cube cube;

#define	p0 2
#define	p1 3
#define	p2 4
#define	p3 5
#define	p4 6
#define z0 7
#define z1 8
#define z2 9
#define z3 10
#define z4 11

void setup() {
  pinMode(p0, OUTPUT);
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(p4, OUTPUT);
  pinMode(z0, OUTPUT);
  pinMode(z1, OUTPUT);
  pinMode(z2, OUTPUT);
  pinMode(z3, OUTPUT);
  pinMode(z4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  cube.bouncingRings(4);
  cube.floatingBox(30);
  cube.randomWalk();
  cube.pinwheel(3);
  cube.raindrops(20);
  cube.ascension();
  cube.opposingRings(3);
  cube.spell("helloworld");
  cube.wave(5);
}








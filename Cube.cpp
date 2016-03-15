#include "Arduino.h"
#include "Cube.h"

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

// ******************** DATA ********************
boolean Letters[26][25] = {
  {1,0,0,0,1, 1,0,0,0,1, 1,1,1,1,1, 1,0,0,0,1, 0,1,1,1,0}, // A
  {1,1,1,1,0, 1,0,0,0,1, 1,1,1,1,0, 1,0,0,0,1, 1,1,1,1,0}, // B
  {0,1,1,1,0, 1,0,0,0,1, 1,0,0,0,0, 1,0,0,0,1, 0,1,1,1,0}, // C
  {1,1,1,1,0, 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1, 1,1,1,1,0}, // D
  {1,1,1,1,1, 1,0,0,0,0, 1,1,1,1,1, 1,0,0,0,0, 1,1,1,1,1}, // E
  {1,0,0,0,0, 1,0,0,0,0, 1,1,1,1,1, 1,0,0,0,0, 1,1,1,1,1}, // F
  {0,1,1,1,0, 1,0,0,0,1, 1,0,0,1,1, 1,0,0,0,0, 0,1,1,1,1}, // G
  {1,0,0,0,1, 1,0,0,0,1, 1,1,1,1,1, 1,0,0,0,1, 1,0,0,0,1}, // H
  {1,1,1,1,1, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 1,1,1,1,1}, // I
  {0,1,1,1,0, 1,0,0,0,1, 0,0,0,0,1, 0,0,0,0,1, 0,0,0,0,1}, // J
  {1,0,0,0,1, 1,0,0,1,0, 1,1,1,0,0, 1,0,0,1,0, 1,0,0,0,1}, // K
  {1,1,1,1,1, 1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0}, // L
  {1,0,0,0,1, 1,0,0,0,1, 1,0,1,0,1, 1,1,0,1,1, 1,0,0,0,1}, // M
  {1,0,0,0,1, 1,0,0,1,1, 1,0,1,0,1, 1,1,0,0,1, 1,0,0,0,1}, // N
  {0,1,1,1,0, 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1, 0,1,1,1,0}, // O
  {1,0,0,0,0, 1,0,0,0,0, 1,1,1,1,0, 1,0,0,0,1, 1,1,1,1,0}, // P
  {0,1,1,1,1, 1,0,0,1,1, 1,0,1,0,1, 1,0,0,0,1, 0,1,1,1,0}, // Q
  {1,0,0,0,1, 1,0,0,1,0, 1,1,1,1,0, 1,0,0,0,1, 1,1,1,1,0}, // R
  {1,1,1,1,0, 0,0,0,0,1, 0,1,1,1,0, 1,0,0,0,0, 0,1,1,1,1}, // S
  {0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 1,1,1,1,1}, // T
  {0,1,1,1,0, 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1}, // U
  {0,0,1,0,0, 0,1,0,1,0, 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1}, // V
  {1,0,0,0,1, 1,1,0,1,1, 1,0,1,0,1, 1,0,0,0,1, 1,0,0,0,1}, // W
  {1,0,0,0,1, 0,1,0,1,0, 0,0,1,0,0, 0,1,0,1,0, 1,0,0,0,1}, // X
  {0,0,1,0,0, 0,0,1,0,0, 0,0,1,0,0, 0,1,0,1,0, 1,0,0,0,1}, // Y
  {1,1,1,1,1, 0,1,0,0,0, 0,0,1,0,0, 0,0,0,1,0, 1,1,1,1,1}  // Z
};

unsigned int layers[] = {z0, z1, z2, z3, z4};

// ******************** INITIALIZATION ********************

Cube::Cube(){
  mode_ = 0;
  reset();
}

void Cube::reset(){
  for(int i=0; i<5; i++){
    layerOff(i);
    for(int j=0; j<5; j++){
      columns_[j+(5*i)] = false;
      for(int k=0; k<5; k++){
        leds_[i][j][k] = false;
      }
    }
  }
}

// ******************** MODIFIERS ********************

void Cube::setMode(int m){
  mode_ = m;
  reset();
}

void Cube::ledOn(int x, int y, int z){
  leds_[x][y][z] = true;
}

void Cube::ledOff(int x, int y, int z){
  leds_[x][y][z] = false;
}

void Cube::columnOn(int x, int y){
  columns_[x+(5*y)] = true;
}

void Cube::columnOff(int x, int y){
  columns_[x+(5*y)] = false;
}

void Cube::layerOn(int z){
  digitalWrite(layers[z], LOW);
}

void Cube::layerOff(int z){
  digitalWrite(layers[z], HIGH);
}

// ******************** UTILITIES ********************

void Cube::run(unsigned long time, int delay_time){
  unsigned long start = millis();
  while(millis() - start <= time){
    if(mode_ == 0){
      mode0(delay_time);
    }else if(mode_ == 1){
      mode1(delay_time);
    }
  }
}

void Cube::mode0(int delay_time){
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
      for(int k=0; k<5; k++){
        if(leds_[i][j][k]){
            digitalWrite(p0, i+(5*j) & 0x01);
            digitalWrite(p1, i+(5*j) & 0x02);
            digitalWrite(p2, i+(5*j) & 0x04);
            digitalWrite(p3, i+(5*j) & 0x08);
            digitalWrite(p4, i+(5*j) & 0x10);
            digitalWrite(z0, k != 0);
            digitalWrite(z1, k != 1);
            digitalWrite(z2, k != 2);
            digitalWrite(z3, k != 3);
            digitalWrite(z4, k != 4);
            delay(delay_time);
        }
      }
    }
  }
}

void Cube::mode1(int delay_time){
  for(int i=0; i<25; i++){
    if(columns_[i]){
      digitalWrite(p0, i & 0x01);
      digitalWrite(p1, i & 0x02);
      digitalWrite(p2, i & 0x04);
      digitalWrite(p3, i & 0x08);
      digitalWrite(p4, i & 0x10);
      delay(delay_time);
    }
  }
}

// **************** HELPER FUNCTIONS ****************

void Cube::dropLED(int x, int y){
  ledOff(x,y,4);
  for(int i=3; i>0; i--){
    ledOn(x,y,i);
    run(25,1);
    ledOff(x,y,i);
  }
  ledOn(x,y,0);
}

void Cube::raiseLED(int x, int y){
  ledOff(x,y,0);
  for(int i=1; i<4; i++){
    ledOn(x,y,i);
    run(25,1);
    ledOff(x,y,i);
  }
  ledOn(x,y,4);
}

void Cube::innerRingOn(int z) {
  for(int i=1; i<4; i++){
    ledOn(1,i,z);
    ledOn(3,i,z);
    ledOn(i,1,z);
    ledOn(i,3,z);
  }
}  

void Cube::innerRingOff(int z) {
  for(int i=1; i<4; i++){
    ledOff(1,i,z);
    ledOff(3,i,z);
    ledOff(i,1,z);
    ledOff(i,3,z);
  }
}

void Cube::outerRingOn(int z) {
  for(int i=0; i<5; i++){
    ledOn(0,i,z);
    ledOn(4,i,z);
    ledOn(i,0,z);
    ledOn(i,4,z);
  }
}

void Cube::outerRingOff(int z) {
  for(int i=0; i<5; i++){
    ledOff(0,i,z);
    ledOff(4,i,z);
    ledOff(i,0,z);
    ledOff(i,4,z);
  }
}

// ******************** PATTERNS ********************

void Cube::bouncingRings(int cycles){
  setMode(0);
  int delay_time = 100;
  for(int i=0; i<cycles; i++){
    for(int z=0; z<5; z++){
      outerRingOn(z);
      run(delay_time,1);
      outerRingOff(z);
    }
    for(int z=3; z>0; z--){
      outerRingOn(z);
      run(delay_time,1);
      outerRingOff(z);
    }
  }  
}

void Cube::floatingBox(int moves){
  int move_delay = 100;
  setMode(0);
  int x = random(0,3);
  int y = random(0,3);
  int z = random(0,3);
  int dx, dy, dz;
  for(int i=0; i<moves; i++){
    ledOn(x,y,z);
    ledOn(x,y+1,z);
    ledOn(x,y,z+1);
    ledOn(x,y+1,z+1);
    ledOn(x+1,y,z);
    ledOn(x+1,y+1,z);
    ledOn(x+1,y,z+1);
    ledOn(x+1,y+1,z+1);
    run(move_delay, 3);
    ledOff(x,y,z);
    ledOff(x,y+1,z);
    ledOff(x,y,z+1);
    ledOff(x,y+1,z+1);
    ledOff(x+1,y,z);
    ledOff(x+1,y+1,z);
    ledOff(x+1,y,z+1);
    ledOff(x+1,y+1,z+1);
    dx = random(-1,2);
    dy = random(-1,2);
    dz = random(-1,2);
    x = constrain(x+dx, 0, 3);
    y = constrain(y+dy, 0, 3);
    z = constrain(z+dz, 0, 3);
  }
}

void Cube::pinwheel(int rotations){
  setMode(1);
  int rotate_delay = 50;
  for(int j=0; j<rotations*2; j++){
    for(int i=0; i<5; i++){ layerOn(i); }
    for(int i=0; i<5; i++){ columnOn(2,i); }
    run(rotate_delay, 3);
    columnOff(2,4); columnOff(2,0); columnOn(3,4); columnOn(1,0);
    run(rotate_delay, 3);
    columnOff(2,3); columnOff(2,1); columnOff(3,4); columnOff(1,0);
    columnOn(4,4); columnOn(3,3); columnOn(1,1); columnOn(0,0);
    run(rotate_delay, 3);
    columnOff(4,4); columnOff(0,0); columnOn(4,3); columnOn(0,1);
    run(rotate_delay, 3);
    columnOff(3,3); columnOff(4,3); columnOff(1,1); columnOff(0,1);
    columnOn(0,2); columnOn(1,2); columnOn(3,2); columnOn(4,2);
    run(rotate_delay, 3);
    columnOff(0,2); columnOff(4,2); columnOn(0,3); columnOn(4,1);
    run(rotate_delay, 3);
    columnOff(0,3); columnOff(1,2); columnOff(3,2); columnOff(4,1);
    columnOn(0,4); columnOn(1,3); columnOn(3,1); columnOn(4,0);
    run(rotate_delay, 3);
    columnOff(0,4); columnOff(4,0); columnOn(1,4); columnOn(3,0);
    run(rotate_delay, 3);
    reset();
  }
}

void Cube::raindrops(int count){
  setMode(0);
  boolean dropped[5][5];
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){ 
      int x = random(0,2);
      if(x == 1){  
        ledOn(i,j,4);
        dropped[i][j] = false;
      }else{
        ledOn(i,j,0);
        dropped[i][j] = true;
      }
    }
  }
  for(int i=0; i<count; i++){
    int x = random(0,5);
    int y = random(0,5);
    if(dropped[x][y] == false){
      dropLED(x,y);
      dropped[x][y] = true;
      run(200,1);
    }else{
      raiseLED(x,y);
      dropped[x][y] = false;
      run(200,1);
    }
  }
}

void Cube::randomWalk(){
  setMode(0);
  int loc[5][5];
  int done_count = 0;
  int x = random(0,5);
  int y = random(0,5);
  int dz = random(0,2);
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
      ledOn(i,j,2);
      loc[i][j] = 2;
    }
  }
  while(done_count < 25){
    if(loc[x][y] >-1 && loc[x][y] < 5){
      ledOff(x,y,loc[x][y]);
      if(dz == 0){
        if(loc[x][y]-1 > -1){
          ledOn(x,y,loc[x][y]-1);
        }else{ ++done_count; }
        loc[x][y] -= 1;
      }else{
        if(loc[x][y]+1 < 5){
          ledOn(x,y,loc[x][y]+1); 
        }else{ ++done_count; }  
        loc[x][y] += 1;     
      }
      if(done_count < 20){ run(50,1); }
      else if(done_count < 22){ run(200, 1); }  
      else{ run(150, 1); }
    }
    x = random(0,5);
    y = random(0,5);
    dz = random(0,2);
  }
}

void Cube::ascension() {
  setMode(1);
  for (int x = 0; x < 5; x++) {
    layerOn(x);
    for (int y = 0; y < 5; y++) {
      columnOn(x, y);
      run(200,1);
    }
  }  
}

void Cube::opposingRings(int cycles) {
  setMode(0);
  int delay_time = 100;
  for(int i=0; i<cycles; i++){
    for(int z=0; z<5; z++){
      outerRingOn(z);
      ledOn(2,2,z);
      innerRingOn(4-z);
      run(delay_time,1);
      outerRingOff(z);
      ledOff(2,2,z);
      innerRingOff(4-z);
    }
    for(int z=3; z>0; z--){
      outerRingOn(z);
      ledOn(2,2,z);
      innerRingOn(4-z);
      run(delay_time,1);
      outerRingOff(z);
      ledOff(2,2,z);
      innerRingOff(4-z);
    }
  } 
}

void Cube::wave(int cycles){
  setMode(0);
  int z;
  for(int c=0; c<cycles; c++){
    for(int i=0; i<8; i++){
      for(int j=0; j<5; j++){
        for(int k=0; k<5; k++){
          z = (i+j)-((2*(((i+j)%5)+1))*((i+j)/5));
          if(z == -1){ z = 1; }
          if(z == 6) {z = 2; }
          ledOn(j,k,z);
        }
      }
      run(100,1);
      for(int j=0; j<5; j++){
        for(int k=0; k<5; k++){
          z = (i+j)-((2*(((i+j)%5)+1))*((i+j)/5));
          if(z == -1){ z = 1; }
          if(z == 6) {z = 2; }
          ledOff(j,k,z);
        }
      }
    }
  }
}

void Cube::spell(String phrase){
  setMode(0);
  for(int letter=0; letter<phrase.length(); letter++){
    for(int i=0; i<5; i++){
      int temp = phrase.charAt(letter)-97;
      Serial.println(temp);
      for(int j=0; j<25; j++){
        if(Letters[temp][j] == 1){
          ledOn(j%5, i, j/5);
        }
      }
      run(200, 1);
      for(int j=0; j<25; j++){
        if(Letters[temp][j] == 1){
          ledOff(j%5, i, j/5);
        }
      }
    }
  }
}

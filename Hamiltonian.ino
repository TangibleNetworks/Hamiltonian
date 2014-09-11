// Hamiltonian.ino
// Espen Knoop, 11/9/14
//
// Find hamiltonian paths in graph

#include <TN.h>

TN Tn = TN(0.0,1.0);

bool starting = false;
double inputs[] = {0.0,0.0,0.0};

int dt = 50;


void setup() {
  unvisited();
}

void loop() {}

void initialise() {
  // reset colour and outputs!
  starting = false;
  cyan();
  Tn.analogWrite(1,0.0);
  Tn.analogWrite(2,0.0);
  Tn.analogWrite(3,0.0);
  delay(100);
  while (1) {
    readInputs();
    if (Tn.sw()) {
      Tn.analogWrite(1,1.0);
      Tn.analogWrite(2,1.0);
      Tn.analogWrite(3,1.0);
      green();
      while (Tn.sw()) { delay(dt); }
      starting = true;
      current();
    }
    if (inputs[0] > 0.98 || inputs[1] > 0.98 || inputs[2] > 0.98) {
      Tn.analogWrite(1,1.0);
      Tn.analogWrite(2,1.0);
      Tn.analogWrite(3,1.0);
      yellow();
      for (int i=0; i<30; i++) {
        if (Tn.masterSw()) initialise();
        delay(10);
      }
      unvisited();
    }
    delay(2);
  }
}


void unvisited() {
  blue();
  Tn.analogWrite(1,1.0);
  Tn.analogWrite(2,1.0);
  Tn.analogWrite(3,1.0);
  while (1) {
    readInputs();
    if (Tn.masterSw()) initialise();
    if (Tn.sw()) {
      randomSeed(analogRead(A3));
      double query = 0.04 + 0.01*0.94*(double)random(100);
      Tn.analogWrite(1,query);
      Tn.analogWrite(2,query);
      Tn.analogWrite(3,query);
      delay(2*dt);
      readInputs();
      for (int i=0; i<3; i++) {
        if ((inputs[i]-query) < 0.01 && (query-inputs[i]) < 0.01) {
          green();
          delay(2*dt);
          while (Tn.sw()) { delay(dt); }
          current();
        } 
      }
      // if not:
      Tn.analogWrite(1,1.0);
      Tn.analogWrite(2,1.0);
      Tn.analogWrite(3,1.0);
      red();
      while (Tn.sw()) { delay(dt); }
      blue();
    }
    for (int i=0; i<3; i++) {
      if (inputs[i] > 0.02 && inputs[i] < 0.04) {
        lost();
      }
    }
    delay(dt);
  }
}


void current() {
  green();
  while (1) {
    if (Tn.masterSw()) initialise();
    readInputs();
    if (inputs[0] < 0.04 & inputs[1] < 0.04 & inputs[2] < 0.04){
      won();
    }
    if (Tn.sw()) {
      red();
      while (Tn.sw()) { delay(dt); }
      green();
    }
    for (int i=0; i<3; i++) {
      if (inputs[i] < 0.98 && inputs[i] > 0.04) {
        Tn.analogWrite(1,inputs[i]);
        Tn.analogWrite(2,inputs[i]);
        Tn.analogWrite(3,inputs[i]);
        delay(2*dt);
        visited();
      }
    }
    delay(dt);
  }
}


void visited() {
  yellow();
  Tn.analogWrite(1,0.0);
  Tn.analogWrite(2,0.0);
  Tn.analogWrite(3,0.0);
  while (1) {
    if (Tn.masterSw()) initialise();
    readInputs();
    for (int i=0; i<3; i++) {
      if (inputs[i] > 0.02 && inputs[i] < 0.04) {
        won();
      }
    }
    if (Tn.sw()) {
      red();
      while (Tn.sw()) { delay(dt); }
      yellow();
    }
    delay(dt);
  }
}

void won() {
  green();
  Tn.analogWrite(1,0.03);
  Tn.analogWrite(2,0.03);
  Tn.analogWrite(3,0.03);
  while (1) {
    if (Tn.masterSw()) initialise();
    delay(dt);
  }
}

void lost() {
  red();
  Tn.analogWrite(1,0.03);
  Tn.analogWrite(2,0.03);
  Tn.analogWrite(3,0.03);
  while (1) {
    if (Tn.masterSw()) initialise();
    delay(dt);
  }
}


void readInputs() {
  for (int i=0; i<3; i++) {
    inputs[i] = Tn.analogRead(i+1);
  }
}



// COLOURS
inline void blue() { Tn.colour(0.0,0.0,0.1); }
inline void red() { Tn.colour(1.0,0.0,0.0); }
inline void yellow() { Tn.colour(1.0,1.0,0.0); }
inline void green() { Tn.colour(0.0,1.0,0.0); }
inline void cyan() { Tn.colour(0.0,0.2,0.2); }





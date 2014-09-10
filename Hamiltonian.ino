// Hamiltonian.ino
// Espen Knoop, 10/9/14
//
// Find hamiltonian paths in graph

#include <TN.h>

TN Tn = TN(-1.0,1.0);

void setup() {
  Tn.digitalWrite(1,0);
  Tn.digitalWrite(2,0);
  Tn.digitalWrite(3,0);
  Tn.digitalRead(1);
  Tn.digitalRead(2);
  Tn.digitalRead(3);
  
  if (Tn.dip1()) {
    current();
  }
  unvisited();
}


void loop() {}

void unvisited() {
  Tn.colour(0,0,0);
  Tn.digitalWrite(1,0);
  Tn.digitalWrite(2,0);
  Tn.digitalWrite(3,0);
  delay(100);
  while (1) {
    if (Tn.masterSw()) setup();
    if (Tn.sw()) {
      if(Tn.digitalRead(1) + Tn.digitalRead(2) + Tn.digitalRead(3)) {
        Tn.colour(0,255,0);
        while(Tn.sw()) delay(50);
        current();
      }
      else {
        Tn.colour(255,0,0);
        while (Tn.sw()) delay(50);
        Tn.colour(0,0,0);
      }
    }
    delay(50);
  }  
}

void current() {
  Tn.colour(0,255,0);
  Tn.digitalWrite(1,1);
  Tn.digitalWrite(2,1);
  Tn.digitalWrite(3,1);
  delay(100);
  while (1) {
    if (Tn.masterSw()) setup();
    if(Tn.digitalRead(1) + Tn.digitalRead(2) + Tn.digitalRead(3)) {
      visited();
    }
    if (Tn.sw()) {
      Tn.colour(255,0,0);
      while (Tn.sw()) delay(50);
      Tn.colour(0,255,0);
    }
    delay(50);
  }  
}


void visited() {
  Tn.colour(255,255,0);
  Tn.digitalWrite(1,0);
  Tn.digitalWrite(2,0);
  Tn.digitalWrite(3,0);
  delay(100);
  while (1) {
    if (Tn.masterSw()) setup();
    if (Tn.sw()) {
      Tn.colour(255,0,0);
      while (Tn.sw()) delay(50);
      Tn.colour(255,255,0);
    }
    delay(50);
  }  
}




#include "Gps.h"

Gps gps;

void setup() {
  // put your setup code here, to run once:
  gps.Initialize();
}

void loop() {
  // put your main code here, to run repeatedly:
  gps.ReadCurrentLocation();
}

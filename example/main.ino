/*
 * Copyright (c) 2024 Andrea Canale.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "MiCS4514.hpp"

// CO pin
#define RED_PIN 32
// NOX pin
#define NOX_PIN 35
// PRE pin
#define PRE_PIN 23

MiCS4514 mics4514(PRE_PIN, NOX_PIN, RED_PIN);

void setup() {
  Serial.begin(9600);
  mics4514.begin();
}

void loop() {
  float nox = mics4514.get_nox();
  float co = mics4514.get_co();
  Serial.printf("NOX: %f\nCO:%f\n", nox, co);
}
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

// Refactored from: https://github.com/tushar-saini/Sensors-Sample-Code/blob/master/MiCS-4514/MiCS-4514.ino

#include "MiCS4514.hpp"
#include <Arduino.h>

#define PRE_HEAT_SECONDS 10

#define CALIB_R0_NO2 2200   // R0 calibration value for the NO2 sensor
#define CALIB_R0_CO 750000  // R0 calibration value for the CO sensor

MiCS4514::MiCS4514(int _pre_pin, int _nox_pin, int _co_pin) {
    pre_pin = _pre_pin;
    nox_pin = _nox_pin;
    co_pin = _co_pin;
}

MiCS4514::~MiCS4514() {}

void MiCS4514::begin() {
    digitalWrite(pre_pin, 1);
    delay(PRE_HEAT_SECONDS * 1000);
    digitalWrite(pre_pin, 0);
}

// NO2 Molecolar Weight
#define NOX_MOL 46.01

float MiCS4514::get_nox() {
    Serial.printf("NOX PIN %i ANALOG: %i\n", nox_pin, analogRead(nox_pin));
    float fVolt = 3.3;
    fVolt *= analogRead(nox_pin);
    fVolt /= 1024.0;

    float fRes = (5000.0 / fVolt - 1000) / CALIB_R0_NO2;
    float fConc = 0.0;

    // Convert to ppm
    if (fRes < 3.0) fRes = 3.0;
    if (fRes >= 3.0 && fRes < 8.0)
        fConc = (fRes - 0.5) / 0.25;
    else
        fConc = (fRes + 129.655) / 4.589;

    return fConc * (NOX_MOL / 24.5);  // Convert to ug/m3
}

// CO Molecolar weight
#define CO_MOL 28.01

float MiCS4514::get_co() {
    float fVolt, fRes, fConc;
    Serial.printf("CO PIN %i ANALOG: %i\n", nox_pin, analogRead(nox_pin));

    fVolt = (analogRead(co_pin) * 3.3) / 1024.0;
    // Get Rs/R0 value
    fRes = (5000.0 / fVolt - 1000) / CALIB_R0_CO;

    // Convert to ppm
    if (fRes > 0.7) fRes = 0.7;
    if (fRes > 0.6)
        fConc = (0.711 - fRes) / 0.011;
    else if (fRes > 0.3)
        fConc = (0.7 - fRes) / 0.01;
    else
        fConc = (0.3233 - fRes) / 0.00058;

    return fConc * (CO_MOL / 24.5);  // Convert to mg/m3
}
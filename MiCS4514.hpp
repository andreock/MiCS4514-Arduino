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

#ifndef MICS4514_H
#define MICS4514_H

class MiCS4514
{
private:
    int pre_pin = 0;
    int nox_pin = 0;
    int co_pin = 0;
public:
    MiCS4514(int _pre_pin, int _nox_pin, int _co_pin);
    ~MiCS4514();
    /// @brief Preheat the sensor
    void begin();
    /// @brief Get NO2 value in ug/m3
    /// @return NO2 value in ug/m3
    float get_nox();
    /// @brief Get CO value in mg/m3
    /// @return CO value in mg/m3
    float get_co();
};

#endif
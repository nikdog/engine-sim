// Engine Simulator
// Copyright (C) 2022 AngeTheGreat (Ange Yaghi)
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
// 
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef ATG_ENGINE_SIM_APPLICATION_SETTINGS_H
#define ATG_ENGINE_SIM_APPLICATION_SETTINGS_H
#include <string>

struct ApplicationSettings {
    bool startFullscreen = false;
    std::string powerUnits = "hp";
    std::string torqueUnits = "lb-ft";
    std::string speedUnits = "mph";
    std::string pressureUnits = "inHg";
    std::string boostUnits = "psi";

    int colorBackground = 0x0E1012;
    int colorForeground = 0xFFFFFF;
    int colorShadow = 0x0E1012;
    int colorHighlight1 = 0xEF4545;
    int colorHighlight2 = 0xFFFFFF;
    int colorPink = 0xF394BE;
    int colorRed = 0xEE4445;
    int colorOrange = 0xF4802A;
    int colorYellow = 0xFDBD2E;
    int colorBlue = 0x77CEE0;
    int colorGreen = 0xBDD869;
};

#endif /* ATG_ENGINE_SIM_APPLICATION_SETTINGS_H */

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

#include "../include/cylinder_bank.h"

#include "../include/constants.h"

#include <cmath>

CylinderBank::CylinderBank() {
    m_angle = 0.0;
    m_bore = 0.0;
    m_deckHeight = 0.0;
    m_cylinderCount = 0;
    m_displayDepth = 0.4;
    m_index = -1;

    m_dx = m_dy = 0;
    m_x = m_y = 0;
}

CylinderBank::~CylinderBank() {
    /* void */
}

void CylinderBank::initialize(const Parameters &params) {
    m_angle = params.angle;
    m_bore = params.bore;
    m_deckHeight = params.deckHeight;
    m_cylinderCount = params.cylinderCount;

    m_dx = std::cos(m_angle + constants::pi / 2);
    m_dy = std::sin(m_angle + constants::pi / 2);

    m_x = params.positionX;
    m_y = params.positionY;

    m_displayDepth = params.displayDepth;

    m_index = params.index;
}

void CylinderBank::destroy() {
    /* void */
}

void CylinderBank::getPositionAboveDeck(double h, double *x, double *y) const {
    *x = m_dx * (m_deckHeight + h) + m_x;
    *y = m_dy * (m_deckHeight + h) + m_y;
}

double CylinderBank::boreSurfaceArea() const {
    return constants::pi * m_bore * m_bore / 4.0;
}

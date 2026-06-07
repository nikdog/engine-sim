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

#include "../include/piston.h"

#include "../include/connecting_rod.h"
#include "../include/crankshaft.h"
#include "../include/cylinder_bank.h"

#include <cmath>

Piston::Piston() {
    m_rod = nullptr;
    m_bank = nullptr;
    m_cylinderConstraint = nullptr;
    m_cylinderIndex = -1;
    m_compressionHeight = 0.0;
    m_displacement = 0.0;
    m_wristPinLocation = 0.0;
    m_mass = 0.0;
    m_blowby_k = 0.0;
}

Piston::~Piston() {
    /* void */
}

void Piston::initialize(const Parameters &params) {
    m_rod = params.Rod;
    m_bank = params.Bank;
    m_cylinderIndex = params.CylinderIndex;
    m_compressionHeight = params.CompressionHeight;
    m_displacement = params.Displacement;
    m_wristPinLocation = params.WristPinPosition;
    m_mass = params.mass;
    m_blowby_k = params.BlowbyFlowCoefficient;
}

void Piston::destroy() {
    /* void */
}

double Piston::relativeX() const {
    return m_body.p_x - m_bank->getX();
}

double Piston::relativeY() const {
    return m_body.p_y - m_bank->getY();
}

double Piston::calculateCylinderWallForce() const {
    return std::sqrt(
        m_cylinderConstraint->F_x[0][0] * m_cylinderConstraint->F_x[0][0]
        + m_cylinderConstraint->F_y[0][0] * m_cylinderConstraint->F_y[0][0]);
}

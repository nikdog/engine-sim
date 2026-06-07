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

#include "../include/standard_valvetrain.h"

#include "../include/camshaft.h"

StandardValvetrain::StandardValvetrain() {
    m_intakeCamshaft = nullptr;
    m_exhaustCamshaft = nullptr;
}

StandardValvetrain::~StandardValvetrain() {
    /* void */
}

void StandardValvetrain::initialize(const Parameters &params) {
    m_intakeCamshaft = params.intakeCamshaft;
    m_exhaustCamshaft = params.exhaustCamshaft;
}

double StandardValvetrain::intakeValveLift(int cylinder) {
    return m_intakeCamshaft->valveLift(cylinder);
}

double StandardValvetrain::exhaustValveLift(int cylinder) {
    return m_exhaustCamshaft->valveLift(cylinder);
}

Camshaft *StandardValvetrain::getActiveIntakeCamshaft() {
    return m_intakeCamshaft;
}

Camshaft *StandardValvetrain::getActiveExhaustCamshaft() {
    return m_exhaustCamshaft;
}

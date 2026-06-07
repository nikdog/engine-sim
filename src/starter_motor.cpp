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

#include "../include/starter_motor.h"

#include "../include/units.h"

StarterMotor::StarterMotor() : atg_scs::Constraint(1, 1) {
    m_ks = 10.0;
    m_kd = 1.0;
    m_maxTorque = units::torque(80.0, units::ft_lb);
    m_rotationSpeed = -units::rpm(200.0);
    m_enabled = false;
}

StarterMotor::~StarterMotor() {
    /* void */
}

void StarterMotor::connectCrankshaft(Crankshaft *crankshaft) {
    m_bodies[0] = &crankshaft->m_body;
}

void StarterMotor::calculate(Output *output, atg_scs::SystemState *state) {
    output->J[0][0] = 0;
    output->J[0][1] = 0;
    output->J[0][2] = 1;

    output->J_dot[0][0] = 0;
    output->J_dot[0][1] = 0;
    output->J_dot[0][2] = 0;

    output->ks[0] = m_ks;
    output->kd[0] = m_kd;

    output->C[0] = 0;

    output->v_bias[0] = -m_rotationSpeed;

    if (m_rotationSpeed < 0) {
        output->limits[0][0] = m_enabled ? -m_maxTorque : 0.0;
        output->limits[0][1] = 0.0;
    }
    else {
        output->limits[0][0] = 0.0;
        output->limits[0][1] = m_enabled ? m_maxTorque : 0.0;
    }
}

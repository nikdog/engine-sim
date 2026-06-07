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

#include "../include/dynamometer.h"

#include "../include/units.h"

#include <cmath>

Dynamometer::Dynamometer() : atg_scs::Constraint(1, 1) {
    m_rotationSpeed = 0.0;
    m_ks = 10.0;
    m_kd = 1.0;
    m_maxTorque = units::torque(10000.0, units::ft_lb);

    m_enabled = false;
    m_hold = false;
}

Dynamometer::~Dynamometer() {
    /* void */
}

void Dynamometer::connectCrankshaft(Crankshaft *crankshaft) {
    m_bodies[0] = &crankshaft->m_body;
}

void Dynamometer::calculate(Output *output, atg_scs::SystemState *state) {
    output->J[0][0] = 0;
    output->J[0][1] = 0;
    output->J[0][2] = 1;

    output->J_dot[0][0] = 0;
    output->J_dot[0][1] = 0;
    output->J_dot[0][2] = 0;

    output->ks[0] = m_ks;
    output->kd[0] = m_kd;

    output->C[0] = 0;

    if (m_bodies[0]->v_theta < 0) {
        output->v_bias[0] = m_rotationSpeed;
        output->limits[0][0] = (m_hold && m_enabled) ? -m_maxTorque : 0.0;
        output->limits[0][1] = m_enabled ? m_maxTorque : 0.0;
    }
    else {
        output->v_bias[0] = -m_rotationSpeed;
        output->limits[0][0] = m_enabled ? -m_maxTorque : 0.0;
        output->limits[0][1] = (m_hold && m_enabled) ? m_maxTorque : 0.0;
    }
}

double Dynamometer::getTorque() const {
    return (m_bodies[0]->v_theta > 0)
        ? -atg_scs::Constraint::F_t[0][0]
        : atg_scs::Constraint::F_t[0][0];
}

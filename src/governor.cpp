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

#include "../include/governor.h"

#include "../include/engine.h"
#include "../include/utilities.h"

Governor::Governor() {
    m_minSpeed = m_maxSpeed = 0;
    m_targetSpeed = 0;
    m_currentThrottle = 1.0;
    m_velocity = 0.0;
    m_minVelocity = m_maxVelocity = 0.0;
    m_k_s = m_k_d = 0.0;
    m_gamma = 1.0;
}

Governor::~Governor() {
    /* void */
}

void Governor::initialize(const Parameters &params) {
    m_minSpeed = params.minSpeed;
    m_maxSpeed = params.maxSpeed;
    m_minVelocity = params.minVelocity;
    m_maxVelocity = params.maxVelocity;
    m_k_s = params.k_s;
    m_k_d = params.k_d;
    m_gamma = params.gamma;
}

void Governor::setSpeedControl(double s) {
    Throttle::setSpeedControl(s);

    m_targetSpeed = (1 - s) * m_minSpeed + s * m_maxSpeed;
}

void Governor::update(double dt, Engine *engine) {
    const double currentSpeed = engine->getSpeed();
    const double ds = m_targetSpeed * m_targetSpeed - currentSpeed * currentSpeed;

    m_velocity += (dt * -ds * m_k_s - m_velocity * dt * m_k_d);
    m_velocity = clamp(m_velocity, m_minVelocity, m_maxVelocity);
   
    if (std::abs(currentSpeed) < std::abs(0.5 * m_minSpeed)) {
        m_velocity = 0;
        m_currentThrottle = 1.0;
    }

    m_currentThrottle += m_velocity * dt;
    m_currentThrottle = clamp(m_currentThrottle);

    engine->setThrottle(1 - std::pow(1 - m_currentThrottle, m_gamma));
}

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

#include "../include/direct_throttle_linkage.h"

#include "../include/engine.h"

#include <cmath>

DirectThrottleLinkage::DirectThrottleLinkage() {
    m_gamma = 1.0;
    m_throttlePosition = 1.0;
}

DirectThrottleLinkage::~DirectThrottleLinkage() {
    /* void */
}

void DirectThrottleLinkage::initialize(const Parameters &params) {
    m_gamma = params.gamma;
}

void DirectThrottleLinkage::setSpeedControl(double s) {
    Throttle::setSpeedControl(s);
    m_throttlePosition = 1 - std::pow(s, m_gamma);
}

void DirectThrottleLinkage::update(double dt, Engine *engine) {
    Throttle::update(dt, engine);
    engine->setThrottle(m_throttlePosition);
}

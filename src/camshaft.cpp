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

#include "../include/camshaft.h"

#include "../include/crankshaft.h"
#include "../include/constants.h"
#include "../include/units.h"

#include <cmath>
#include <assert.h>

Camshaft::Camshaft() {
    m_crankshaft = nullptr;
    m_lobeAngles = nullptr;
    m_lobeProfile = nullptr;
    m_lobes = 0;
    m_advance = 0;
    m_baseRadius = 0;
}

Camshaft::~Camshaft() {
    assert(m_lobeAngles == nullptr);
}

void Camshaft::initialize(const Parameters &params) {
    m_lobeAngles = new double[params.lobes];
    memset(m_lobeAngles, 0, sizeof(double) * params.lobes);

    m_lobes = params.lobes;
    m_crankshaft = params.crankshaft;
    m_lobeProfile = params.lobeProfile;
    m_advance = params.advance;
    m_baseRadius = params.baseRadius;
}

void Camshaft::destroy() {
    delete[] m_lobeAngles;
    m_lobeAngles = nullptr;

    m_lobes = 0;
}

double Camshaft::valveLift(int lobe) const {
    return sampleLobe(getAngle() + m_lobeAngles[lobe]);
}

double Camshaft::sampleLobe(double theta) const {
    double clampedTheta = std::fmod(theta, 2 * constants::pi);
    if (clampedTheta < 0) clampedTheta += 2 * constants::pi;
    if (clampedTheta >= constants::pi) clampedTheta -= 2 * constants::pi;

    return m_lobeProfile->sampleTriangle(clampedTheta);
}

double Camshaft::getAngle() const {
    const double angle =
        std::fmod((m_crankshaft->getAngle() + m_advance) * 0.5, 2 * constants::pi);
    return (angle < 0)
        ?  angle + 2 * constants::pi
        :  angle;
}

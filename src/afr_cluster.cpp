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

#include "../include/afr_cluster.h"

#include "../include/units.h"
#include "../include/gauge.h"
#include "../include/constants.h"
#include "../include/engine_sim_application.h"

#include <sstream>

AfrCluster::AfrCluster() {
    m_engine = nullptr;
    m_intakeAfrGauge = nullptr;
    m_exhaustAfrGauge = nullptr;
}

AfrCluster::~AfrCluster() {
    /* void */
}

void AfrCluster::initialize(EngineSimApplication *app) {
    UiElement::initialize(app);

    m_intakeAfrGauge = addElement<LabeledGauge>();
    m_exhaustAfrGauge = addElement<LabeledGauge>();

    constexpr float shortenAngle = (float)units::angle(1.0, units::deg);

    m_intakeAfrGauge->m_title = "IN. AFR";
    m_intakeAfrGauge->m_unit = "";
    m_intakeAfrGauge->m_precision = 1;
    m_intakeAfrGauge->setLocalPosition({ 0, 0 });
    m_intakeAfrGauge->m_gauge->m_min = 0;
    m_intakeAfrGauge->m_gauge->m_max = 50;
    m_intakeAfrGauge->m_gauge->m_minorStep = 1;
    m_intakeAfrGauge->m_gauge->m_majorStep = 5;
    m_intakeAfrGauge->m_gauge->m_maxMinorTick = 7000;
    m_intakeAfrGauge->m_gauge->m_thetaMin = (float)constants::pi * 1.2f;
    m_intakeAfrGauge->m_gauge->m_thetaMax = -(float)constants::pi * 0.2f;
    m_intakeAfrGauge->m_gauge->m_needleWidth = 4.0f;
    m_intakeAfrGauge->m_gauge->m_gamma = 1.0f;
    m_intakeAfrGauge->m_gauge->m_needleKs = 1000.0f;
    m_intakeAfrGauge->m_gauge->m_needleKd = 20.0f;
    m_intakeAfrGauge->m_gauge->setBandCount(0);

    m_exhaustAfrGauge->m_title = "EX. O2";
    m_exhaustAfrGauge->m_unit = "";
    m_exhaustAfrGauge->m_precision = 1;
    m_exhaustAfrGauge->setLocalPosition({ 0, 0 });
    m_exhaustAfrGauge->m_gauge->m_min = 0;
    m_exhaustAfrGauge->m_gauge->m_max = 100;
    m_exhaustAfrGauge->m_gauge->m_minorStep = 5;
    m_exhaustAfrGauge->m_gauge->m_majorStep = 10;
    m_exhaustAfrGauge->m_gauge->m_maxMinorTick = 200;
    m_exhaustAfrGauge->m_gauge->m_thetaMin = (float)constants::pi * 1.2f;
    m_exhaustAfrGauge->m_gauge->m_thetaMax = -(float)constants::pi * 0.2f;
    m_exhaustAfrGauge->m_gauge->m_needleWidth = 4.0f;
    m_exhaustAfrGauge->m_gauge->m_gamma = 1.0f;
    m_exhaustAfrGauge->m_gauge->m_needleKs = 1000.0f;
    m_exhaustAfrGauge->m_gauge->m_needleKd = 20.0f;
    m_exhaustAfrGauge->m_gauge->setBandCount(0);
}

void AfrCluster::destroy() {
    UiElement::destroy();
}

void AfrCluster::update(float dt) {
    UiElement::update(dt);
}

void AfrCluster::render() {
    const Bounds top = m_bounds.verticalSplit(0.5f, 1.0f);
    const Bounds bottom = m_bounds.verticalSplit(0.0f, 0.5f);

    m_intakeAfrGauge->m_bounds = top;
    m_intakeAfrGauge->m_gauge->m_value = (m_engine != nullptr)
        ? static_cast<float>(m_engine->getIntakeAfr())
        : 0.0f;

    m_exhaustAfrGauge->m_bounds = bottom;
    m_exhaustAfrGauge->m_gauge->m_value = (m_engine != nullptr)
        ? static_cast<float>(m_engine->getExhaustO2()) * 100.0f
        : 0.0f;

    UiElement::render();
}

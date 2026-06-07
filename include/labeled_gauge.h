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

#ifndef ATG_ENGINE_SIM_LABELED_GAUGE_H
#define ATG_ENGINE_SIM_LABELED_GAUGE_H

#include "ui_element.h"

#include "gauge.h"

#include <string>

class LabeledGauge : public UiElement {
    public:
        LabeledGauge();
        virtual ~LabeledGauge();

        virtual void initialize(EngineSimApplication *app);
        virtual void destroy();

        virtual void update(float dt);
        virtual void render();

        Gauge *m_gauge;
        std::string m_title;

        int m_precision;
        bool m_spaceBeforeUnit;
        std::string m_unit;

        float m_margin = 10.0f;
        float m_needleInnerRadius = 0.1f;
        float m_needleOuterRadius = 0.7f;
};

#endif /* ATG_ENGINE_SIM_LABELED_GAUGE_H */

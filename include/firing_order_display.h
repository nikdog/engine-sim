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

#ifndef ATG_ENGINE_SIM_FIRING_ORDER_DISPLAY_H
#define ATG_ENGINE_SIM_FIRING_ORDER_DISPLAY_H

#include "ui_element.h"

#include "engine.h"
#include "gauge.h"

class FiringOrderDisplay : public UiElement {
    public:
        FiringOrderDisplay();
        virtual ~FiringOrderDisplay();

        virtual void initialize(EngineSimApplication *app);
        virtual void destroy();

        virtual void update(float dt);
        virtual void render();

        Engine *m_engine;

    protected:
        int m_cylinderCount;
        float *m_cylinderLit;
};

#endif /* ATG_ENGINE_SIM_FIRING_ORDER_DISPLAY_H */

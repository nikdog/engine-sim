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

#ifndef ATG_ENGINE_SIM_UI_MANAGER_H
#define ATG_ENGINE_SIM_UI_MANAGER_H

#include "ui_element.h"

#include <vector>

class EngineSimApplication;
class UiManager {
    public:
        UiManager();
        ~UiManager();

        void initialize(EngineSimApplication *app);
        void destroy();

        void update(float dt);
        void render();

        UiElement *getRoot() { return &m_root; }

    protected:
        UiElement m_root;

        UiElement *m_dragStart;
        UiElement *m_hover;
        Point m_mouse_p0;
        Point m_drag_p0;

        int m_lastMouseScroll;

    protected:
        EngineSimApplication *m_app;
};

#endif /* ATG_ENGINE_SIM_UI_MANAGER_H */

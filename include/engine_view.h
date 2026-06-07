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

#ifndef ATG_ENGINE_SIM_ENGINE_VIEW_H
#define ATG_ENGINE_SIM_ENGINE_VIEW_H

#include "ui_element.h"

class EngineView : public UiElement {
    public:
        EngineView();
        virtual ~EngineView();

        virtual void update(float dt);
        virtual void render();
        virtual void onMouseDown(const Point &mouseLocal);
        virtual void onDrag(const Point &p0, const Point &mouse0, const Point &mouse);
        virtual void onMouseScroll(int scroll);

        void setDrawFrame(bool drawFrame) { m_drawFrame = drawFrame; }
        void setBounds(const Bounds &bounds);

        Point getCenter() const;

        Point getCameraPosition() const;
        float m_zoom;
        
    protected:
        Point m_pan;
        Point m_dragStart;
        int m_lastScroll;
        bool m_drawFrame;
};

#endif /* ATG_ENGINE_SIM_ENGINE_VIEW_H */

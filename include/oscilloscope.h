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

#ifndef ATG_ENGINE_SIM_OSCILLOSCOPE_H
#define ATG_ENGINE_SIM_OSCILLOSCOPE_H

#include "ui_element.h"

class Oscilloscope : public UiElement {
    public:
        struct DataPoint {
            double x, y;
        };

    public:
        Oscilloscope();
        virtual ~Oscilloscope();

        virtual void initialize(EngineSimApplication *app);
        virtual void destroy();

        virtual void update(float dt);
        virtual void render();
        void render(const Bounds &bounds);

        Point dataPointToRenderPosition(
            const DataPoint &p,
            const Bounds &bounds) const;

        void addDataPoint(double x, double y);

        void setBufferSize(int n);
        void reset();

        double m_xMin;
        double m_xMax;

        double m_yMin;
        double m_yMax;

        double m_dynamicallyResizeX;
        double m_dynamicallyResizeY;

        double m_lineWidth;
        bool m_drawReverse;
        bool m_drawZero;

        ysVector i_color;

    protected:
        DataPoint *m_points;
        Point *m_renderBuffer;
        int m_writeIndex;
        int m_bufferSize;
        int m_pointCount;
};

#endif /* ATG_ENGINE_SIM_OSCILLOSCOPE_H */

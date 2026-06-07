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

#ifndef ATG_ENGINE_SIM_FUNCTION_H
#define ATG_ENGINE_SIM_FUNCTION_H

#include "gaussian_filter.h"

class Function {
    protected:
        static GaussianFilter *DefaultGaussianFilter;

    public:
        Function();
        virtual ~Function();

        void initialize(int size, double filterRadius, GaussianFilter *filter = nullptr);
        void resize(int newCapacity);
        void destroy();

        void setInputScale(double s) { m_inputScale = s; }
        void setOutputScale(double s) { m_outputScale = s; }
        void addSample(double x, double y);

        double sampleTriangle(double x) const;
        double sampleGaussian(double x) const;
        double triangle(double x) const;
        int closestSample(double x) const;

        bool isOrdered() const;

        void getDomain(double *x0, double *x1);
        void getRange(double *y0, double *y1);

    protected:
        double *m_x;
        double *m_y;

        double m_yMin;
        double m_yMax;
        double m_inputScale;
        double m_outputScale;

        double m_filterRadius;

        int m_capacity;
        int m_size;

        GaussianFilter *m_gaussianFilter;
};

#endif /* ATG_ENGINE_SIM_FUNCTION_H */

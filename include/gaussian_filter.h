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

#ifndef ATG_ENGINE_SIM_GUASSIAN_FILTER_H
#define ATG_ENGINE_SIM_GUASSIAN_FILTER_H

#include "scs.h"

#include "crankshaft.h"

class GaussianFilter {
    public:
        GaussianFilter();
        ~GaussianFilter();

        void initialize(double alpha, double radius, int cacheSteps=1024);
        double evaluate(double s) const;

        double getRadius() const { return m_radius; }
        double getAlpha() const { return m_alpha; }

    protected:
        double calculate(double s) const;
        void generateCache();

    protected:
        double *m_cache;

        int m_cacheSteps;
        double m_radius;
        double m_alpha;

        double m_exp_s;
        double m_inv_r;
};

#endif /* ATG_ENGINE_SIM_GAUSSIAN_FILTER_H */

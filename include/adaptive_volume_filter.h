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

#ifndef ATG_ENGINE_SIM_ADAPTIVE_VOLUME_FILTER_H
#define ATG_ENGINE_SIM_ADAPTIVE_VOLUME_FILTER_H

#include "filter.h"

class AdaptiveVolumeFilter : public Filter {
    public:
        AdaptiveVolumeFilter();
        virtual ~AdaptiveVolumeFilter();

        void initialize(int lookahead);
        virtual double f(double sample);
        virtual void destroy();

    protected:
        double *m_samples;
        int m_sampleCount;
        int m_lookahead;
};

#endif /* ATG_ENGINE_SIM_CONVOLUTION_ADAPTIVE_VOLUME */

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

#ifndef ATG_ENGINE_SIM_PREEMPHASIS_FILTER_H
#define ATG_ENGINE_SIM_PREEMPHASIS_FILTER_H

#include "filter.h"

#include "low_pass_filter.h"

#include <random>

class PreemphasisFilter : public Filter {
public:
    PreemphasisFilter() { m_lastSample = 0; }
    virtual ~PreemphasisFilter() {}

    virtual float f(float sample) override { return fast_f(sample); }

    __forceinline float fast_f(float sample) {
        const float s = -0.95f * sample + m_lastSample;

        m_lastSample = sample;
        return s;
    }

protected:
    float m_lastSample;
};

#endif /* ATG_ENGINE_SIM_PREEMPHASIS_FILTER_H */

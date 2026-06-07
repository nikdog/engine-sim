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

#ifndef ATG_ENGINE_SIM_LOW_PASS_FILTER_H
#define ATG_ENGINE_SIM_LOW_PASS_FILTER_H

#include "filter.h"

#include "constants.h"

class LowPassFilter : public Filter {
    public:
        LowPassFilter();
        virtual ~LowPassFilter();

        virtual float f(float sample) override;

        __forceinline float fast_f(float sample) {
            const float alpha = m_dt / (m_rc + m_dt);
            m_y = alpha * sample + (1 - alpha) * m_y;

            return m_y;
        }

        inline void setCutoffFrequency(float f) {
            m_rc = 1.0f / (f * 2.0f * static_cast<float>(constants::pi));
        }

        float m_dt;

    protected:
        float m_y;
        float m_rc;
};

#endif /* ATG_ENGINE_SIM_LOW_PASS_FILTER_H */

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

#ifndef ATG_ENGINE_SIM_LEVELING_FILTER_H
#define ATG_ENGINE_SIM_LEVELING_FILTER_H

#include "filter.h"

#include "function.h"

class LevelingFilter : public Filter {
    public:
        LevelingFilter();
        virtual ~LevelingFilter();

        virtual float f(float sample);
        float getAttenuation() const { return m_attenuation; }

    protected:
        float m_peak;
        float m_attenuation;

    public:
        float p_maxLevel;
        float p_minLevel;
        float p_target;
};

#endif /* ATG_ENGINE_SIM_LEVELING_FILTER_H */

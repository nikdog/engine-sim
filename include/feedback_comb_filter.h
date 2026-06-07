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

#ifndef ATG_ENGINE_SIM_FEEDBACK_COMB_FILTER_H
#define ATG_ENGINE_SIM_FEEDBACK_COMB_FILTER_H

#include "filter.h"

class FeedbackCombFilter : public Filter {
    public:
        FeedbackCombFilter();
        virtual ~FeedbackCombFilter();

        void initialize(int M);
        virtual float f(float sample) override;
        virtual void destroy();

        float a_M;

    protected:
        float *m_y;
        int m_offset;

    protected:
        int M;
};

#endif /* ATG_ENGINE_SIM_FEEDBACK_COMB_FILTER_H */

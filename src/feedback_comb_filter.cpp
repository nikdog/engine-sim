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

#include "../include/feedback_comb_filter.h"

#include <assert.h>

FeedbackCombFilter::FeedbackCombFilter() {
    M = 0;
    a_M = 1.0;
    m_y = nullptr;
    m_offset = 0;
}

FeedbackCombFilter::~FeedbackCombFilter() {
    assert(m_y == nullptr);
}

void FeedbackCombFilter::initialize(int M) {
    this->M = M;
    m_y = new float[M];
    m_offset = 0;
}

float FeedbackCombFilter::f(float sample) {
    const float y_n_min_M = m_y[m_offset];

    const float y_n = sample + a_M * y_n_min_M;

    m_y[m_offset] = y_n;
    m_offset = (m_offset + 1) % M;

    return y_n;
}

void FeedbackCombFilter::destroy() {
    delete[] m_y;

    m_y = nullptr;
}

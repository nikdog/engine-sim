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

#ifndef ATG_ENGINE_SIM_GOVERNOR_H
#define ATG_ENGINE_SIM_GOVERNOR_H

#include "throttle.h"

class Governor : public Throttle {
public:
    struct Parameters {
        double minSpeed;
        double maxSpeed;
        double minVelocity;
        double maxVelocity;
        double k_s;
        double k_d;
        double gamma;
    };

public:
    Governor();
    virtual ~Governor();

    void initialize(const Parameters &params);

    virtual void setSpeedControl(double s);
    virtual void update(double dt, Engine *engine);

protected:
    double m_minSpeed;
    double m_maxSpeed;
    double m_minVelocity;
    double m_maxVelocity;
    double m_k_s;
    double m_k_d;
    double m_gamma;

    double m_targetSpeed;

    double m_currentThrottle;
    double m_velocity;
};

#endif /* ATG_ENGINE_SIM_GOVERNOR_H */

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

#ifndef ATG_ENGINE_SIM_STANDARD_VALVETRAIN_H
#define ATG_ENGINE_SIM_STANDARD_VALVETRAIN_H

#include "valvetrain.h"

class StandardValvetrain : public Valvetrain {
public:
    struct Parameters {
        Camshaft *intakeCamshaft;
        Camshaft *exhaustCamshaft;
    };

public:
    StandardValvetrain();
    virtual ~StandardValvetrain();

    void initialize(const Parameters &parameters);

    virtual double intakeValveLift(int cylinder) override;
    virtual double exhaustValveLift(int cylinder) override;

    virtual Camshaft *getActiveIntakeCamshaft() override;
    virtual Camshaft *getActiveExhaustCamshaft() override;

private:
    Camshaft *m_intakeCamshaft;
    Camshaft *m_exhaustCamshaft;
};

#endif /* ATG_ENGINE_SIM_STANDARD_VALVETRAIN_H */

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

#ifndef ATG_ENGINE_SIM_COMBUSTION_CHAMBER_OBJECT_H
#define ATG_ENGINE_SIM_COMBUSTION_CHAMBER_OBJECT_H

#include "simulation_object.h"

#include "combustion_chamber.h"
#include "geometry_generator.h"

class CombustionChamberObject : public SimulationObject {
    public:
        CombustionChamberObject();
        virtual ~CombustionChamberObject();

        virtual void generateGeometry();
        virtual void render(const ViewParameters *view);
        virtual void process(float dt);
        virtual void destroy();

        CombustionChamber *m_chamber;

    protected:
        GeometryGenerator::GeometryIndices m_indices;
};

#endif /* ATG_ENGINE_SIM_COMBUSTION_CHAMBER_OBJECT_H */

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

#ifndef ATG_ENGINE_SIM_FUEL_NODE_H
#define ATG_ENGINE_SIM_FUEL_NODE_H

#include "object_reference_node.h"

#include "engine_context.h"
#include "function_node.h"

#include "engine_sim.h"

#include <map>
#include <vector>

namespace es_script {

    class FuelNode : public ObjectReferenceNode<FuelNode> {
    public:
        FuelNode() { /* void */ }
        virtual ~FuelNode() { /* void */ }

        void generate(Fuel *fuel, EngineContext *context) const {
            Fuel::Parameters params = m_parameters;
            params.turbulenceToFlameSpeedRatio =
                m_turbulenceToFlameSpeedRatio->generate(context);

            fuel->initialize(params);
        }

    protected:
        virtual void registerInputs() {
            addInput(
                "turbulence_to_flame_speed_ratio",
                &m_turbulenceToFlameSpeedRatio,
                InputTarget::Type::Object);
            addInput("name", &m_parameters.name);
            addInput("molecular_mass", &m_parameters.molecularMass);
            addInput("energy_density", &m_parameters.energyDensity);
            addInput("density", &m_parameters.density);
            addInput("molecular_afr", &m_parameters.molecularAfr);
            addInput("max_burning_efficiency", &m_parameters.maxBurningEfficiency);
            addInput("burning_efficiency_randomness", &m_parameters.burningEfficiencyRandomness);
            addInput("low_efficiency_attenuation", &m_parameters.lowEfficiencyAttenuation);
            addInput("max_turbulence_effect", &m_parameters.maxTurbulenceEffect);
            addInput("max_dilution_effect", &m_parameters.maxDilutionEffect);

            ObjectReferenceNode<FuelNode>::registerInputs();
        }

        virtual void _evaluate() {
            setOutput(this);

            // Read inputs
            readAllInputs();
        }

        FunctionNode *m_turbulenceToFlameSpeedRatio = nullptr;
        Fuel::Parameters m_parameters;
    };

} /* namespace es_script */

#endif /* ATG_ENGINE_SIM_FUEL_NODE_H */

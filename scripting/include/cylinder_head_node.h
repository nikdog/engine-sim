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

#ifndef ATG_ENGINE_SIM_CYLINDER_HEAD_NODE_H
#define ATG_ENGINE_SIM_CYLINDER_HEAD_NODE_H

#include "object_reference_node.h"

#include "valvetrain_node.h"
#include "function_node.h"
#include "exhaust_system_node.h"
#include "intake_node.h"

#include "engine_sim.h"

#include <map>
#include <vector>

namespace es_script {

    class CylinderHeadNode : public ObjectReferenceNode<CylinderHeadNode> {
    public:
        CylinderHeadNode() { /* void */ }
        virtual ~CylinderHeadNode() { /* void */ }

        void generate(
            CylinderHead *head,
            CylinderBank *bank,
            Crankshaft *crankshaft,
            EngineContext *context) const
        {
            CylinderHead::Parameters params = m_parameters;
            params.Bank = bank;
            params.Valvetrain = m_valvetrain->generate(context, crankshaft);
            params.IntakePortFlow = m_intakePortFlow->generate(context);
            params.ExhaustPortFlow = m_exhaustPortFlow->generate(context);

            head->initialize(params);
        }

        void setBank(CylinderBankNode *bank) { m_bank = bank; }
        CylinderBankNode *getBank() const { return m_bank; }

    protected:
        virtual void registerInputs() {
            addInput(
                "intake_port_flow",
                &m_intakePortFlow,
                InputTarget::Type::Object);
            addInput(
                "exhaust_port_flow",
                &m_exhaustPortFlow,
                InputTarget::Type::Object);
            addInput(
                "valvetrain",
                &m_valvetrain,
                InputTarget::Type::Object);
            addInput("chamber_volume", &m_parameters.CombustionChamberVolume);
            addInput("flip_display", &m_parameters.FlipDisplay);
            addInput("intake_runner_volume", &m_parameters.IntakeRunnerVolume);
            addInput("intake_runner_cross_section_area", &m_parameters.IntakeRunnerCrossSectionArea);
            addInput("exhaust_runner_volume", &m_parameters.ExhaustRunnerVolume);
            addInput("exhaust_runner_cross_section_area", &m_parameters.ExhaustRunnerCrossSectionArea);

            ObjectReferenceNode<CylinderHeadNode>::registerInputs();
        }

        virtual void _evaluate() {
            setOutput(this);

            // Read inputs
            readAllInputs();

            m_parameters.Bank = nullptr;
            m_parameters.Valvetrain = nullptr;
            m_parameters.IntakePortFlow = nullptr;
            m_parameters.ExhaustPortFlow = nullptr;
        }

        CylinderHead::Parameters m_parameters;

        CylinderBankNode *m_bank = nullptr;
        FunctionNode *m_intakePortFlow = nullptr;
        FunctionNode *m_exhaustPortFlow = nullptr;
        ValvetrainNode *m_valvetrain = nullptr;
    };

} /* namespace es_script */

#endif /* ATG_ENGINE_SIM_CYLINDER_HEAD_NODE_H */

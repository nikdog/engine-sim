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

#ifndef ATG_ENGINE_SIM_CONNECTING_ROD_NODE_H
#define ATG_ENGINE_SIM_CONNECTING_ROD_NODE_H

#include "object_reference_node.h"

#include "rod_journal_node.h"

#include "engine_sim.h"

#include <map>
#include <vector>

namespace es_script {

    class ConnectingRodNode : public ObjectReferenceNode<ConnectingRodNode> {
    public:
        ConnectingRodNode() { /* void */ }
        virtual ~ConnectingRodNode() { /* void */ }

        void addRodJournal(RodJournalNode *rodJournal) {
            m_rodJournals.push_back(rodJournal);
            rodJournal->m_rod = this;
        }

        bool isMaster() const {
            return !m_rodJournals.empty();
        }

        void indexSlaveJournals(EngineContext *context) const {
            int index = 0;
            for (RodJournalNode *journal : m_rodJournals) {
                context->addRodJournal(journal, index++);
            }
        }

        void generate(
            ConnectingRod *connectingRod,
            Crankshaft *crankshaft,
            Piston *piston,
            int rodJournal) const
        {
            ConnectingRod::Parameters params = m_parameters;
            params.crankshaft = crankshaft;
            params.journal = rodJournal;
            params.piston = piston;
            params.rodJournals = static_cast<int>(m_rodJournals.size());
            params.master = nullptr;

            connectingRod->initialize(params);

            for (int i = 0; i < params.rodJournals; ++i) {
                connectingRod->setRodJournalAngle(i, m_rodJournals[i]->getAngle() + constants::pi / 2);
            }
        }

    protected:
        virtual void registerInputs() {
            addInput("mass", &m_parameters.mass);
            addInput("moment_of_inertia", &m_parameters.momentOfInertia);
            addInput("center_of_mass", &m_parameters.centerOfMass);
            addInput("length", &m_parameters.length);
            addInput("slave_throw", &m_parameters.slaveThrow);

            ObjectReferenceNode<ConnectingRodNode>::registerInputs();
        }

        virtual void _evaluate() {
            setOutput(this);

            // Read inputs
            readAllInputs();

            m_parameters.crankshaft = nullptr;
            m_parameters.piston = nullptr;
        }

        ConnectingRod::Parameters m_parameters;
        std::vector<RodJournalNode *> m_rodJournals;
    };

} /* namespace es_script */

#endif /* ATG_ENGINE_SIM_CONNECTING_ROD_NODE_H */

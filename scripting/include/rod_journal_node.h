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

#ifndef ATG_ENGINE_SIM_ROD_JOURNAL_NODE_H
#define ATG_ENGINE_SIM_ROD_JOURNAL_NODE_H

#include "object_reference_node.h"

#include "engine_sim.h"

#include <map>

namespace es_script {

    class CrankshaftNode;
    class ConnectingRodNode;
    class RodJournalNode : public ObjectReferenceNode<RodJournalNode> {
        friend CrankshaftNode;
        friend ConnectingRodNode;

    public:
        RodJournalNode() { /* void */ }
        virtual ~RodJournalNode() { /* void */ }

        double getAngle() const {
            return m_angle;
        }

        CrankshaftNode *getCrankshaft() const {
            return m_crankshaft;
        }

        ConnectingRodNode *getRod() const {
            return m_rod;
        }

    protected:
        virtual void registerInputs() {
            addInput("angle", &m_angle);

            ObjectReferenceNode<RodJournalNode>::registerInputs();
        }

        virtual void _evaluate() {
            setOutput(this);

            // Read inputs
            readAllInputs();
        }

        CrankshaftNode *m_crankshaft = nullptr;
        ConnectingRodNode *m_rod = nullptr;
        double m_angle = 0.0;
    };

} /* namespace es_script */

#endif /* ATG_ENGINE_SIM_ROD_JOURNAL_NODE_H */

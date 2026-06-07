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

#ifndef ATG_ENGINE_SIM_IGNITION_WIRE_NODE_H
#define ATG_ENGINE_SIM_IGNITION_WIRE_NODE_H

#include "object_reference_node.h"

#include "engine_context.h"
#include "function_node.h"

#include "engine_sim.h"

#include <set>

namespace es_script {

    class IgnitionWireNode : public ObjectReferenceNode<IgnitionWireNode> {
    public:
        using Connection = std::pair<CylinderBankNode *, int>;

    public:
        IgnitionWireNode() { /* void */ }
        virtual ~IgnitionWireNode() { /* void */ }

        void connect(CylinderBankNode *bank, int i) {
            m_connections.insert({ bank, i });
        }

        std::set<Connection> getConnections() const {
            return m_connections;
        }

    protected:
        virtual void registerInputs() {
            ObjectReferenceNode<IgnitionWireNode>::registerInputs();
        }

        virtual void _evaluate() {
            setOutput(this);
        }

        std::set<Connection> m_connections;
    };

} /* namespace es_script */

#endif /* ATG_ENGINE_SIM_IGNITION_WIRE_NODE_H */

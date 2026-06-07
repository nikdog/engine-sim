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

#ifndef ATG_ENGINE_SIM_THROTTLE_NODES_H
#define ATG_ENGINE_SIM_THROTTLE_NODES_H

#include "object_reference_node.h"

#include "engine_sim.h"

namespace es_script {

    class ThrottleNode : public ObjectReferenceNode<ThrottleNode> {
    public:
        ThrottleNode() { /* void */ }
        virtual ~ThrottleNode() { /* void */ }

        virtual Throttle *generate() const = 0;

    protected:
        virtual void _evaluate() {
            setOutput(this);
            readAllInputs();
        }
    };

    class DirectThrottleLinkageNode : public ThrottleNode {
    public:
        DirectThrottleLinkageNode() { /* void */ }
        virtual ~DirectThrottleLinkageNode() { /* void */ }

        virtual Throttle *generate() const override {
            DirectThrottleLinkage *throttle = new DirectThrottleLinkage;
            throttle->initialize(m_parameters);

            return static_cast<Throttle *>(throttle);
        }

    protected:
        virtual void registerInputs() override {
            addInput("gamma", &m_parameters.gamma);

            ThrottleNode::registerInputs();
        }

        DirectThrottleLinkage::Parameters m_parameters;
    };

    class GovernorNode : public ThrottleNode {
    public:
        GovernorNode() { /* void */ }
        virtual ~GovernorNode() { /* void */ }

        virtual Throttle *generate() const override {
            Governor *throttle = new Governor;
            throttle->initialize(m_parameters);

            return static_cast<Throttle *>(throttle);
        }

    protected:
        virtual void registerInputs() override {
            addInput("min_speed", &m_parameters.minSpeed);
            addInput("max_speed", &m_parameters.maxSpeed);
            addInput("min_v", &m_parameters.minVelocity);
            addInput("max_v", &m_parameters.maxVelocity);
            addInput("k_s", &m_parameters.k_s);
            addInput("k_d", &m_parameters.k_d);
            addInput("gamma", &m_parameters.gamma);

            ThrottleNode::registerInputs();
        }

        Governor::Parameters m_parameters;
    };

} /* namespace es_script */

#endif /* ATG_ENGINE_SIM_THROTTLE_NODES_H */

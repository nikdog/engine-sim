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

#ifndef ATG_ENGINE_SIM_IMPULSE_RESPONSE_NODE_H
#define ATG_ENGINE_SIM_IMPULSE_RESPONSE_NODE_H

#include "object_reference_node.h"

#include "engine_context.h"
#include "impulse_response_node.h"

#include "engine_sim.h"

#include <map>
#include <vector>

namespace es_script {

    class ImpulseResponseNode
        : public ObjectReferenceNode<ImpulseResponseNode> {
    public:
        ImpulseResponseNode() { /* void */ }
        virtual ~ImpulseResponseNode() { /* void */ }

        ImpulseResponse *generate(EngineContext *context) {
            ImpulseResponse *existingIr = context->getImpulseResponse(this);
            if (existingIr != nullptr) {
                return existingIr;
            }
            else {
                piranha::Path path = m_filename;
                piranha::Path parentPath;
                m_irStructure->getParentUnit()->getPath().getParentPath(&parentPath);
                if (!path.isAbsolute()) {
                    path = parentPath.append(path);
                }

                ImpulseResponse *impulseResponse = new ImpulseResponse;
                impulseResponse->initialize(
                    path.toString(),
                    m_volume);

                return impulseResponse;
            }
        }

    protected:
        virtual void registerInputs() {
            addInput("filename", &m_filename);
            addInput("volume", &m_volume);

            ObjectReferenceNode<ImpulseResponseNode>::registerInputs();
        }

        virtual void _evaluate() {
            setOutput(this);

            // Read inputs
            readAllInputs();
        }

        std::string m_filename = "";
        double m_volume = 1.0;
    };

} /* namespace es_script */

#endif /* ATG_ENGINE_SIM_IMPULSE_RESPONSE_NODE_H */

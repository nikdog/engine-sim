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

#ifndef ATG_ENGINE_SIM_VALVETRAIN_NODE_H
#define ATG_ENGINE_SIM_VALVETRAIN_NODE_H

#include "object_reference_node.h"

#include "engine_context.h"

namespace es_script {

    class ValvetrainNode : public ObjectReferenceNode<ValvetrainNode> {
    public:
        ValvetrainNode() { /* void */ }
        virtual ~ValvetrainNode() { /* void */ }

        virtual Valvetrain *generate(EngineContext *context, Crankshaft *crank) = 0;

    protected:
        virtual void registerInputs() {
            ObjectReferenceNode<ValvetrainNode>::registerInputs();
        }

        virtual void _evaluate() {
            setOutput(this);
            readAllInputs();
        }
    };

} /* namespace es_script */

#endif /* ATG_ENGINE_SIM_VALVETRAIN_NODE_H */

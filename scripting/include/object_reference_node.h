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

#ifndef ATG_ENGINE_SIM_OBJECT_REFERENCE_H
#define ATG_ENGINE_SIM_OBJECT_REFERENCE_H

#include "node.h"

#include "object_reference_node_output.h"

namespace es_script {

    template <typename Type>
    class ObjectReferenceNode : public Node {
    public:
        ObjectReferenceNode() {
            /* void */
        }

        ~ObjectReferenceNode() {
            /* void */
        }

        template <typename T>
        void overrideType() {
            m_output.overrideType(LookupChannelType<T>());
        }

    protected:
        virtual void registerOutputs() {
            setPrimaryOutput("__out");
            registerOutput(&m_output, "__out");
        }

        virtual void _evaluate() {
            m_output.setReference(nullptr);
        }

        void setOutput(Type *output) { m_output.setReference(output); }

        ObjectReferenceNodeOutput<Type> m_output;
    };

    template <typename T_ReferenceType>
    using NullReferenceNode = ObjectReferenceNode<T_ReferenceType>;

} /* namespace manta */

#endif /* ATG_ENGINE_SIM_OBJECT_REFERENCE_H */

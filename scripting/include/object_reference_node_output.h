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

#ifndef ATG_ENGINE_SIM_OBJECT_REFERENCE_NODE_OUTPUT_H
#define ATG_ENGINE_SIM_OBJECT_REFERENCE_NODE_OUTPUT_H

#include "piranha.h"

#include "channel_types.h"

namespace es_script {

    template <typename Type>
    class ObjectReferenceNodeOutput : public piranha::NodeOutput {
    public:
        ObjectReferenceNodeOutput() : NodeOutput(LookupChannelType<Type>()) {
            m_data = nullptr;
        }

        virtual ~ObjectReferenceNodeOutput() {
            /* void */
        }

        virtual void fullCompute(void *target) const {
            *reinterpret_cast<Type **>(target) = m_data;
        }

        Type *getReference() const { return m_data; }
        void setReference(Type *data) { m_data = data; }

    protected:
        Type *m_data;
    };

    template <typename Type>
    Type *getObject(piranha::pNodeInput input) {
        return static_cast<ObjectReferenceNodeOutput<Type> *>(input)->getReference();
    }

} /* namespace manta */

#endif /* ATG_ENGINE_SIM_OBJECT_REFERENCE_NODE_OUTPUT_H */

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

#ifndef ATG_ENGINE_SIM_AUDIO_BUFFER_H
#define ATG_ENGINE_SIM_AUDIO_BUFFER_H

#include "scs.h"

#include <stdint.h>

class AudioBuffer {
    public:
        AudioBuffer();
        ~AudioBuffer();

        void initialize(int sampleRate, int bufferSize);
        void destroy();

        inline double offsetToTime(int offset) const {
            return offset * m_offsetToSeconds;
        }

        inline double timeDelta(int offset0, int offset1) const {
            if (offset1 == offset0) return 0;
            else if (offset1 < offset0) {
                return offsetToTime((m_bufferSize - offset0) + offset1);
            }
            else {
                return offsetToTime(offset1 - offset0);
            }
        }

        inline int offsetDelta(int offset0, int offset1) const {
            if (offset1 == offset0) return 0;
            else if (offset1 < offset0) {
                return (m_bufferSize - offset0) + offset1;
            }
            else {
                return offset1 - offset0;
            }
        }

        inline void writeSample(int16_t sample, int offset, int index = 0) {
            m_samples[getBufferIndex(offset, index)] = sample;
        }

        inline int16_t readSample(int offset, int index) const {
            return m_samples[getBufferIndex(offset, index)];
        }

        inline void commitBlock(int length) {
            m_writePointer = getBufferIndex(m_writePointer, length);
        }

        inline int getBufferIndex(int offset, int index = 0) const {
            return (((offset + index) % m_bufferSize) + m_bufferSize) % m_bufferSize;
        }

        inline void copyBuffer(int16_t *dest, int offset, int length) {
            const int start = getBufferIndex(offset, 0);
            const int end = getBufferIndex(offset, length);

            if (start == end) return;
            else if (start < end) {
                memcpy(dest, m_samples + start, length * sizeof(int16_t));
            }
            else {
                memcpy(dest, m_samples + start, ((size_t)m_bufferSize - start) * sizeof(int16_t));
                memcpy(dest + m_bufferSize - start, m_samples, end * sizeof(int16_t));
            }
        }

        bool checkForDiscontinuitiy(int threshold) const;

        int m_writePointer;

    protected:
        int m_sampleRate;
        int16_t *m_samples;
        int m_bufferSize;

        double m_offsetToSeconds;
};

#endif /* ATG_ENGINE_SIM_AUDIO_BUFFER_H */

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

#ifndef ATG_ENGINE_SIM_CRANKSHAFT_H
#define ATG_ENGINE_SIM_CRANKSHAFT_H

#include "part.h"

class Crankshaft : public Part {
    public:
        struct Parameters {
            double mass;
            double flywheelMass;
            double momentOfInertia;
            double crankThrow;
            double pos_x = 0;
            double pos_y = 0;
            double tdc = 0;
            double frictionTorque = 0;
            int rodJournals;
        };

    public:
        Crankshaft();
        virtual ~Crankshaft();

        void initialize(const Parameters &params);
        virtual void destroy();
        inline int getRodJournalCount() const { return m_rodJournalCount; }
        void setRodJournalAngle(int i, double angle);
        void getRodJournalPositionLocal(int i, double *x, double *y);
        void getRodJournalPositionGlobal(int i, double *x, double *y);
        double getRodJournalAngle(int i) { return m_rodJournalAngles[i]; }

        void resetAngle();

        double getAngle() const;
        double getCycleAngle(double offset = 0.0);

        inline double getTdc() const { return m_tdc; }
        inline double getThrow() const { return m_throw; }
        inline double getMass() const { return m_m; }
        inline double getMomentOfInertia() const { return m_I; }
        inline double getFlywheelMass() const { return m_flywheelMass; }
        inline double getPosX() const { return m_p_x; }
        inline double getPosY() const { return m_p_y; }
        inline double getFrictionTorque() const { return m_frictionTorque; }

    protected:
        double *m_rodJournalAngles;
        int m_rodJournalCount;

        double m_tdc;
        double m_throw;
        double m_m;
        double m_I;
        double m_flywheelMass;
        double m_p_x;
        double m_p_y;
        double m_frictionTorque;
};

#endif /* ATG_ENGINE_SIM_CRANKSHAFT_H */

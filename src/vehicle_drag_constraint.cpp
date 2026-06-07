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

#include "../include/vehicle_drag_constraint.h"

#include "../include/constants.h"
#include "../include/units.h"
#include "../include/vehicle.h"

VehicleDragConstraint::VehicleDragConstraint() : Constraint(1, 1) {
    m_ks = 10.0;
    m_kd = 1.0;

    m_vehicle = nullptr;
}

VehicleDragConstraint::~VehicleDragConstraint() {
    /* void */
}

void VehicleDragConstraint::initialize(atg_scs::RigidBody *rotatingMass, Vehicle *vehicle) {
    m_bodies[0] = rotatingMass;
    m_vehicle = vehicle;
}

void VehicleDragConstraint::calculate(Output *output, atg_scs::SystemState *system) {
    output->C[0] = 0;

    output->J[0][0] = 0.0;
    output->J[0][1] = 0.0;
    output->J[0][2] = -1.0;

    output->J[0][3] = 0.0;
    output->J[0][4] = 0.0;
    output->J[0][5] = 1.0;

    output->J_dot[0][0] = 0;
    output->J_dot[0][1] = 0;
    output->J_dot[0][2] = 0;

    output->J_dot[0][3] = 0;
    output->J_dot[0][4] = 0;
    output->J_dot[0][5] = 0;

    output->kd[0] = m_kd;
    output->ks[0] = m_ks;

    output->v_bias[0] = 0;

    constexpr double airDensity =
        units::AirMolecularMass * units::pressure(1.0, units::atm)
        / (constants::R * units::celcius(25.0));
    const double v = m_vehicle->getSpeed();
    const double v_squared = v * v;
    const double c_d = m_vehicle->getDragCoefficient();
    const double A = m_vehicle->getCrossSectionArea();
    const double rollingResistance = m_vehicle->getRollingResistance();

    output->limits[0][0] =
        -m_vehicle->linearForceToVirtualTorque(rollingResistance + 0.5 * airDensity * v_squared * c_d * A);
    output->limits[0][1] = 0;
}

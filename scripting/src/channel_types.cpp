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

#include "../include/channel_types.h"

#define DEFINE_CHANNEL(channel_type) const piranha::ChannelType es_script::ObjectChannel::channel_type(#channel_type);

DEFINE_CHANNEL(EngineChannel);
DEFINE_CHANNEL(CrankshaftChannel);
DEFINE_CHANNEL(RodJournalChannel);
DEFINE_CHANNEL(ConnectingRodChannel);
DEFINE_CHANNEL(CylinderBankChannel);
DEFINE_CHANNEL(PistonChannel);
DEFINE_CHANNEL(FunctionChannel);
DEFINE_CHANNEL(IntakeChannel);
DEFINE_CHANNEL(ExhaustSystemChannel);
DEFINE_CHANNEL(CylinderHeadChannel);
DEFINE_CHANNEL(CamshaftChannel);
DEFINE_CHANNEL(IgnitionModuleChannel);
DEFINE_CHANNEL(IgnitionWireChannel);
DEFINE_CHANNEL(FuelChannel);
DEFINE_CHANNEL(ImpulseResponseChannel);
DEFINE_CHANNEL(ValvetrainChannel);
DEFINE_CHANNEL(VehicleChannel);
DEFINE_CHANNEL(TransmissionChannel);
DEFINE_CHANNEL(ThrottleChannel);

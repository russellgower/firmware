/*
 * Copyright 2012-2013 BrewPi/Elco Jacobs.
 *
 * This file is part of BrewPi.
 *
 * BrewPi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BrewPi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BrewPi.  If not, see <http://www.gnu.org/licenses/>.
 */



#pragma once

#include <vector>
#include "Pid.h"
#include "ActuatorInterfaces.h"
#include "TempSensor.h"
#include "TempSensorFallback.h"
#include "ActuatorMutexDriver.h"
#include "ActuatorPwm.h"
#include "ActuatorTimeLimited.h"
#include "ActuatorMutexGroup.h"
#include "json_writer.h"
#include "ActuatorSetPoint.h"

class Control
{
public:
    Control();

    ~Control();

    void update(); // update everything
    void fastUpdate(); // update things that need fast updating (like PWM)

    void updateSensors();
    void updatePids();
    void updateActuators();
    void fastUpdateActuators();

    void serialize(JSON::Adapter& adapter);

    std::vector<SetPoint*> setpoints;
    std::vector<TempSensorBasic*> sensors;
    std::vector<Pid*>        pids;
    std::vector<Actuator*>   actuators;

    // static setup below, we should support generating this dynamically later
protected:
    TempSensor * fridgeSensor;
    TempSensor * beer1Sensor;
    TempSensor * beer2Sensor;

    TempSensorFallback * heaterInputSensor;
    TempSensorFallback * coolerInputSensor;

    ActuatorTimeLimited * coolerTimeLimited;
    ActuatorMutexDriver * coolerMutex;
    ActuatorPwm * cooler;

    ActuatorMutexDriver * heater1Mutex;
    ActuatorPwm * heater1;

    ActuatorMutexDriver * heater2Mutex;
    ActuatorPwm * heater2;

    ActuatorSetPoint * fridgeSetPointActuator;

    ActuatorMutexGroup * mutex;

    Pid * heater1Pid;
    Pid * heater2Pid;
    Pid * coolerPid;
    Pid * beerToFridgePid;

    SetPointSimple * beer1Set;
    SetPointSimple * beer2Set;
    SetPointSimple * fridgeSet;

    friend class TempControl;
    friend class DeviceManager;
};

extern Control control;

/**
        * ScrewD
        * This file is a part of ScrewD (Arduino Implementation)
        *
        * For project description read (https://bitbucket.org/rijulg/smart-screwdriver/overview)
        *
        * @author Rijul Gupta (rijulg@gmail.com)
        * @since June 2017
        *
        * ScrewD is free software: you can redistribute it and/or modify
        * it under the terms of the GNU General Public License as published by
        * the Free Software Foundation, either version 3 of the License, or
        * (at your option) any later version.
        *
        * ScrewD is distributed in the hope that it will be useful,
        * but WITHOUT ANY WARRANTY; without even the implied warranty of
        * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        * GNU General Public License for more details.
        *
        * For the GNU General Public License associated with ScrewD,  
        * visit <http://www.gnu.org/licenses/>.
*/

void setup()
{
    initLogger();
    initBluetooth();
    initMotorDriver(); 
    initScrewDriver();
    setMotorPorts(2);
    setMotorMode('x',0);
    setMotorMode('y',0);
    wakePort('x');
    wakePort('y');
}


void loop()
{
    getBluetoothCommand();
    MotorStatus();
}

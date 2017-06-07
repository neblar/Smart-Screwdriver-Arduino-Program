/**
        * ScrewDriver
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

#define OneTurn 42
#define OnePitch 7
#define ScrewLength 4

/**
 * Used for screw function
 */
int screwState = 0;

void initScrewDriver(){
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC2);
  TC_Configure(TC0, 2, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_ACPC_TOGGLE | TC_CMR_TCCLKS_TIMER_CLOCK1);
  TC0->TC_CHANNEL[2].TC_IER = TC_IER_CPCS;
  NVIC_EnableIRQ(TC2_IRQn);
}


/**
 * losen
 * rotates the horizontal motor (port x) by one turn counter clockwise
 * pushed the motor up vertically by one minimal distance
 */
void loosen(){
  prepareMotors();
  stepMotor('x',1,OneTurn);
  stepMotor('y',0,OnePitch);
}

/**
 * Prepares the motors to work for driving screws
 * enables both port
 * wakes both port
 * sets both port to full step mode
 * sets 0 delay
 */
void prepareMotors(){
  setMotorPorts(enableBoth);
  wakePort('x');
  wakePort('y');
  setMotorMode('x',fullStep);
  setMotorMode('y',fullStep);
  setDelay('x',0);
  setDelay('y',0);
}

/**
 * screw
 * Screws a screw
 * runs 4 times to tighten and 4 times to loosen (to return to initial state)
 */
void screw(){
  TC_SetRC(TC0,2,(int)(masterClock * yStepDelay * 100 / 1000000));
  TC_Start(TC0,2);
  log("ScrewDriver.screw","Starting the screwdriver.");
  screwState = 0;
}

         /*
         * handler for screw function
         * runs on timer 0 channel 2
         * interrupt = compare RA
         */
         void TC2_Handler(){
            TC_GetStatus(TC0,2);
            log("ScrewDriver.screwHandler","Running screwdriver.");
            if(screwState>=2*ScrewLength){
              screwState=0;
              TC_Stop(TC0,2);
              return;
            }
            if(screwState<ScrewLength){
              tighten();
            }
            else{
              loosen();
            }
            screwState++;
         }

/**
 * stopAllScrewDrivers
 * stops all the processes running in parrallel (through timers)
 */
void stopAllScrewDrivers(){
  TC_Stop(TC0,2);
  screwState=0;
}

/**
 * tighten
 * rotates the horizontal motor (port y) by one turn clockwise
 * pushed the motor down vertically by one minimal distance
 */
void tighten(){
  prepareMotors();
  stepMotor('x',0,OneTurn);
  stepMotor('y',1,OnePitch);  
}


/**
        * MotorDriver
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

#define pin_xStep 2
#define pin_xDir 3
#define pin_xMS1 4
#define pin_xMS2 5
#define pin_xEnable 56
#define pin_xSleep 57

#define pin_yStep 6
#define pin_yDir 7
#define pin_yMS1 8
#define pin_yMS2 9
#define pin_yEnable 54
#define pin_ySleep 55

enum portStates{ enableX=0, enableY=1, enableBoth=2, disableBoth=3};
enum motorModes{ fullStep=0, halfStep=1, quarterStep=2, eigthStep=3};

/*
 * delay used in step loop
 * Optimized for fullStep mode
 */
double baseStepDelay = 2830;
double xStepDelay = 2830;
double yStepDelay = 2830;

unsigned long xSteps = 0;
unsigned long ySteps = 0;

unsigned int masterClock = VARIANT_MCK;

/**
 * getMotorStatus
 * Reads all the pins of the motor driver
 * and returns a compiled result as a string
 * @return String motor driver status
 */
String getMotorStatus(){
  String log2 = "xEnable:"+String(digitalRead(pin_xEnable),DEC);
    log2 += " :: yEnable:"+String(digitalRead(pin_yEnable),DEC);
    log2 += " :: xSleep:"+String(digitalRead(pin_xSleep),DEC);
    log2 += " :: ySleep:"+String(digitalRead(pin_ySleep),DEC);
    
    log2 += " :: xMS1:"+String(digitalRead(pin_xMS1),DEC);
    log2 += " :: xMS2:"+String(digitalRead(pin_xMS2),DEC);
    log2 += " :: yMS1:"+String(digitalRead(pin_yMS1),DEC);
    log2 += " :: yMS2:"+String(digitalRead(pin_yMS2),DEC);
    
    log2 += " :: xStep:"+String(digitalRead(pin_xStep),DEC);
    log2 += " :: xDir:"+String(digitalRead(pin_xDir),DEC);
    
    log2 += " :: yStep:"+String(digitalRead(pin_yStep),DEC);
    log2 += " :: yDir:"+String(digitalRead(pin_yDir),DEC);
    
    log2 += " :: xSteps:"+String(xSteps,DEC);
    log2 += " :: ySteps:"+String(ySteps,DEC);

    return log2;
}

/**
 * initMotorDriver
 * initializes the motor driver
 */
void initMotorDriver(){
  pinMode(pin_xStep,OUTPUT);
  pinMode(pin_xDir,OUTPUT);
  pinMode(pin_xMS1,OUTPUT);
  pinMode(pin_xMS2,OUTPUT);
  pinMode(pin_xEnable,OUTPUT);
  pinMode(pin_xSleep,OUTPUT);
  
  pinMode(pin_yStep,OUTPUT);
  pinMode(pin_yDir,OUTPUT);
  pinMode(pin_yMS1,OUTPUT);
  pinMode(pin_yMS2,OUTPUT);
  pinMode(pin_yEnable,OUTPUT);
  pinMode(pin_ySleep,OUTPUT);

  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC0);
  pmc_enable_periph_clk(ID_TC1);
  TC_Configure(TC0, 0, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_ACPC_TOGGLE | TC_CMR_TCCLKS_TIMER_CLOCK1);
  TC_Configure(TC0, 1, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_ACPC_TOGGLE | TC_CMR_TCCLKS_TIMER_CLOCK1);
  TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;
  TC0->TC_CHANNEL[1].TC_IER = TC_IER_CPCS;
  NVIC_EnableIRQ(TC0_IRQn);
  NVIC_EnableIRQ(TC1_IRQn);
}

/**
 * MotorStatus
 * logs the motor status as long as the 
 * motors are running
 */
void MotorStatus(){
    if(xSteps<1 || ySteps<1) return;    
    log("MotorDriver.status",getMotorStatus());
}

/*
 * setDelay
 * multiplies the base delay with given multiplier
 * @param multiplier
 */
void setDelay(char port, double multiplier){
  if(multiplier<=0) return;
  switch(port){
    case 'X':
    case 'x':
              xStepDelay = baseStepDelay*multiplier;
              break;
    case 'Y':
    case 'y':
              yStepDelay = baseStepDelay*multiplier;
              break;
  }
}

/**
 * setMotorMode
 * @param port char which port to set
 * @param mode int which mode to set {motorModes}
 */
void setMotorMode(char port, int mode){
  switch(port){
    case 'X':
    case 'x':
            switch(mode){
              case fullStep:
                      digitalWrite(pin_xMS1,LOW);
                      digitalWrite(pin_xMS2,LOW);
                      break;
              case halfStep:
                      digitalWrite(pin_xMS1,HIGH);
                      digitalWrite(pin_xMS2,LOW);
                      break;
              case quarterStep:
                      digitalWrite(pin_xMS1,LOW);
                      digitalWrite(pin_xMS2,HIGH);
                      break;
              case eigthStep:
                      digitalWrite(pin_xMS1,HIGH);
                      digitalWrite(pin_xMS2,HIGH);
                      break;
            }
            break;
    case 'Y':
    case 'y':
            switch(mode){
              case fullStep:
                      digitalWrite(pin_yMS1,LOW);
                      digitalWrite(pin_yMS2,LOW);
                      break;
              case halfStep:
                      digitalWrite(pin_yMS1,HIGH);
                      digitalWrite(pin_yMS2,LOW);
                      break;
              case quarterStep:
                      digitalWrite(pin_yMS1,LOW);
                      digitalWrite(pin_yMS2,HIGH);
                      break;
              case eigthStep:
                      digitalWrite(pin_yMS1,HIGH);
                      digitalWrite(pin_yMS2,HIGH);
                      break;
            }
            break;
  }
}

/*
 * setMotorPorts
 * @param ports int ports to enable/disable {portStates}
 */
void setMotorPorts(int portState){
  switch(portState){
    case disableBoth: 
            digitalWrite(pin_xEnable,HIGH);
            digitalWrite(pin_yEnable,HIGH);
            break;
    case enableBoth: 
            digitalWrite(pin_xEnable,LOW);
            digitalWrite(pin_yEnable,LOW);
            break;
    case enableX: 
            digitalWrite(pin_xEnable,LOW);
            digitalWrite(pin_yEnable,HIGH);
            break;
    case enableY: 
            digitalWrite(pin_xEnable,HIGH);
            digitalWrite(pin_yEnable,LOW);
            break;
  }
}

/**
 * sleepPort
 * @param port char port to put to sleep 
 */
void sleepPort(char port){
  switch(port){
    case 'X':
    case 'x':
              digitalWrite(pin_xSleep,LOW);
              break;
    case 'Y':
    case 'y':
              digitalWrite(pin_ySleep,LOW);
              break;
  }

}

/**
 * stepMotor
 * runs the motor through specified steps in given direction
 * steps the global steps variable to be used by the interrupt handlers
 *      sets double the value because to run one step the pin needs to be set High and then Low
 * @param port char which port to run
 * @param direction bool direction to run on port {0 = Counter Clockwise, 1 = Clockwise}
 * @param steps int number of steps to run on port
 */
void stepMotor(char port, bool direction, unsigned long steps){
  if(steps<1)
    return;
  
  switch(port){
    case 'X':
    case 'x':
              digitalWrite(pin_xDir,direction);
              if(xSteps==0){
                TC_SetRC(TC0,0,(int)(masterClock * xStepDelay / 1000000));
                TC_Start(TC0,0);
              }
              xSteps = 2*steps;
              break;
    case 'Y':
    case 'y':
              digitalWrite(pin_yDir,direction);
              if(ySteps==0){
                TC_SetRC(TC0,1,(int)(masterClock * yStepDelay / 1000000));
                TC_Start(TC0,1);
              }
              ySteps = 2*steps;
              break;
  }
  
}


        /*
         * handler for xPort
         * runs on timer 0 channel 0
         * interrupt = compare RA
         */
         void TC0_Handler(){
            TC_GetStatus(TC0,0);
            digitalWrite(pin_xStep, !digitalRead(pin_xStep));
            if(xSteps<=0){
              TC_Stop(TC0,0);
              return;
            }
            xSteps--;
         }
         
        /*
         * handler for yPort
         * runs on timer 0 channel 1
         * interrupt = compare RC
         */
         void TC1_Handler(){
            TC_GetStatus(TC0,1);
            digitalWrite(pin_yStep, !digitalRead(pin_yStep));
            if(ySteps<=0){
              TC_Stop(TC0,1);
              return;
            }
            ySteps--;       
         }


/**
 * stopAllMotors
 * stops both the motor ports
 */
void stopAllMotors(){
      TC_Stop(TC0,1);
      TC_Stop(TC0,0);
      xSteps=0;
      ySteps=0;
}

/**
 * wakePort
 * @param port char port to put to wake
 */
void wakePort(char port){
  switch(port){
    case 'X':
    case 'x':
              digitalWrite(pin_xSleep,HIGH);
              break;
    case 'Y':
    case 'y':
              digitalWrite(pin_ySleep,HIGH);
              break;
  }

}

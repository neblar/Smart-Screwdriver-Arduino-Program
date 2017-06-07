/**
        * Logger
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


/**
 * initLogger
 * Initializes the Serial port for logging
 */
void initLogger(){
  Serial.begin(9600);
}

/**
 * log
 * Logs the data to the Serial port
 * @param caller String name of calling function {Class.functionName}
 * @param data String data which needs to be logged to serial port
 */
void log(String caller, String data){
  Serial.println(caller+": "+data);
}


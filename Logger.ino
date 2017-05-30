
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


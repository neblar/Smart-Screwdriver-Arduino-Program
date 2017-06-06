#define BluetoothSerial Serial3

String bluetoothName = "Screwd";

/**
 * initBluetooth
 * Initializes the bluetooth shield to connect with the Android app
 * Uses Globally defined bluetoothName as name for bluetooth device
 * Uses #defined BluetoothSerial as Serial to interface with Arduino
 */
void initBluetooth(){
  BluetoothSerial.begin(38400);
  BluetoothSerial.print("\r\n+STWMOD=0\r\n");
  BluetoothSerial.print("\r\n+STNA="+bluetoothName+"\r\n");
  BluetoothSerial.print("\r\n+STOAUT=1\r\n");
  BluetoothSerial.print("\r\n+STAUTO=0\r\n");
  BluetoothSerial.print("\r\n+STPIN=1234\r\n");
  delay(2000);
  BluetoothSerial.print("\r\n+INQ=1\r\n");
  delay(2000);
  BluetoothSerial.flush();
}

/**
 * getBluetoothCommand
 * get's the command sent from the app and executes the corresponding function
 */
void getBluetoothCommand(){

  String TAG = "BluetoothController.getBluetoothCommand";
  
  if(BluetoothSerial.available()){
    String command = BluetoothSerial.readString();
    switch(command[0]){
      case 'm': 
                {
                  int i=2,j=0;
                  while(command[i]!=0){
                    String part = "";
                    while(command[i]!=0 && command[i]!=','){
                      part += command[i];
                      i++; 
                    }
                    switch(j){
                      case 0: {
                                setMotorPorts(part.toInt());
                              }break;
                      case 1: {
                                switch(part.toInt()){
                                  case 0: wakePort('x');break;
                                  case 1: sleepPort('x');break;
                                }
                              }break;
                      case 2: {
                                setMotorMode('x',part.toInt());
                              }break;
                      case 3: {
                                setDelay('x',part.toFloat());
                              }break;
                      case 4: {
                                int steps = part.toInt();
                                if(steps<0) stepMotor('x',0,steps*-1);
                                else stepMotor('x',1,steps);
                              }break;
                      case 5: {
                                switch(part.toInt()){
                                  case 0: wakePort('y');break;
                                  case 1: sleepPort('y');break;
                                }
                              }break;
                      case 6: {
                                setMotorMode('y',part.toInt());
                              }break;
                      case 7: {
                                setDelay('y',part.toFloat());
                              }break;
                      case 8: {
                                int steps = part.toInt();
                                if(steps<0) stepMotor('y',0,steps*-1);
                                else stepMotor('y',1,steps);
                              }break;
                    }
                    j++;
                    i++;
                  }
                }
                log(TAG,"Manual Control"); 
                break;
      case 'S': 
                {
                  log(TAG,"Starting");
                  screw();
                }
                break;
      case 'Q':
                {
                  stopAllMotors();
                  stopAllScrewDrivers();
                  log(TAG,"Ending");
                }
                break;
      case 'F':
                {
                  tighten();
                  sendBluetoothData("Feedback");
                }
                break;
      case 'T':
                {
                  tighten();
                }
                break;
      case 'L':
                {
                  loosen();
                  
                }
                break;
    }
    
    log(TAG,"Got command: "+command);
  }  
}

/**
 * sendBluetoothData
 * @param data String data that needs to be sent to Android App
 */
void sendBluetoothData(String data){
 
    BluetoothSerial.print(data);
  
}


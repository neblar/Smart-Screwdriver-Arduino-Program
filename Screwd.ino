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

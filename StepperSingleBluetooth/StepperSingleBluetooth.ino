#include <SoftwareSerial.h>
#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  3     // IN1 on the ULN2003 driver 1
#define motorPin2  4     // IN2 on the ULN2003 driver 1
#define motorPin3  5     // IN3 on the ULN2003 driver 1
#define motorPin4  6     // IN4 on the ULN2003 driver 1

char incomingValue = ' ';
bool serialPrinted = false;
int incomingByte = 0;


SoftwareSerial EEBlue(10, 11); // RX | TX

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup()
{
 
  Serial.begin(9600);
  EEBlue.begin(9600);  //Default Baud for comm, it may be different for your Module. 
  Serial.println("The bluetooth gates are open.\n Connect to HC-05 from any other bluetooth device with 1234 as pairing key!.");
  
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(700.0);
  stepper1.setSpeed(900);
  //stepper1.moveTo(2000);
}
 
void loop()
{

  stepper1.run();
  
  if (EEBlue.available() > 0){ 
    incomingValue = EEBlue.read();

    if (incomingValue == 'R'){
      //stepper1.move(2000);
      stepper1.move(50);
      Serial.println("Right");
      
    }else if(incomingValue == 'L'){
      //stepper1.move(-2000);
      stepper1.move(-50);
      Serial.println("Left");
      
    }else if (incomingValue == 'O'){
      stepper1.stop();
    }
    Serial.write(incomingValue);
    Serial.println(" ");
  }
   

}


  
#define LEFT_FOR 9 // PWMB
#define LEFT_BACK 5  // DIRB  ---  left
#define RIGHT_FOR 6  // PWMA
#define RIGHT_BACK 10  // DIRA  ---  right
int xAxis,yAxis;

int speedLeft = 0; 
int speedRight = 0; 
//-----------------------------------------------

void setup() {
  pinMode(LEFT_FOR, OUTPUT);
  pinMode(LEFT_BACK, OUTPUT);
  pinMode(RIGHT_FOR, OUTPUT);
  pinMode(RIGHT_BACK, OUTPUT);
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
    Serial1.begin(9600); // Setting the baud rate of Software Serial Library  
    delay(500);  
    stopMoving();  
}

//---------------------------------------------------------

void loop() {
  
    if(Serial1.available() > 0)
      {     
      xAxis = Serial1.parseInt(); //  read xAxis in range (-500, 500)
      if (xAxis >= 255)  xAxis = 255 ;  
      if (xAxis <= -255)  xAxis = -255 ;   
      if ((xAxis >= -50) && (xAxis <= 50))  xAxis = 0 ;  
      delay(10);
      yAxis = Serial1.parseInt(); //  read yAxis in range (-500, 500)
      if (yAxis >= 255)  yAxis = 255 ;  
      if (yAxis <= -255)  yAxis = -255 ;   
      if ((yAxis >= -50) && (yAxis <= 50))  yAxis = 0 ;  
        
     // Serial.print("xAxis:"); 
     //Serial.print(xAxis); 
     //Serial.print("   yAxis:"); 
     //Serial.println(yAxis);

     if (xAxis <= 0 && yAxis >= 0 ){
      speedRight = abs(xAxis); // speed for leading motor in range (0-255)
      speedLeft = (255.0-abs(yAxis))*abs(xAxis)/255.0;  // !!! speed for turning motor in range (0-255)
      moveForward(); 
      } 

     if (xAxis <= 0 && yAxis < 0 ){
      speedLeft = abs(xAxis); // speed for leading motor in range (0-255)
      speedRight = (255.0-abs(yAxis))*abs(xAxis)/255.0;  // !!! speed for turning motor in range (0-255)
      moveForward();  
      }
      
     if (xAxis > 0 && yAxis >= 0 ){
      speedRight = abs(xAxis); // speed for leading motor in range (0-255)
      speedLeft = (255.0-abs(yAxis))*abs(xAxis)/255.0;  // !!! speed for turning motor in range (0-255)
      moveBackward(); 
      }

     if (xAxis > 0 && yAxis < 0 ){
      speedLeft = abs(xAxis); // speed for leading motor in range (0-255)
      speedRight = (255.0-abs(yAxis))*abs(xAxis)/255.0;  // !!! speed for turning motor in range (0-255)
      moveBackward();  
      }
    
     Serial.print("motorSpeed1");
     Serial.print(speedLeft);
     Serial.print(" , motorSpeed2:");
     Serial.println(speedRight); 
      }
}

//------------------------------------------------------------

void moveForward() // Move forward
{
     analogWrite(LEFT_FOR, abs(speedRight));
     analogWrite(LEFT_BACK, LOW);
     analogWrite(RIGHT_FOR, abs(speedLeft));
     analogWrite(RIGHT_BACK, LOW);
     }

void moveBackward() // Move backward
{      
     analogWrite(LEFT_FOR, LOW);
     analogWrite(LEFT_BACK, abs(speedRight));
     analogWrite(RIGHT_FOR, LOW);
     analogWrite(RIGHT_BACK, abs(speedLeft));
     }

void stopMoving() // Stop movement
{
     analogWrite(LEFT_FOR, HIGH);
     analogWrite(LEFT_BACK, HIGH);
     analogWrite(RIGHT_FOR, HIGH);
     analogWrite(RIGHT_BACK,HIGH);
     }

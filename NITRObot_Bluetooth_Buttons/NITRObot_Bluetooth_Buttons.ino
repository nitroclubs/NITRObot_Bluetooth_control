#define LEFT_FOR 9 // PWMB
#define LEFT_BACK 5  // DIRB  ---  left
#define RIGHT_FOR 6  // PWMA
#define RIGHT_BACK 10  // DIRA  ---  right
int state;
int Speed ;

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
    // Read the incoming data from the Smartphone Android App
    if(Serial1.available() > 0){     
      state = Serial1.read(); 
      //Serial.println(state);
      if(state > 10){
       Speed = state + 100;}      
      

      if(Speed >= 255){
       Speed = 255;}      
}      
   // if the state is '1' the DC motor will go forward
   if (state == 1)
   { 
   moveForward(); 
   }

   // if the state is '2' the motor will Reverse
   else if (state == 2)
   { 
   moveBackward();
   }
   // if the state is '3' the motor will turn left
   else if (state == 3)
   { 
   turnLeft();
   }
   // if the state is '4' the motor will turn right
   else if (state == 4)
   { 
   turnRight();
   }
    
   // if the state is '5' the motor will Stop
   else if (state == 5)
   { 
   stopMoving();
   } 

Serial.println(Speed); 
}

//------------------------------------------------------------

void moveForward() // Move forward
{
  analogWrite(LEFT_FOR,  Speed);
  analogWrite(LEFT_BACK, LOW);
  analogWrite(RIGHT_FOR,  Speed);
  analogWrite(RIGHT_BACK, LOW);
}

void moveBackward() // Move backward
{
  analogWrite(LEFT_FOR, LOW);
  analogWrite(LEFT_BACK, Speed);
  analogWrite(RIGHT_FOR, LOW);
  analogWrite(RIGHT_BACK,  Speed);
}

void turnLeft() // Turn Left
{
  analogWrite(LEFT_FOR, LOW);
  analogWrite(LEFT_BACK,  Speed);
  analogWrite(RIGHT_FOR,  Speed);
  analogWrite(RIGHT_BACK, LOW);
}

void turnRight() // Turn Right
{
  analogWrite(LEFT_FOR,  Speed);
  analogWrite(LEFT_BACK, LOW);
  analogWrite(RIGHT_FOR, LOW);
  analogWrite(RIGHT_BACK,  Speed);
}

void stopMoving() // Stop movement
{
  analogWrite(LEFT_FOR, HIGH);
  analogWrite(LEFT_BACK, HIGH);
  analogWrite(RIGHT_FOR, HIGH);
  analogWrite(RIGHT_BACK, HIGH);
}

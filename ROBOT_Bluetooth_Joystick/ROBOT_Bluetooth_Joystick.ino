#define LEFT_FOR 9 // PWMB
#define LEFT_BACK 5  // DIRB  ---  left
#define RIGHT_FOR 6  // PWMA
#define RIGHT_BACK 10  // DIRA  ---  right

int xAxis=0, yAxis=0;

int speedLeft =0;
int speedRight = 0;

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

void loop() {  
 
  while (Serial1.available() >= 2) {
    xAxis = (Serial1.read()-140)*3.19;  //  !!! set xAxis in range (0 - 255)
    delay(10);
    yAxis = (Serial1.read()-140)*3.19;  // !!! set yAxis in range (0 - 255)
  // Serial.print("xAxis:");
  // Serial.print(xAxis);
  // Serial.print(" , YAxis:");
  // Serial.println(yAxis);
  }
  delay(10);
  
if (yAxis <= 0 && xAxis >= 0 ){
  speedRight = abs(yAxis); // speed for leading motor in range (0-255)
  speedLeft = (255.0-abs(xAxis))*abs(yAxis)/255.0;  // !!! speed for turning motor in range (0-255)
   moveForward();  
  }
if (yAxis <= 0 && xAxis < 0 ){  
  speedLeft = abs(yAxis); // speed for leading motor in range (0-255)
  speedRight = (255.0-abs(xAxis))*abs(yAxis)/255.0;// !!! speed for turning motor in range (0-255);
   moveForward();
  }
if (yAxis > 0 && xAxis >= 0 ){
 speedRight = abs(yAxis); // speed for leading motor in range (0-255)
  speedLeft = (255.0-abs(xAxis))*abs(yAxis)/255.0;  // !!! speed for turning motor in range (0-255)
  moveBackward();
  }
if (yAxis > 0 && xAxis < 0 ){
  speedLeft = abs(yAxis); // speed for leading motor in range (0-255)
  speedRight = (255.0-abs(xAxis))*abs(yAxis)/255.0;  // !!! speed for turning motor in range (0-255)
  moveBackward();
 }
     Serial.print("motorSpeed1:");
     Serial.print(speedLeft);
     Serial.print(" , motorSpeed2:");
     Serial.println(speedRight); 
}

void moveForward() // Move forward
{
  analogWrite(LEFT_FOR,  speedRight);
  analogWrite(LEFT_BACK, LOW);
  analogWrite(RIGHT_FOR,  speedLeft);
  analogWrite(RIGHT_BACK, LOW);
}

void moveBackward() // Move backward
{
  analogWrite(LEFT_FOR, LOW);
  analogWrite(LEFT_BACK, speedRight);
  analogWrite(RIGHT_FOR, LOW);
  analogWrite(RIGHT_BACK,  speedLeft);
}

void stopMoving() // Stop movement
{
  analogWrite(LEFT_FOR, HIGH);
  analogWrite(LEFT_BACK, HIGH);
  analogWrite(RIGHT_FOR, HIGH);
  analogWrite(RIGHT_BACK, HIGH);
}

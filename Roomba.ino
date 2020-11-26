// wheel variables
int leftWheelDir1 = 2, leftWheelDir2 = 3; // direction pins for left wheel 
int rightWheelDir1 = 4, rightWheelDir2 = 5; // direction pins for right wheel

// sensor variables
int trigPin = 10;
int echoPin = 8;
int distance;

// timer variable
extern volatile unsigned long timer0_millis;
 
void setup() {
  // wheel pins
  pinMode(leftWheelDir1, OUTPUT);
  pinMode(leftWheelDir2, OUTPUT);
  pinMode(rightWheelDir1, OUTPUT);
  pinMode(rightWheelDir2, OUTPUT);

  // sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
}

void loop() {
  // get a distance value
  getDistance();

  // move forward if the path is clear
  // turn if object is in the way
  if(distance > 1000) moveForward();
  else turn();
  
  // force turn every 15 seconds of moving forward
  if((millis()/1000)%16 == 15) turn();
}

// gets distance value
void getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(20);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  distance = pulseIn(echoPin, HIGH);
}

// drives roomba forward
void moveForward() {
  // left wheel
  digitalWrite(leftWheelDir1, HIGH);
  digitalWrite(leftWheelDir2, LOW);
  
  // right wheel
  digitalWrite(rightWheelDir1, LOW);
  digitalWrite(rightWheelDir2, HIGH);
}

// turns roomba in a random direction
// at a random angle
void turn() {
  // turn random direction
  if (random(0, 2) == 0) turnRight();
  else turnLeft();

  // duration of turn
  delay(random(300, 550));

  // reset timer
  noInterrupts();
  timer0_millis = 0;
  interrupts();
}

// turns the roomba to the left
void turnLeft() {
  // left wheel
  digitalWrite(leftWheelDir1, LOW);
  digitalWrite(leftWheelDir2, HIGH);
  
  // right wheel
  digitalWrite(rightWheelDir1, LOW);
  digitalWrite(rightWheelDir2, HIGH);
}

// turns the roomba to the right
void turnRight() {
  // left wheel
  digitalWrite(leftWheelDir1, HIGH);
  digitalWrite(leftWheelDir2, LOW);
  
  // right wheel
  digitalWrite(rightWheelDir1, HIGH);
  digitalWrite(rightWheelDir2, LOW);
}

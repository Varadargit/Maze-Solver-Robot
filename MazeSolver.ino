// ==========================================
// Maze Solver Robot
// Arduino Uno + IR Sensors + Ultrasonic
// L298N Motor Driver + 2 DC Motors
// ==========================================


// ------------------------------------------
// IR Sensors
// ------------------------------------------

#define IR_LEFT 2
#define IR_RIGHT 3


// ------------------------------------------
// Ultrasonic Sensor
// ------------------------------------------

#define TRIG_PIN 4
#define ECHO_PIN 5


// ------------------------------------------
// L298N Motor Driver
// ------------------------------------------

#define LEFT_MOTOR_IN1 6
#define LEFT_MOTOR_IN2 7

#define RIGHT_MOTOR_IN1 8
#define RIGHT_MOTOR_IN2 9


// ------------------------------------------
// Configuration
// ------------------------------------------

#define FRONT_CLEAR_DISTANCE 25


// ==========================================
// SETUP
// ==========================================

void setup() {

    Serial.begin(9600);

    pinMode(IR_LEFT, INPUT);
    pinMode(IR_RIGHT, INPUT);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    pinMode(LEFT_MOTOR_IN1, OUTPUT);
    pinMode(LEFT_MOTOR_IN2, OUTPUT);

    pinMode(RIGHT_MOTOR_IN1, OUTPUT);
    pinMode(RIGHT_MOTOR_IN2, OUTPUT);

    stopRobot();

    Serial.println("Maze Solver Started");
}


// ==========================================
// ULTRASONIC SENSOR
// ==========================================

long getDistance() {

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);

    long distance = duration * 0.034 / 2;

    return distance;
}


// ==========================================
// IR SENSOR READING
// ==========================================

int readLeftSensor() {

    return digitalRead(IR_LEFT);
}


int readRightSensor() {

    return digitalRead(IR_RIGHT);
}


// ==========================================
// MOTOR CONTROL
// ==========================================

void moveForward() {

    digitalWrite(LEFT_MOTOR_IN1, HIGH);
    digitalWrite(LEFT_MOTOR_IN2, LOW);

    digitalWrite(RIGHT_MOTOR_IN1, HIGH);
    digitalWrite(RIGHT_MOTOR_IN2, LOW);
}


void stopRobot() {

    digitalWrite(LEFT_MOTOR_IN1, LOW);
    digitalWrite(LEFT_MOTOR_IN2, LOW);

    digitalWrite(RIGHT_MOTOR_IN1, LOW);
    digitalWrite(RIGHT_MOTOR_IN2, LOW);
}


void turnLeft() {

    digitalWrite(LEFT_MOTOR_IN1, LOW);
    digitalWrite(LEFT_MOTOR_IN2, HIGH);

    digitalWrite(RIGHT_MOTOR_IN1, HIGH);
    digitalWrite(RIGHT_MOTOR_IN2, LOW);

    delay(400);

    stopRobot();
}


void turnRight() {

    digitalWrite(LEFT_MOTOR_IN1, HIGH);
    digitalWrite(LEFT_MOTOR_IN2, LOW);

    digitalWrite(RIGHT_MOTOR_IN1, LOW);
    digitalWrite(RIGHT_MOTOR_IN2, HIGH);

    delay(400);

    stopRobot();
}


// ==========================================
// SENSOR DEBUGGING
// ==========================================

void printSensors(
    int left,
    int right,
    long distance
) {

    Serial.print("Left: ");
    Serial.print(left);

    Serial.print(" | Right: ");
    Serial.print(right);

    Serial.print(" | Front: ");
    Serial.print(distance);

    Serial.println(" cm");
}


// ==========================================
// NAVIGATION LOGIC
// ==========================================

String decideMovement(
    int leftSensor,
    int rightSensor,
    long frontDistance
) {

    bool frontClear =
        frontDistance > FRONT_CLEAR_DISTANCE;


    if (frontClear) {

        return "FORWARD";
    }


    if (!frontClear && leftSensor == LOW) {

        return "LEFT";
    }


    if (!frontClear && rightSensor == LOW) {

        return "RIGHT";
    }


    return "STOP";
}


// ==========================================
// MOVEMENT EXECUTION
// ==========================================

void executeMovement(String command) {

    if (command == "FORWARD") {

        moveForward();
    }

    else if (command == "LEFT") {

        turnLeft();
    }

    else if (command == "RIGHT") {

        turnRight();
    }

    else {

        stopRobot();
    }
}


// ==========================================
// MAIN LOOP
// ==========================================

void loop() {

    // Read sensors
    int leftSensor = readLeftSensor();

    int rightSensor = readRightSensor();

    long frontDistance = getDistance();


    // Print sensor values
    printSensors(
        leftSensor,
        rightSensor,
        frontDistance
    );


    // Decide movement
    String command = decideMovement(
        leftSensor,
        rightSensor,
        frontDistance
    );


    // Execute movement
    executeMovement(command);


    delay(50);
}
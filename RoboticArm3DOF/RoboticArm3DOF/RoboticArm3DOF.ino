/*
 * Purpose
 *  Positioning the end effector at a specific location in space through the simultaneous movement of three servomotors
 * Hardware
 *  The servos are connected in series, to a 3.3V power source and GND
 *  The signals for the servos are at digital pins: base-7, large link-5, small link-6
 *  The anode of the LED is connected to digital pin 12 through a resistor and the cathode to GND
 * Software
 *  The Servo.h library is used
 *  To find the angle, e.g., f, the law of cosines is used (f=(A*A+B*B-C*C)/2*A*B)
 *  A, B are the adjacent sides of the angle and C is the opposite side
 * Limitations
 *  The movement occurs along the axes: xx', y, z
 *  This system has a minimum possible distance from (0,0,0) of 4cm and a maximum of 13cm 
 *  The LED lights up when the coordinates are outside the workspace
*/

#include <Servo.h>
Servo baseServo, bigServo, smallServo;  //servo motors names
float length1 = 8.5;                    //length of link 1
float length2 = 4.5;                    //length of link 2
double pi = 3.1415926535897;
float x = 0;  //Initialization of coordinates
float y = 0;
float z = 0;
//-------------
float getbigServo(float x, float z, float length1, float lenght2, float dist) {
  //Finding the angle of link 1
  float a1 = atan2(z, x);
  a1 = a1 * 180 / pi;
  Serial.print("a1= ");
  Serial.println(a1);
  //---
  float a2 = acos(((length1 * length1) + (dist * dist) - (lenght2 * lenght2)) / (2 * length1 * dist));
  a2 = a2 * 180 / pi;
  Serial.print("a2= ");
  Serial.println(a2);
  Serial.print("megalo= ");
  Serial.println(a1 + a2);
  return a1 + a2;
}
//----------
float getsmallServo(float length1, float length2, float dist) {
  //Finding the angle of link 2
  float a3 = acos(((length1 * length1) + (length2 * length2) - (dist * dist)) / (2 * length1 * length2));
  a3 = a3 * 180 / pi;
  Serial.print("a3= ");
  Serial.println(180 - a3);
  return 180 - a3;
}
//-------------
void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  baseServo.attach(7);  //arduino's digital pins
  bigServo.attach(5);
  smallServo.attach(6);
  baseServo.write(0);  //Initialization in degrees
  bigServo.write(0);
  smallServo.write(180);
}
//---
void loop() {
  Serial.println("Enter x");
  while (Serial.available() == 0)
    ;
  {
    x = Serial.parseFloat();
    Serial.println(x);
  }
  Serial.println("Enter y");
  while (Serial.available() == 0)
    ;
  {
    y = Serial.parseFloat();
    Serial.println(y);
  }
  Serial.println("Enter  z");
  while (Serial.available() == 0)
    ;
  {
    z = Serial.parseFloat();
    Serial.println(z);
  }
  //________________________________________________________________________________________
  float distance = sqrt(x * x + y * y + z * z);  //Distance of the point from (0,0,0)
  Serial.print("distance= ");
  Serial.println(distance);
  float maxDist = length1 + length2;  //Maximum distance
  Serial.print("max dist= ");
  Serial.println(maxDist);
  float minDist = length1 - length2;  //Minimum distance
  Serial.print("min dist= ");
  Serial.println(minDist);
  digitalWrite(12, LOW);  //LED voltage=0
  //________________________________________________________________________________________
  if (distance > maxDist || distance < minDist || y < 0 || z < 0) {
    //Error condition
    Serial.println("Off limits");
    digitalWrite(12, HIGH);
  }
  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  else if (x > 0) {
    if (z == 0) {
      if (y == 0) {
        if (distance == maxDist) {  //Ox max
          baseServo.write(0);
          bigServo.write(0);
          smallServo.write(0);
        } else if (distance == minDist) {  //Ox min
          baseServo.write(0);
          bigServo.write(0);
          smallServo.write(180);
        } else {  //Ox Intermediate value
          baseServo.write(0);
          bigServo.write(getbigServo(x, z, length1, length2, distance));  //Ox Axis, any other x
          smallServo.write(getsmallServo(length1, length2, distance));
        }
      } else if (y > 0) {  //Oxz
        float base = atan2(y, x);
        base = base * 180 / pi;
        baseServo.write(base);
        bigServo.write(getbigServo(x, z, length1, length2, distance));
        smallServo.write(getsmallServo(length1, length2, distance));
      }
    } else if (z > 0) {
      if (y == 0) {
        baseServo.write(0);  //Oxz
        bigServo.write(getbigServo(x, z, length1, length2, distance));
        smallServo.write(getsmallServo(length1, length2, distance));
      } else if (z > 0) {  //Oxzy
        float base = atan2(y, x);
        base = base * 180 / pi;
        baseServo.write(base);
        bigServo.write(getbigServo(x, z, length1, length2, distance));
        smallServo.write(getsmallServo(length1, length2, distance));
      }
    }
  }
  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  else if (x == 0) {
    if (z == 0) {
      if (y > 0) {
        if (distance == maxDist) {  //Oy max
          baseServo.write(90);
          bigServo.write(0);
          smallServo.write(0);
        } else if (distance == minDist) {  //Oy min
          baseServo.write(90);
          bigServo.write(0);
          smallServo.write(180);
        } else {
          baseServo.write(90);  //Oy Intermediate value
          x = y;
          bigServo.write(getbigServo(x, z, length1, length2, distance));
          smallServo.write(getsmallServo(length1, length2, distance));
        }
      }
    } else if (z > 0) {
      if (y == 0) {
        if (distance == maxDist) {  //Oz max
          baseServo.write(0);
          bigServo.write(90);
          smallServo.write(0);
        } else if (distance == minDist) {  //Oz min
          baseServo.write(0);
          bigServo.write(90);
          smallServo.write(180);
        } else {  //Oz Intermediate value
          baseServo.write(0);
          float k;
          k = x;
          x = z;
          z = k;
          bigServo.write(90 + getbigServo(x, z, length1, length2, distance));
          smallServo.write(getsmallServo(length1, length2, distance));
        }
      } else if (y > 0) {  //Oyz
        baseServo.write(90);
        x = y;
        bigServo.write(getbigServo(x, z, length1, length2, distance));
        smallServo.write(getsmallServo(length1, length2, distance));
      }
    }
  }
  //---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  else if (x < 0) {
    if (z == 0) {
      if (y == 0) {
        if (distance == maxDist) {  //Ox' max
          baseServo.write(0);
          bigServo.write(180);
          smallServo.write(0);
        } else if (distance == minDist) {  //Ox' min
          baseServo.write(0);
          bigServo.write(180);
          smallServo.write(180);
        } else {  //Ox' Intermediate value
          x = abs(x);
          baseServo.write(180);
          bigServo.write(getbigServo(x, z, length1, length2, distance));
          smallServo.write(getsmallServo(length1, length2, distance));
        }
      } else if (y > 0) {  //Ox'y
        x = abs(x);
        float base = atan2(y, x);
        base = base * 180 / pi;
        baseServo.write(180 - base);
        bigServo.write(getbigServo(x, z, length1, length2, distance));
        smallServo.write(getsmallServo(length1, length2, distance));
      }
    } else if (z > 0) {  //Ox'y
      if (y == 0) {
        x = abs(x);
        baseServo.write(180);
        bigServo.write(getbigServo(x, z, length1, length2, distance));
        smallServo.write(getsmallServo(length1, length2, distance));
      }
      if (y > 0) {  //Ox'yz
        x = abs(x);
        float base = atan2(y, x);
        base = base * 180 / pi;
        baseServo.write(180 - base);  //-------------------------
        bigServo.write(getbigServo(x, z, length1, length2, distance));
        smallServo.write(getsmallServo(length1, length2, distance));
      }
    }
  }
}

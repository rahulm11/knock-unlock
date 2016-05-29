#include "CurieIMU.h"

int ax, ay, az,
    gx, gy, gz;

long minKnockInterval = 100; // 100 ms
long prevKnockTime = 0;


boolean blinkState = false; // state of LED
    
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);

  CurieIMU.begin();
  CurieIMU.attachInterrupt(accCallBack);
//  CurieIMU.setDetectionThreshold(CURIE_IMU_SHOCK, 1000);  // 10 mg
  CurieIMU.setDetectionThreshold(CURIE_IMU_SHOCK, 1000);  // 10 mg
  CurieIMU.setDetectionDuration(CURIE_IMU_SHOCK, 1000);  // 200 ms
  CurieIMU.interrupts(CURIE_IMU_SHOCK);
//  CurieIMU.setDetectionThreshold(CURIE_IMU_TAP_SHOCK, 100);  // 10 mg
//  CurieIMU.setDetectionDuration(CURIE_IMU_TAP_SHOCK, 50);  // 200 ms
//  CurieIMU.interrupts(CURIE_IMU_TAP_SHOCK);
  
  Serial.println("Started");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, blinkState);
  blinkState = !blinkState;
  delay(200);
  
//  CurieIMU.readMotionSensor(ax, ay, az, gz, gy, gz);
  CurieIMU.readAccelerometer(ax, ay, az);
  

//  if (Serial.available() > 0) {
    Serial.print(ax);
    Serial.print(" ");
    Serial.print(ay);
    Serial.print(" ");
    Serial.print(az);
    Serial.println();
//  }
}

static void accCallBack(void){
  long tn = millis();
   if (CurieIMU.getInterruptStatus(CURIE_IMU_SHOCK)
        && (tn > (prevKnockTime + minKnockInterval))) {

    prevKnockTime = tn;
    if (CurieIMU.shockDetected(X_AXIS, POSITIVE))
      Serial.println("Negative shock detected on X-axis");
    if (CurieIMU.shockDetected(X_AXIS, NEGATIVE))
      Serial.println("Positive shock detected on X-axis");
    if (CurieIMU.shockDetected(Y_AXIS, POSITIVE))
      Serial.println("Negative shock detected on Y-axis");
    if (CurieIMU.shockDetected(Y_AXIS, NEGATIVE))
      Serial.println("Positive shock detected on Y-axis");
    if (CurieIMU.shockDetected(Z_AXIS, POSITIVE))
      Serial.println("Negative shock detected on Z-axis");
    if (CurieIMU.shockDetected(Z_AXIS, NEGATIVE))
      Serial.println("Positive shock detected on Z-axis");
  }
}


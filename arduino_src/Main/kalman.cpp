/*
 * File name:   kalman.cpp
 * Author:      Garrett Clay
 * Description: Kalman filter.
 * 
 * https://github.com/TKJElectronics/KalmanFilter/blob/master/Kalman.cpp
 * 
 */

 #include "kalman.h"

/*
 * @brief Initialization of kalman variables
 */
void kalman::kalmanInit() {
  //variables for roll
  //we set the variables like so, there can also be tuned by the user
  QAngleRoll = 0.01f;    //0.001
  QBiasRoll  = 0.03f;    //0.003
  RMeasureRoll = 0.03f;   //0.03

  RollAngle = 0.0f;   // reset the angle
  RollBias  = 0.0f;   // reset bias

  PRoll[0][0] = 0.0f; // since we assume bias is 0 we know the starting angle (use SetAngle), see orginal src
  PRoll[0][1] = 0.0f;
  PRoll[1][0] = 0.0f;
  PRoll[1][1] = 0.0f;

  //variables for pitch
  //we set the variables like so, there can also be tuned by the user
  QAnglePitch = 0.001f;
  QBiasPitch  = 0.003f;
  RMeasurePitch = 0.03f;

  PitchAngle = 0.0f;   // reset the angle
  PitchBias  = 0.0f;   // reset bias

  PPitch[0][0] = 0.0f; // since we assume bias is 0 we know the starting angle (use SetAngle), see orginal src
  PPitch[0][1] = 0.0f;
  PPitch[1][0] = 0.0f;
  PPitch[1][1] = 0.0f;
};

/*
 *  @brief Calculate kalman filtered roll
 *  
 *  @param[in]  NewAngle  angle in degrees
 *  @param[in]  NewRate   rate in degrees per second
 *  @param[in]  Dt        delta in seconds
 *  
 *  @retval   RollAngle   filtered roll angle in degrees
 */
float kalman::GetRollAngle(float NewAngle, float NewRate, float Dt) {

  // discrete kalman filter time update eq. - Time Update ("Predict")
  // Update xhat - project the state ahead
  /* step 1 */
  RollRate = NewRate - RollBias;
  RollAngle += Dt * RollRate;

  // update estimation error covariance - project the error covariance ahead
  /* step 2 */
  PRoll[0][0] += Dt * (Dt*PRoll[1][1] - PRoll[0][1] - PRoll[1][0] + QAngleRoll);
  PRoll[0][1] -= Dt * PRoll[1][1];
  PRoll[1][0] -= Dt * PRoll[1][1];
  PRoll[1][1] += QBiasRoll * Dt;

  // discrete kalman filter measurement update equations - measurement update ("correct")
  // calculate kalman gain - compute the kalman gain
  /* step 4 */
  float s = PRoll[0][0] + RMeasureRoll;  // estimate error

  /* step 5 */
  float K[2]; // Kalman gain - this is a 2x1 vector
  K[0] = PRoll[0][0] / s;
  K[1] = PRoll[1][0] / s;

  // calculate angle and bias - update estimate with measurement zk (NewAngle)
  /* step 3 */
  float y = NewAngle - RollAngle; // angle difference

  /* step 6 */
  RollAngle += K[0] * y;
  RollBias += K[1] * y;

  // calculate estimation error covariance - update the error covariance
  /* step 7 */
  float P00_temp = PRoll[0][0];
  float P01_temp = PRoll[0][1];

  PRoll[0][0] -= K[0] * P00_temp;
  PRoll[0][1] -= K[0] * P01_temp;
  PRoll[1][0] -= K[1] * P00_temp;
  PRoll[1][1] -= K[1] * P01_temp;
  
  return RollAngle;
};

/*
 *  @brief Calculate kalman filtered pitch
 *  
 *  @param[in]  NewAngle  angle in degrees
 *  @param[in]  NewRate   rate in degrees per second
 *  @param[in]  Dt        delta in seconds
 *  
 *  @retval   PitchAngle   filtered pitch angle in degrees
 */
float kalman::GetPitchAngle(float NewAngle, float NewRate, float Dt) {

  // discrete kalman filter time update eq. - Time Update ("Predict")
  // Update xhat - project the state ahead
  /* step 1 */
  PitchRate = NewRate - PitchBias;
  PitchAngle += Dt * PitchRate;

  // update estimation error covariance - project the error covariance ahead
  /* step 2 */
  PPitch[0][0] += Dt * (Dt*PPitch[1][1] - PPitch[0][1] - PPitch[1][0] + QAnglePitch);
  PPitch[0][1] -= Dt * PPitch[1][1];
  PPitch[1][0] -= Dt * PPitch[1][1];
  PPitch[1][1] += QBiasPitch * Dt;

  // discrete kalman filter measurement update equations - measurement update ("correct")
  // calculate kalman gain - compute the kalman gain
  /* step 4 */
  float s = PPitch[0][0] + RMeasurePitch;  // estimate error

  /* step 5 */
  float K[2]; // Kalman gain - this is a 2x1 vector
  K[0] = PPitch[0][0] / s;
  K[1] = PPitch[1][0] / s;

  // calculate angle and bias - update estimate with measurement zk (NewAngle)
  /* step 3 */
  float y = NewAngle - PitchAngle; // angle difference

  /* step 6 */
  PitchAngle += K[0] * y;
  PitchBias += K[1] * y;

  // calculate estimation error covariance - update the error covariance
  /* step 7 */
  float P00_temp = PPitch[0][0];
  float P01_temp = PPitch[0][1];

  PPitch[0][0] -= K[0] * P00_temp;
  PPitch[0][1] -= K[0] * P01_temp;
  PPitch[1][0] -= K[1] * P00_temp;
  PPitch[1][1] -= K[1] * P01_temp;
  
  return PitchAngle;
};

/*
 * functions below for roll
 */
void kalman::SetRollAngle(float angle) { this->RollAngle = angle; }; // used to set angle, this should be set as the starting angle
float kalman::GetRollRate() { return this->RollRate; }; // return the unbiased rate

/* these are used to tune the kalman filter */
void kalman::SetQAngleRoll(float QAngleRoll) { this->QAngleRoll = QAngleRoll; };
void kalman::SetQBiasRoll(float QBiasRoll) { this->QBiasRoll = QBiasRoll; };
void kalman::SetRMeasureRoll(float RMeasureRoll) { this->RMeasureRoll = RMeasureRoll; };

float kalman::GetQAngleRoll() { return this->QAngleRoll; };
float kalman::GetQBiasRoll() { return this->QBiasRoll; };
float kalman::GetRMeasureRoll() { return this->RMeasureRoll; };

/*
 * functions below for pitch
 */
void kalman::SetPitchAngle(float angle) { this->PitchAngle = angle; }; // used to set angle, this should be set as the starting angle
float kalman::GetPitchRate() { return this->PitchRate; }; // return the unbiased rate

/* these are used to tune the kalman filter */
void kalman::SetQAnglePitch(float QAnglePitch) { this->QAnglePitch = QAnglePitch; };
void kalman::SetQBiasPitch(float QBiasPitch) { this->QBiasPitch = QBiasPitch; };
void kalman::SetRMeasurePitch(float RMeasurePitch) { this->RMeasurePitch = RMeasurePitch; };

float kalman::GetQAnglePitch() { return this->QAnglePitch; };
float kalman::GetQBiasPitch() { return this->QBiasPitch; };
float kalman::GetRMeasurePitch() { return this->RMeasurePitch; };

 

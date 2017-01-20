/*
 * File name:   kalman.cpp
 * Author:      Garrett Clay
 * Description: Kalman filter.
 * 
 * https://github.com/TKJElectronics/KalmanFilter/blob/master/Kalman.cpp
 * 
 */

 #include "kalman.h"

kalman::kalman() {
  // we set the variables like so, there can also be tuned by the user
  Q_angle = 0.001f;
  Q_bias  = 0.003f;
  R_measure = 0.03f;

  angle = 0.0f;   // reset the angle
  bias  = 0.0f;   // reset bias

  P[0][0] = 0.0f; // since we assume bias is 0 we know the starting angle (use SetAngle), see orginal src
  P[0][1] = 0.0f;
  P[1][0] = 0.0f;
  P[1][1] = 0.0f;
};

// angle in degrees, rate in degrees per second, delta in seconds
float kalman::GetAngle(float NewAngle, float NewRate, float Dt) {
  //

  // discrete kalman filter time update eq. - Time Update ("Predict")
  // Update xhat - project the state ahead
  /* step 1 */
  rate = NewRate - bias;
  angle += Dt * rate;

  // update estimation error covariance - project the error covariance ahead
  /* step 2 */
  P[0][0] += Dt * (Dt*P[1][1] - P[0][1] - P[1][0] + Q_angle);
  P[0][1] -= Dt * P[1][1];
  P[1][0] -= Dt * P[1][1];
  P[1][1] += Q_bias * Dt;

  // discrete kalman filter measurement update equations - measurement update ("correct")
  // calculate kalman gain - compute the kalman gain
  /* step 4 */
  float s = P[0][0] + R_measure;  // estimate error

  /* step 5 */
  float K[2]; // Kalman gain - this is a 2x1 vector
  K[0] = P[0][0] / s;
  K[1] = P[1][0] / s;

  // calculate angle and bias - update estimate with measurement zk (NewAngle)
  /* step 3 */
  float y = NewAngle - angle; // angle difference

  /* step 6 */
  angle += K[0] * y;
  bias += K[1] * y;

  // calculate estimation error covariance - update the error covariance
  /* step 7 */
  float P00_temp = P[0][0];
  float P01_temp = P[0][1];

  P[0][0] -= K[0] * P00_temp;
  P[0][1] -= K[0] * P01_temp;
  P[1][0] -= K[1] * P00_temp;
  P[1][1] -= K[1] * P01_temp;
  
  return angle;
};

  void kalman::SetAngle(float angle) { this->angle = angle; }; // used to set angle, this should be set as the starting angle
  float kalman::GetRate() { return this->rate; }; // return the unbiased rate

  /* these are used to tune the kalman filter */
  void kalman::SetQAngle(float Q_angle) { this->Q_angle = Q_angle; };
  void kalman::SetQBias(float Q_bias) { this->Q_bias = Q_bias; };
  void kalman::SetRMeasure(float R_measure) { this->R_measure = R_measure; };

  float kalman::GetQAngle() { return this->Q_angle; };
  float kalman::GetQBias() { return this->Q_bias; };
  float kalman::GetRMeasure() { return this->R_measure; };
 

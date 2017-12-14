/*
 * File name:   kalman.h
 * Author:      Garrett Clay
 * Description: Kalman filter.
 */

#ifndef KALMAN_H
#define KALMAN_H

class kalman{
  public:
    void kalmanInit();
    /*
     * functions below for roll angle
     */
    // angle in degrees, rate in degrees per second, delta time in seconds
    float GetRollAngle(float NewAngle, float NewRate, float Dt);

    void SetRollAngle(float angle); // use to set angle, this should be set as the starting angle
    float GetRollRate();            // return the unbiased rate
  
    // use to tune the Kalman filter
    void SetQAngleRoll(float Q_angle);
    void SetQBiasRoll(float Q_bias);
    void SetRMeasureRoll(float R_measure);

    float GetQAngleRoll();
    float GetQBiasRoll();
    float GetRMeasureRoll();

    /*
     * functions below for pitch angle
     */
    // angle in degrees, rate in degrees per second, delta time in seconds
    float GetPitchAngle(float NewAngle, float NewRate, float Dt);

    void SetPitchAngle(float angle); // use to set angle, this should be set as the starting angle
    float GetPitchRate();            // return the unbiased rate
  
    // use to tune the Kalman filter
    void SetQAnglePitch(float Q_angle);
    void SetQBiasPitch(float Q_bias);
    void SetRMeasurePitch(float R_measure);

    float GetQAnglePitch();
    float GetQBiasPitch();
    float GetRMeasurePitch();

  private:
    /* 
     * kalman filter variables - roll 
     */
    float QAngleRoll;    // process noise variance for the accelerometer
    float QBiasRoll;     // process noise variance for the gyro bias
    float RMeasureRoll;  // measurement noise variance - this is actually the variance of the measurement noise

    float RollAngle;    // the angle calculated by the kalman filter - part of the 2x1 state vector
    float RollBias;     // the gyro bias calculated by the Kalman filter - part of the 2x1 state vector 
    float RollRate;     // unbiased rate calculated from the rate and the calculated bias - you have to call GetAngle to update the rate

    float PRoll[2][2];  // error covariance matrix - this is a 2x2 matrix

    /* 
     * kalman filter variables - pitch 
     */
    float QAnglePitch;    // process noise variance for the accelerometer
    float QBiasPitch;     // process noise variance for the gyro bias
    float RMeasurePitch;  // measurement noise variance - this is actually the variance of the measurement noise

    float PitchAngle;    // the angle calculated by the kalman filter - part of the 2x1 state vector
    float PitchBias;     // the gyro bias calculated by the Kalman filter - part of the 2x1 state vector 
    float PitchRate;     // unbiased rate calculated from the rate and the calculated bias - you have to call GetAngle to update the rate

    float PPitch[2][2];  // error covariance matrix - this is a 2x2 matrix
};

#endif

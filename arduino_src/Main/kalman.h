/*
 * File name:   kalman.h
 * Author:      Garrett Clay
 * Description: Kalman filter.
 */

#ifndef kalman_h
#define kalman_h

class kalman{
  public:
    kalman();

    // angle in degrees, rate in degrees per second, delta time in seconds
    float GetAngle(float NewAngle, float NewRate, float Dt);

    void SetAngle(float angle); // use to set angle, this should be set as the starting angle
    float GetRate();            // return the unbiased rate
  
    // use to tune the Kalman filter
    void SetQAngle(float Q_angle);
    void SetQBias(float Q_bias);
    void SetRMeasure(float R_measure);

    float GetQAngle();
    float GetQBias();
    float GetRMeasure();

  private:
    // kalman filter variables
    float Q_angle;    // process noise variance for the accelerometer
    float Q_bias;     // process noise variance for the gyro bias
    float R_measure;  // measurement noise variance - this is actually the variance of the measurement noise

    float angle;    // the angle calculated by the kalman filter - part of the 2x1 state vector
    float bias;     // the gyro bias calculated by the Kalman filter - part of the 2x1 state vector 
    float rate;     // unbiased rate calculated from the rate and the calculated bias - you have to call GetAngle to update the rate

    float P[2][2];  // error covariance matrix - this is a 2x2 matrix
};

#endif

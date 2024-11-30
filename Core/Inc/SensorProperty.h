/*
 * SensorProperty.h
 *
 *  Created on: Nov 30, 2024
 *      Author: vital
 */

#ifndef INC_SENSORPROPERTY_H_
#define INC_SENSORPROPERTY_H_

typedef enum {
    ACCEL_X_RAW,
    ACCEL_Y_RAW,
    ACCEL_Z_RAW,
    AX,
    AY,
    AZ,

    GYRO_X_RAW,
    GYRO_Y_RAW,
    GYRO_Z_RAW,
    GX,
	GY,
	GZ,

    TEMPERATURE,

    KALMAN_ANGLE_X,
    KALMAN_ANGLE_Y
} SensorProperty;

#endif /* INC_SENSORPROPERTY_H_ */

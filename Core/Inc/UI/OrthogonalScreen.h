/*
 * OrthogonalScreen.h
 *
 *  Created on: Nov 30, 2024
 *      Author: vital
 */

#ifndef INC_UI_ORTHOGONALSCREEN_H_
#define INC_UI_ORTHOGONALSCREEN_H_
#include "mpu6050.h"
#include "ssd1306.h"

typedef enum {
	X,
	Y
} OrthogonalAxis;

void displayOrthogonalScreen(MPU6050_t sensorData, OrthogonalAxis orthogonalAxis);

#endif /* INC_UI_ORTHOGONALSCREEN_H_ */

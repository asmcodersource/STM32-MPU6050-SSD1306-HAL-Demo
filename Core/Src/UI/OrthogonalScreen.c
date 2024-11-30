/*
 * OrthogonalScreen.c
 *
 *  Created on: Nov 30, 2024
 *      Author: vital
 */

#include "UI/OrthogonalScreen.h"
#include "mpu6050.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "math.h"

double getActualValue(int orthogonalAxis, MPU6050_t sensorData);
double normalizedAngleVectorX(double angle);
double normalizedAngleVectorY(double angle);
double radians(double angle);

void displayOrthogonalScreen(MPU6050_t sensorData, OrthogonalAxis orthogonalAxis){
	static char valueStr[32];
	double actualAngle = getActualValue((int)orthogonalAxis, sensorData);
	const double radius = 27;
	const int anchorAngles[] = {
		-135,
		-90,
		-45,
		0,
		45,
		90,
		135,
		180
	};

	ssd1306_DrawCircle(64, 32, radius, White);

	// Draw actual value number
	sprintf(valueStr, "%.2f", (double)actualAngle);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(
		orthogonalAxis == X ? "Angle X" : "Angle Y",
		Font_6x8,
		White
	);
	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(
		valueStr,
		Font_6x8,
		White
	);


	// Draw anchor points
	double anchorLinesLength = 4;
	for(int i = 0; i < sizeof(anchorAngles) / sizeof(anchorAngles[0]); i++){
		int angle = anchorAngles[i];
		double nx = normalizedAngleVectorX(angle);
		double ny = normalizedAngleVectorY(angle);
		double circleX = nx * radius + 64;
		double circleY = ny * radius + 32;
		ssd1306_Line(
			circleX - nx * anchorLinesLength,
			circleY - ny * anchorLinesLength,
			circleX + nx * anchorLinesLength,
			circleY + ny * anchorLinesLength,
			White
		);

		int shift = 5;
		if (abs(angle) > 45.0)
			continue;
		sprintf(valueStr, "%.2f", (double)angle);
		ssd1306_SetCursor(circleX + shift, circleY);
		ssd1306_WriteString(valueStr, Font_6x8, White);
	}

	// Draw sensor value line
	double nx = normalizedAngleVectorX(actualAngle);
	double ny = normalizedAngleVectorY(actualAngle);
	double actualLineRadius = 36;
	ssd1306_Line(
		64 - nx * actualLineRadius,
		32 - ny * actualLineRadius,
		64 + nx * actualLineRadius,
		32 + ny * actualLineRadius,
		White
	);
}

double getActualValue(int orthogonalAxis, MPU6050_t sensorData){
	switch(orthogonalAxis){
		case X:
			return sensorData.KalmanAngleX;
		case Y:
			return sensorData.KalmanAngleY;
	}
	while(1);
}


double normalizedAngleVectorX(double angle){
	return cos(radians(angle));
}

double normalizedAngleVectorY(double angle){
	return sin(radians(angle));
}

double radians(double angle){
	return angle * (M_PI / 180.0);
}

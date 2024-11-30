/*
 * ValuesScreen.c
 *
 *  Created on: Nov 30, 2024
 *      Author: vital
 */

#include "UI/ValuesScreen.h"
#include "SensorProperty.h"
#include "ssd1306_fonts.h"
#include "mpu6050.h"
#include "ssd1306.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

const char* getSensorPropertyStringValue(SensorProperty property, MPU6050_t sensorData);
const char* getSensorPropertyStringIdentifier(SensorProperty property);

// Function to display values on the screen
void displayValuesScreen(MPU6050_t sensorData) {
    // Static array of properties to display
    static const SensorProperty propertiesToDisplay[] = {
        KALMAN_ANGLE_X,
        KALMAN_ANGLE_Y,
		AX,
		AY,
		AZ,
		TEMPERATURE
    };

    // Loop through each property and display its identifier and value
    for (int i = 0; i < sizeof(propertiesToDisplay) / sizeof(propertiesToDisplay[0]); i++) {
        SensorProperty property = propertiesToDisplay[i];
        char* propertyIdentifier = (char*)getSensorPropertyStringIdentifier(property);
        char* propertyValues = (char*)getSensorPropertyStringValue(property, sensorData);

        // Set cursor position and write the identifier and value to the screen
        ssd1306_SetCursor(0, i * 10);
        ssd1306_WriteString(propertyIdentifier, Font_6x8, White);
        ssd1306_SetCursor(90, i * 10);
        ssd1306_WriteString(propertyValues, Font_6x8, White);
    }
}

// Function to return a string value based on the property
const char* getSensorPropertyStringValue(SensorProperty property, MPU6050_t sensorData) {
    static char valueStr[32]; // Static buffer to store the string value of the property

    switch (property) {
        case ACCEL_X_RAW:
            sprintf(valueStr, "%d", sensorData.Accel_X_RAW); // Convert to string
            return valueStr;
        case ACCEL_Y_RAW:
            sprintf(valueStr, "%d", sensorData.Accel_Y_RAW); // Convert to string
            return valueStr;
        case ACCEL_Z_RAW:
            sprintf(valueStr, "%d", sensorData.Accel_Z_RAW); // Convert to string
            return valueStr;
        case AX:
            sprintf(valueStr, "%.2f", sensorData.Ax); // Convert to string (floating point)
            return valueStr;
        case AY:
            sprintf(valueStr, "%.2f", sensorData.Ay); // Convert to string (floating point)
            return valueStr;
        case AZ:
            sprintf(valueStr, "%.2f", sensorData.Az); // Convert to string (floating point)
            return valueStr;
        case GYRO_X_RAW:
            sprintf(valueStr, "%d", sensorData.Gyro_X_RAW); // Convert to string
            return valueStr;
        case GYRO_Y_RAW:
            sprintf(valueStr, "%d", sensorData.Gyro_Y_RAW); // Convert to string
            return valueStr;
        case GYRO_Z_RAW:
            sprintf(valueStr, "%d", sensorData.Gyro_Z_RAW); // Convert to string
            return valueStr;
        case TEMPERATURE:
            sprintf(valueStr, "%.2f", sensorData.Temperature); // Convert to string (floating point)
            return valueStr;
        case KALMAN_ANGLE_X:
            sprintf(valueStr, "%.2f", sensorData.KalmanAngleX); // Convert to string (floating point)
            return valueStr;
        case KALMAN_ANGLE_Y:
            sprintf(valueStr, "%.2f", sensorData.KalmanAngleY); // Convert to string (floating point)
            return valueStr;
        default:
            return "Property not found";
    }
}

// Function to return the string identifier for a sensor property
const char* getSensorPropertyStringIdentifier(SensorProperty property) {
    switch (property) {
        case ACCEL_X_RAW:
            return "Accel X (RAW)";
        case ACCEL_Y_RAW:
            return "Accel Y (RAW)";
        case ACCEL_Z_RAW:
            return "Accel Z (RAW)";
        case AX:
            return "Accel X (m/s)";
        case AY:
            return "Accel Y (m/s)";
        case AZ:
            return "Accel Z (m/s)";
        case GYRO_X_RAW:
            return "Gyro X (RAW)";
        case GYRO_Y_RAW:
            return "Gyro Y (RAW)";
        case GYRO_Z_RAW:
            return "Gyro Z (RAW)";
        case TEMPERATURE:
            return "Temp (C)";
        case KALMAN_ANGLE_X:
            return "Kalman Y(deg)";
        case KALMAN_ANGLE_Y:
            return "Kalman X(deg)";
        default:
            return "Error";
    }
}

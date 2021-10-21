#include "mpu6050.h"

#include <wiringPiI2C.h>
#include <wiringPi.h>

#define PWR_MGMT_1   0x6B
#define SMPLRT_DIV   0x19
#define CONFIG       0x1A
#define GYRO_CONFIG  0x1B
#define INT_ENABLE   0x38
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H  0x43
#define GYRO_YOUT_H  0x45
#define GYRO_ZOUT_H  0x47

short mpu6050::read_raw_data(int address) {
	short high_byte = wiringPiI2CReadReg8(m_fd, address);
	short low_byte = wiringPiI2CReadReg8(m_fd, address + 1);
	short value = (high_byte << 8) | low_byte;
	return value;
}

mpu6050::mpu6050(int device_address) {
    m_fd = wiringPiI2CSetup(device_address);
    wiringPiI2CWriteReg8(m_fd, SMPLRT_DIV, 0x07);
	wiringPiI2CWriteReg8(m_fd, PWR_MGMT_1, 0x01);
	wiringPiI2CWriteReg8(m_fd, CONFIG, 0x00);
	wiringPiI2CWriteReg8(m_fd, GYRO_CONFIG, 0x18);
	wiringPiI2CWriteReg8(m_fd, INT_ENABLE, 0x01);
}

mpu6050::~mpu6050() {

}

mpu6050_data mpu6050::read_data(void) const {
    mpu6050_data data;
    data.a_x = read_raw_data(ACCEL_XOUT_H) / 16384.0f;
	data.a_y = read_raw_data(ACCEL_YOUT_H) / 16384.0f;
	data.a_z = read_raw_data(ACCEL_ZOUT_H) / 16384.0f;
	data.g_x = read_raw_data(GYRO_XOUT_H) / 131.0f;
	data.g_y = read_raw_data(GYRO_YOUT_H) / 131.0f;
	data.g_z = read_raw_data(GYRO_ZOUT_H) / 131.0f;
    return data;
}
#!/usr/bin/env python
#-*- coding: utf-8 -*-

import smbus
import math
class kalman_filter:
    def __init__(self, bias, Q_angle = 0.001, Q_gyro_bias = 0.003, R_measure = 0.03):
        self.angle = 0.0
        self.rate = 0.0
        self.bias = bias
        self.Q_angle = Q_angle
        self.Q_gyro_bias = Q_gyro_bias
        self.R_measure = R_measure
        self.P = [[0.0,0.0],[0.0,0.0]]

    def filte(self, angle, rate, dt):
        self.angle += (rate - self.bias) * dt
        self.rate = rate

        self.P[0][0] += (dt*self.P[1][1] -self.P[0][1] - self.P[1][0] + self.Q_angle) * dt
        self.P[0][1] -= self.P[1][1]
        self.P[1][0] -= self.P[1][1]
        self.P[1][1] += self.Q_gyro_bias * dt

        K_gain = [0.0,0.0]
        K_gain[0] = self.P[0][0] / (self.P[0][0] + self.R_measure)
        K_gain[1] = self.P[1][0] / (self.P[1][0] + self.R_measure)

        y = angle - self.angle

        self.angle += K_gain[0] * y
        self.rate += K_gain[1] * y

        P00_temp = self.P[0][0]
        P01_temp = self.P[0][1]

        self.P[0][0] -= P00_temp * K_gain[0]
        self.P[0][1] -= P01_temp * K_gain[0]
        self.P[1][0] -= P00_temp * K_gain[1]
        self.P[1][1] -= P01_temp * K_gain[1]

        return self.angle


def init(device = 0x68):
    global mpu6050_device__
    mpu6050_device__ = device

    global mpu6050_bus__
    mpu6050_bus__ = smbus.SMBus(1)
    mpu6050_bus__.write_byte_data(mpu6050_device__, 0x6b, 0)

    global mpu6050_data__
    mpu6050_data__ = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]

def shutdown():
    pass

def get_data():
    def read_word_2c(address):
        high = mpu6050_bus__.read_byte_data(mpu6050_device__, address)
        low = mpu6050_bus__.read_byte_data(mpu6050_device__, address + 1)
        val = (high << 8) + low
        if (val >= 0x8000):
            return -((65535 - val) + 1)
        else:
            return val

    mpu6050_data__[0] = read_word_2c(0x43) / 131.0
    mpu6050_data__[1] = read_word_2c(0x45) / 131.0
    mpu6050_data__[2] = read_word_2c(0x47) / 131.0

    mpu6050_data__[3] = read_word_2c(0x3b) / 16384.0
    mpu6050_data__[4] = read_word_2c(0x3d) / 16384.0
    mpu6050_data__[5] = read_word_2c(0x3f) / 16384.0

    return mpu6050_data__

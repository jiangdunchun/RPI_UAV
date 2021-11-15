#!/usr/bin/env python
#-*- coding: utf-8 -*-

import smbus
import math


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

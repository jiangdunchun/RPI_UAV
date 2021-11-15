#!/usr/bin/env python
#-*- coding: utf-8 -*-

from time import sleep
import logger
import control
import mpu6050
import motors

def clip(val, min, max):
    if val < min:
        val = min
    if val > max:
        val = max
    return val

if __name__ == '__main__':
    logger.init('localhost', 8086, 'UAV')
    control.init()
    mpu6050.init()
    motors.init()

    last_channels = [False, 0.0, 0.0, 0.0, 0.0, 0, 0]
    now_channels = [False, 0.0, 0.0, 0.0, 0.0, 0, 0]

    frame = 0

    while(True):
        # read control states
        states = control.get_states()
        if states and states[0] == 1:
            now_channels[0] = True
            now_channels[1] = clip((states[1] - 1081) / 780.0, -1.0, 1.0)
            now_channels[2] = clip((states[2] - 1169) / 780.0, -1.0, 1.0)
            now_channels[3] = clip((states[3] - 435) / 1530.0, 0.0, 1.0)
            now_channels[4] = clip((states[4] - 817) / 780.0, -1.0, 1.0)
            if states[5] > 1300:
                now_channels[5] = 0
            elif states[5] > 500:
                now_channels[5] = 1
            else:
                now_channels[5] = 2
            if states[6] > 1000:
                now_channels[6] = 0
            else:
                now_channels[6] = 1
        elif states:
            now_channels[0] = False

        # init the motor while channel 6 is 0
        if (now_channels[6] != last_channels[6]):
            if (now_channels[6] == 0):
                logger.log("events", "msg", "MOTORS_INIT_MODE on")
                motors.set_zero(0)
                motors.set_zero(1)
                motors.set_zero(2)
                motors.set_zero(3)
            else:
                logger.log("events", "msg", "MOTORS_INIT_MODE off")
        # allow to set speed while channel 6 is 1
        if (now_channels[6] == 1):
            motors.set_speed(0, now_channels[3])

        last_channels = now_channels.copy()



        data = mpu6050.get_data() 

        frame += 1
        if frame % (1 << 8) == 0:
            print(now_channels)
            print(data)
            logger.log("mpu6050", "a_x", data[0])
            logger.log("mpu6050", "a_y", data[1])
            logger.log("mpu6050", "a_z", data[2])
            logger.log("mpu6050", "g_x", data[3])
            logger.log("mpu6050", "g_y", data[4])
            logger.log("mpu6050", "g_z", data[5])



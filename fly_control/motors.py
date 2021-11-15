#!/usr/bin/env python
#-*- coding: utf-8 -*-

import RPi.GPIO as gpio

def init(m_0 = 29, m_1 = 31, m_2 = 33, m_3 = 35):
    gpio.setmode(gpio.BOARD)
    gpio.setwarnings(False)
    gpio.setup([m_0, m_1, m_2, m_3], gpio.OUT)

    global motors_pins__
    motors_pins__ = [0, 0, 0, 0]

    motors_pins__[0] = gpio.PWM(m_0, 500)
    motors_pins__[1] = gpio.PWM(m_1, 500)
    motors_pins__[2] = gpio.PWM(m_2, 500)
    motors_pins__[3] = gpio.PWM(m_3, 500)
    for pin in motors_pins__:
        pin.start(0.0)

def shutdown():
    pass

def set_zero(motor):
    if motor < 0 and motor > 3:
        pass
    motors_pins__[motor].ChangeDutyCycle(0.0)


# from 0.0(min) - 1.0(max)
def set_speed(motor, speed):
    if motor < 0 and motor > 3:
        pass
    if speed < 0.0 and speed > 100.0:
        pass

    motors_pins__[motor].ChangeDutyCycle(speed * 50.0 + 50.0)

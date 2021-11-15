#!/usr/bin/env python
#-*- coding: utf-8 -*-

import serial

def init(device = '/dev/ttyAMA0', baud = 100000):
    global control_serial__
    control_serial__ = serial.Serial(
        port = device,
        baudrate = baud,
        parity = serial.PARITY_EVEN,
        stopbits = serial.STOPBITS_TWO,
        bytesize = serial.EIGHTBITS,
        timeout = 0,
    )
    global control_state
    control_state = [0, 0, 0, 0, 0, 0, 0]

    global control_frame
    control_frame = bytearray(25)

def shutdown():
    pass

def get_states():
    def to_int(val):
        return int(val) 

    def decode_frame():
        control_state[0] = 1
        control_state[1] = (to_int(control_frame[1]) | to_int(control_frame[2])<<8) & 0x07FF
        control_state[2] = (to_int(control_frame[2])>>3 | to_int(control_frame[3])<<5) & 0x07FF
        control_state[3] = (to_int(control_frame[3])>>6 | to_int(control_frame[4])<<2 |to_int(control_frame[5])<<10) & 0x07FF
        control_state[4] = (to_int(control_frame[5])>>1 | to_int(control_frame[6])<<7) & 0x07FF
        control_state[5] = (to_int(control_frame[6])>>4 | to_int(control_frame[7])<<4) & 0x07FF
        control_state[6] = (to_int(control_frame[7])>>7 | to_int(control_frame[8])<<1 |to_int(control_frame[9])<<9) & 0x07FF
        if (control_state[3] < 100):
            control_state[0] = 0

    if control_serial__.inWaiting() >= 25*2:
        temp_buffer = control_serial__.read(control_serial__.inWaiting())
        for end in range(0, len(temp_buffer)):
            if temp_buffer[len(temp_buffer) - end - 1] == 0x00:
                if temp_buffer[len(temp_buffer) - end - 25] == 0x0f:
                    control_frame = temp_buffer[len(temp_buffer) - end - 25 : len(temp_buffer) - end - 1]
                    decode_frame()
                    return control_state

    return None
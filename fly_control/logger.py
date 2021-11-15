#!/usr/bin/env python
#-*- coding: utf-8 -*-

from influxdb import InfluxDBClient

def init(ip, port, db, usr = '', psw = ''):
    global logger_connection__
    logger_connection__ = InfluxDBClient(ip, port, usr, psw, db)

def shutdown():
    pass

def log(tag, name, value):
    data = {}
    data['measurement'] = tag
    data['fields'] = {}
    data['fields'][name] = value
    logger_connection__.write_points([data])

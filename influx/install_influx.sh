#!/bin/bash

sudo dpkg -i influxdb_1.8.3_armhf.deb
sudo service influxdb start
sudo dpkg -i chronograf_1.8.7_armhf.deb
sudo service chronograf start
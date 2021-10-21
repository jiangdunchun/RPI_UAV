#!/bin/bash

echo "start install influxdb and chronograf=====>"

sudo dpkg -i influxdb_1.7.10_armhf.deb
sudo service influxdb start

sudo dpkg -i chronograf_1.8.7_armhf.deb
sudo service chronograf start

echo "influxdb and chronograf have been installed, the port is 8888"
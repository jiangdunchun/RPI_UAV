#include "motor.h"

#include <algorithm>
#include <wiringPi.h>
#include <wiringSerial.h>

using namespace std;

void motor::motor_run(void) {
    while (true) {
        int tmp;
        pthread_mutex_lock(m_mutex);
        tmp = m_speed;
        pthread_mutex_unlock(m_mutex);

        digitalWrite(m_address, HIGH);
		usleep(1000 + tmp);
		digitalWrite(m_address, LOW);
		usleep(1000 - tmp);
    }
}

motor::motor(unsigned int address, unsigned int max_speed) {
    m_address = address;
    m_max_speed = max_speed;
    m_speed = 0;

    pthread_create(&m_run, (const pthread_attr_t*) NULL, (void* (*)(void*)) &motor_run, NULL);
    pthread_join(m_run, NULL);
}

motor::~motor() {
    pthread_cancel(m_run);
}

unsigned int motor::get_speed(void) {
    int tmp;
    pthread_mutex_lock(m_mutex);
    tmp = m_speed;
    pthread_mutex_unlock(m_mutex);
    return tmp;
}

void motor::set_speed(unsigned int speed) {
    int tmp = min(m_max_speed, speed);
    pthread_mutex_lock(m_mutex);
    m_speed = tmp;
    pthread_mutex_unlock(m_mutex);
}
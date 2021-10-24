#include <device/power.h>

#include <algorithm>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>

using namespace std;

unsigned int power::m_max_speed = 0;
vector<motor_info> power::m_motors = {};
vector<pthread_t> power::m_speed_threads = {};

void* power::speed_func(void* mi) {
    motor_info* m_info = (motor_info*)mi;
    while (true) {
        int tmp;
        pthread_mutex_lock(m_info->mutex);
        tmp = m_info->speed;
        pthread_mutex_unlock(m_info->mutex);

        digitalWrite(m_info->address, HIGH);
		usleep(m_max_speed + tmp);
		digitalWrite(m_info->address, LOW);
		usleep(m_max_speed - tmp);
    }
}

void power::init(vector<unsigned int> addresses, unsigned int max_speed) {
    for (unsigned int i = 0; i < addresses.size(); i++) {
        m_motors.push_back({i, addresses[i], 0, new pthread_mutex_t()});
    }
    
    wiringPiSetup();
    m_speed_threads.resize(m_motors.size());
    for (unsigned int i = 0; i < m_motors.size(); i++) {
        pinMode(m_motors[i].address, OUTPUT);
        pthread_create(&m_speed_threads[i], NULL, speed_func, &m_motors[i]);
    }

    m_max_speed = max_speed;
}

void power::shutdown(void) {
    for (unsigned int i = 0; i < m_speed_threads.size(); i++) {
        pthread_cancel(m_speed_threads[i]);
    }
    m_speed_threads.clear();

    for (unsigned int i = 0; i < m_motors.size(); i++) {
        delete m_motors[i].mutex;
    }
    m_motors.clear();
}

void power::set_speed(unsigned int index, unsigned int speed) {
    unsigned int tmp = min(m_max_speed, speed);
    pthread_mutex_lock(m_motors[index].mutex);
    m_motors[index].speed = tmp;
    pthread_mutex_unlock(m_motors[index].mutex);
}
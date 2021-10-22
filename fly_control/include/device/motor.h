#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <pthread.h>

class motor {
private:
    unsigned int m_address;
    unsigned int m_speed;
    unsigned int m_max_speed;
    pthread_mutex_t m_mutex;
    pthread_t m_run;

    static void motor_run(motor* m_ptr);
public:
    motor(unsigned int address, unsigned int max_speed = 1000);
    ~motor();
    unsigned int get_speed(void);
    void set_speed(unsigned int speed);
};
#endif
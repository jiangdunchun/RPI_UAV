#ifndef __POWER_H__
#define __POWER_H__

#include <pthread.h>
#include <vector>

struct motor_info {
    unsigned int index;
    unsigned int address;
    unsigned int speed;
    pthread_mutex_t* mutex;
};

class power {
private:
    static unsigned int m_max_speed;
    static std::vector<motor_info> m_motors;
    static std::vector<pthread_t> m_speed_threads;

    static void* speed_func(void* mi);
public:
    static void init(std::vector<unsigned int> addresses, unsigned int max_speed = 1000);
    static void shutdown(void);
    static void set_speed(unsigned int index, unsigned int speed);
};
#endif
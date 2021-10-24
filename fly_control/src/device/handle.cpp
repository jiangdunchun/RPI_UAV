#include <device/handle.h>

#include <wiringPi.h>
#include <unistd.h>
#include <sys/time.h>

#include <iostream>


using namespace std;

vector<channel_info> handle::m_channels = {};
vector<pthread_t> handle::m_pwn_threads = {};
CONTROL_CALLBACK handle::m_callback = nullptr;

void* handle::pwn_func(void* ci) {
    channel_info* c_info = (channel_info*)ci;
    struct timeval tv;
    struct timezone tz;
    long time_0, time_1, time_2;
    float rate;
    while (true) {
        while (digitalRead(c_info->address) == 0) continue;
        gettimeofday(&tv,&tz);
        time_0 = tv.tv_usec; 
        while (digitalRead(c_info->address) == 1) continue;
        gettimeofday(&tv,&tz);
        time_1 = tv.tv_usec; 
        while (digitalRead(c_info->address) == 0) continue;
        gettimeofday(&tv,&tz);
        time_2 = tv.tv_usec; 
        rate = float(time_1 - time_0) * 100.0f / float(time_2 - time_0);

        if (rate > 5.5f && rate < 8.5f) m_callback(c_info->index, LEVEL_H);
        else if (rate > 8.5f && rate < 11.5f) m_callback(c_info->index, LEVEL_M);
        else if (rate > 11.5f && rate < 14.5f) m_callback(c_info->index, LEVEL_L);
        else m_callback(c_info->index, LEVEL_ERROR);

    }
}

void handle::init(vector<unsigned int> addresses, CONTROL_CALLBACK callback) {
    for (unsigned int i = 0; i < addresses.size(); i++) {
        m_channels.push_back({i, addresses[i]});
    }
    
    wiringPiSetup();
    m_pwn_threads.resize(m_channels.size());
    for (unsigned int i = 0; i < m_channels.size(); i++) {
        pinMode(m_channels[i].address, INPUT);
        pthread_create(&m_pwn_threads[i], NULL, pwn_func, &m_channels[i]);
    }

    m_callback = callback;
}

void handle::shutdown(void) {
    for (unsigned int i = 0; i < m_pwn_threads.size(); i++) {
        pthread_cancel(m_pwn_threads[i]);
    }
    m_pwn_threads.clear();
    m_channels.clear();
}
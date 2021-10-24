#ifndef __HANDLE_H__
#define __HANDLE_H__

#include <vector>
#include <pthread.h>

#define LEVEL_ERROR 0
#define LEVEL_L 1
#define LEVEL_M 2
#define LEVEL_H 3

struct channel_info {
    unsigned int index;
    unsigned int address;
};

typedef void(*CONTROL_CALLBACK)(int, unsigned int);

class handle {
private:
    static CONTROL_CALLBACK m_callback;
    static std::vector<channel_info> m_channels;
    static std::vector<pthread_t> m_pwn_threads;

    static void* pwn_func(void* ci);
public:
    static void init(std::vector<unsigned int> addresses, CONTROL_CALLBACK callback);
    static void shutdown(void);
};

#endif
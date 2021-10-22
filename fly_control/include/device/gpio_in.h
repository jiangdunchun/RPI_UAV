#ifndef __GPIO_IN_H__
#define __GPIO_IN_H__

#include <vector>

class gpio_in {
private:
    unsigned int m_address;
    void (*m_callback)(unsigned int, bool);
    void changed_func(void);
public:
    gpio_in(unsigned int address, void(*callback)(unsigned int, bool));
    ~gpio_in();
};

#endif
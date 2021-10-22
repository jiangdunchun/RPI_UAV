#include <device/gpio_in.h>

#include <wiringPi.h>

using namespace std;

void gpio_in::changed_func(void) {
    int state = digitalRead(m_address);
    m_callback(m_address, state);
}

gpio_in::gpio_in(unsigned int address, void(*callback)(unsigned int, bool)) : m_address(address), m_callback(callback) {
    wiringPiSetup();
    pinMode(m_address, INPUT);
    typedef void (*FUNC)(void);
    FUNC func = (FUNC)&gpio_in::changed_func;
    wiringPiISR(m_address, INT_EDGE_BOTH, func);
}

gpio_in::~gpio_in() {

}
#ifndef __REMOTE_CONTROL_H__
#define __REMOTE_CONTROL_H__

#include <vector>

class remote_control {
private:
    
public:
    remote_control(std::vector<unsigned int> addresses);
    ~remote_control();
};

#endif
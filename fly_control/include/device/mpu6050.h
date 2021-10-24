#ifndef __MPU6050_H__
#define __MPU6050_H__

struct mpu6050_data {
    float a_x;
    float a_y;
    float a_z;
    float g_x;
    float g_y;
    float g_z;
};

class mpu6050 {
private:
    static unsigned int m_fd;
    
    static short read_raw_data(unsigned int address);
public:
    static void init(unsigned int device_address);
    static void shutdown();
    static mpu6050_data read_data(void);
};

#endif
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
    int m_fd;
    short read_raw_data(int address);
public:
    mpu6050(int device_address);
    ~mpu6050();
    mpu6050_data read_data(void) const;
};

#endif
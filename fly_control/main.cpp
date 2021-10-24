#include <common/logger.h>
#include <device/mpu6050.h>
#include <device/handle.h>
#include <device/power.h>

void callback(int button, unsigned int state) {
	logger::log("test", "1", (int)state);
}


int main() {
	logger::init("127.0.0.1", 8086, "test");
	mpu6050::init(0x68);
	handle::init({0}, callback);
	power::init({1}, 1000);

	while (1) {
		mpu6050_data data = mpu6050::read_data();
		logger::log("test", "a_x", data.a_x);

		sleep(1);
	}
}

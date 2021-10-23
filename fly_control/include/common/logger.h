#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>
#include <influxdb-cpp/influxdb.hpp>

class logger {
private:
    influxdb_cpp::server_info* m_si;
    static void post(influxdb_cpp::detail::field_caller& data, server_info* si);
public:
    logger(std::string ip, int port, std::string db);
    ~logger();
    void log(std::string tag, std::string name, std::string value);
    void log(std::string tag, std::string name, int value);
    void log(std::string tag, std::string name, float value);
};

#endif

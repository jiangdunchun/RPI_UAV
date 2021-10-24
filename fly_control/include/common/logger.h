#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>
#include <influxdb-cpp/influxdb.hpp>

class logger {
private:
<<<<<<< HEAD
    static influxdb_cpp::server_info* m_si;
    static void post(influxdb_cpp::detail::field_caller* data, influxdb_cpp::server_info* m_si);
=======
    influxdb_cpp::server_info* m_si;
    static void post(influxdb_cpp::detail::field_caller& data, server_info* si);
>>>>>>> 76031e13acdc38cc0447a302496c6ef04f58f8ff
public:
    static void init(std::string ip, int port, std::string db);
    static void shutdown();
    static void log(std::string tag, std::string name, std::string value);
    static void log(std::string tag, std::string name, int value);
    static void log(std::string tag, std::string name, float value);
};

#endif

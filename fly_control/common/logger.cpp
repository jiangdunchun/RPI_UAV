#include "logger.h"

using namespace std;
using namespace influxdb_cpp;

logger::logger(std::string ip, int port, std::string db) {
    m_si = server_info(ip, port, db);
}

logger::~logger() {

}

void logger::log(std::string tag, std::string name, std::string value) {
    builder()
        .meas(tag)
        .field(name, value)
        .post_http(m_si);
}

void logger::log(std::string tag, std::string name, int value) {
    builder()
        .meas(tag)
        .field(name, value)
        .post_http(m_si);
}

void logger::log(std::string tag, std::string name, float value) {
    builder()
        .meas(tag)
        .field(name, value)
        .post_http(m_si);
}


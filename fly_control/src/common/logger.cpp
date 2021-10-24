#include <common/logger.h>

#include <future>

using namespace std;
using namespace influxdb_cpp;

server_info* logger::m_si = nullptr;

void logger::post(detail::field_caller* data, server_info* si) {
    data->post_http(*si);
}

void logger::init(std::string ip, int port, std::string db) {
    m_si = new server_info(ip, port, db);
}

void logger::shutdown() {
    delete m_si;
}

void logger::log(std::string tag, std::string name, std::string value) {
    detail::field_caller& data = builder().meas(tag).field(name, value);
    async(post, &data, m_si);
}

void logger::log(std::string tag, std::string name, int value) {
    detail::field_caller& data = builder().meas(tag).field(name, value);
    async(post, &data, m_si);
}

void logger::log(std::string tag, std::string name, float value) {
    detail::field_caller& data = builder().meas(tag).field(name, value);
    async(post, &data, m_si);
}


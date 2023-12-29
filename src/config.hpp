#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string_view>

#include "easylogging++.hpp"
#include "toml.hpp"

class Config {
   private:
    toml::table m_config;
    el::Configurations m_log_conf;

   protected:
    Config() {
        m_config = toml::parse_file("config.toml");
        std::string_view log_file =
            m_config["log"]["conf_file"].value_or("log.conf");
        m_log_conf = el::Configurations(log_file.data());
        el::Loggers::reconfigureAllLoggers(m_log_conf);
    }

   public:
    Config(Config &other) = delete;
    void operator=(const Config &) = delete;

    static Config &getInstance() {
        static Config instance;
        return instance;
    }

    toml::v3::node_view<const toml::v3::node> operator[](
        const std::string &key) const {
        return m_config[key];
    }
};

#endif  // CONFIG_HPP

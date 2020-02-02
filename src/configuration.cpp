#include "configuration.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace SM {

    namespace pt = boost::property_tree;

    Configuration::Configuration(int argc, char **argv)
    {
        parserFile();
    }

    void Configuration::parserFile()
    {
            pt::ptree root;
            pt::read_json("config/config.json", root);

            auto servers = root.get_child("servers");

            for (auto &server : servers)
            {
                ServerConfiguration sv;
                
                sv.name = server.second.get<std::string>("server_name");
                sv.address = server.second.get<std::string>("server_address");
                sv.port = server.second.get<unsigned short>("server_port");

                mServersConfig.emplace_back(sv);
            }
    }
};
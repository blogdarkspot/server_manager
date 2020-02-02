#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <memory>
#include <string>
#include <vector>

namespace SM {

    struct ServerConfiguration {
        std::string name;
        std::string address;
        unsigned short port;       
    };

    class Configuration : public std::enable_shared_from_this<Configuration> {
        
        public:

            std::shared_ptr<Configuration> getPtr() {
                return shared_from_this();
            }

            explicit Configuration(int argc, char **argv);

            std::vector<ServerConfiguration> getServersConfiguration () const
            {
                return mServersConfig;
            }

    private:

        void parserFile();

        std::vector<ServerConfiguration> mServersConfig;    
    };

};

#endif //CONFIGURATION_H
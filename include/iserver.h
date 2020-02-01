#ifndef ISERVER_H
#define ISERVER_H

#include <boost/noncopyable.hpp>

namespace SM {

    class IServer : private boost::noncopyable {

public:
        virtual void run() = 0;
        virtual void stop() = 0;

        virtual ~IServer() {}
    };
};
#endif
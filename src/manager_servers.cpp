#include "manager_servers.h"
#include "tcp_server.h"

#include <thread>
#include <iostream>

namespace SM {

    ServerMananger::ServerMananger(const Configuration& configuration) : mWork(mIOC.get_executor())
    {

        ServerConfiguration s1;
        ServerConfiguration s2;
        ServerConfiguration s3;

        s1.address = "0.0.0.0";
        s1.port = 5001;

        s2.address = "0.0.0.0";
        s2.port = 5002;

        s3.address = "0.0.0.0";
        s3.port = 5003;
         
        mServers.push_back(std::make_unique<TcpServer>(mIOC, s1));
        mServers.push_back(std::make_unique<TcpServer>(mIOC, s2));
        mServers.push_back(std::make_unique<TcpServer>(mIOC, s3));
    }

    void ServerMananger::run()
    {
        std::vector<std::shared_ptr<std::thread>>  pool;
        for(size_t i = 0; i < std::thread::hardware_concurrency() * 2; ++i)
        {
            pool.emplace_back(std::make_shared<std::thread>(&ServerMananger::addPool, this));
        }

        for(size_t i = 0; i < mServers.size(); ++i)
        {
            (mServers[i])->run();
        }

        for (auto th : pool)
        {
            th->join();
            std::cout << "thread Join" << std::endl;
        }
    }

    void ServerMananger::addPool()
    {
        mIOC.run();
    }
}
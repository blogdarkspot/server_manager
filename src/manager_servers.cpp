#include "manager_servers.h"
#include "tcp_server.h"

#include <thread>
#include <iostream>

namespace SM {

    ServerMananger::ServerMananger(const Configuration& configuration) : mWork(mIOC.get_executor())
    {
           const auto servers = configuration.getServersConfiguration();
            for(auto server: servers)
            {
                mServers.push_back(std::make_unique<TcpServer>(mIOC, server));
            }
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
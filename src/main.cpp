#include "manager_servers.h"
#include "configuration.h"

#include<iostream>


int main(int argc, char **argv)
{
    SM::Configuration config(argc, argv);
    SM::ServerMananger sm(config); 
    sm.run();
    return 0;
}
#include <iostream>
#include "AppLogger.hpp"
#include "AppServer.hpp"

int main(int argc, char** argv)
{
    AppServer appserver;
    return appserver.run(argc,argv);
}

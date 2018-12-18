/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2018  yuribadz <email>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "AppServer.hpp"
#include "AppLogger.hpp"
#include "AppRequestHandlerFactory.hpp"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Util/ServerApplication.h"

AppServer::AppServer() : _helpRequested(false)
{
    poco_debug(applog::AppLogger::log, "AppServer Object created");
}

AppServer::~AppServer()
{
    poco_debug(applog::AppLogger::log, "AppServer Object destroyed");
}

void AppServer::initialize(Poco::Util::Application &self)
{
    loadConfiguration();
    Poco::Util::ServerApplication::initialize(self);
}

void AppServer::uninitialize()
{
    Poco::Util::ServerApplication::uninitialize();
}

void AppServer::defineOptions(Poco::Util::OptionSet &options)
{
    Poco::Util::ServerApplication::defineOptions(options);
    options.addOption(
        Poco::Util::Option("help", "h", "display argument help information")
            .required(false)
            .repeatable(false)
            .callback(Poco::Util::OptionCallback<AppServer>(this, &AppServer::handleHelp)));
}

void AppServer::handleHelp(const std::string &name,
                           const std::string &value)
{
    Poco::Util::HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader("Application server"
     " written by yuribadz");
    helpFormatter.format(std::cout);
    stopOptionsProcessing();
    _helpRequested = true;
}

int AppServer::main(const std::vector<std::string>& args)
{
    if(!_helpRequested)
    {
        unsigned short port = (unsigned short) config().getInt("AppServer.port",9980);
        std::string format(
            config().getString("AppServer.format",
            Poco::DateTimeFormat::SORTABLE_FORMAT)
            );
        Poco::Net::ServerSocket svs(port);
        Poco::Net::HTTPServer srv(new AppRequestHandlerFactory(format),
        svs,new Poco::Net::HTTPServerParams);
        srv.start();
        waitForTerminationRequest();
        srv.stop();
    }
    return Poco::Util::Application::EXIT_OK;
}

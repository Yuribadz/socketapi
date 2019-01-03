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

#include "AppRequestHandler.hpp"
#include "AppLogger.hpp"
#include "DbMock.hpp"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include <Poco/StreamCopier.h>
#include <iostream>
#include <sstream>

// helper function to convert istream to string
// it is used because stringstream is fairly slow
std::string gulp(std::istream &in)
{
    std::string ret;
    char buffer[4096];
    while (in.read(buffer, sizeof(buffer)))
    {
        ret.append(buffer, sizeof(buffer));
    }
    const unsigned int extractedCharCount =
            static_cast<const unsigned int>(in.gcount());
    ret.append(buffer, extractedCharCount);
    return ret;
}

AppRequestHandler::AppRequestHandler(const std::string &format) : _format(format)
{
    poco_debug(applog::AppLogger::log, "RequestHandler Constructor called");
}

void AppRequestHandler::handleRequest(Poco::Net::HTTPServerRequest &request,
                                   Poco::Net::HTTPServerResponse &response)
{
    Poco::Util::Application &app = Poco::Util::Application::instance();
    poco_information(applog::AppLogger::log,
                     "Request from " + request.clientAddress().toString());
    // Get request body, poco gives istream for request body
    std::istream &responseBodyIStream = request.stream();
    std::string responseBody = gulp(responseBodyIStream);
    response.setChunkedTransferEncoding(true);
    response.setContentType("text/plain");

    std::ostream &ostr = response.send();
    ostr << "We have received your request. You sent: \n" << responseBody;
    DbMock saywhat;
    std::string testdata = "{\"key\" : \"username\",\"username\": [{\"First Name\" : \"Yuriy\" ,\"Last Name\" : \"Badziuk\",\"Phone\" : \"+phone\",\"Company\" : \"company\"}]}";
    std::string testdata2 = "{\"key\" : \"username\"}";
    std::string testdata3 = "{\"key\" : \"username\",\"username\": [{\"First Name\" : \"Andriy\" ,\"Last Name\" : \"Badziuk\",\"Phone\" : \"+phone\",\"Company\" : \"company\"}]}";
    saywhat.addUserToDb(testdata);
    saywhat.updatePersonInDb(testdata3);
    saywhat.deleteUserFromDb(testdata2);
}
 
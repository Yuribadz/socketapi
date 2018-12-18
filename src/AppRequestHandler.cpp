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
#include "Poco/Util/ServerApplication.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"

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

    Poco::Timestamp now;
    std::string dt(Poco::DateTimeFormatter::format(now, _format));

    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");

    std::ostream &ostr = response.send();
    ostr << "<html><head><title>HTTPTimeServer powered by "
            "POCO C++ Libraries</title>";
    ostr << "<meta http-equiv=\"refresh\" content=\"1\"></head>";
    ostr << "<body><p style=\"text-align: center; "
            "font-size: 48px;\">";
    ostr << dt;
    ostr << "</p></body></html>";
}

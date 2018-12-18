/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2018  yuribadz yuribadz@gmail.com
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

#ifndef APPSERVER_H
#define APPSERVER_H

#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/OptionSet.h"

class AppServer: public Poco::Util::ServerApplication
{
public:
    AppServer();
    ~AppServer();

protected:
    void initialize(Poco::Util::Application& self);
    void uninitialize();
    void defineOptions(Poco::Util::OptionSet& options);

    void handleHelp(const std::string& name, 
                    const std::string& value);

    int main(const std::vector<std::string>& args);

private:
    bool _helpRequested;
};


#endif // APPSERVER_H
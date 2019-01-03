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

#ifndef DBMOCK_H
#define DBMOCK_H

#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/Parser.h"
#include <string>


class DbMock{
public:
    DbMock();
    Poco::JSON::Object::Ptr buildJSON();
    void addUserToDb(std::string& json);
    void updatePersonInDb(std::string& json);
    void deleteUserFromDb(std::string& user);
private:
    Poco::JSON::Object::Ptr _dbJSON;
    Poco::JSON::Parser _parser;
    Poco::Dynamic::Var _parseResult;
};

#endif // DBMOCK_H
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
#include "DbMock.hpp"
#include <sstream>

DbMock::DbMock():_dbJSON(buildJSON())
{
}
void DbMock::addUserToDb(std::string& json)
{
    _parseResult = _parser.parse(json);
    Poco::JSON::Object::Ptr jsonObj = _parseResult.extract<Poco::JSON::Object::Ptr>();
    std::string userName = jsonObj->get("key");
    Poco::JSON::Array::Ptr userArray = jsonObj->getArray(userName);
    _dbJSON->set(userName,userArray);
    _parseResult.clear();
}

void DbMock::updatePersonInDb(std::string& json)
{
    _parseResult = _parser.parse(json);
    Poco::JSON::Object::Ptr jsonObj = _parseResult.extract<Poco::JSON::Object::Ptr>();
    std::string userName = jsonObj->get("key");
    Poco::JSON::Array::Ptr userArray = jsonObj->getArray(userName);
    _dbJSON->set(userName,userArray);
    _parseResult.clear();

}
void DbMock::deleteUserFromDb(std::string& json)
{
    _parseResult = _parser.parse(json);
    Poco::JSON::Object::Ptr jsonObj = _parseResult.extract<Poco::JSON::Object::Ptr>();
    std::string userName = jsonObj->get("key");
    _dbJSON->remove(userName);
    _parseResult.clear();
}

Poco::JSON::Object::Ptr DbMock::buildJSON()
{
   Poco::JSON::Object::Ptr root = new Poco::JSON::Object();
   return root;
}
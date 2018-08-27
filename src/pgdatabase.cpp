/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2018  <copyright holder> <email>
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
 */

#include <iostream>
#include <libpq-fe.h>
#include "pgdatabase.h"

PgDatabase::PgDatabase()
{
    std::cout << "Database resources allocated" << "\n";
}
PgDatabase::~PgDatabase()
{
    std::cout << "Releasing database resources" << "\n";
    do_exit(_conn);
}

void PgDatabase::do_exit(PGconn *conn)
{
    PQfinish(conn);
    exit(0);
}
void PgDatabase::connect() {
    _conn = PQconnectdb("user=projadmin password=projadmin "
                        "dbname=project_db");
    
    if (PQstatus(_conn) == CONNECTION_BAD) {

        std::cout << "Connection to Database failed\n" <<  PQerrorMessage(_conn)
                  << "\n";
        do_exit(_conn);
    }

    char *user = PQuser(_conn);
    char *db_name = PQdb(_conn);
    char *pswd = PQpass(_conn);
    printf("User: %s\n", user);
    printf("Database name: %s\n", db_name);
    printf("Password: %s\n", pswd);
    std::cout << "Connected" << "\n";

}

#include <iostream>
#include <libpq-fe.h>
#include "pgdatabase.h"

void do_exit(PGconn *conn) {

    PQfinish(conn);
    exit(1);
}

int main() {

    PGconn *conn = PQconnectdb("user=projadmin password=projadmin "
                               "dbname=project_db");
    if (PQstatus(conn) == CONNECTION_BAD) {

        std::cout << "Connection to Database failed\n" <<  PQerrorMessage(conn) \
                  << "\n";
        do_exit(conn);
    }

    char *user = PQuser(conn);
    char *db_name = PQdb(conn);
    char *pswd = PQpass(conn);
    
    printf("User: %s\n", user);
    printf("Database name: %s\n", db_name);
    printf("Password: %s\n", pswd);
    PgDatabase database;
    database.connect();

    PQfinish(conn);

    return 0;
}

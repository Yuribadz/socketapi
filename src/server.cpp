#include <iostream>
#include <libpq-fe.h>
#include "pgdatabase.h"

int main() {
    PgDatabase database;
    database.connect();

    return 0;
}

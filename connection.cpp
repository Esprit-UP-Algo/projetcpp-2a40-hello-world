#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("source_projet2a");
db.setUserName("mariem");
db.setPassword("esprit18");

if (db.open())
test=true;





    return  test;
}
void Connection::closeConnection(){db.close();}

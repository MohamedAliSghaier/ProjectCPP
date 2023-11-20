#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("ProjetQt");
db.setUserName("dalouka");//inserer nom de l'utilisateur
db.setPassword("dalouka");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}

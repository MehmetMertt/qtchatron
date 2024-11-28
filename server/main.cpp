#include <QCoreApplication>

#include <Server/Server.h>

#include <Database/databasehandler.h>


int main(int argc, char *argv[])
{

    QCoreApplication app(argc, argv);

    databaseHandler dbHandler = databaseHandler();

    dbHandler.AddUser("Mehmett","Ok","Hi");

    QSqlDatabase db = QSqlDatabase::database();

    Server server;
    server.start();


    return app.exec();
}

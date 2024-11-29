#include <QCoreApplication>

#include <Server/Server.h>

#include <Database/databasehandler.h>


int main(int argc, char *argv[])
{

    QCoreApplication app(argc, argv);

    databaseHandler dbHandler = databaseHandler();

    QSharedPointer<DatabaseResponse> dbr = dbHandler.AddUser("Mehmwewett","hwhwhdwhdwdw","Hi");
    qDebug() << dbr->message();

    dbr = dbHandler.LoginUser("Mehmwewsett","hwhwhdwhdwdw");

    qDebug() << dbr->message();

    QSqlDatabase db = QSqlDatabase::database();

    Server server;
    server.start();


    return app.exec();
}

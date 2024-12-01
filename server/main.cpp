#include <QCoreApplication>

#include <Server/Server.h>

#include <Database/databasehandler.h>


int main(int argc, char *argv[])
{

    QCoreApplication app(argc, argv);

    databaseHandler *dbHandler = new databaseHandler();

    QSharedPointer<DatabaseResponse> dbr = dbHandler->AddUser("myUser","myPassword","Hi");
    qDebug() << dbr->message();

    dbr = dbHandler->LoginUser("Mehmwewett","hwhwhdwhdwdw");



    QString token = dbr->message();
    qDebug() << "token: " << token;

    //dbr = dbHandler.getAllDirectMessagesByUserID("2");

   // qDebug() << dbr->message();

    dbr = dbHandler->getIDByToken(token+"gg");

    qDebug() << dbr->message();

    Server server;
    server.start();


    return app.exec();
}

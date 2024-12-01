#include <QCoreApplication>

#include <Server/Server.h>

#include <Database/databasehandler.h>


int main(int argc, char *argv[])
{

    QCoreApplication app(argc, argv);

    databaseHandler *dbHandler = new databaseHandler();

    QSharedPointer<DatabaseResponse> dbr;
   // qDebug() << dbr->message();

  //  dbr = dbHandler->LoginUser("Mehmwewett","hwhwhdwhdwdw");

/*
    dbr = dbHandler->createThread("2","asddwdf","3");

    qDebug() << dbr->message();

    dbr = dbHandler->createThread("1","asddwdf","2");

    qDebug() << dbr->message();


    dbr = dbHandler->createThread("1","","2");

    qDebug() << dbr->message();
*/

   // qDebug() << "1";


  //  dbr = dbHandler->createThread("2","asddwdf","3");

    //qDebug() << dbr->message();
/*
    qDebug() << "2";


    dbr = dbHandler->getThreadsFromChannel("1");
    qDebug() << dbr->message();


    qDebug() << "3";

    dbr = dbHandler->getThreadsFromChannel("2");
    qDebug() << dbr->message();

    qDebug() << "2";


    dbr = dbHandler->getThreadsFromChannel("1337");
    qDebug() << dbr->message();
*/

   // QString token = dbr->message();
    //qDebug() << "token: " << token;

    //dbr = dbHandler.getAllDirectMessagesByUserID("2");

   // qDebug() << dbr->message();
    /*
    qDebug() << "2";

    dbr = dbHandler->getChannelsFromUser("2");


    qDebug() << dbr->message();

    qDebug() << "1";

    dbr = dbHandler->getChannelsFromUser("1");


    qDebug() << dbr->message();

    qDebug() << "3";

    dbr = dbHandler->getChannelsFromUser("3");


    qDebug() << dbr->message();

    qDebug() << "Testing GetChannels()";

    dbr = dbHandler->getChannels();
    qDebug() << dbr->message();


    dbr = dbHandler->createChannel("qtiscool","text",true,"2");
    qDebug() << dbr->message();


    dbr = dbHandler->createChannel("qtiscool","voice",false,"1");
    qDebug() << dbr->message();


    dbr = dbHandler->createChannel("qtiscool","efef",true,"2");
    qDebug() << dbr->message();
*/
/*
    dbr = dbHandler->checkIfUserExists("Mehmet");
    qDebug() << dbr->message();
    dbr = dbHandler->checkIfUserExists("we23");
    qDebug() << dbr->message();
*/

    qDebug() << "1";
    dbr = dbHandler->getThreadMessagesByThreadID("1");
    qDebug() << dbr->message();


    qDebug() << "2";
    dbr = dbHandler->getThreadMessagesByThreadID("2");
    qDebug() << dbr->message();

    qDebug() << "3";
    dbr = dbHandler->getThreadMessagesByThreadID("4");
    qDebug() << dbr->message();


    Server server;
    server.start();


    return app.exec();
}

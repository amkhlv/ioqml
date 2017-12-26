#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "iofunctions.h"
#include "pipereader.h"
#include <QObject>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String(argv[1])));

    QThread* pipeReaderThread = new QThread();

    PipeReader* pipeReader = new PipeReader();

    pipeReader->moveToThread(pipeReaderThread);
    //mayaposch.wordpress.com/2011/11/01/how-to-really-truly-use-qthreads-the-full-explanation/

    QObject::connect(pipeReaderThread, SIGNAL(started()), pipeReader, SLOT(process()));
    QObject::connect(pipeReader, SIGNAL(finished()), pipeReaderThread, SLOT(quit()));
    QObject::connect(pipeReader, SIGNAL(finished()), pipeReader, SLOT(deleteLater()));
    QObject::connect(pipeReaderThread, SIGNAL(finished()), pipeReaderThread, SLOT(deleteLater()));

    QObject* root = engine.rootObjects()[0];
    IOFunctions* ioFunctions = new IOFunctions(root, pipeReaderThread);

    QObject::connect(pipeReader, SIGNAL(error(QString)), ioFunctions, SLOT(reportError(QString)));
    QObject::connect(pipeReader, SIGNAL(newcmd(QString)), ioFunctions, SLOT(sendToQML(QString)));
    QObject::connect(root, SIGNAL(putStr(QString)), ioFunctions, SLOT(putStrSlot(QString)));
    QObject::connect(&engine, SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));

    pipeReaderThread->start();

    int r = app.exec();
    return r;
}

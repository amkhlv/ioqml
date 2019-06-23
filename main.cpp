#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "iofunctions.h"
#include "pipereader.h"
#include <QObject>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QCommandLineParser parser;
    parser.setApplicationDescription("Generic GUI");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("qmlfile", "QML file");
    QCommandLineOption classOption(QStringList() << "c" << "class", "set WM_CLASS", "wmclass");
    parser.addOption(classOption);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    parser.process(app);
    const QStringList args = parser.positionalArguments();
    if (parser.isSet(classOption)) {
        QCoreApplication::setApplicationName(parser.value(classOption)) ;
    }

    QQmlApplicationEngine engine;
    engine.load(QUrl(args.at(0)));

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

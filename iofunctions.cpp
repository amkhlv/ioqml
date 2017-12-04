#include "iofunctions.h"
#include "pipereader.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QWindow>
#include <QDebug>
#include <exception>

IOFunctions::IOFunctions(QObject *r, QThread *pipereader, QObject *parent) : QObject(parent)
{
    this->mainwin = r;
    this->state = r->findChild<QObject*>("stateObject");
    this->control = r->findChild<QObject*>("controlObject");
    this->listener = pipereader;
}

void IOFunctions::putStrSlot(QString msg) {
    QTextStream(stdout) << msg << endl;
}

void IOFunctions::sendToQML(QString msg) {
    if (msg == "stop") {
        control->setProperty("dismiss",QVariant(1));
    } else if (msg == "hide") {
        mainwin->setProperty("visibility", QWindow::Hidden);
    } else if (msg == "show") {
        mainwin->setProperty("visibility", QWindow::AutomaticVisibility);
    } else {
        QJsonDocument jsdoc = QJsonDocument::fromJson(msg.toUtf8());
        QJsonObject jsobj = jsdoc.object();
        foreach(QString k,jsobj.keys()) {
            state->setProperty(k.toLocal8Bit().data(), jsobj.take(k).toVariant());
        };
    }
}

void IOFunctions::stopReadingStream() {
    //qDebug() << "stopping the stdin reader" << endl;
    listener->terminate();
}

void IOFunctions::reportError(QString err) {
    //qDebug() << "ERROR in Pipe Reader: " << err << endl;
}

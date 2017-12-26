#ifndef IOFUNCTIONS_H
#define IOFUNCTIONS_H

#include <QObject>
#include <QThread>

class IOFunctions : public QObject
{
    Q_OBJECT
public:
    explicit IOFunctions(QObject* mainwin, QThread* pipereader, QObject *parent = 0);

private:
    QObject* mainwin;
    QObject* state;
    QObject* control;
    QThread* listener;

signals:

public slots:
    void putStrSlot(QString msg);
    void sendToQML(QString msg);
    void reportError(QString err);
};

#endif // IOFUNCTIONS_H

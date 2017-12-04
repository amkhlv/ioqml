#ifndef INSTREAM_H
#define INSTREAM_H
#include <QtCore>

class PipeReader  : public QObject
{
    Q_OBJECT
private:
    bool go;
public slots:
    void process();
signals:
    void newcmd(QString cmd);
    void finished();
    void error(QString err);
};

#endif // INSTREAM_H

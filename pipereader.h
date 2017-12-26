#ifndef INSTREAM_H
#define INSTREAM_H
#include <QtCore>
#include <string>

class PipeReader  : public QObject
{
    Q_OBJECT
public:
    PipeReader();
    ~PipeReader();
private:
    bool go;
    std::string x;
public slots:
    void process();
signals:
    void newcmd(QString cmd);
    void finished();
    void error(QString err);
};

#endif // INSTREAM_H

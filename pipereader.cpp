#include <string>
#include <iostream>
#include <QObject>
#include <QThread>
#include "pipereader.h"

void PipeReader::process() {
    go = true;
    while(go) {
        std::string x;
        std::getline(std::cin, x); // <--- blocking
        char * writable = new char[x.size() + 1];
        std::copy(x.begin(), x.end(), writable);
        writable[x.size()] = '\0';
        emit newcmd(QString(writable));
        delete[] writable;
        if (x.compare("stop") == 0) {go = false;}
    };
    emit finished();
}


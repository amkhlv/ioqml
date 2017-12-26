#include <iostream>
#include <QObject>
#include <QThread>
#include "pipereader.h"

PipeReader::PipeReader() {}

void PipeReader::process() {
    go = true;
    std::string x;
    while(go && std::getline(std::cin, x)) {
        char * writable = new char[x.size() + 1];
        std::copy(x.begin(), x.end(), writable);
        writable[x.size()] = '\0';
        emit newcmd(QString(writable));
        delete[] writable;
        if (x.compare("stop") == 0) { x = "" ; go = false; emit finished(); }
        x.erase();
    };
}

PipeReader::~PipeReader() {
    x.erase();
}

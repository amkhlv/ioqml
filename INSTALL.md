Installing dependencies
=======================

    aptitude install build-essential qt5-default qt5-qmake qtdeclarative5-dev qml-module-qtquick2 qml-module-qtquick-layouts qml-module-qtquick-controls2 qml-module-qtquick-templates2 qml-module-qtquick-window2

Building
========

In this directory:

    mkdir build
    cd build
    qmake -makefile ../
    make

This will generate the binary file `ioqml`. Copy it to some place on the `PATH`, _e.g._ to `/usr/local/bin/`

Testing
=======

    echo '{"prompt":"please enter passphrase and press Enter"}' | ioqml ../examples/pass-prompt.qml

Description
===========

`ioqml` is a [Zenity](https://en.wikipedia.org/wiki/Zenity)-like universal GUI dialog, but [QML](https://en.wikipedia.org/wiki/QML)-based.

It accepts some __commands on `stdin`__ and prints __results to `stdout`__.


Example of invocation
=====================

    echo '{"prompt":"please enter passphrase and press Enter"}' | ioqml examples/pass-prompt.qml


Accepted commands
=================

The commands incoming on `stdin` should be __newline-separated__ . The following are understood as commands:

1. Single word `stop` : terminates the program

2. Single word `hide` : hides the window

3. Single word `show` : shows the window (if it was hidden); more precisely, restores the window to its "default visibility"

4. [JSON](https://en.wikipedia.org/wiki/JSON) string of the form, for example `{"x": {"y":0, "z":1}}` sets the object
`st.x` inside `QML` to `{"y":0, "z":1}`. The object `st` is [pre-defined in the header](examples/pass-prompt.qml) of the `QML` file; its property `x` 
__should be declared__ in the `QML` file (or you get error). Then setting `st.x` can be hooked to some useful action by writing an 
[on-property-change handler](http://doc.qt.io/qt-5/qtqml-syntax-signals.html#property-change-signal-handlers)

See [examples of QML files](examples/). 

__Do not push pretty-printed `JSON`__ on `stdin`, because, remember, `newline` is the command separator;
all incoming `JSON` should be onelines.

To generate output
==================

Emitting the [QML signal](http://doc.qt.io/qt-5/qtqml-syntax-signals.html) `putStr(x)` prints `x` to `stdout` (see [examples](examples/)).


To change WM_CLASS of the ioqml window
======================================

invoke with flags, _e.g._ :

    ioqml --name MYNAME --class MYCLASS   myapp.qml

--- sets `res_name` to `MYNAME` and `res_class` to `MYCLASS`

(Notice that `--name` works for all `Qt` applications, starting from Qt 5.2)

CONFIG      += qt
SOURCES     += main.cpp AnimatedQuarterWidget.cpp spammodule.c
HEADERS     += AnimatedQuarterWidget.h spammodule.h
FORMS       += gfide.ui
INCLUDEPATH += /usr/include/python2.4/

LIBS        += -L/usr/local/lib -lQuarter -lpython2.4

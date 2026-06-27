#ifndef GFIDESCRIPTFILEDIALOG_H
#define GFIDESCRIPTFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include <QString>
#include <QFileDialog>
#include "ui_gfide.h"






class GfideMainWindow: public QMainWindow
{
  Q_OBJECT;
public:
  GfideMainWindow();  
  
    public slots:
      void currentChanged(const QString & path);
    void loadScriptFile(); 
    void printFiles(const QStringList & selected);

};



#endif

#include "gfideMainWindow.h"
#include <iostream>

using namespace std;




void GfideMainWindow::printFiles(const QStringList & selected) {
  
  while (true)
    cout << "Files:" << selected.size() << endl;
}

void GfideMainWindow::currentChanged(const QString & path) {
  cout << (const char *)path.toAscii() << endl;
}

GfideMainWindow::GfideMainWindow() {

}
  

void GfideMainWindow::loadScriptFile() {
  QString fileName = QFileDialog::getOpenFileName();
  cout << (const char *)fileName.toAscii() << endl;
}

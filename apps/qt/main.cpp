
#include <Python.h>


#include <iostream>
#include <QThread>
#include <QStatusBar>
#include <QString>

#include <qmutex.h>

#include <Quarter/QuarterWidget.h>
#include <Quarter/QuarterApplication.h>
#include <Inventor/nodes/SoTransform.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/threads/SbThreadAutoLock.h>
#include <Inventor/threads/SbMutex.h>


#include "gfideMainWindow.h"


#include "spammodule.h"
#include "AnimatedQuarterWidget.h"
#include "AnimatedQuarterWidgetPYTHON_wrap.cxx"
#include "ui_gfide.h"


void runPyIterator(void *data) {
  PyRun_SimpleString("gfIterate()\n");
  
}

#define C_OWNS 0

PyObject * pass_instance(AnimatedQuarterWidget *arg, const char *type_name, int own = C_OWNS)
{
  printf("pass_instance(AnimatedQuarterWidget \n");
  return cxx_to_py ((void *) arg, type_name, own);
}


using namespace SIM::Coin3D::Quarter;

using namespace std;

int main(int argc, char *argv[])
{
  //Q_INIT_RESOURCE(testqtdesigner);
  QuarterApplication app(argc, argv);

  std::cout << "Starting Quarter test program\n";
  //QMainWindow * qmw = (QMainWindow *)SoQt::init(argv[0]);
  //QMainWindow * qmw = new QMainWindow();
  GfideMainWindow qmw;
  QFileDialog fileDialog;
  Ui_MainWindow mw;
  mw.setupUi(&qmw);

  qmw.statusBar()->showMessage(QString("Ready 123"));

  

  QObject::connect((const QObject*)mw.actionLoad_Script, (const char*)SIGNAL(activated()), (const QObject*)&qmw, (const char*)SLOT(loadScriptFile()));




  QObject::connect((const QObject*)&fileDialog, (const char*)SIGNAL(currentChanged(const QString &)), (const QObject*)&qmw, (const char*)SLOT(currentChanged(const QString &)));

   
  mw.animatedQuarterWidget->animationCallback = runPyIterator;
  mw.animatedQuarterWidget->animationCallbackData = NULL;
  mw.animatedQuarterWidget->timerInterval = 94;

  Py_Initialize();
  initspam();


  //SWIG_init();
  PyObject*    aqwModule, * global_dict, * expression;
  PyObject *key = PyString_FromString("implicitAQW");
  PyObject *ival = PyInt_FromLong(42);
  PyRun_SimpleString("import sys\n");
  PyRun_SimpleString("sys.path.append('../lib')\n");
  PyRun_SimpleString("sys.path.append('./')\n");
  PyRun_SimpleString("from time import time,ctime\n");
  PyRun_SimpleString("import spam\n");
  

  PyRun_SimpleString("import gfcoin\n");
  

  PyRun_SimpleString("import gforce\n");


  PyObject* aqwModuleRef = PyImport_Import(PyString_FromString("aqw"));

  PyObject *aqwobj = NULL;
  printf("Next line is pass_instance\n");
  
  aqwModule = PyImport_AddModule("aqw");
  global_dict = PyModule_GetDict(aqwModule);

  aqwobj = pass_instance(mw.animatedQuarterWidget,"AnimatedQuarterWidget *",C_OWNS);

  int retval = PyObject_SetItem (global_dict, key, aqwobj) ;
  
  FILE * fp = fopen( "testgfcoin.py", "r" ); 
  PyObject *module = PyImport_AddModule("__main__");
  PyObject *dict   = PyModule_GetDict(module);
  PyObject *aqwModuleKey = PyString_FromString("aqw");
  retval = PyObject_SetItem (dict, aqwModuleKey, aqwModuleRef) ;
  PyRun_SimpleString("print('Begin loaded Python script')"); 
  PyRun_File( fp,"testgfcoin.py",Py_file_input, dict, dict );
  PyRun_SimpleString("print('Done loaded Python script')"); 


  PyRun_SimpleString("print(type(aqw.implicitAQW))"); 
  PyRun_SimpleString("print 'aqw.implicitAQW.timerInterval:', aqw.implicitAQW.timerInterval"); 
  PyRun_SimpleString("print('End all Python execution')"); 

  mw.animatedQuarterWidget->startAnimation();

  //log_py_objects();
  
  qmw.show();
  
  int r = app.exec();
  //return 0;
  Py_Finalize();    
  return r;
}


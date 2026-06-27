#ifndef QUARTER_QUARTERWIDGET_H
#define QUARTER_QUARTERWIDGET_H

%{
#include <QtOpenGL/QGLWidget>
#include <Inventor/SbBasic.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Quarter/Basic.h>
  %}

class SoNode;
class SoEvent;
class SoCamera;
class SoDirectionalLight;

namespace SIM { namespace Coin3D { namespace Quarter {

namespace PreviewSupport {
class SoEventManager;
class SoRenderManager;
}

class DeviceManager;

class QuarterWidget : public QGLWidget {
  typedef QGLWidget inherited;
  //Q_OBJECT

public:
  QuarterWidget(QWidget * parent = 0, const QGLWidget * sharewidget = 0);
  QuarterWidget(QGLContext * context, QWidget * parent = 0, const QGLWidget * sharewidget = 0);
  virtual ~QuarterWidget();

  void enableHeadlight(const SbBool onoff);
  SoDirectionalLight * getHeadlight(void);
  uint32_t getCacheContextId(void) const;

  void setTransparencyType(SoGLRenderAction::TransparencyType type);
  
  virtual void setSceneGraph(SoNode * root);
  virtual SoNode * getSceneGraph(void) const;
  DeviceManager * getDeviceManager(void) const;
  PreviewSupport::SoEventManager * getSoEventManager(void) const;
  PreviewSupport::SoRenderManager * getSoRenderManager(void) const;
                                                   
  //public slots:
  //virtual void viewAll(void);

protected:
  virtual void resizeGL(int width, int height);
  virtual void initializeGL(void);
  virtual void paintGL(void);
  virtual bool event(QEvent * event);
  virtual void actualRedraw(void);

  static void renderCB(void * closure, PreviewSupport::SoRenderManager *);

private:
  void constructor(const QGLWidget * sharewidget);
  friend class QuarterWidgetP;
  class QuarterWidgetP * pimpl;
};

}}} // namespace

#endif // QUARTER_QUARTERWIDGET_H

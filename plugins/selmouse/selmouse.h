#ifndef _SELKEY_H
#define _SELKEY_H

#include "basicplugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

 class Selmouse : public QObject, public BasicPlugin
 {
     Q_OBJECT
#if QT_VERSION >= 0x050000
     Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif
     Q_INTERFACES(BasicPlugin)

 public:
     void postFrame();
     void onPluginLoad();
     void mouseReleaseEvent(QMouseEvent *e);
     void drawSelectedBox();
     void createBuffers();
     void drawDrawColorScene();
     void setSelectedObject(int s);

 private:
     QOpenGLShaderProgram *progBox, *progCol;
     QOpenGLShader *vsBox, *fsBox, *vsCol, *fsCol;
     GLuint VAO;	
     float cube[24];
};
 
 #endif
 
 

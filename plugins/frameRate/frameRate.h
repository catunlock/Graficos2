#ifndef _ANIMATEVERTICESPLUGIN_H
#define _ANIMATEVERTICESPLUGIN_H

#include "basicplugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <QElapsedTimer>

// Documentation: http://www.cs.upc.edu/~virtual/Gdocs/interfaces/html/class_basic_plugin.html

class FrameRate : public QObject, public BasicPlugin
{
     Q_OBJECT
#if QT_VERSION >= 0x050000
     Q_PLUGIN_METADATA(IID "BasicPlugin")
#endif
     Q_INTERFACES(BasicPlugin)

public:
    void onPluginLoad();
    void postFrame();


public slots:
    void update();

private:
    QOpenGLShaderProgram* program;
    QOpenGLShader* vs, *fs;
    QTimer timer;
    GLuint textureID;
    char strBuff[30];

    // Add here additional members
    int frames;
    int showFrames;
};
#endif

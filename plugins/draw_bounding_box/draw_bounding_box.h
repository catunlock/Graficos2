#ifndef _ANIMATEVERTICESPLUGIN_H
#define _ANIMATEVERTICESPLUGIN_H

#include "basicplugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QElapsedTimer>

// Documentation: http://www.cs.upc.edu/~virtual/Gdocs/interfaces/html/class_basic_plugin.html

class Draw_bounding_box : public QObject, public BasicPlugin
{
     Q_OBJECT
#if QT_VERSION >= 0x050000
     Q_PLUGIN_METADATA(IID "BasicPlugin")
#endif
     Q_INTERFACES(BasicPlugin)

public:
    void onPluginLoad();

    void postFrame();

    void crearCubo();
    void calcularPosicion(const Object& obj);
public slots:
    void update();

private:
    QOpenGLShaderProgram* program;
    QOpenGLShader* vs, *fs;
    QTimer timer;
    QElapsedTimer elapsedTimer;
    // Add here additional members

    GLuint VAO,VBO;
};
#endif

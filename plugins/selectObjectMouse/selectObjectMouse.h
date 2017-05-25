#ifndef _ANIMATEVERTICESPLUGIN_H
#define _ANIMATEVERTICESPLUGIN_H

#include "basicplugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QElapsedTimer>

// Documentation: http://www.cs.upc.edu/~virtual/Gdocs/interfaces/html/class_basic_plugin.html

class SelectObjectMouse : public QObject, public BasicPlugin
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
    void keyPressEvent(QKeyEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    union MyColor {
        GLubyte rgb[4];
        uint32_t value;
    };

public slots:
    void update();

private:
    QOpenGLShaderProgram *program, *programSelect;
    QOpenGLShader *vs, *fs, *vsSelect, *fsSelect;
    QTimer timer;
    QElapsedTimer elapsedTimer;
    // Add here additional members
    int seleccionat;
    GLuint VAO,VBO;
};
#endif

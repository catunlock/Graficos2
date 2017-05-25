#ifndef _MODELINFO_H
#define _MODELINFO_H

#include "basicplugin.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QElapsedTimer>
#include <QPainter>

// Documentation: http://www.cs.upc.edu/~virtual/Gdocs/interfaces/html/class_basic_plugin.html

class ModelInfo2 : public QObject, public BasicPlugin
{
     Q_OBJECT
#if QT_VERSION >= 0x050000
     Q_PLUGIN_METADATA(IID "BasicPlugin")
#endif
     Q_INTERFACES(BasicPlugin)

public:
    void onPluginLoad();
    void onObjectAdd();
    void postFrame();
    void infoScene();

public slots:

private:
    QOpenGLShaderProgram* program;
    QOpenGLShader* vs, *fs;
    QTimer timer;
    QElapsedTimer elapsedTimer;
    // Add here additional members
    GLuint textureID;

    int numObjetos;
    int nVertices;
    int nFaces;
    int nTriangulos;

    char strBuffObjetos[30];
    char strBuffVertices[30];
    char strBuffFaces[30];
    char strBuffTriangulos[30];

};
#endif

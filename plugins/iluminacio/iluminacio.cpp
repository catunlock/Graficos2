#include "iluminacio.h"
#include <cstdlib>

// Documentation: http://www.cs.upc.edu/~virtual/Gdocs/interfaces/html/class_basic_plugin.html

void Iluminacio::onPluginLoad()
{
    glwidget()->makeCurrent();
    // Carregar shader, compile & link
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("plugins/iluminacio/lighting3.vert");
     cout << "VS log:" << vs->log().toStdString() << endl;
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("plugins/iluminacio/lighting3.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;
    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;    
}

void Iluminacio::preFrame()
{
    //uniform mat4 modelViewProjectionMatrix;
    //uniform mat3 normalMatrix;
    QMatrix4x4 viewMatrix = camera()->viewMatrix();
    QMatrix3x3 normalMatrix = viewMatrix.normalMatrix();

    program->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * viewMatrix;
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    program->setUniformValue("modelViewMatrix", viewMatrix);
    program->setUniformValue("normalMatrix", normalMatrix);

    program->setUniformValue("lightAmbient", QVector4D(0.1, 0.1, 0.1, 1));
    program->setUniformValue("lightDiffuse", QVector4D(1,1,1, 1));
    program->setUniformValue("lightSpecular", QVector4D(1,1,1, 1));
    program->setUniformValue("lightPosition", QVector4D(0, 0, 0, 1));
    program->setUniformValue("matAmbient", QVector4D(1, 0.5, 0.3, 1));
    program->setUniformValue("matDiffuse", QVector4D(1, 0.5, 0.3, 1));
    program->setUniformValue("matSpecular", QVector4D(1,1,1, 1));
    program->setUniformValue("matShininess", 64.0f);
    
}

void Iluminacio::postFrame()
{
    program->release();
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(Iluminacio, Iluminacio)   // plugin name, plugin class
#endif

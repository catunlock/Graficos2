#include "defaultSelector.h"
#include <cstdlib>

// Documentation: http://www.cs.upc.edu/~virtual/Gdocs/interfaces/html/class_basic_plugin.html

void DefaultSelector::onPluginLoad()
{
    glwidget()->makeCurrent();
    // Carregar shader, compile & link
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("plugins/defaultSelector/defaultSelector.vert");
     cout << "VS log:" << vs->log().toStdString() << endl;
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("plugins/defaultSelector/defaultSelector.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;
    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;

    elapsedTimer.start();
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(1000.0f/60.0f);
    
}

void DefaultSelector::update()
{
    timer.start(1000.0f/60.0f);
    glwidget()->update();
}


void DefaultSelector::preFrame()
{
    //uniform mat4 modelViewProjectionMatrix;
    //uniform mat3 normalMatrix;
    QMatrix4x4 viewMatrix = camera()->viewMatrix();
    QMatrix3x3 normalMatrix = viewMatrix.normalMatrix();

    program->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * viewMatrix;
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    program->setUniformValue("normalMatrix", normalMatrix);

    float myTime = elapsedTimer.elapsed()/1000.0f;
    program->setUniformValue("time", myTime);

}

void DefaultSelector::postFrame()
{
    program->release();
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(DefaultSelector, DefaultSelector)   // plugin name, plugin class
#endif

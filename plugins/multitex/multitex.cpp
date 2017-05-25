#include "multitex.h"
#include <QFileDialog>
 
void Multitex::onPluginLoad()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("plugins/multitex/multitex.vert");
     cout << "VS log:" << vs->log().toStdString() << endl;
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("plugins/multitex/multitex.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;
    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;
	
	// Load Texture 1
	g.glActiveTexture(GL_TEXTURE0);
	QString filename = QFileDialog::getOpenFileName(0, "Open Image", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
	QImage img0(filename);	
	QImage im0 = img0.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
	g.glGenTextures( 1, &textureId0);
	g.glBindTexture(GL_TEXTURE_2D, textureId0);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);

	// Load Texture 2
	g.glActiveTexture(GL_TEXTURE1);
	QString filename2 = QFileDialog::getOpenFileName(0, "Open Image 2", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
	QImage img1(filename2);	
	QImage im1 = img1.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
	g.glGenTextures( 1, &textureId1);
	g.glBindTexture(GL_TEXTURE_2D, textureId1);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);
}

void Multitex::preFrame() 
{
    GLWidget &g = *glwidget();
    g.makeCurrent();

    // bind shader and define uniforms
    program->bind();
    program->setUniformValue("sampler0", 0);  // texture unit del primer sampler 
    program->setUniformValue("sampler1", 1);  // texture unit del segon  sampler 
    program->setUniformValue("radius", float(scene()->boundingBox().radius()));  // radi d'una esfera que engloba l'escena
    program->setUniformValue("modelViewProjectionMatrix", g.camera()->projectionMatrix() * g.camera()->viewMatrix());
    // bind textures
    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, textureId0);
    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, textureId1);
}

void Multitex::postFrame() 
{
    GLWidget &g = *glwidget();
    g.makeCurrent();

    // unbind shader
    program->release();
    // unbind textures
    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    g.glActiveTexture(GL_TEXTURE1);
    g.glBindTexture(GL_TEXTURE_2D, 0);
}


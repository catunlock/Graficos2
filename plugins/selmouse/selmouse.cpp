#include "selmouse.h"
#include "glwidget.h"
#include <iostream>

void chk(GLWidget &g, string msg) {
 GLuint err = g.glGetError();
 if (err == GL_NO_ERROR) return;
 cout << "error a " << msg << endl;
}

void Selmouse::setSelectedObject(int selected) {
    GLWidget &g = *glwidget();
    g.makeCurrent();
    if (selected<0 || selected>=(int)g.scene()->objects().size()) selected=-1;
    g.scene()->setSelectedObject(selected);
}

void encodeID(int index, GLubyte *color) {
    color[0]=color[1]=color[2]=index;
}

int decodeID(GLubyte *color) {
    if (color[0]==255) return -1;
    return color[0];
}

void Selmouse::mouseReleaseEvent (QMouseEvent *e){
    if (!(e->button()&Qt::LeftButton)) return;          // boto esquerre del ratoli
    if (e->modifiers()&(Qt::ShiftModifier)) return;     // res de tenir shift pulsat
    if (!(e->modifiers()&Qt::ControlModifier)) return;  // la tecla control ha d'estar pulsada
    
    GLWidget &g = *glwidget();
    g.makeCurrent();
    
    g.glClearColor(1, 1, 1, 1);                           // esborrar els buffers amb un color de fons únic (blanc)
    g.glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    progCol->bind();                               // activar (bind) el shader program amb el VS+FS d’abans
    drawDrawColorScene();
    progCol->release();
    
    int x=e->x();                                       // llegir el color del buffer de color sota la posició del cursor
    int y=g.height() - e->y();
    
    GLubyte read[4];
    
    g.glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, read);
    
    cout << x << " " << y << " " << (int)read[0] << endl;
    
    int seleccio=decodeID(&read[0]);                    // obtenir l'identificador de l'objecte corresponent i, 
    setSelectedObject(seleccio);                        // si no és color de fons, establir l'objecte seleccionat
    
    glwidget()->update();                             // cridar a updateGL per tal que es repinti l'escena
}

void Selmouse::drawDrawColorScene() {
    GLWidget &g = *glwidget();
    g.makeCurrent();
    // enviar la modelViewProjectionMatrix, i el color identificador dels objectes
    QMatrix4x4 MVP=g.camera()->projectionMatrix()*g.camera()->viewMatrix();
    progCol->setUniformValue("viewProjectionMatrix", MVP);
    for (unsigned int i=0; i<scene()->objects().size(); ++i) {
	cout << "pinta " << i << endl;
	GLubyte color[4];
	encodeID(i, color);
	progCol->setUniformValue("color", QVector4D(color[0]/255., color[1]/255., color[2]/255., 1));
	drawPlugin()->drawObject(i);
    }
}

void Selmouse::onPluginLoad(){
    GLWidget &g = *glwidget();
    g.makeCurrent();
    vsBox=new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsBox->compileSourceFile(QString(getenv ("VIEWER"))+"plugins/selmouse/selmouseBox.vert");
    cout << "VS log:" << vsBox->log().toStdString() << endl;
    fsBox=new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsBox->compileSourceFile(QString(getenv ("VIEWER"))+"plugins/selmouse/selmouseBox.frag");
    cout << "FS log:" << fsBox->log().toStdString() << endl;
    progBox=new QOpenGLShaderProgram(this);
    progBox->addShader(vsBox);
    progBox->addShader(fsBox);
    progBox->link();
    qDebug() << progBox->log() << endl;
    // Carregar shader, compile & link (escena colors unics)
    vsCol=new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsCol->compileSourceFile(QString(getenv ("VIEWER"))+"plugins/selmouse/selmouseCol.vert");
    cout << "VS log:" << vsCol->log().toStdString() << endl;
    fsCol=new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsCol->compileSourceFile(QString(getenv ("VIEWER"))+"plugins/selmouse/selmouseCol.frag");
    cout << "FS log:" << fsCol->log().toStdString() << endl;
    progCol=new QOpenGLShaderProgram(this);
    progCol->addShader(vsCol);
    progCol->addShader(fsCol);
    progCol->link();
    qDebug() << progCol->log() << endl;
}

void Selmouse::createBuffers(){
    GLWidget &g = *glwidget();
    g.makeCurrent();
    Point min, max;
    int selected = g.scene()->selectedObject();
    if (selected != -1){
	g.scene()->objects()[selected].computeBoundingBox();
	chk (g,"computeBoundingBox");
	Box box = g.scene()->objects()[selected].boundingBox();
	min = box.min();
	max = box.max();
    }
    else {
	min.setX(0.0);
	min.setY(0.0);
	min.setZ(0.0);
	max.setX(0.0);
	max.setY(0.0);
	max.setZ(0.0);
    }
    float distX = max.x() - min.x();
    float distY = max.y() - min.y();
    float distZ = max.z() - min.z();

    Point center = (max+min)/2;

    float verts[] = {
	-0.5, -0.5, -0.5,
	-0.5, -0.5, 0.5,
	-0.5, 0.5, -0.5,
	-0.5, 0.5, 0.5,
	0.5, -0.5, -0.5,
	0.5, -0.5, 0.5,
	0.5, 0.5, -0.5,
	0.5, 0.5, 0.5};
    for (int i = 0; i < 24; i+=3){
	cube[i] = distX*verts[i] + center.x();
	cube[i + 1] = distY*verts[i + 1] + center.y();
	cube[i + 2] = distZ*verts[i + 2] + center.z();
    }
    unsigned int indices[] = {
	0, 1,
	0, 2,
	1, 3,
	2, 3,
	0, 4,
	1, 5,
	3, 7,
	2, 6,
	4, 5,
	5, 7,
	4, 6,
	6, 7};


    g.glGenVertexArrays(1, &VAO);
    chk (g,"glGenVertexArrays &VAO");
    g.glBindVertexArray(VAO);
    chk (g,"glBindVertexArray VAO");
    
    GLuint coordBufferID;
    g.glGenBuffers(1, &coordBufferID);
    chk (g,"glGenBuffers vertexs");

    GLuint indexBufferID;
    g.glGenBuffers(1, &indexBufferID);
    chk (g,"glGenBuffers indexs");
    
    g.glBindBuffer(GL_ARRAY_BUFFER, coordBufferID);
    chk (g,"bind vertexs");
    g.glBufferData(GL_ARRAY_BUFFER, 8*sizeof(*cube)*3, &cube[0], GL_STATIC_DRAW);
    chk (g,"bufferdata vertexs");
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);  // VAO
    chk (g,"glVertexAttribPointer vertexs");
    g.glEnableVertexAttribArray(0);
    chk (g,"enable vertexs");

    g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    chk (g,"bind indexs");
    g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24*sizeof(*indices), &indices[0], GL_STATIC_DRAW);
    chk (g,"bufferdata indexs");
  
    g.glBindVertexArray(0);
}

void Selmouse::drawSelectedBox(){
    GLWidget &g = *glwidget();
    g.makeCurrent();
    int seleccionat=scene()->selectedObject();
    if (seleccionat>=0 && seleccionat<(int)scene()->objects().size()) {
	createBuffers();
	
	// establir modelViewProjection
	QMatrix4x4 MVP=g.camera()->projectionMatrix()*g.camera()->viewMatrix();
	progBox->setUniformValue("viewProjectionMatrix", MVP);

	g.glBindVertexArray(VAO);
	g.glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, (GLvoid*) 0);
	g.glBindVertexArray(0);
    }
}

void Selmouse::postFrame ()
{   
    GLWidget &g = *glwidget();
    g.makeCurrent();
  
    progBox->bind();
    drawSelectedBox();
    progBox->release();
}


#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(selmouse, Selmouse)   // plugin name, plugin class
#endif


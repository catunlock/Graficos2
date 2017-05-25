#include "selectObjectKeyboard.h"
#include <cstdlib>
#include <vector>

// Documentation: http://www.cs.upc.edu/~virtual/Gdocs/interfaces/html/class_basic_plugin.html

void SelectObjectKeyboard::onPluginLoad()
{
    glwidget()->makeCurrent();
    // Carregar shader, compile & link
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile("plugins/selectObjectKeyboard/selectObjectKeyboard.vert");
     cout << "VS log:" << vs->log().toStdString() << endl;
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile("plugins/selectObjectKeyboard/selectObjectKeyboard.frag");
    cout << "FS log:" << fs->log().toStdString() << endl;
    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;

    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    crearCubo();

    //scene()->setSelectedObject(0);
    //seleccionat = scene()->selectedObject();
    qDebug() << scene()->selectedObject();
    seleccionat = 0;
}

void SelectObjectKeyboard::crearCubo()
{
    GLWidget &g = *glwidget();
    g.makeCurrent();
    
    float vertices[] = {
        //FRONT
        -1.0f, -1.0f, 1.0f, // 1
         1.0f, -1.0f, 1.0f, // 2
        -1.0f,  1.0f, 1.0f, // 3
         1.0f,  1.0f, 1.0f, // 4

        //BACK
        -1.0f, -1.0f, -1.0f, // 5
         1.0f, -1.0f, -1.0f, // 6
        -1.0f,  1.0f, -1.0f, // 7
         1.0f,  1.0f, -1.0f, // 8
    };

    float normals[] = {
        //FRONT
        -1.0f, -1.0f, 1.0f, // 1
         1.0f, -1.0f, 1.0f, // 2
        -1.0f,  1.0f, 1.0f, // 3
         1.0f,  1.0f, 1.0f, // 4

        //BACK
        -1.0f, -1.0f, -1.0f, // 5
         1.0f, -1.0f, -1.0f, // 6
        -1.0f,  1.0f, -1.0f, // 7
         1.0f,  1.0f, -1.0f, // 8
    };

    int indices[] = {
        // FRONT
        0,3,2,
        0,1,3,

        6,4,5,
        5,7,6,

        6,4,0,
        0,2,6,

        // Right
        3,1,5,
        5,7,3,

        2,6,7,
        7,3,2,

        0,4,5,
        5,1,0
    };

    GLuint VBO_Vertices, VBO_Indices, VBO_Normales;
    g.glGenVertexArrays(1, &VAO);
    g.glBindVertexArray(VAO);

    g.glGenBuffers(1, &VBO_Vertices);
    g.glGenBuffers(1, &VBO_Indices);
    g.glGenBuffers(1, &VBO_Normales);

    // Vertices
    g.glBindBuffer(GL_ARRAY_BUFFER, VBO_Vertices);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 24, &vertices[0], GL_STATIC_DRAW);
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(0);
    
    // Normals
    g.glBindBuffer(GL_ARRAY_BUFFER, VBO_Normales);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*24, &normals[0], GL_STATIC_DRAW);
    g.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);  // VAO
    g.glEnableVertexAttribArray(1);

    // Indices
    g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_Indices);
    g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*36, &indices[0], GL_STATIC_DRAW);

    g.glBindVertexArray(0);
    g.glBindBuffer(GL_ARRAY_BUFFER, 0);
    g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SelectObjectKeyboard::update()
{
    glwidget()->update();
}

void SelectObjectKeyboard::calcularPosicion(const Object& obj) 
{
    Box boundingBox = obj.boundingBox();
    Point pMin = boundingBox.min();
    Point pMax = boundingBox.max();
    Point pCenter = boundingBox.center();

    QVector3D qCenter(pCenter.x(), pCenter.y(), pCenter.z());
    QVector3D qScale(pMax.x() - pMin.x(), pMax.y() - pMin.y(), pMax.z() - pMin.z());

    program->setUniformValue("center", qCenter);
    program->setUniformValue("scale", qScale/2.0f);
}

void SelectObjectKeyboard::keyPressEvent(QKeyEvent *event)
{
    int nObj = event->key() - 0x30;

    qDebug() << "Tecla: " << nObj << "\n";

    if (nObj >= 0 && nObj <= 9 && nObj < scene()->objects().size()) {
        seleccionat = nObj;
        glwidget()->update();
    }
    else {
        seleccionat = -1;
        glwidget()->update();
    }
}

void SelectObjectKeyboard::postFrame()
{
    qDebug() << "Seleccionat:" << seleccionat;
    if (seleccionat != -1) {
        GLWidget &g = *glwidget();
    
        //uniform mat4 modelViewProjectionMatrix;
        //uniform mat3 normalMatrix;
        QMatrix4x4 viewMatrix = camera()->viewMatrix();
        QMatrix3x3 normalMatrix = viewMatrix.normalMatrix();

        program->bind();
        QMatrix4x4 MVP = camera()->projectionMatrix() * viewMatrix;
        program->setUniformValue("modelViewProjectionMatrix", MVP);
        program->setUniformValue("normalMatrix", normalMatrix);
        g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        g.makeCurrent();

        const Object& obj = scene()->objects()[seleccionat];

        calcularPosicion(obj);

        g.glBindVertexArray(VAO);
        //g.glBindVertexArray(0);
        g.glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, (GLvoid*) 0);

        g.glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        program->release();
    }
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(SelectObjectKeyboard, SelectObjectKeyboard)   // plugin name, plugin class
#endif

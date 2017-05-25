#include "ModelInfo.h"
#include <cstdlib>

// Documentation: http://www.cs.upc.edu/~virtual/Gdocs/interfaces/html/class_basic_plugin.html

void ModelInfo::onPluginLoad()
{
    infoScene();
}

void ModelInfo::onObjectAdd()
{
    infoScene();
}

void ModelInfo::infoScene() {
    int numObjetos = scene()->objects().size();
    int nFaces = 0;
    int nVertices = 0;
    int nTriangulos = 0;
    for (int i = 0; i < numObjetos; ++i) {
        Object& objeto = scene()->objects()[i];
        nFaces += objeto.faces().size();
        nVertices += objeto.vertices().size();
        for (Face f : objeto.faces()) {
            if (f.numVertices() == 3) ++nTriangulos;
        }
    }

    cout << "Objetos totales: " << numObjetos << endl;
    cout << "\tPoligonos: " << nFaces << endl;
    cout << "\tVertices: " << nVertices << endl;
    cout << "\t% de Tringulos: " << (float(nTriangulos)/float(nFaces)) * 100.0f << endl;
}


#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ModelInfop, ModelInfo)   // plugin name, plugin class
#endif

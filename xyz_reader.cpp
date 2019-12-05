#include "xyz_reader.h"

#include <osg/Geometry>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osgUtil/DelaunayTriangulator>
#include <osgViewer/Viewer>


#define MAX_VERTICES 10000
#define Z_FACTOR 20

namespace pc2m {
    XyzReader::XyzReader(const char * path) {

        vertices = new osg::Vec3Array();

        std::ifstream input(path);
        int i = 0;
        if (input.is_open()) {
            for(std::string line; std::getline(input, line); ) {
                std::istringstream in(line);
                std::string type;
                float x, y, z;
                in >> x >> y >> z;
                z *= Z_FACTOR;
                //std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
                vertices->push_back(osg::Vec3(x,y,z));
                if (++i == MAX_VERTICES) {
                    break;
                }
            }
            input.close();
            std::cout << "Size of array after loading: " << vertices->size() << std::endl;
        } else {
            std::cerr << "Error opening xyz file" << std::endl;
        }
    }

    XyzReader::~XyzReader() {

    }
}

void usage(const char *self) {
    std::cout << "Usage : " << self << " <filename>" << std::endl;
}

int main(int argc, char **argv) {

    if ((argc != 2) || (! std::filesystem::exists(argv[1]))) {
        usage(argv[0]);
        return 0;
    }

    pc2m::XyzReader r(argv[1]);

    osg::ref_ptr<osgUtil::DelaunayTriangulator> dt = new osgUtil::DelaunayTriangulator;
    dt->setInputPointArray( r.getVertices() );
    dt->setOutputNormalArray( new osg::Vec3Array );
    std::cout << "Calling triangulate() ..." << std::endl;
    dt->triangulate();
    std::cout << "Triangulation done." << std::endl;

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;
    geometry->setVertexArray( dt->getInputPointArray() );
    geometry->setNormalArray( dt->getOutputNormalArray() );
    geometry->setNormalBinding( osg::Geometry::BIND_PER_PRIMITIVE_SET );
    geometry->addPrimitiveSet( dt->getTriangles() );

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( geometry.get() );

    osgViewer::Viewer viewer;
    viewer.setSceneData( geode.get() );
    return viewer.run();

    return 0;
}

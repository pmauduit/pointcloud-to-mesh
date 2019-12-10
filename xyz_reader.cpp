#include "xyz_reader.h"

#include <osg/Geometry>
#include <osg/Geode>
#include <osg/Camera>
#include <osgDB/ReadFile>
#include <osgUtil/DelaunayTriangulator>
#include <osgViewer/Viewer>
#include <osgGA/UFOManipulator>


#define Z_FACTOR 1.0

namespace pc2m {
    XyzReader::XyzReader(const char * path) {

        vertices = new osg::Vec3Array();
        colors = new osg::Vec4Array();

        osg::Vec4 black = osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f);
        osg::Vec4 darkblue = osg::Vec4(0.05f, 0.0f, 0.34f, 1.0f);
        osg::Vec4 blue = osg::Vec4(0.50f, 0.42f, 0.94f, 1.0f);
        osg::Vec4 yellow = osg::Vec4(0.76f, 0.76f, 0.22f, 1.0f);
        osg::Vec4 lightgreen = osg::Vec4(0.34f, 0.92f, 0.42f, 1.0f);
        osg::Vec4 darkgreen = osg::Vec4(0.69f, 0.35f, 0.0f, 1.0F);

        std::ifstream input(path);
        if (input.is_open()) {
            std::cout << "Loading " << path << std::endl;
            for(std::string line; std::getline(input, line); ) {
                std::istringstream in(line);
                std::string type;
                float x, y, z;
                in >> x >> y >> z;
                if ((z > -50) && (z <= -40)) {
                    colors->push_back(black);
                } else if ((z > -40) && (z <= -35)) {
                    colors->push_back(darkblue);
                } else if ((z > -35) && (z <= -28)) {
                    colors->push_back(blue);
                } else if ((z > -28) && (z <= -22)) {
                    colors->push_back(yellow);
                } else if ((z > -22) && (z <= -18)) {
                    colors->push_back(lightgreen);
                } else {
                    colors->push_back(darkgreen);
                }
                z *= Z_FACTOR;
                vertices->push_back(osg::Vec3(x,y,z));
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

    if ((argc != 2) || (! std::experimental::filesystem::exists(argv[1]))) {
        usage(argv[0]);
        return 0;
    }

    pc2m::XyzReader r(argv[1]);

    osg::Vec3Array * vertices = r.getVertices();
    // osg::ref_ptr<osg::Vec3Array> current_sample = new osg::Vec3Array;
    // osg::ref_ptr<osg::Vec3Array> total_triangles = new osg::Vec3Array;

    // for (int i = 0 ; i < vertices->size(); ++i) {
    //   current_sample << vertices[i];
    //   // batch of 1k points to triangulate (or the end of the array)
    //   if (i % 1000) || (i == vertices->size() - 1) {
    //     osg::ref_ptr<osgUtil::DelaunayTriangulator> dt = new osgUtil::DelaunayTriangulator;
    //     dt->setInputPointArray( current_sample );
    //     dt->setOutputNormalArray( new osg::Vec3Array );
    //     std::cout << "Calling triangulate() ..." << std::endl;
    //     dt->triangulate();
    //     std::cout << "Triangulation done." << std::endl;
    //     total_triangles << dt->getTriangles();
    //     current_sample = new osg::Vec3Array;
    //   }
    // }


    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;

    geometry->setColorArray(r.getColors(), osg::Array::BIND_PER_VERTEX);

    geometry->setVertexArray( vertices );
    //geometry->setNormalArray( dt->getOutputNormalArray() );
    geometry->setNormalArray(vertices,  osg::Array::BIND_OVERALL);

    geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, vertices->size()));

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( geometry.get() );

    osgViewer::Viewer viewer;
    viewer.setSceneData( geode.get() );

    osg::ref_ptr< osg::Light > light = new osg::Light;
    light->setAmbient(osg::Vec4(1.0f,1.0f,1.0f,1.0f));
    viewer.setLight(light);



    osg::ref_ptr< osgGA::UFOManipulator > manipulator = new osgGA::UFOManipulator( );
	viewer.setCameraManipulator( manipulator  );

    osg::Camera * camera = viewer.getCamera();
    camera->setClearColor(osg::Vec4(0.094f, 0.247f, 0.539f, 0.1f));

    return viewer.run();

    return 0;
}

#include "pointscloud_reader.h"

void usage(const char *self) {
    std::cout << "Usage : " << self << " <filename>" << std::endl;
}

int main(int argc, char **argv) {

    if ((argc != 2) || (! std::experimental::filesystem::exists(argv[1]))) {
        usage(argv[0]);
        return 0;
    }

    pc2m::PointsCloudReader r;

    std::string inputPath(argv[1]);
    // poorly deducing the format
    if ((strcasestr(argv[1], ".laz") != NULL)
        || (strcasestr(argv[1], ".las") != NULL)) {
          std::cout << "LAS/LAZ format detected." << std::endl;
          return 0;
    } else {
        std::cout << "Trying to load the file as xyz." << std::endl;

        r.xyzLoad(inputPath);
    }


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

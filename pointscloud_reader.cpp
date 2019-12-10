#include "pointscloud_reader.h"

namespace pc2m {

    PointsCloudReader::PointsCloudReader() {
        vertices = new osg::Vec3Array();
        colors = new osg::Vec4Array();
    }

    void PointsCloudReader::xyzLoad(const std::string & path) {

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

    PointsCloudReader::~PointsCloudReader() {

    }
}



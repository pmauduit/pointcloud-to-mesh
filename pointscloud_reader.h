#ifndef __POINTS_CLOUD_READER_H
#define __POINTS_CLOUD_READER_H

#include <fstream>
#include <experimental/filesystem>
#include <string>

#include <osg/Camera>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osgUtil/Tessellator>
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgGA/UFOManipulator>

#include <osgUtil/DelaunayTriangulator>


#define Z_FACTOR 1.0


namespace pc2m  {

  class PointsCloudReader {
    private:
        osg::ref_ptr<osg::Vec3Array> vertices;
        osg::ref_ptr<osg::Vec4Array> colors;

    public:
     PointsCloudReader();
     void xyzLoad(const std::string &);
     void lasLoad(const std::string &);
     osg::Vec3Array * getVertices() { return vertices; }
     osg::Vec4Array * getColors() { return colors; }
     ~PointsCloudReader();
  };
}


#endif // __POINTS_CLOUD_READER_H

#ifndef __XYZ_READER_H
#define __XYZ_READER_H

#include <fstream>
#include <filesystem>
#include <string>

#include <gdal/gdal_priv.h>
#include <gdal/cpl_conv.h>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_core.h>
#include <gdal/ogr_feature.h>
#include <gdal/ogr_geometry.h>

#include <osg/Geometry>
#include <osg/Geode>
#include <osg/LineWidth>
#include <osgUtil/Tessellator>
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgGA/TerrainManipulator>

namespace pc2m  {

  class XyzReader {
    private:
        osg::ref_ptr<osg::Vec3Array> vertices;

    public:
     XyzReader(const char * path);
     osg::Vec3Array * getVertices() { return vertices; }
     ~XyzReader();
  };
}


#endif // __XYZ_READER_H

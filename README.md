# Purpose

This is meant to read a `xyz` file, like the ones provided by the SHOM here:

http://services.data.shom.fr/public/download/prepackageGroup/L3D_LIDAR_CORSE_2018_v20190430_PACK_DL/prepackage/1240_6165/file/1240_6165.7z

And triangulates against the dataset to generate a mesh from it.

# Setting things up

If you want to open a LAS/LAZ file (and if you want to compile the code anyway), you will need to setup the PDAL library, as done in here:

https://github.com/pmauduit/lopocs/blob/docker-compo/docker/lopocs/Dockerfile#L7-L21

# Results

Here is a screenshot when launched on the LiDAR files provided by [SNCF OpenData](https://ressources.data.sncf.com/explore/dataset/nuage-points-3d/table/)


![](https://raw.githubusercontent.com/pmauduit/pointcloud-to-mesh/master/pc2m.png)

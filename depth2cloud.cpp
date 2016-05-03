#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;



pcl::PointCloud<pcl::PointXYZRGB>::Ptr depth2cloud( cv::Mat rgb_image, cv::Mat depth_image )
{
  float f = 570.3;
  float cx = 320.0, cy = 240.0;

  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_ptr( new pcl::PointCloud<pcl::PointXYZRGB> () );
  cloud_ptr->width  = rgb_image.cols;
  cloud_ptr->height = rgb_image.rows;
  cloud_ptr->is_dense = false;

  for ( int y = 0; y < rgb_image.rows; ++ y ) {
    for ( int x = 0; x < rgb_image.cols; ++ x ) {
      pcl::PointXYZRGB pt;
      if ( depth_image.at<unsigned short>(y, x) != 0 )
      {
          pt.z = depth_image.at<unsigned short>(y, x)/1000.0;
          pt.x = (x-cx)*pt.z/f;
          pt.y = (y-cy)*pt.z/f;
          pt.r = rgb_image.at<cv::Vec3b>(y, x)[2];
          pt.g = rgb_image.at<cv::Vec3b>(y, x)[1];
          pt.b = rgb_image.at<cv::Vec3b>(y, x)[0];
          cloud_ptr->points.push_back( pt );
      }
      else
      {
          pt.z = 0;
          pt.x = 0;
          pt.y = 0;
          pt.r = 0;
          pt.g = 0;
          pt.b = 0;
          cloud_ptr->points.push_back( pt );
      }
    }
  }
  return cloud_ptr;
}

int main(int argc,char* argv[])
{
    cv::Mat depth;
    cv::Mat image;
    image=cv::imread(argv[1]);
    depth=cv::imread(argv[2],IMREAD_ANYDEPTH);
    string pcdName(argv[3]);
    if(!image.data||!depth.data)        // 判断图片调入是否成功
      return -1;        // 调入图片失败则退出

   pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);

    cloud=depth2cloud(image,depth);

    pcl::io::savePCDFileASCII(pcdName,*cloud);

    return 0;
}

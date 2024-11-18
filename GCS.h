#include "lasreader.hpp"
#include "laswriter.hpp"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <pcl/filters/crop_box.h>
#include <fstream>
#include <iomanip>


class GCS
{
public:
	pcl::PointCloud<pcl::PointXYZ>::Ptr readLasData(const char* filename);
	double euclideanDistance(double x1, double y1, double x2, double y2);
	pcl::PointCloud<pcl::PointXYZ>::Ptr samplePoint(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, const Eigen::Vector2f & begin_point, const Eigen::Vector2f & end_point, float distance);
	std::vector<std::pair<float, float>> getHeight(const pcl::PointCloud<pcl::PointXYZ>::Ptr  cloud_sampled, const Eigen::Vector2f & begin_point, const Eigen::Vector2f & end_point,int num_point);
	//将点云转换到断面坐标系上
	pcl::PointCloud<pcl::PointXYZ>::Ptr projrctPoint(pcl::PointCloud<pcl::PointXYZ>::Ptr samplecloud, const Eigen::Vector2f & begin_point, const Eigen::Vector2f & end_point);
	void txtWrite(const char* filename, const std::string& survey_area, const std::string& coordinate_system, const std::string& zone_band, const std::string& elevation_system, std::vector<std::pair<float, float>> results);
};


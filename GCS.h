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
	GCS();
	void readLasData(const char* filename);
	double euclideanDistance(double x1, double y1, double x2, double y2);
	void samplePoint(float distance);
	void getHeight(int num_point);
	//将点云转换到断面坐标系上
	pcl::PointCloud<pcl::PointXYZ>::Ptr projrctPoint(pcl::PointCloud<pcl::PointXYZ>::Ptr samplecloud, const Eigen::Vector2f & begin_point, const Eigen::Vector2f & end_point);
	void txtWrite(const char* filename, const std::string& survey_area, const std::string& coordinate_system, const std::string& zone_band, const std::string& elevation_system);
	pcl::PointCloud<pcl::PointXYZ>::Ptr getPcdPointCloud();
	pcl::PointCloud<pcl::PointXYZ>::Ptr getPcdSampledPointCloud();
	std::vector<std::pair<float, float>> getResults();
private:
	pcl::PointCloud<pcl::PointXYZ>::Ptr m_pcdPointCloud;
	pcl::PointCloud<pcl::PointXYZ>::Ptr m_pcdSampledPointCloud;
	std::vector<std::pair<float, float>> m_results;
};


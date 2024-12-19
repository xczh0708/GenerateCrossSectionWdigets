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
#include <pcl/kdtree/kdtree_flann.h> 
//提取线用到的点类型

using Point = std::pair<float, float>;
struct CenterLine {
	Point bengin_point;
	Point end_point;
	float height;
};
//绘制dxf文件用到的点类型
struct PointDistance {
	pcl::PointXYZ point;
	float distance;
};
class GCS
{
public:
	GCS();
	void readLasData(const char* filename);
	double euclideanDistance(double x1, double y1, double x2, double y2);
	/*void samplePoint(float distance, const Point& p1, const Point& p2);*/
	void getHeight(float distance,int num_point);
	//将点云转换到断面坐标系上
	pcl::PointCloud<pcl::PointXYZ>::Ptr projrctPoint(pcl::PointCloud<pcl::PointXYZ>::Ptr samplecloud, const Eigen::Vector2f & begin_point, const Eigen::Vector2f & end_point);
	void txtWrite(const char* foldername, const std::string& survey_area, const std::string& coordinate_system, const std::string& zone_band, const std::string& elevation_system);
	pcl::PointCloud<pcl::PointXYZ>::Ptr getPcdPointCloud();
	//pcl::PointCloud<pcl::PointXYZ>::Ptr getPcdSampledPointCloud();
	std::vector<std::vector<std::pair<float, float>>> getResults();
	void getCenterLines(const std::vector<Point>& centerline, float targetDistance, float reslong);
	std::pair<Point, Point> calculatePerpendicularLine(const Point& p1, const Point& p2, const Point& interpolatedPoint, float distance = 100.0f);
private:
	pcl::PointCloud<pcl::PointXYZ>::Ptr m_pcdPointCloud;
	//pcl::PointCloud<pcl::PointXYZ>::Ptr m_pcdSampledPointCloud;
	std::vector<std::vector<std::pair<float, float>>> m_results; //储存多条提取线的结果
	std::vector<CenterLine> m_initial_extraction_line;
	std::vector<CenterLine> m_final_extraction_line;
};


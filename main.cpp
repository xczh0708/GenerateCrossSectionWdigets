#include "GenerateCrossSectionWdigets.h"
#include <QtWidgets/QApplication>
#include"GCS.h"
#include"CADRW.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GenerateCrossSectionWdigets w;
    w.show();
    return a.exec();


	//liadr部分测试
	//GCS test;
	//pcl::PointCloud<pcl::PointXYZ>::Ptr  cloud(new pcl::PointCloud<pcl::PointXYZ>);
	//pcl::PointCloud<pcl::PointXYZ>::Ptr  sampled_cloud(new pcl::PointCloud<pcl::PointXYZ>);
	//pcl::PointCloud<pcl::PointXYZ>::Ptr  projected_sampled_cloud(new pcl::PointCloud<pcl::PointXYZ>);
	//cloud = test.readLasData("D:/Users/xia/Desktop/yanqihu_file/水利工程断面/中铁水利/4.las");
	//pcl::io::savePCDFileASCII("D:/Users/xia/Desktop/output1.pcd", *cloud);
	////测试点 需要更改为CAD文件读取的结果
	//Eigen::Vector2f begin_point(524922.375000f, 3199527.250000f);
	//Eigen::Vector2f end_point(524884.812500f, 3199537.000000f);
	//sampled_cloud = test.samplePoint(cloud, begin_point, end_point,0.01);
	//pcl::io::savePCDFileASCII("D:/Users/xia/Desktop/output001.pcd", *sampled_cloud);
	//std::vector<std::pair<float, float>> results = test.getHeight(sampled_cloud, begin_point, end_point, 20);
	//test.txtWrite("D:/Users/xia/Desktop/output.txt","测区名称","坐标系名称","度带数","高程系统名称", results);
	//projected_sampled_cloud = test.projrctPoint(sampled_cloud, begin_point, end_point);
	//pcl::io::savePCDFileASCII("D:/Users/xia/Desktop/output3.pcd", *projected_sampled_cloud);
	////CAD部分测试
	//dxfRW dxf("file.dxf");
	//CADRW writer(dxf, results);
	//dxf.write(&writer, DRW::Version::AC1027, false);

}

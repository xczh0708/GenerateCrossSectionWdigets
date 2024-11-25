#include "GCS.h"
struct PointDistance {
	pcl::PointXYZ point;
	float distance;
};
bool compareDistance(const PointDistance& a, const PointDistance& b) {
	return a.distance < b.distance;
}//����getHeight���вɵ�ıȽϷ����ͽṹ��

//��ȡlas����
pcl::PointCloud<pcl::PointXYZ>::Ptr GCS::readLasData(const char* filename)
{
	//��las�ļ�
	LASreadOpener lasrReadOpener;
	lasrReadOpener.set_file_name(filename);//�Լ���las�ļ���ַ
	LASreader* lasReader = lasrReadOpener.open(false);
	size_t count = lasReader->header.number_of_point_records;
	//����pcl��ʽ
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);//ע���Լ���las�ļ���ʽ������ɫ��ʹ��PointXYZRGB
	cloud->width = count;
	cloud->height = 1;
	cloud->resize(count);
	cloud->is_dense = false;

	//��ȡlas�ļ�ƫ��ֵ������ֵ
	//double xOffset = lasReader->header.x_offset;// ƫ��ֵ
	//double yOffset = lasReader->header.y_offset;
	//double zOffset = lasReader->header.z_offset;
	//double scaleX = lasReader->header.x_scale_factor;
	//double scaleY = lasReader->header.y_scale_factor;
	//double scaleZ = lasReader->header.z_scale_factor;
	//std::cout << " scaleX: "<<scaleX << " scaleY: " << scaleY << " scaleZ: " << scaleZ << std::endl;
	//std::cout << " xOffset: " << xOffset << " yOffset: " << yOffset << " zOffset: " << zOffset << std::endl;
	//��ȡ��
	size_t j = 0;
	while (lasReader->read_point() && j < count)
	{
		lasReader->compute_coordinates();
		cloud->points[j].x = lasReader->get_x();
		cloud->points[j].y = lasReader->get_y();
		cloud->points[j].z = lasReader->get_z();
		/*cloud->points[j].x = (lasReader->point.get_x() * scaleX) + xOffset;
		cloud->points[j].y = (lasReader->point.get_y() * scaleY) + yOffset;
		cloud->points[j].z = (lasReader->point.get_z() * scaleZ) + zOffset;*/
		//cloud->points[j].r = lasReader->point.get_R();
		//cloud->points[j].g = lasReader->point.get_G();
		//cloud->points[j].b = lasReader->point.get_B();	
		++j;
	}
	return cloud;
}
//��������֮�����
double GCS::euclideanDistance(double x1, double y1, double x2, double y2)
{
	return std::sqrt(std::pow(x1 - x2, 2) + std::pow( y1 - y2, 2));
}
//�����߶���Χ����
pcl::PointCloud<pcl::PointXYZ>::Ptr GCS::samplePoint(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, const Eigen::Vector2f & begin_point, const Eigen::Vector2f & end_point, float distance)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr  cloud_sampled(new pcl::PointCloud<pcl::PointXYZ>);
	Eigen::Vector2f delta = end_point - begin_point;//�����߶��ϵķ�������
	Eigen::Vector2f perpendicular_direction(-delta[1], delta[0]);//��ֱ���߷�������
	float length = perpendicular_direction.norm();  // ������ģ
	Eigen::Vector2f unit_perpendicular_direction = perpendicular_direction / length; //���㴹ֱ���������ĵ�λ��
	//������Χ��ȡ
	Eigen::Vector2f point1 = begin_point + distance * unit_perpendicular_direction;
	Eigen::Vector2f point2 = begin_point - distance * unit_perpendicular_direction;
	Eigen::Vector2f point3 = end_point + distance * unit_perpendicular_direction;
	Eigen::Vector2f point4 = end_point - distance * unit_perpendicular_direction;
	float min_x = std::min({ point1.x(), point2.x(), point3.x(), point4.x() });
	float max_x = std::max({ point1.x(), point2.x(), point3.x(), point4.x() });
	float min_y = std::min({ point1.y(), point2.y(), point3.y(), point4.y() });
	float max_y = std::max({ point1.y(), point2.y(), point3.y(), point4.y() });
	//ͨ���߽����вü�
	pcl::CropBox<pcl::PointXYZ> crop_box;
	crop_box.setMin(Eigen::Vector4f(min_x, min_y, -std::numeric_limits<float>::infinity(), 1.0f));  // ������С��
	crop_box.setMax(Eigen::Vector4f(max_x, max_y, std::numeric_limits<float>::infinity(), 1.0f));     // ��������
	crop_box.setInputCloud(cloud);
	crop_box.filter(*cloud_sampled);

	//pcl::PointCloud<pcl::PointXYZ>::Ptr Pointcloud(new pcl::PointCloud<pcl::PointXYZ>);

	//// ��begin_pointת��Ϊpcl::PointXYZ����ӵ�����
	//pcl::PointXYZ pcl_begin_point;
	//pcl_begin_point.x = begin_point.x();
	//pcl_begin_point.y = begin_point.y();
	//pcl_begin_point.z = 0.0f;  // ��z����Ϊ0����ʾ��ά��
	//Pointcloud->points.push_back(pcl_begin_point);

	//// ��end_pointת��Ϊpcl::PointXYZ����ӵ�����
	//pcl::PointXYZ pcl_end_point;
	//pcl_end_point.x = end_point.x();
	//pcl_end_point.y = end_point.y();
	//pcl_end_point.z = 0.0f;  // ��z����Ϊ0����ʾ��ά��
	//Pointcloud->points.push_back(pcl_end_point);

	//// ���õ��ƴ�С
	//Pointcloud->width = 2;  // ֻ��������
	//Pointcloud->height = 1; // ���е���

	//// �������ΪPCD�ļ�
	//if (pcl::io::savePCDFileASCII("D:/Users/xia/Desktop/outputPoint.pcd", *Pointcloud) == 0) {
	//	std::cout << "PCD file saved to " << "D:/Users/xia/Desktop/output1.pcd" << std::endl;
	//}
	//else {
	//	std::cerr << "Failed to save PCD file!" << std::endl;
	//}
	return cloud_sampled;
}

std::vector<std::pair<float, float>> GCS::getHeight(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_sampled, const Eigen::Vector2f & begin_point, const Eigen::Vector2f & end_point, int num_point)
{
	int num_closest = 3;//��Ѱ��������
	std::vector<Eigen::Vector2f> key_points;
	std::vector<std::pair<float, float>> results;
	Eigen::Vector2f direction = end_point - begin_point;
	//���߶��ϰ��յ�ĸ������вɼ�
	for (int i = 0; i < num_point; ++i) {
		float t = static_cast<float>(i) / (num_point - 1);  // t �Ǵ� 0 �� 1 �ı���
		Eigen::Vector2f point = begin_point + t * direction;
		key_points.push_back(point);//����Ľ��������ʼ��
	}
	for (int i = 0; i < key_points.size(); ++i) {
		std::vector<PointDistance> distances;
		float height = 0.0;
		//��ȡ��keypoint����ʼ��ľ���
		float dis_to_begin = euclideanDistance(key_points[i].x(), key_points[i].y(), begin_point.x(), begin_point.y());

		for (const auto& point : cloud_sampled->points) {
			float dist = euclideanDistance(key_points[i].x(), key_points[i].y(), point.x, point.y);
			distances.push_back({ point, dist });
		}
		std::sort(distances.begin(), distances.end(), compareDistance);//�õ�����keypoint�����ɽ���Զ��������
		for (int i = 0; i < num_closest; ++i) {
			height += distances[i].point.z;
		}
		height = height / num_closest;
		results.emplace_back(dis_to_begin, height);
	}
	return results;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr GCS::projrctPoint(pcl::PointCloud<pcl::PointXYZ>::Ptr samplecloud, const Eigen::Vector2f & begin_point, const Eigen::Vector2f & end_point)
{
	double X1 = begin_point.x();
	double Y1 = begin_point.y();
	double X2 = end_point.x();
	double Y2 = end_point.y();

	//����ͶӰ����������
	for (auto& point : samplecloud->points) {
		double X0 = point.x;
		double Y0 = point.y;
		// ��������еĲ�����
		double deltaY = Y2 - Y1;
		double deltaX = X2 - X1;
		double term1 = X0 + (deltaY / deltaX) * (Y0 - Y1 + (deltaY / deltaX) * X1);
		double numerator = term1 * std::pow(deltaX, 2);

		// �����ĸ
		double Xdenominator = std::pow(deltaY, 2) + std::pow(deltaX, 2);

		// ���� XM
		double XM = numerator / Xdenominator;

		double term2_part1 = std::pow(deltaY / deltaX, 2) * Y0;
		double term2_part2 = (deltaY / deltaX) * X0;
		double term2_part3 = Y1;
		double term2_part4 = -(deltaY / deltaX) * X1;

		double term2 = (term2_part1 + term2_part2 + term2_part3 + term2_part4) * std::pow(deltaX, 2);

		// �����ĸ
		double Ydenominator = std::pow(deltaY, 2) + std::pow(deltaX, 2);

		// ���� YM
		double YM = term2 / Ydenominator;
		point.x = XM;
		point.y = YM;
	}

	//��ת����
	// 1. ��������ߵķ�������
	Eigen::Vector2f direction = end_point - begin_point;

	// 2. ������ת�Ƕȣ�ʹֱ��A��X��ƽ��
	float angle = std::atan2(direction.y(), direction.x());  // ������X��ļн�
	float rotation_angle = -angle;  // Ϊ��ʹֱ��ˮƽ����Ҫ������ת��X��
	 // 3. ������ת������Z����ת��
	Eigen::Matrix3f rotation_matrix;
	rotation_matrix << std::cos(rotation_angle), -std::sin(rotation_angle), 0,
		std::sin(rotation_angle), std::cos(rotation_angle), 0,
		0, 0, 1;

	// 4. �Ե����е�ÿ����Ӧ����ת����
	for (auto &point : samplecloud->points) {
		Eigen::Vector3f p(point.x, point.y, point.z);
		p = rotation_matrix * p;  // ��ת��
		point.x = p.x();
		point.y = p.y();
		point.z = p.z();
	}

	// ���¶����ߵ������յ㣬ʹ����Ҳ��ת��ˮƽλ��
	Eigen::Vector3f rotated_begin(begin_point.x(), begin_point.y(), 0);
	Eigen::Vector3f rotated_end(end_point.x(), end_point.y(), 0);
	rotated_begin = rotation_matrix * rotated_begin;
	rotated_end = rotation_matrix * rotated_end;

	// 5. �����µķ�����������Ϊ�Ƹ�ֱ����ת����
	Eigen::Vector3f axis = (rotated_end - rotated_begin).normalized();

	// 6. ������ֱ��A�����µ�X�ᣩ��ת90�ȵ���ת����
	float rotation_angle_90 = M_PI / 2;  // 90�� = ��/2 ����
	Eigen::AngleAxisf rotation_90(rotation_angle_90, axis);
	Eigen::Matrix3f rotation_matrix_90 = rotation_90.toRotationMatrix();

	// 7. Ӧ����ֱ��A��ת90�ȵľ���
	for (auto &point : samplecloud->points) {
		Eigen::Vector3f p(point.x, point.y, point.z);
		p = rotation_matrix_90 * p;
		point.x = p.x();
		point.y = p.y();
		point.z = p.z();
	}
	return samplecloud;
}

void GCS::txtWrite(const char * filename, const std::string & survey_area, const std::string & coordinate_system, const std::string & zone_band, const std::string & elevation_system, std::vector<std::pair<float, float>> results)
{
	std::ofstream file(filename);
	// �������˵��
	file << "�����ɹ���\n";
	file << "������" << survey_area << "\n";
	file << "����ϵͳ��" << coordinate_system << "\n";
	file << "�ȴ���" << zone_band << "\n";
	file << "�߳�ϵͳ��" << elevation_system << "\n\n";
	// ��ͷ
	file << std::left << std::setw(8) << "����"
		<< std::setw(15) << "����(m)"
		<< std::setw(10) << "�߳�(m)"
		<< std::setw(10) << "��ע"
		<< std::endl;
	file << std::string(43, '-') << std::endl;
	for (int i = 0; i < results.size(); i++) {
		file <<std::left<< std::setw(8) << (i + 1) 
			<< std::setw(15) << std::fixed << std::setprecision(6) << results[i].first
			<< std::setw(10) << std::fixed << std::setprecision(4)<<results[i].second 
			<< std::setw(10) << "��ע" << std::endl;
	}
	file.close();
}


             



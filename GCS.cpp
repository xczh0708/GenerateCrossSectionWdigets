#include "GCS.h"

bool compareDistance(const PointDistance& a, const PointDistance& b) {
	return a.distance < b.distance;
}//����getHeight���вɵ�ıȽϷ����ͽṹ��

Point interpolate(const Point& p1, const Point& p2, float t) {
	return { p1.first + t * (p2.first - p1.first), p1.second + t * (p2.second - p1.second) };
}//���ڻ�����ȡ���ϵĵ�

GCS::GCS()
{
	m_pcdPointCloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>());
	//m_pcdSampledPointCloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>());
}

//��ȡlas����
void GCS::readLasData(const char* filename)
{
	std::cout << "������ȡlas�ļ�" << std::endl;
	//��las�ļ�
	LASreadOpener lasrReadOpener;
	lasrReadOpener.set_file_name(filename);//�Լ���las�ļ���ַ
	LASreader* lasReader = lasrReadOpener.open(false);
	size_t count = lasReader->header.number_of_point_records;
	//����pcl��ʽ
	//pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);//ע���Լ���las�ļ���ʽ������ɫ��ʹ��PointXYZRGB
	m_pcdPointCloud->width = count;
	m_pcdPointCloud->height = 1;
	m_pcdPointCloud->resize(count);
	m_pcdPointCloud->is_dense = false;

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
		m_pcdPointCloud->points[j].x = lasReader->get_x();
		m_pcdPointCloud->points[j].y = lasReader->get_y();
		m_pcdPointCloud->points[j].z = lasReader->get_z();
		/*cloud->points[j].x = (lasReader->point.get_x() * scaleX) + xOffset;
		cloud->points[j].y = (lasReader->point.get_y() * scaleY) + yOffset;
		cloud->points[j].z = (lasReader->point.get_z() * scaleZ) + zOffset;*/
		//cloud->points[j].r = lasReader->point.get_R();
		//cloud->points[j].g = lasReader->point.get_G();
		//cloud->points[j].b = lasReader->point.get_B();	
		++j;
	}
	pcl::io::savePCDFileASCII("D:/Users/xia/Desktop/output1.pcd", *m_pcdPointCloud);
	std::cout << "������ȡlas�ļ�" << std::endl;
}
//��������֮�����
double GCS::euclideanDistance(double x1, double y1, double x2, double y2)
{
	return std::sqrt(std::pow(x1 - x2, 2) + std::pow( y1 - y2, 2));
}
////�����߶���Χ����
//void GCS::samplePoint(float distance,const Point& p1, const Point& p2)
//{
//	std::cout << "��ʼ�²���" << std::endl;
//	Eigen::Vector2f begin_point(p1.first, p1.second);
//	Eigen::Vector2f end_point(p2.first, p2.second);
//	Eigen::Vector2f delta = end_point - begin_point;//�����߶��ϵķ�������
//	Eigen::Vector2f perpendicular_direction(-delta[1], delta[0]);//��ֱ���߷�������
//	float length = perpendicular_direction.norm();  // ������ģ
//	Eigen::Vector2f unit_perpendicular_direction = perpendicular_direction / length; //���㴹ֱ���������ĵ�λ��
//	//������Χ��ȡ
//	Eigen::Vector2f point1 = begin_point + distance * unit_perpendicular_direction;
//	Eigen::Vector2f point2 = begin_point - distance * unit_perpendicular_direction;
//	Eigen::Vector2f point3 = end_point + distance * unit_perpendicular_direction;
//	Eigen::Vector2f point4 = end_point - distance * unit_perpendicular_direction;
//	float min_x = std::min({ point1.x(), point2.x(), point3.x(), point4.x() });
//	float max_x = std::max({ point1.x(), point2.x(), point3.x(), point4.x() });
//	float min_y = std::min({ point1.y(), point2.y(), point3.y(), point4.y() });
//	float max_y = std::max({ point1.y(), point2.y(), point3.y(), point4.y() });
//	//ͨ���߽����вü�
//	pcl::CropBox<pcl::PointXYZ> crop_box;
//	crop_box.setMin(Eigen::Vector4f(min_x, min_y, -std::numeric_limits<float>::infinity(), 1.0f));  // ������С��
//	crop_box.setMax(Eigen::Vector4f(max_x, max_y, std::numeric_limits<float>::infinity(), 1.0f));     // ��������
//	crop_box.setInputCloud(m_pcdPointCloud);
//	crop_box.filter(*m_pcdSampledPointCloud);
//	std::cout << "�����²���" << std::endl;
//	std::cout << "��ʼ��ȡ�߶�" << std::endl;
//}

void GCS::getHeight(float distance,int num_point)
{
	std::cout << "��ʼ��ȡ�߶�" << std::endl;
	int num_closest = 3;
	//ȷ����Ч�㣬���߳�����
	for (const auto& line : m_initial_extraction_line) {
		std::vector<std::pair<float, float>> result;
		pcl::PointCloud<pcl::PointXYZ>::Ptr pcdSampledPointCloud(new pcl::PointCloud<pcl::PointXYZ>());
		Eigen::Vector2f begin_point(line.bengin_point.first, line.bengin_point.second);
		Eigen::Vector2f end_point(line.end_point.first, line.end_point.second);
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
		crop_box.setInputCloud(m_pcdPointCloud);
		crop_box.filter(*pcdSampledPointCloud);

		if (pcdSampledPointCloud->size() > num_point) {		//�жϸ���ȡ���Ƿ��ڵ�����
			m_final_extraction_line.push_back(line);
		}
	}
	std::sort(m_final_extraction_line.begin(), m_final_extraction_line.end(), [](const CenterLine& a, const CenterLine& b) -> bool {
		return a.height > b.height;  // �� height ��������
		});

	//��ȡ�߶�
	for (const auto& line : m_final_extraction_line) {
		std::vector<std::pair<float, float>> result;
		pcl::PointCloud<pcl::PointXYZ>::Ptr pcdSampledPointCloud(new pcl::PointCloud<pcl::PointXYZ>());
		Eigen::Vector2f begin_point(line.bengin_point.first, line.bengin_point.second);
		Eigen::Vector2f end_point(line.end_point.first, line.end_point.second);
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
		crop_box.setInputCloud(m_pcdPointCloud);
		crop_box.filter(*pcdSampledPointCloud);
		//��ȡ�ؼ���
		std::vector<Eigen::Vector2f> key_points;
		Eigen::Vector2f direction = end_point - begin_point;
		for (int i = 0; i < num_point; ++i) {
			float t = static_cast<float>(i) / (num_point);  // t �Ǵ� 0 �� 1 �ı���
			Eigen::Vector2f point = begin_point + t * direction;
			key_points.push_back(point);//����Ľ��������ʼ��
		}
		//��߶�
		for (int i = 0; i < key_points.size(); i++) {
			float height = 0.0;
			std::vector<PointDistance> distances;
			//��ȡ��keypoint����ʼ��ľ���
			float dis_to_begin = euclideanDistance(key_points[i].x(), key_points[i].y(), begin_point.x(), begin_point.y());
			for (const auto& point : pcdSampledPointCloud->points) {
				float dist = euclideanDistance(key_points[i].x(), key_points[i].y(), point.x, point.y);
				distances.push_back({ point, dist });
			}
			std::sort(distances.begin(), distances.end(), compareDistance);//�õ�����keypoint�����ɽ���Զ��������
			for (int i = 0; i < num_closest; ++i) {
				height += distances[i].point.z;
			}
			height = (height / num_closest);
			result.emplace_back(dis_to_begin, height);
		}
			m_results.push_back(result);
	}
	std::cout << "������ȡ�߶�" << std::endl;
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

void GCS::txtWrite(const char * foldersname, const std::string & survey_area, const std::string & coordinate_system, const std::string & zone_band, const std::string & elevation_system)
{
	int num_file = 0;
	std::cout << "��ʼд��txt" << std::endl;
	for (int i = 0; i < m_results.size(); i++) {
		std::vector < std::pair<float, float>> result = m_results[i];
		std::string filename = std::string(foldersname) + "/txt_res" + std::to_string(num_file) + ".txt";
		std::ofstream file(filename);
		// �������˵��
		file << "�����ɹ���\n";
		file << "������" << survey_area << "\n";
		file << "����ϵͳ��" << coordinate_system << "\n";
		file << "�ȴ���" << zone_band << "\n";
		file << "�߳�ϵͳ��" << elevation_system << "\n";
		file<<"��ȡ���������:("<<m_final_extraction_line[i].bengin_point.first<<","<< m_final_extraction_line[i].bengin_point.second<<")"
			<<"��ȡ���յ�����:(" << m_final_extraction_line[i].end_point.first << "," << m_final_extraction_line[i].end_point.second << ")" << "\n\n";
		// ��ͷ
		file << std::left << std::setw(8) << "����"
			<< std::setw(15) << "����(m)"
			<< std::setw(10) << "�߳�(m)"
			<< std::setw(10) << "��ע"
			<< std::endl;
		file << std::string(43, '-') << std::endl;
		for (int i = 0; i < result.size(); i++) {
			file << std::left << std::setw(8) << (i + 1)
				<< std::setw(15) << std::fixed << std::setprecision(6) << result[i].first
				<< std::setw(10) << std::fixed << std::setprecision(4) << result[i].second
				<< std::setw(10) << "��ע" << std::endl;
		}
		file.close();
		num_file++;
	}
	//for (const auto& result : m_results) {
	//	std::string filename = std::string(foldersname) + "/txt_res" + std::to_string(num_file) + ".txt";
	//	std::ofstream file(filename);
	//	// �������˵��
	//	file << "�����ɹ���\n";
	//	file << "������" << survey_area << "\n";
	//	file << "����ϵͳ��" << coordinate_system << "\n";
	//	file << "�ȴ���" << zone_band << "\n";
	//	file << "�߳�ϵͳ��" << elevation_system << "\n\n";
	//	// ��ͷ
	//	file << std::left << std::setw(8) << "����"
	//		<< std::setw(15) << "����(m)"
	//		<< std::setw(10) << "�߳�(m)"
	//		<< std::setw(10) << "��ע"
	//		<< std::endl;
	//	file << std::string(43, '-') << std::endl;
	//	for (int i = 0; i < result.size(); i++) {
	//		file << std::left << std::setw(8) << (i + 1)
	//			<< std::setw(15) << std::fixed << std::setprecision(6) << result[i].first
	//			<< std::setw(10) << std::fixed << std::setprecision(4) << result[i].second
	//			<< std::setw(10) << "��ע" << std::endl;
	//	}
	//	file.close();
	//	num_file++;
	//}
	std::cout << "����д��txt" << std::endl;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr GCS::getPcdPointCloud()
{
	return m_pcdPointCloud;
}

//pcl::PointCloud<pcl::PointXYZ>::Ptr GCS::getPcdSampledPointCloud()
//{
//	return m_pcdSampledPointCloud;
//}

std::vector<std::vector<std::pair<float, float>>> GCS::getResults()
{
	return m_results;
}

void GCS::getCenterLines(const std::vector<Point>& centerline, float targetDistance,float reslong)
{
	float accumulatedDistance = 0.0f;  // �ۼƾ���
	pcl::KdTreeFLANN<pcl::PointXYZ> kd_tree;
	kd_tree.setInputCloud(m_pcdPointCloud);
	float distance_xy = 0.0f;
	CenterLine line;
	// �������е�
	for (size_t i = 1; i < centerline.size(); ++i) {
		// ���㵱ǰ����ǰһ����֮��ľ���
		float segmentDistance = euclideanDistance(centerline[i - 1].first,centerline[i - 1].second, centerline[i].first, centerline[i].second);
		accumulatedDistance += segmentDistance;  // �ۼӾ���

		// ����ۼƾ�����ڵ���Ŀ�����
		while (accumulatedDistance >= targetDistance) {
			// ������߶���Ŀ�����Ĳ�ֵ��
			float t = (accumulatedDistance - targetDistance) / segmentDistance;
			Point interpolatedPoint = interpolate(centerline[i - 1], centerline[i], t);
			pcl::PointXYZ query_point(interpolatedPoint.first, interpolatedPoint.second, 0.0f);
			std::vector<int> nearest_indices(1);  // ����ڵĵ�����
			std::vector<float> nearest_distances(1);  // ����ڵľ���

			if (kd_tree.nearestKSearch(query_point, 1, nearest_indices, nearest_distances) > 0)
			{
				const pcl::PointXYZ& nearest_point = m_pcdPointCloud->points[nearest_indices[0]];
				// �����ѯ�������ڵ�� xy ƽ�����
				float dx = query_point.x - nearest_point.x;
				float dy = query_point.y - nearest_point.y;
				float distance_xy = std::sqrt(dx * dx + dy * dy);  // ���� z ����

				std::cout << "Point (" << interpolatedPoint.first << ", " << interpolatedPoint.second << ") "
					<< "has nearest point (" << nearest_point.x << ", " << nearest_point.y << ", " << nearest_point.z << ") "
					<< "with distance: " << distance_xy << std::endl;
				line.height = nearest_point.z;
			}
			auto perpendicularLine = calculatePerpendicularLine(centerline[i - 1], centerline[i], interpolatedPoint, reslong / 2.0);
			line.bengin_point = perpendicularLine.first;
			line.end_point = perpendicularLine.second;
			m_initial_extraction_line.push_back(line);
			// �����ۼƾ��룬��ȥĿ�����
			accumulatedDistance -= targetDistance;
		}
	}
}


std::pair<Point, Point> GCS::calculatePerpendicularLine(const Point & p1, const Point & p2, const Point & interpolatedPoint, float distance)
{
	// �����߶εķ�������
	float dx = p2.first - p1.first;
	float dy = p2.second - p1.second;

	// ���㵥λ��������
	float length = euclideanDistance(p1.first, p1.second, p2.first, p2.second);
	float unit_dx = dx / length;
	float unit_dy = dy / length;

	// ���㴹ֱ��������
	float perpendicular_dx = -unit_dy;
	float perpendicular_dy = unit_dx;

	// ���ݲ�ֵ��ʹ�ֱ������������ƶ���ĵ�
	Point startPoint = { interpolatedPoint.first - perpendicular_dx * distance, interpolatedPoint.second - perpendicular_dy * distance };
	Point endPoint = { interpolatedPoint.first + perpendicular_dx * distance, interpolatedPoint.second + perpendicular_dy * distance };
	return { startPoint, endPoint };
}



             



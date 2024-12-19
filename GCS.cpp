#include "GCS.h"

bool compareDistance(const PointDistance& a, const PointDistance& b) {
	return a.distance < b.distance;
}//用于getHeight进行采点的比较方法和结构体

Point interpolate(const Point& p1, const Point& p2, float t) {
	return { p1.first + t * (p2.first - p1.first), p1.second + t * (p2.second - p1.second) };
}//用于绘制提取线上的点

GCS::GCS()
{
	m_pcdPointCloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>());
	//m_pcdSampledPointCloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>());
}

//读取las数据
void GCS::readLasData(const char* filename)
{
	std::cout << "开启读取las文件" << std::endl;
	//打开las文件
	LASreadOpener lasrReadOpener;
	lasrReadOpener.set_file_name(filename);//自己的las文件地址
	LASreader* lasReader = lasrReadOpener.open(false);
	size_t count = lasReader->header.number_of_point_records;
	//创建pcl格式
	//pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);//注意自己的las文件格式。有颜色的使用PointXYZRGB
	m_pcdPointCloud->width = count;
	m_pcdPointCloud->height = 1;
	m_pcdPointCloud->resize(count);
	m_pcdPointCloud->is_dense = false;

	//读取las文件偏移值和缩放值
	//double xOffset = lasReader->header.x_offset;// 偏移值
	//double yOffset = lasReader->header.y_offset;
	//double zOffset = lasReader->header.z_offset;
	//double scaleX = lasReader->header.x_scale_factor;
	//double scaleY = lasReader->header.y_scale_factor;
	//double scaleZ = lasReader->header.z_scale_factor;
	//std::cout << " scaleX: "<<scaleX << " scaleY: " << scaleY << " scaleZ: " << scaleZ << std::endl;
	//std::cout << " xOffset: " << xOffset << " yOffset: " << yOffset << " zOffset: " << zOffset << std::endl;
	//读取点
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
	std::cout << "结束读取las文件" << std::endl;
}
//计算两点之间距离
double GCS::euclideanDistance(double x1, double y1, double x2, double y2)
{
	return std::sqrt(std::pow(x1 - x2, 2) + std::pow( y1 - y2, 2));
}
////采样线段周围点云
//void GCS::samplePoint(float distance,const Point& p1, const Point& p2)
//{
//	std::cout << "开始下采样" << std::endl;
//	Eigen::Vector2f begin_point(p1.first, p1.second);
//	Eigen::Vector2f end_point(p2.first, p2.second);
//	Eigen::Vector2f delta = end_point - begin_point;//计算线段上的方向向量
//	Eigen::Vector2f perpendicular_direction(-delta[1], delta[0]);//垂直该线方向向量
//	float length = perpendicular_direction.norm();  // 向量的模
//	Eigen::Vector2f unit_perpendicular_direction = perpendicular_direction / length; //计算垂直方向向量的单位化
//	//采样框范围获取
//	Eigen::Vector2f point1 = begin_point + distance * unit_perpendicular_direction;
//	Eigen::Vector2f point2 = begin_point - distance * unit_perpendicular_direction;
//	Eigen::Vector2f point3 = end_point + distance * unit_perpendicular_direction;
//	Eigen::Vector2f point4 = end_point - distance * unit_perpendicular_direction;
//	float min_x = std::min({ point1.x(), point2.x(), point3.x(), point4.x() });
//	float max_x = std::max({ point1.x(), point2.x(), point3.x(), point4.x() });
//	float min_y = std::min({ point1.y(), point2.y(), point3.y(), point4.y() });
//	float max_y = std::max({ point1.y(), point2.y(), point3.y(), point4.y() });
//	//通过边界框进行裁剪
//	pcl::CropBox<pcl::PointXYZ> crop_box;
//	crop_box.setMin(Eigen::Vector4f(min_x, min_y, -std::numeric_limits<float>::infinity(), 1.0f));  // 设置最小点
//	crop_box.setMax(Eigen::Vector4f(max_x, max_y, std::numeric_limits<float>::infinity(), 1.0f));     // 设置最大点
//	crop_box.setInputCloud(m_pcdPointCloud);
//	crop_box.filter(*m_pcdSampledPointCloud);
//	std::cout << "结束下采样" << std::endl;
//	std::cout << "开始提取高度" << std::endl;
//}

void GCS::getHeight(float distance,int num_point)
{
	std::cout << "开始提取高度" << std::endl;
	int num_closest = 3;
	//确定有效点，按高程排序
	for (const auto& line : m_initial_extraction_line) {
		std::vector<std::pair<float, float>> result;
		pcl::PointCloud<pcl::PointXYZ>::Ptr pcdSampledPointCloud(new pcl::PointCloud<pcl::PointXYZ>());
		Eigen::Vector2f begin_point(line.bengin_point.first, line.bengin_point.second);
		Eigen::Vector2f end_point(line.end_point.first, line.end_point.second);
		Eigen::Vector2f delta = end_point - begin_point;//计算线段上的方向向量
		Eigen::Vector2f perpendicular_direction(-delta[1], delta[0]);//垂直该线方向向量
		float length = perpendicular_direction.norm();  // 向量的模
		Eigen::Vector2f unit_perpendicular_direction = perpendicular_direction / length; //计算垂直方向向量的单位化
		//采样框范围获取
		Eigen::Vector2f point1 = begin_point + distance * unit_perpendicular_direction;
		Eigen::Vector2f point2 = begin_point - distance * unit_perpendicular_direction;
		Eigen::Vector2f point3 = end_point + distance * unit_perpendicular_direction;
		Eigen::Vector2f point4 = end_point - distance * unit_perpendicular_direction;
		float min_x = std::min({ point1.x(), point2.x(), point3.x(), point4.x() });
		float max_x = std::max({ point1.x(), point2.x(), point3.x(), point4.x() });
		float min_y = std::min({ point1.y(), point2.y(), point3.y(), point4.y() });
		float max_y = std::max({ point1.y(), point2.y(), point3.y(), point4.y() });
		//通过边界框进行裁剪
		pcl::CropBox<pcl::PointXYZ> crop_box;
		crop_box.setMin(Eigen::Vector4f(min_x, min_y, -std::numeric_limits<float>::infinity(), 1.0f));  // 设置最小点
		crop_box.setMax(Eigen::Vector4f(max_x, max_y, std::numeric_limits<float>::infinity(), 1.0f));     // 设置最大点
		crop_box.setInputCloud(m_pcdPointCloud);
		crop_box.filter(*pcdSampledPointCloud);

		if (pcdSampledPointCloud->size() > num_point) {		//判断该提取线是否在点云上
			m_final_extraction_line.push_back(line);
		}
	}
	std::sort(m_final_extraction_line.begin(), m_final_extraction_line.end(), [](const CenterLine& a, const CenterLine& b) -> bool {
		return a.height > b.height;  // 按 height 降序排序
		});

	//提取高度
	for (const auto& line : m_final_extraction_line) {
		std::vector<std::pair<float, float>> result;
		pcl::PointCloud<pcl::PointXYZ>::Ptr pcdSampledPointCloud(new pcl::PointCloud<pcl::PointXYZ>());
		Eigen::Vector2f begin_point(line.bengin_point.first, line.bengin_point.second);
		Eigen::Vector2f end_point(line.end_point.first, line.end_point.second);
		Eigen::Vector2f delta = end_point - begin_point;//计算线段上的方向向量
		Eigen::Vector2f perpendicular_direction(-delta[1], delta[0]);//垂直该线方向向量
		float length = perpendicular_direction.norm();  // 向量的模
		Eigen::Vector2f unit_perpendicular_direction = perpendicular_direction / length; //计算垂直方向向量的单位化
		//采样框范围获取
		Eigen::Vector2f point1 = begin_point + distance * unit_perpendicular_direction;
		Eigen::Vector2f point2 = begin_point - distance * unit_perpendicular_direction;
		Eigen::Vector2f point3 = end_point + distance * unit_perpendicular_direction;
		Eigen::Vector2f point4 = end_point - distance * unit_perpendicular_direction;
		float min_x = std::min({ point1.x(), point2.x(), point3.x(), point4.x() });
		float max_x = std::max({ point1.x(), point2.x(), point3.x(), point4.x() });
		float min_y = std::min({ point1.y(), point2.y(), point3.y(), point4.y() });
		float max_y = std::max({ point1.y(), point2.y(), point3.y(), point4.y() });
		//通过边界框进行裁剪
		pcl::CropBox<pcl::PointXYZ> crop_box;
		crop_box.setMin(Eigen::Vector4f(min_x, min_y, -std::numeric_limits<float>::infinity(), 1.0f));  // 设置最小点
		crop_box.setMax(Eigen::Vector4f(max_x, max_y, std::numeric_limits<float>::infinity(), 1.0f));     // 设置最大点
		crop_box.setInputCloud(m_pcdPointCloud);
		crop_box.filter(*pcdSampledPointCloud);
		//提取关键点
		std::vector<Eigen::Vector2f> key_points;
		Eigen::Vector2f direction = end_point - begin_point;
		for (int i = 0; i < num_point; ++i) {
			float t = static_cast<float>(i) / (num_point);  // t 是从 0 到 1 的比例
			Eigen::Vector2f point = begin_point + t * direction;
			key_points.push_back(point);//输出的结果包含起始点
		}
		//提高度
		for (int i = 0; i < key_points.size(); i++) {
			float height = 0.0;
			std::vector<PointDistance> distances;
			//获取到keypoint到起始点的距离
			float dis_to_begin = euclideanDistance(key_points[i].x(), key_points[i].y(), begin_point.x(), begin_point.y());
			for (const auto& point : pcdSampledPointCloud->points) {
				float dist = euclideanDistance(key_points[i].x(), key_points[i].y(), point.x, point.y);
				distances.push_back({ point, dist });
			}
			std::sort(distances.begin(), distances.end(), compareDistance);//得到距离keypoint距离由近到远的排序点对
			for (int i = 0; i < num_closest; ++i) {
				height += distances[i].point.z;
			}
			height = (height / num_closest);
			result.emplace_back(dis_to_begin, height);
		}
			m_results.push_back(result);
	}
	std::cout << "结束提取高度" << std::endl;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr GCS::projrctPoint(pcl::PointCloud<pcl::PointXYZ>::Ptr samplecloud, const Eigen::Vector2f & begin_point, const Eigen::Vector2f & end_point)
{
	double X1 = begin_point.x();
	double Y1 = begin_point.y();
	double X2 = end_point.x();
	double Y2 = end_point.y();

	//将点投影到断面线上
	for (auto& point : samplecloud->points) {
		double X0 = point.x;
		double Y0 = point.y;
		// 计算分子中的部分项
		double deltaY = Y2 - Y1;
		double deltaX = X2 - X1;
		double term1 = X0 + (deltaY / deltaX) * (Y0 - Y1 + (deltaY / deltaX) * X1);
		double numerator = term1 * std::pow(deltaX, 2);

		// 计算分母
		double Xdenominator = std::pow(deltaY, 2) + std::pow(deltaX, 2);

		// 计算 XM
		double XM = numerator / Xdenominator;

		double term2_part1 = std::pow(deltaY / deltaX, 2) * Y0;
		double term2_part2 = (deltaY / deltaX) * X0;
		double term2_part3 = Y1;
		double term2_part4 = -(deltaY / deltaX) * X1;

		double term2 = (term2_part1 + term2_part2 + term2_part3 + term2_part4) * std::pow(deltaX, 2);

		// 计算分母
		double Ydenominator = std::pow(deltaY, 2) + std::pow(deltaX, 2);

		// 计算 YM
		double YM = term2 / Ydenominator;
		point.x = XM;
		point.y = YM;
	}

	//旋转点云
	// 1. 计算断面线的方向向量
	Eigen::Vector2f direction = end_point - begin_point;

	// 2. 计算旋转角度，使直线A与X轴平行
	float angle = std::atan2(direction.y(), direction.x());  // 计算与X轴的夹角
	float rotation_angle = -angle;  // 为了使直线水平，需要逆向旋转到X轴
	 // 3. 构建旋转矩阵（绕Z轴旋转）
	Eigen::Matrix3f rotation_matrix;
	rotation_matrix << std::cos(rotation_angle), -std::sin(rotation_angle), 0,
		std::sin(rotation_angle), std::cos(rotation_angle), 0,
		0, 0, 1;

	// 4. 对点云中的每个点应用旋转矩阵
	for (auto &point : samplecloud->points) {
		Eigen::Vector3f p(point.x, point.y, point.z);
		p = rotation_matrix * p;  // 旋转点
		point.x = p.x();
		point.y = p.y();
		point.z = p.z();
	}

	// 更新断面线的起点和终点，使它们也旋转至水平位置
	Eigen::Vector3f rotated_begin(begin_point.x(), begin_point.y(), 0);
	Eigen::Vector3f rotated_end(end_point.x(), end_point.y(), 0);
	rotated_begin = rotation_matrix * rotated_begin;
	rotated_end = rotation_matrix * rotated_end;

	// 5. 计算新的方向向量，作为绕该直线旋转的轴
	Eigen::Vector3f axis = (rotated_end - rotated_begin).normalized();

	// 6. 构建绕直线A（即新的X轴）旋转90度的旋转矩阵
	float rotation_angle_90 = M_PI / 2;  // 90度 = π/2 弧度
	Eigen::AngleAxisf rotation_90(rotation_angle_90, axis);
	Eigen::Matrix3f rotation_matrix_90 = rotation_90.toRotationMatrix();

	// 7. 应用绕直线A旋转90度的矩阵
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
	std::cout << "开始写入txt" << std::endl;
	for (int i = 0; i < m_results.size(); i++) {
		std::vector < std::pair<float, float>> result = m_results[i];
		std::string filename = std::string(foldersname) + "/txt_res" + std::to_string(num_file) + ".txt";
		std::ofstream file(filename);
		// 表格标题和说明
		file << "横断面成果表\n";
		file << "测区：" << survey_area << "\n";
		file << "坐标系统：" << coordinate_system << "\n";
		file << "度带：" << zone_band << "\n";
		file << "高程系统：" << elevation_system << "\n";
		file<<"提取线起点坐标:("<<m_final_extraction_line[i].bengin_point.first<<","<< m_final_extraction_line[i].bengin_point.second<<")"
			<<"提取线终点坐标:(" << m_final_extraction_line[i].end_point.first << "," << m_final_extraction_line[i].end_point.second << ")" << "\n\n";
		// 表头
		file << std::left << std::setw(8) << "点名"
			<< std::setw(15) << "起点距(m)"
			<< std::setw(10) << "高程(m)"
			<< std::setw(10) << "备注"
			<< std::endl;
		file << std::string(43, '-') << std::endl;
		for (int i = 0; i < result.size(); i++) {
			file << std::left << std::setw(8) << (i + 1)
				<< std::setw(15) << std::fixed << std::setprecision(6) << result[i].first
				<< std::setw(10) << std::fixed << std::setprecision(4) << result[i].second
				<< std::setw(10) << "备注" << std::endl;
		}
		file.close();
		num_file++;
	}
	//for (const auto& result : m_results) {
	//	std::string filename = std::string(foldersname) + "/txt_res" + std::to_string(num_file) + ".txt";
	//	std::ofstream file(filename);
	//	// 表格标题和说明
	//	file << "横断面成果表\n";
	//	file << "测区：" << survey_area << "\n";
	//	file << "坐标系统：" << coordinate_system << "\n";
	//	file << "度带：" << zone_band << "\n";
	//	file << "高程系统：" << elevation_system << "\n\n";
	//	// 表头
	//	file << std::left << std::setw(8) << "点名"
	//		<< std::setw(15) << "起点距(m)"
	//		<< std::setw(10) << "高程(m)"
	//		<< std::setw(10) << "备注"
	//		<< std::endl;
	//	file << std::string(43, '-') << std::endl;
	//	for (int i = 0; i < result.size(); i++) {
	//		file << std::left << std::setw(8) << (i + 1)
	//			<< std::setw(15) << std::fixed << std::setprecision(6) << result[i].first
	//			<< std::setw(10) << std::fixed << std::setprecision(4) << result[i].second
	//			<< std::setw(10) << "备注" << std::endl;
	//	}
	//	file.close();
	//	num_file++;
	//}
	std::cout << "结束写入txt" << std::endl;
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
	float accumulatedDistance = 0.0f;  // 累计距离
	pcl::KdTreeFLANN<pcl::PointXYZ> kd_tree;
	kd_tree.setInputCloud(m_pcdPointCloud);
	float distance_xy = 0.0f;
	CenterLine line;
	// 遍历所有点
	for (size_t i = 1; i < centerline.size(); ++i) {
		// 计算当前点与前一个点之间的距离
		float segmentDistance = euclideanDistance(centerline[i - 1].first,centerline[i - 1].second, centerline[i].first, centerline[i].second);
		accumulatedDistance += segmentDistance;  // 累加距离

		// 如果累计距离大于等于目标距离
		while (accumulatedDistance >= targetDistance) {
			// 计算该线段上目标距离的插值点
			float t = (accumulatedDistance - targetDistance) / segmentDistance;
			Point interpolatedPoint = interpolate(centerline[i - 1], centerline[i], t);
			pcl::PointXYZ query_point(interpolatedPoint.first, interpolatedPoint.second, 0.0f);
			std::vector<int> nearest_indices(1);  // 最近邻的点索引
			std::vector<float> nearest_distances(1);  // 最近邻的距离

			if (kd_tree.nearestKSearch(query_point, 1, nearest_indices, nearest_distances) > 0)
			{
				const pcl::PointXYZ& nearest_point = m_pcdPointCloud->points[nearest_indices[0]];
				// 计算查询点和最近邻点的 xy 平面距离
				float dx = query_point.x - nearest_point.x;
				float dy = query_point.y - nearest_point.y;
				float distance_xy = std::sqrt(dx * dx + dy * dy);  // 忽略 z 坐标

				std::cout << "Point (" << interpolatedPoint.first << ", " << interpolatedPoint.second << ") "
					<< "has nearest point (" << nearest_point.x << ", " << nearest_point.y << ", " << nearest_point.z << ") "
					<< "with distance: " << distance_xy << std::endl;
				line.height = nearest_point.z;
			}
			auto perpendicularLine = calculatePerpendicularLine(centerline[i - 1], centerline[i], interpolatedPoint, reslong / 2.0);
			line.bengin_point = perpendicularLine.first;
			line.end_point = perpendicularLine.second;
			m_initial_extraction_line.push_back(line);
			// 更新累计距离，减去目标距离
			accumulatedDistance -= targetDistance;
		}
	}
}


std::pair<Point, Point> GCS::calculatePerpendicularLine(const Point & p1, const Point & p2, const Point & interpolatedPoint, float distance)
{
	// 计算线段的方向向量
	float dx = p2.first - p1.first;
	float dy = p2.second - p1.second;

	// 计算单位方向向量
	float length = euclideanDistance(p1.first, p1.second, p2.first, p2.second);
	float unit_dx = dx / length;
	float unit_dy = dy / length;

	// 计算垂直方向向量
	float perpendicular_dx = -unit_dy;
	float perpendicular_dy = unit_dx;

	// 根据插值点和垂直方向计算上下移动后的点
	Point startPoint = { interpolatedPoint.first - perpendicular_dx * distance, interpolatedPoint.second - perpendicular_dy * distance };
	Point endPoint = { interpolatedPoint.first + perpendicular_dx * distance, interpolatedPoint.second + perpendicular_dy * distance };
	return { startPoint, endPoint };
}



             



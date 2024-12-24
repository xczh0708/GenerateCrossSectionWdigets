#include "CADRW.h"





CADRW::CADRW(dxfRW &dxfW, std::vector<std::pair<float, float>> results) : m_dxfW(dxfW), m_results(results){
}






void CADRW::writeEntities()
{
	float maxDis = std::numeric_limits<float>::lowest();
	float maxHeight = std::numeric_limits<float>::lowest();
	for (const auto& pair : m_results) {
		if (pair.first > maxDis) maxDis = pair.first;
		if (pair.second > maxHeight) maxHeight = pair.second;
	}
	maxDis = std::ceil(maxDis / 10.0f) * 10.0f;
	maxHeight = std::ceil(maxHeight / 10.0f) * 10.0f;
	double labeset = -2.5;
	double basex = 10.0;
	DRW_LWPolyline polyline;
	polyline.flags = 0; // 0 表示不闭合
	polyline.elevation = 0; // 多段线的 Z 坐标
	DRW_Line axisLiney;
	DRW_Line axisLinex;
	//绘制坐标轴
	axisLiney.basePoint.x = 0;    // 起点 X
	axisLiney.basePoint.y = 0;   // 起点 Y
	axisLiney.secPoint.x = 0;     // 终点 X
	axisLiney.secPoint.y = maxHeight - 1500;    // 终点 Y
	m_dxfW.writeLine(&axisLiney);
	axisLinex.basePoint.x = 0;    // 起点 X
	axisLinex.basePoint.y = 0;   // 起点 Y
	axisLinex.secPoint.x = maxDis + basex;     // 终点 X
	axisLinex.secPoint.y = 0;    // 终点 Y
	m_dxfW.writeLine(&axisLinex);
	 // 2. 绘制刻度线并添加文字标注
	double yMin = 1500;  // 坐标轴起始 Y
	double yMax = maxHeight;  // 坐标轴结束 Y
	double ymajorStep = 5; // 主要刻度间隔
	double yminorStep = 1; // 次要刻度间隔

	double xMin = basex;  // 坐标轴起始 x
	double xMax = maxDis + basex;  // 坐标轴结束 x
	double xmajorStep = 10; // 主要刻度间隔
	double xminorStep = 1; // 次要刻度间隔
	//y轴
	for (double y = yMin; y <= yMax; y += yminorStep) {
		DRW_Line tickLine;
		tickLine.basePoint.x = 0;       // 起点 X
		tickLine.basePoint.y = y - 1500;       // 起点 Y
		tickLine.secPoint.y = y - 1500;        // 终点 Y

		if (static_cast<int>(y) % static_cast<int>(ymajorStep) == 0) {
			// 主要刻度（长刻度线）
			tickLine.secPoint.x = 2.0;  // 长刻度长度
		}
		else {
			// 次要刻度（短刻度线）
			tickLine.secPoint.x = 1.0;  // 短刻度长度
		}
		m_dxfW.writeLine(&tickLine);

		// 为主要刻度添加文字标注
		if (static_cast<int>(y) % static_cast<int>(ymajorStep) == 0) {
			DRW_Text label;
			label.basePoint.x = labeset;    // 文字偏移 X
			label.basePoint.y = y - 1500;      // 文字 Y 坐标
			label.basePoint.z = 0;      // 文字 Z 坐标
			label.text = std::to_string(static_cast<int>(y)); // 标注内容
			label.height = 1.0;         // 字体高度
			label.angle = 0.0;          // 旋转角度
			//label.alignH = DRW_Text::HAlign::HLeft; // 水平左对齐
			//label.alignV = DRW_Text::VAlign::VMiddle; // 垂直居中
			m_dxfW.writeText(&label);
		}
	}
	//x轴
	for (double x = xMin; x <= xMax; x += xminorStep) {
		DRW_Line tickLine;
		tickLine.basePoint.x = x;       // 起点 X
		tickLine.basePoint.y = 0;       // 起点 Y
		tickLine.secPoint.x = x;        // 终点 Y

		if (static_cast<int>(x) % static_cast<int>(xmajorStep) == 0) {
			// 主要刻度（长刻度线）
			tickLine.secPoint.y = 2.0;  // 长刻度长度
		}
		else {
			// 次要刻度（短刻度线）
			tickLine.secPoint.y = 1.0;  // 短刻度长度
		}
		m_dxfW.writeLine(&tickLine);

		// 为主要刻度添加文字标注
		if (static_cast<int>(x) % static_cast<int>(xmajorStep) == 0) {
			DRW_Text label;
			label.basePoint.x = x;    // 文字偏移 X
			label.basePoint.y = labeset;      // 文字 Y 坐标
			label.basePoint.z = 0;      // 文字 Z 坐标
			label.text = std::to_string(static_cast<int>(x)); // 标注内容
			label.height = 1.0;         // 字体高度
			label.angle = 0.0;          // 旋转角度
			m_dxfW.writeText(&label);
		}
	}
	//绘制高度线
	for (int i = 0; i < m_results.size(); i++) {
		DRW_Line line;
		DRW_Text textnum;
		DRW_Text textheight;
		textnum.basePoint.x = m_results[i].first + basex;              // 插入点 X 坐标
		textnum.basePoint.y = m_results[i].second-1499;             // 插入点 Y 坐标
		textnum.height = 0.5;                   // 文本大小 可以调整
		textnum.text = std::to_string(static_cast<int>(i+1));         // 文本内容
		textnum.angle = 0;                     // 旋转角度（水平）

		textheight.basePoint.x = m_results[i].first + basex - 1;
		textheight.basePoint.y = ((m_results[i].second -1500) / 2);
		textheight.height = 0.5;
		textheight.text = std::to_string(static_cast<float>(m_results[i].second));
		textheight.angle = 90;
		textheight.color = 1;
		//绘制高度竖线
		line.basePoint.x = m_results[i].first + basex;//设置起始点坐标
		line.basePoint.y = 0;
		line.secPoint.x = m_results[i].first + basex;//设置终点坐标
		line.secPoint.y = m_results[i].second - 1500;
		m_dxfW.writeLine(&line);
		m_dxfW.writeText(&textnum);
		m_dxfW.writeText(&textheight);
	}
	for (int i = 0; i < m_results.size(); i++) {
		// 添加顶点
		DRW_Vertex2D* v1 = polyline.addVertex();
		v1->x = m_results[i].first + basex;
		v1->y = m_results[i].second - 1500;
		m_dxfW.writeLWPolyline(&polyline);
	}

}

std::vector<std::vector<std::pair<float, float>>> DXFREAD::getCenterlines()
{
	return m_centerlines;
}

void DXFREAD::addLWPolyline(const DRW_LWPolyline & data)
{
	std::cout << "Found LWPolyline with " << data.vertlist.size() << " vertices." << std::endl;
	std::vector<std::pair<float, float>> centerline;
	// 读取并打印所有顶点信息
	for (const auto& vertex : data.vertlist) {
		std::pair<float, float> point(vertex->x, vertex->y);
		centerline.push_back(point);
		std::cout << "Vertex: x = " << vertex->x << ", y = " << vertex->y
			<< ", Start Width = " << vertex->stawidth
			<< ", End Width = " << vertex->endwidth
			<< ", Bulge = " << vertex->bulge << std::endl;
	}
	m_centerlines.push_back(centerline);
}

DXFALLWRITE::DXFALLWRITE(dxfRW &dxfW, std::vector<std::vector<pcl::PointXYZ>> results_points) : m_dxfW(dxfW), m_results_points(results_points) {
}

void DXFALLWRITE::writeEntities()
{
	for (int i = 0; i < m_results_points.size(); i++) {
		//DRW_Polyline  polyline;
		//polyline.flags = 0; // 0 表示不闭合
		//for (int j = 0; j < m_results_points[i].size(); j++) {
		//	DRW_Vertex vertex;
		//	vertex.basePoint.x = m_results_points[i][j].x;  // 设置顶点的 X 坐标
		//	vertex.basePoint.y = m_results_points[i][j].y;  // 设置顶点的 Y 坐标
		//	vertex.basePoint.z = m_results_points[i][j].z;  // 设置顶点的 Z 坐标
		//	polyline.addVertex(vertex);
		//}
		//m_dxfW.writePolyline(&polyline);
		DRW_LWPolyline polyline;
		polyline.flags = 0; // 0 表示不闭合
		polyline.elevation = 0; // 多段线的 Z 坐标
		for (int j = 0; j < m_results_points[i].size(); j++) {
			// 添加顶点
			DRW_Vertex2D* v1 = polyline.addVertex();
			v1->x = m_results_points[i][j].x;
			v1->y = m_results_points[i][j].y;
			m_dxfW.writeLWPolyline(&polyline);
			DRW_Text textheight;
			textheight.basePoint.x = m_results_points[i][j].x;
			textheight.basePoint.y = m_results_points[i][j].y+5;
			textheight.height = 1;
			textheight.text = std::to_string(static_cast<float>(m_results_points[i][j].z));
			textheight.color = 1;
			m_dxfW.writeLWPolyline(&polyline);
			m_dxfW.writeText(&textheight);
		}
	}
}


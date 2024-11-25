#include "CADRW.h"





CADRW::CADRW(dxfRW &dxfW, std::vector<std::pair<float, float>> results) : m_dxfW(dxfW), m_results(results){
}


void CADRW::writeEntities()
{
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
	axisLiney.secPoint.y = 65;    // 终点 Y
	m_dxfW.writeLine(&axisLiney);
	axisLinex.basePoint.x = 0;    // 起点 X
	axisLinex.basePoint.y = 0;   // 起点 Y
	axisLinex.secPoint.x = 190+ basex;     // 终点 X
	axisLinex.secPoint.y = 0;    // 终点 Y
	m_dxfW.writeLine(&axisLinex);
	 // 2. 绘制刻度线并添加文字标注
	double yMin = 0;  // 坐标轴起始 Y
	double yMax = 65;  // 坐标轴结束 Y
	double ymajorStep = 5; // 主要刻度间隔
	double yminorStep = 1; // 次要刻度间隔

	double xMin = basex;  // 坐标轴起始 x
	double xMax = 190 + basex;  // 坐标轴结束 x
	double xmajorStep = 10; // 主要刻度间隔
	double xminorStep = 1; // 次要刻度间隔
	//y轴
	for (double y = yMin; y <= yMax; y += yminorStep) {
		DRW_Line tickLine;
		tickLine.basePoint.x = 0;       // 起点 X
		tickLine.basePoint.y = y;       // 起点 Y
		tickLine.secPoint.y = y;        // 终点 Y

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
			label.basePoint.x = -2.5;    // 文字偏移 X
			label.basePoint.y = y;      // 文字 Y 坐标
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
			label.basePoint.y = -2.5;      // 文字 Y 坐标
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
		textnum.basePoint.y = m_results[i].second + 1;             // 插入点 Y 坐标
		textnum.height = 0.5;                   // 文本大小 可以调整
		textnum.text = std::to_string(static_cast<int>(i+1));         // 文本内容
		textnum.angle = 0;                     // 旋转角度（水平）

		textheight.basePoint.x = m_results[i].first + basex - 1;
		textheight.basePoint.y = (m_results[i].second / 2);
		textheight.height = 0.5;
		textheight.text = std::to_string(static_cast<float>(m_results[i].second));
		textheight.angle = 90;
		textheight.color = 1;
		line.basePoint.x = m_results[i].first + basex;//设置起始点坐标
		line.basePoint.y = 0;
		line.secPoint.x = m_results[i].first + basex;//设置终点坐标
		line.secPoint.y = m_results[i].second;
		m_dxfW.writeLine(&line);
		m_dxfW.writeText(&textnum);
		m_dxfW.writeText(&textheight);
	}
	for (int i = 0; i < m_results.size(); i++) {
		// 添加顶点
		DRW_Vertex2D* v1 = polyline.addVertex();
		v1->x = m_results[i].first + basex;
		v1->y = m_results[i].second;
		m_dxfW.writeLWPolyline(&polyline);
	}

}



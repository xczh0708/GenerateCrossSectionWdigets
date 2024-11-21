#include "CADRW.h"





CADRW::CADRW(dxfRW &dxfW, std::vector<std::pair<float, float>> results) : m_dxfW(dxfW), m_results(results){
}


void CADRW::writeEntities()
{
	for (int i = 0; i < m_results.size(); i++) {
		DRW_Line line;
		DRW_Text text;
	
		text.basePoint.x = m_results[i].first;              // 插入点 X 坐标
		text.basePoint.y = 0;             // 插入点 Y 坐标
		text.height = 10;                   // 文本大小 可以调整
		text.text = "Hello, DXF!";          // 文本内容
		text.angle = 0;                     // 旋转角度（水平）
		text.style = "STANDARD";            // 字体样式
		text.alignH = DRW_Text::HAlign::HCenter; // 水平居中对齐
		text.alignV = DRW_Text::VAlign::VMiddle; // 垂直居中对齐

		line.basePoint.x = m_results[i].first;//设置起始点坐标
		line.basePoint.y = 0;
		line.secPoint.x = m_results[i].first;//设置终点坐标
		line.secPoint.y = m_results[i].second;
		m_dxfW.writeLine(&line);
		m_dxfW.writeText(&text);
	}
	
}



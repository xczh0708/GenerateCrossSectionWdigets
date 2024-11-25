#include "CADRW.h"





CADRW::CADRW(dxfRW &dxfW, std::vector<std::pair<float, float>> results) : m_dxfW(dxfW), m_results(results){
}


void CADRW::writeEntities()
{
	double basex = 10.0;
	DRW_LWPolyline polyline;
	polyline.flags = 0; // 0 ��ʾ���պ�
	polyline.elevation = 0; // ����ߵ� Z ����
	DRW_Line axisLiney;
	DRW_Line axisLinex;
	//����������
	axisLiney.basePoint.x = 0;    // ��� X
	axisLiney.basePoint.y = 0;   // ��� Y
	axisLiney.secPoint.x = 0;     // �յ� X
	axisLiney.secPoint.y = 65;    // �յ� Y
	m_dxfW.writeLine(&axisLiney);
	axisLinex.basePoint.x = 0;    // ��� X
	axisLinex.basePoint.y = 0;   // ��� Y
	axisLinex.secPoint.x = 190+ basex;     // �յ� X
	axisLinex.secPoint.y = 0;    // �յ� Y
	m_dxfW.writeLine(&axisLinex);
	 // 2. ���ƿ̶��߲�������ֱ�ע
	double yMin = 0;  // ��������ʼ Y
	double yMax = 65;  // ��������� Y
	double ymajorStep = 5; // ��Ҫ�̶ȼ��
	double yminorStep = 1; // ��Ҫ�̶ȼ��

	double xMin = basex;  // ��������ʼ x
	double xMax = 190 + basex;  // ��������� x
	double xmajorStep = 10; // ��Ҫ�̶ȼ��
	double xminorStep = 1; // ��Ҫ�̶ȼ��
	//y��
	for (double y = yMin; y <= yMax; y += yminorStep) {
		DRW_Line tickLine;
		tickLine.basePoint.x = 0;       // ��� X
		tickLine.basePoint.y = y;       // ��� Y
		tickLine.secPoint.y = y;        // �յ� Y

		if (static_cast<int>(y) % static_cast<int>(ymajorStep) == 0) {
			// ��Ҫ�̶ȣ����̶��ߣ�
			tickLine.secPoint.x = 2.0;  // ���̶ȳ���
		}
		else {
			// ��Ҫ�̶ȣ��̶̿��ߣ�
			tickLine.secPoint.x = 1.0;  // �̶̿ȳ���
		}
		m_dxfW.writeLine(&tickLine);

		// Ϊ��Ҫ�̶�������ֱ�ע
		if (static_cast<int>(y) % static_cast<int>(ymajorStep) == 0) {
			DRW_Text label;
			label.basePoint.x = -2.5;    // ����ƫ�� X
			label.basePoint.y = y;      // ���� Y ����
			label.basePoint.z = 0;      // ���� Z ����
			label.text = std::to_string(static_cast<int>(y)); // ��ע����
			label.height = 1.0;         // ����߶�
			label.angle = 0.0;          // ��ת�Ƕ�
			//label.alignH = DRW_Text::HAlign::HLeft; // ˮƽ�����
			//label.alignV = DRW_Text::VAlign::VMiddle; // ��ֱ����
			m_dxfW.writeText(&label);
		}
	}
	//x��
	for (double x = xMin; x <= xMax; x += xminorStep) {
		DRW_Line tickLine;
		tickLine.basePoint.x = x;       // ��� X
		tickLine.basePoint.y = 0;       // ��� Y
		tickLine.secPoint.x = x;        // �յ� Y

		if (static_cast<int>(x) % static_cast<int>(xmajorStep) == 0) {
			// ��Ҫ�̶ȣ����̶��ߣ�
			tickLine.secPoint.y = 2.0;  // ���̶ȳ���
		}
		else {
			// ��Ҫ�̶ȣ��̶̿��ߣ�
			tickLine.secPoint.y = 1.0;  // �̶̿ȳ���
		}
		m_dxfW.writeLine(&tickLine);

		// Ϊ��Ҫ�̶�������ֱ�ע
		if (static_cast<int>(x) % static_cast<int>(xmajorStep) == 0) {
			DRW_Text label;
			label.basePoint.x = x;    // ����ƫ�� X
			label.basePoint.y = -2.5;      // ���� Y ����
			label.basePoint.z = 0;      // ���� Z ����
			label.text = std::to_string(static_cast<int>(x)); // ��ע����
			label.height = 1.0;         // ����߶�
			label.angle = 0.0;          // ��ת�Ƕ�
			m_dxfW.writeText(&label);
		}
	}
	//���Ƹ߶���
	for (int i = 0; i < m_results.size(); i++) {
		DRW_Line line;
		DRW_Text textnum;
		DRW_Text textheight;
		textnum.basePoint.x = m_results[i].first + basex;              // ����� X ����
		textnum.basePoint.y = m_results[i].second + 1;             // ����� Y ����
		textnum.height = 0.5;                   // �ı���С ���Ե���
		textnum.text = std::to_string(static_cast<int>(i+1));         // �ı�����
		textnum.angle = 0;                     // ��ת�Ƕȣ�ˮƽ��

		textheight.basePoint.x = m_results[i].first + basex - 1;
		textheight.basePoint.y = (m_results[i].second / 2);
		textheight.height = 0.5;
		textheight.text = std::to_string(static_cast<float>(m_results[i].second));
		textheight.angle = 90;
		textheight.color = 1;
		line.basePoint.x = m_results[i].first + basex;//������ʼ������
		line.basePoint.y = 0;
		line.secPoint.x = m_results[i].first + basex;//�����յ�����
		line.secPoint.y = m_results[i].second;
		m_dxfW.writeLine(&line);
		m_dxfW.writeText(&textnum);
		m_dxfW.writeText(&textheight);
	}
	for (int i = 0; i < m_results.size(); i++) {
		// ��Ӷ���
		DRW_Vertex2D* v1 = polyline.addVertex();
		v1->x = m_results[i].first + basex;
		v1->y = m_results[i].second;
		m_dxfW.writeLWPolyline(&polyline);
	}

}



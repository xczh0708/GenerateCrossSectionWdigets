#include "CADRW.h"





CADRW::CADRW(dxfRW &dxfW, std::vector<std::pair<float, float>> results) : m_dxfW(dxfW), m_results(results){
}


void CADRW::writeEntities()
{
	for (int i = 0; i < m_results.size(); i++) {
		DRW_Line line;
		DRW_Text text;
	
		text.basePoint.x = m_results[i].first;              // ����� X ����
		text.basePoint.y = 0;             // ����� Y ����
		text.height = 10;                   // �ı���С ���Ե���
		text.text = "Hello, DXF!";          // �ı�����
		text.angle = 0;                     // ��ת�Ƕȣ�ˮƽ��
		text.style = "STANDARD";            // ������ʽ
		text.alignH = DRW_Text::HAlign::HCenter; // ˮƽ���ж���
		text.alignV = DRW_Text::VAlign::VMiddle; // ��ֱ���ж���

		line.basePoint.x = m_results[i].first;//������ʼ������
		line.basePoint.y = 0;
		line.secPoint.x = m_results[i].first;//�����յ�����
		line.secPoint.y = m_results[i].second;
		m_dxfW.writeLine(&line);
		m_dxfW.writeText(&text);
	}
	
}



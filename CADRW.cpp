#include "CADRW.h"



CADRW::CADRW(const std::string & filename)
{
	m_file.open(filename);
	if (!m_file.is_open()) {
		throw std::runtime_error("�޷����ļ���д�룡");
	}
}

CADRW::~CADRW()
{
	if (m_file.is_open()) {
		m_file.close();
	}
}

void CADRW::dxfWrite(dxfRW & dxfW)
{
	DRW_Line line;
	line.basePoint.x = 100;
	line.basePoint.y = 200;
	line.secPoint.x = 300;
	line.secPoint.y = 300;
	dxfW.writeLine(&line);

	DRW_Line line2;
	line2.basePoint.x = 0;
	line2.basePoint.y = 0;
	line2.secPoint.x = 0;
	line2.secPoint.y = 300;
	dxfW.writeLine(&line2);
}

void CADRW::writePoint(double x, double y, double z)
{
	m_file << "  0\nPOINT\n";
	m_file << "  8\n0\n";               // ͼ�����ƣ�Ĭ��ͼ�� 0
	m_file << " 10\n" << x << "\n";     // X ����
	m_file << " 20\n" << y << "\n";     // Y ����
	m_file << " 30\n" << z << "\n";     // Z ����
}

void CADRW::writeLine(double x1, double y1, double z1, double x2, double y2, double z2)
{
	m_file << "  0\nLINE\n";
	m_file << "  8\n0\n";               // ͼ�����ƣ�Ĭ��ͼ�� 0
	m_file << " 10\n" << x1 << "\n";    // ��� X
	m_file << " 20\n" << y1 << "\n";    // ��� Y
	m_file << " 30\n" << z1 << "\n";    // ��� Z
	m_file << " 11\n" << x2 << "\n";    // �յ� X
	m_file << " 21\n" << y2 << "\n";    // �յ� Y
	m_file << " 31\n" << z2 << "\n";    // �յ� Z
}

void CADRW::endSection()
{
	m_file << "  0\nENDSEC\n";
}

void CADRW::endFile()
{
	m_file << "  0\nEOF\n";
}

void CADRW::addHeader(const DRW_Header * data)
{
	m_file << "  0\nSECTION\n  2\nHEADER\n"; // д�� HEADER ��
	m_file << "  0\nENDSEC\n";              // HEADER ����
}



#include "GenerateCrossSectionWdigets.h"

GenerateCrossSectionWdigets::GenerateCrossSectionWdigets(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	connect(ui.actionOpen, &QAction::triggered, this, &GenerateCrossSectionWdigets::openFile);
}

void GenerateCrossSectionWdigets::openFile() {
	m_fileName = QFileDialog::getOpenFileName(this, tr("���ļ�"), "", tr("All Files (*.*);;Text Files (*.txt)"));
	if (!m_fileName.isEmpty()) {
		// ����ѡ����ļ�
		// ���磬���Խ��ļ�·����ʾ��״̬���������ؼ���
		
	}
}

GenerateCrossSectionWdigets::~GenerateCrossSectionWdigets()
{
}

#include "GenerateCrossSectionWdigets.h"

GenerateCrossSectionWdigets::GenerateCrossSectionWdigets(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	connect(ui.actionOpen, &QAction::triggered, this, &GenerateCrossSectionWdigets::openFile);
}

void GenerateCrossSectionWdigets::openFile() {
	m_fileName = QFileDialog::getOpenFileName(this, tr("打开文件"), "", tr("All Files (*.*);;Text Files (*.txt)"));
	if (!m_fileName.isEmpty()) {
		// 处理选择的文件
		// 例如，可以将文件路径显示在状态栏或其他控件中
		
	}
}

GenerateCrossSectionWdigets::~GenerateCrossSectionWdigets()
{
}

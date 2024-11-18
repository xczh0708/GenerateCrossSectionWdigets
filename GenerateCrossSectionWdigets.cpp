#include "GenerateCrossSectionWdigets.h"

GenerateCrossSectionWdigets::GenerateCrossSectionWdigets(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	// 连接按钮点击信号到槽函数
	connect(ui.actionOpen, &QAction::triggered, this, &GenerateCrossSectionWdigets::openFile);
	connect(ui.quitButton, &QPushButton::clicked, this, &GenerateCrossSectionWdigets::onQuitButtonClicked);
}

void GenerateCrossSectionWdigets::openFile() {
	m_fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("打开点云文件"), "", tr("All Files (*.*);;Text Files (*.las)"));
	if (!m_fileName.isEmpty()) {
		// 处理选择的文件
		// 例如，可以将文件路径显示在状态栏或其他控件中
	}
}

GenerateCrossSectionWdigets::~GenerateCrossSectionWdigets()
{
}

QString GenerateCrossSectionWdigets::getOpenFileName()
{
	return m_fileName;
}

void GenerateCrossSectionWdigets::onQuitButtonClicked()
{
	QApplication::quit(); // 退出程序
}

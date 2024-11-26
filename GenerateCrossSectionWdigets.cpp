#include "GenerateCrossSectionWdigets.h"

GenerateCrossSectionWdigets::GenerateCrossSectionWdigets(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	// 连接按钮点击信号到槽函数
	connect(ui.actionOpen, &QAction::triggered, this, &GenerateCrossSectionWdigets::openFile);
	connect(ui.quitButton, &QPushButton::clicked, this, &GenerateCrossSectionWdigets::onQuitButtonClicked);
	connect(ui.lidarOpenButton, &QPushButton::clicked, this, &GenerateCrossSectionWdigets::onOpenLidar);
	connect(ui.sectionOpenButton, &QPushButton::clicked, this, &GenerateCrossSectionWdigets::onOpenSection);
	connect(ui.dxfSaveButton, &QPushButton::clicked, this, &GenerateCrossSectionWdigets::onSaveDXF);
	connect(ui.dwgSaveButton, &QPushButton::clicked, this, &GenerateCrossSectionWdigets::onSaveDWG);
	connect(ui.txtSaveButton, &QPushButton::clicked, this, &GenerateCrossSectionWdigets::onSaveTXT);
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

void GenerateCrossSectionWdigets::onOpenLidar()
{
	m_lidarOpenFileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("打开点云文件"), "", QString::fromLocal8Bit("激光雷达点云文件(*.las)"));
	if (!m_lidarOpenFileName.isEmpty()) {
		ui.lidarLE->setText(m_lidarOpenFileName);
	}
}

void GenerateCrossSectionWdigets::onOpenSection()
{
	m_sectionOpenFileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("打开横断面提取线文件"), "", QString::fromLocal8Bit("提取线文件 (*.*);"));
	if (!m_sectionOpenFileName.isEmpty()) {
		ui.sectionLE->setText(m_sectionOpenFileName);
	}
}

void GenerateCrossSectionWdigets::onSaveDXF()
{
	m_dxfSaveFileName = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("保存dxf文件"), "", QString::fromLocal8Bit("dxf文件 (*.dxf)"));
	if (!m_dxfSaveFileName.isEmpty()) {
		ui.dxfSaveLE->setText(m_lidarOpenFileName);
	}
}

void GenerateCrossSectionWdigets::onSaveDWG()
{
	m_dwgSaveFileName = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("保存dwg文件"), "", QString::fromLocal8Bit("dwg文件(*.dwg)"));
	if (!m_dwgSaveFileName.isEmpty()) {
		ui.dwgSaveLE->setText(m_lidarOpenFileName);
	}
}

void GenerateCrossSectionWdigets::onSaveTXT()
{
	m_txtSaveFileName = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("保存txt文件"), "", tr("文本文件 (*.txt)"));
	if (!m_txtSaveFileName.isEmpty()) {
		ui.txtSaveLE->setText(m_lidarOpenFileName);
	}
}

void GenerateCrossSectionWdigets::start()
{
	m_gcs.readLasData(m_lidarOpenFileName.toStdString().c_str());
	m_gcs.samplePoint();//需要文件读取
	m_gcs.getResults();
}

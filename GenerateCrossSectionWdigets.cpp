#include "GenerateCrossSectionWdigets.h"

GenerateCrossSectionWdigets::GenerateCrossSectionWdigets(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	// ���Ӱ�ť����źŵ��ۺ���
	connect(ui.actionOpen, &QAction::triggered, this, &GenerateCrossSectionWdigets::openFile);
	connect(ui.quitButton, &QPushButton::clicked, this, &GenerateCrossSectionWdigets::onQuitButtonClicked);
	connect(ui.lidarOpenButton, &QPushButton::clicked, this, &GenerateCrossSectionWdigets::onOpenLidar);
	connect(ui.sectionOpenButton, &QPushButton::clicked, this, &GenerateCrossSectionWdigets::onOpenSection);
	connect(ui.dxfSaveButton, &QPushButton::clicked, this, &GenerateCrossSectionWdigets::onSaveDXF);
	connect(ui.dwgSaveButton, &QPushButton::clicked, this, &GenerateCrossSectionWdigets::onSaveDWG);
	connect(ui.txtSaveButton, &QPushButton::clicked, this, &GenerateCrossSectionWdigets::onSaveTXT);
}

void GenerateCrossSectionWdigets::openFile() {
	m_fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("�򿪵����ļ�"), "", tr("All Files (*.*);;Text Files (*.las)"));
	if (!m_fileName.isEmpty()) {
		// ����ѡ����ļ�
		// ���磬���Խ��ļ�·����ʾ��״̬���������ؼ���
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
	QApplication::quit(); // �˳�����
}

void GenerateCrossSectionWdigets::onOpenLidar()
{
	m_lidarOpenFileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("�򿪵����ļ�"), "", QString::fromLocal8Bit("�����״�����ļ�(*.las)"));
	if (!m_lidarOpenFileName.isEmpty()) {
		ui.lidarLE->setText(m_lidarOpenFileName);
	}
}

void GenerateCrossSectionWdigets::onOpenSection()
{
	m_sectionOpenFileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("�򿪺������ȡ���ļ�"), "", QString::fromLocal8Bit("��ȡ���ļ� (*.*);"));
	if (!m_sectionOpenFileName.isEmpty()) {
		ui.sectionLE->setText(m_sectionOpenFileName);
	}
}

void GenerateCrossSectionWdigets::onSaveDXF()
{
	m_dxfSaveFileName = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("����dxf�ļ�"), "", QString::fromLocal8Bit("dxf�ļ� (*.dxf)"));
	if (!m_dxfSaveFileName.isEmpty()) {
		ui.dxfSaveLE->setText(m_lidarOpenFileName);
	}
}

void GenerateCrossSectionWdigets::onSaveDWG()
{
	m_dwgSaveFileName = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("����dwg�ļ�"), "", QString::fromLocal8Bit("dwg�ļ�(*.dwg)"));
	if (!m_dwgSaveFileName.isEmpty()) {
		ui.dwgSaveLE->setText(m_lidarOpenFileName);
	}
}

void GenerateCrossSectionWdigets::onSaveTXT()
{
	m_txtSaveFileName = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("����txt�ļ�"), "", tr("�ı��ļ� (*.txt)"));
	if (!m_txtSaveFileName.isEmpty()) {
		ui.txtSaveLE->setText(m_lidarOpenFileName);
	}
}

void GenerateCrossSectionWdigets::start()
{
	m_gcs.readLasData(m_lidarOpenFileName.toStdString().c_str());
	m_gcs.samplePoint();//��Ҫ�ļ���ȡ
	m_gcs.getResults();
}

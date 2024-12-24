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
	connect(ui.startButton, &QPushButton::clicked, this, &GenerateCrossSectionWdigets::start);
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
	m_dxfSaveFolderName = QFileDialog::getExistingDirectory(this, "ѡ���ļ���");
	if (!m_dxfSaveFolderName.isEmpty()) {
		ui.dxfSaveLE->setText(m_dxfSaveFolderName);
	}
}

void GenerateCrossSectionWdigets::onSaveDWG()
{
	m_dwgSaveFileName = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("����dwg�ļ�"), "", QString::fromLocal8Bit("dwg�ļ�(*.dwg)"));
	if (!m_dwgSaveFileName.isEmpty()) {
		ui.dwgSaveLE->setText(m_dwgSaveFileName);
	}
}

void GenerateCrossSectionWdigets::onSaveTXT()
{
	m_txtSaveFolderName = QFileDialog::getExistingDirectory(this, "ѡ���ļ���");
	if (!m_txtSaveFolderName.isEmpty()) {
		ui.txtSaveLE->setText(m_txtSaveFolderName);
	}
}

void GenerateCrossSectionWdigets::start()
{
	m_extra_line_long = ui.extra_line_long->text().toFloat();
	m_extra_line_point_num = ui.extra_line_point_num->text().toInt();
	m_extra_line_num = ui.extra_line_num->text().toFloat();
	// ���� MyDxfInterface ʵ��
	DXFREAD interface1;
	// ���� dxfRW ʵ����ָ�� DXF �ļ�·��
	dxfRW reader(m_sectionOpenFileName.toStdString().c_str());
	// ��ȡ DXF �ļ��������ݴ��ݸ� MyDxfInterface
	bool ext = true;  // �����Ҫ�ڶ�ȡʱӦ�ü�����ת��Ϊ2D��������Ϊ true
	if (reader.read(&interface1, ext)) {
		std::cout << "DXF file read successfully!" << std::endl;
	}
	else {
		std::cerr << "Failed to read the DXF file." << std::endl;
	}
	std::vector<std::vector<std::pair<float, float>>> centerlines = interface1.getCenterlines();
	std::vector<std::pair<float, float>> centerline = centerlines[centerlines.size() - 1];
	m_gcs.readLasData(m_lidarOpenFileName.toStdString().c_str());
	m_gcs.getCenterLines(centerline, m_extra_line_num, m_extra_line_long);
	m_gcs.getHeight(0.5, m_extra_line_point_num);
	m_gcs.txtWrite(m_txtSaveFolderName.toStdString().c_str(), "��������", "����ϵ����", "�ȴ���", "�߳�ϵͳ����");
	m_gcs.txtAllWrite(m_txtSaveFolderName.toStdString().c_str());
	int num_file = 0;
	for (const auto& result : m_gcs.getResults()) {
		std::string filename = std::string(m_dxfSaveFolderName.toStdString().c_str()) + "/dxf_res" + std::to_string(num_file) + ".dxf";
		dxfRW dxf(filename.c_str());
		CADRW writer(dxf, result);
		dxf.write(&writer, DRW::Version::AC1027, false);
		num_file++;
	}
	//д�븩��ͼ
	std::vector<std::vector<pcl::PointXYZ>> results_points;
	results_points = m_gcs.getResultsPoints();
	std::string filename = std::string(m_dxfSaveFolderName.toStdString().c_str()) + "/dxf_all.dxf";
	dxfRW dxf(filename.c_str());
	DXFALLWRITE dxfallwrite(dxf, results_points);
	dxf.write(&dxfallwrite, DRW::Version::AC1027, false);
	std::cout << "����" << std::endl;
}

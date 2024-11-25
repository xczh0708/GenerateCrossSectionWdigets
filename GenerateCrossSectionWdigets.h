#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GenerateCrossSectionWdigets.h"
#include <QFileDialog>
#include <QApplication>
class GenerateCrossSectionWdigets : public QMainWindow
{
    Q_OBJECT

public:
    GenerateCrossSectionWdigets(QWidget *parent = nullptr);
    ~GenerateCrossSectionWdigets();
	QString getOpenFileName();
private slots:
	void openFile();
	void onQuitButtonClicked();
	void onOpenLidar();
	void onOpenSection();
	void onSaveDXF();
	void onSaveDWG();
	void onSaveTXT();
private:
    Ui::GenerateCrossSectionWdigetsClass ui;
	QString m_fileName;
	QString m_lidarOpenFileName;
	QString m_sectionOpenFileName;
	QString m_dwgSaveFileName;
	QString m_dxfSaveFileName;
	QString m_txtSaveFileName;
};

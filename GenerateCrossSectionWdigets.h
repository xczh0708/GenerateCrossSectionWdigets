#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GenerateCrossSectionWdigets.h"
#include <QFileDialog>
class GenerateCrossSectionWdigets : public QMainWindow
{
    Q_OBJECT

public:
    GenerateCrossSectionWdigets(QWidget *parent = nullptr);
    ~GenerateCrossSectionWdigets();
	QString getOpenFileName();
private slots:
	void openFile();
private:
    Ui::GenerateCrossSectionWdigetsClass ui;
	QString m_fileName;
};

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QGridLayout>
#include <QApplication>
#include <QCoreApplication>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTabWidget>
#include <QFont>
#include <QFileDialog>

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
private:
	QWidget *_baseWindow;
	QTabWidget *huffmanTabs;
	void createHuffmanTree();
	void encodeFile();
	void decodeFile();
	void setStyle();
};
#endif // MAINWINDOW_H

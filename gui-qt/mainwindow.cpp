#include "mainwindow.h"
#include <QGraphicsTextItem>
#include <QFileDialog>
#include <QPushButton>
#include "huffman_builder.h"
#include "huffman_encoder.h"
#include "huffman_decoder.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	this->setStyle();

	_baseWindow = new QWidget(this);
	_baseWindow->setFixedSize(400, 230);
	QGridLayout *baseLayout = new QGridLayout(_baseWindow);

	huffmanTabs = new QTabWidget(_baseWindow);
	huffmanTabs->setFixedSize(380,200);

	QWidget *treeCreateTab = new QWidget();
	QGridLayout *treeCreateGrid = new QGridLayout(treeCreateTab);
	QPushButton *selectFileButton = new QPushButton("Select file", treeCreateTab);
	selectFileButton->setFixedSize(200, 50);
	treeCreateGrid->addWidget(selectFileButton, 5, 5, 5, 5, Qt::AlignCenter);
	huffmanTabs->addTab(treeCreateTab, "Huffman Tree");

	QWidget *encodeTab = new QWidget();
	QGridLayout *encodeTabGrid = new QGridLayout(encodeTab);
	QPushButton *selectFileButton1 = new QPushButton("Select huffman tree and file", encodeTab);
	selectFileButton1->setFixedSize(200, 50);
	encodeTabGrid->addWidget(selectFileButton1, 5, 5, 5, 5, Qt::AlignCenter);
	huffmanTabs->addTab(encodeTab, "Encode");

	QWidget *decodeTab = new QWidget();
	QGridLayout *decodeTabGrid = new QGridLayout(decodeTab);
	QPushButton *selectFileButton2 = new QPushButton("Select huffman tree and file", decodeTab);
	selectFileButton2->setFixedSize(200, 50);
	decodeTabGrid->addWidget(selectFileButton2, 5, 5, 5, 5, Qt::AlignCenter);
	huffmanTabs->addTab(decodeTab, "Decode");

	baseLayout->addWidget(huffmanTabs);

	QObject::connect(selectFileButton, &QPushButton::clicked, this, &MainWindow::createHuffmanTree);
	QObject::connect(selectFileButton1, &QPushButton::clicked, this, &MainWindow::encodeFile);
	QObject::connect(selectFileButton2, &QPushButton::clicked, this, &MainWindow::decodeFile);

	this->setCentralWidget(_baseWindow);
}

MainWindow::~MainWindow() {}

void MainWindow::createHuffmanTree() {
	QString filename = QFileDialog::getOpenFileName(this, "Base input file");
	huffmanBuilder huffBuild(filename.toUtf8().data());
	filename += ".hufftree";
	huffBuild.writeHuffmanTree(filename.toUtf8().data());
}

void MainWindow::encodeFile() {
	QString filename = QFileDialog::getOpenFileName(this, "Huffman tree file");
	huffmanEncoder enc(filename.toUtf8().data());
	filename = QFileDialog::getOpenFileName(this, "File to encode");
	QString encd = filename + ".huff";
	enc.encode(filename.toUtf8().data(), encd.toUtf8().data());
}

void MainWindow::decodeFile() {
	QString filename = QFileDialog::getOpenFileName(this, "Huffman tree file");
	huffmanDecoder dec(filename.toUtf8().data());
	filename = QFileDialog::getOpenFileName(this, "File to decode");
	QString decd = filename;
	if (decd.contains(".huff"))
		decd = decd.mid(0, decd.length()-5);
	dec.decode(filename.toUtf8().data(), decd.toUtf8().data());
}

void MainWindow::setStyle()
{
	static_cast<QApplication*>(QCoreApplication::instance())->
		  setStyleSheet(""
						"* {"
							"font-family: DejaVu sans;"
							"font-size: 4em;"
							"color: #d9d8ff;"
						"}"
						""
						"QWidget {"
							"background: #2c3e50;"
							"font-family: DejaVu sans;"
							"font-size: 10em;"
							"color: #bedaed;"
						"}"
						""
						".QPushButton {"
							"border-radius: 5%;"
							"height: 30%;"
							"width: 30%;"
							"border: 2px solid #2a6fb5;"
							"background: #4874a1;"
							"color: #ecf0f1;"
						"}"
						""
						".QPushButton:pressed {"
							"background: #1882ed"
						"}"
						".QLineEdit {"
							"border-radius: 0px;"
							"color: #000000;"
							"background: #61798f;"
						"}"
						".QLabel {"
							"font-size: 18px;"
							"color: #ecf0f1;"
							"font-family: Arial;"
						"}"
						""
	);
}

#include <QtGui>

#include "QMenu"
#include "QAction"
#include "QTextEdit"
#include "QLabel"
#include "QWorkspace"
#include "QFileDialog"

#include "mainwindow.h"

MainWindow::MainWindow()
{
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle("TestWindow");
	text = new QTextEdit("QTextEdit",this);
	setCentralWidget(text);
	
	createActions();
	createMenus();
	createTools();
	createStatus();

}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newFileAction);	
	fileMenu->addAction(openFileAction);
	fileMenu->addAction(saveFileAction);	
	fileMenu->addAction(exitAction);
	
	editMenu = menuBar()->addMenu(tr("Edit"));
	editMenu->addAction(copyAction);
	editMenu->addAction(cutAction);
	editMenu->addAction(pasteAction);
	
	helpMenu = menuBar()->addMenu(tr("Help"));
	helpMenu->addAction(aboutAction);
}

void MainWindow::createActions()
{
	//file
	newFileAction = new QAction(QIcon(":/images/new.png"),tr("New"),this);
	newFileAction->setShortcut(tr("Ctrl+N"));  
	newFileAction->setStatusTip(tr("New File"));  
	connect(newFileAction,SIGNAL(triggered()),this,SLOT(slotNewFile()));
	
	openFileAction = new QAction(QIcon(":/images/open.png"),tr("Open"),this);
	openFileAction->setStatusTip(tr("Open File"));  
	connect(openFileAction,SIGNAL(triggered()),this,SLOT(slotOpenFile()));
	
	saveFileAction = new QAction(QIcon(":/images/save.png"),tr("Save"),this);
	saveFileAction->setStatusTip(tr("Save File")); 	
	connect(saveFileAction,SIGNAL(triggered()),this,SLOT(slotSaveFile()));
	
	exitAction = new QAction("Exit",this);
	exitAction->setStatusTip(tr("Exit"));  
	connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
	
	//edit
	copyAction = new QAction(QIcon(":/images/copy.png"),tr("Copy"),this);
	copyAction->setStatusTip(tr("Copy"));  	
	connect(copyAction,SIGNAL(triggered()),this,SLOT(slotCopy()));
	
	cutAction = new QAction(QIcon(":/images/cut.png"),tr("Cut"),this);
	cutAction->setStatusTip(tr("Cut"));  
	connect(cutAction,SIGNAL(triggered()),this,SLOT(slotCut()));
	
	pasteAction = new QAction(QIcon(":/images/paste.png"),tr("Paste"),this);
	pasteAction->setStatusTip(tr("Paste")); 
	connect(pasteAction,SIGNAL(triggered()),this,SLOT(slotPaste()));
	
	//help
	aboutAction = new QAction(tr("About"),this);
	aboutAction->setStatusTip(tr("About Qt")); 
	connect(aboutAction,SIGNAL(triggered()),this,SLOT(slotAbout()));
	
}


void MainWindow::createTools()
{
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->setMovable(false);
	fileToolBar->addAction(newFileAction);
	fileToolBar->addAction(openFileAction);
	fileToolBar->addAction(saveFileAction);	
	
	editToolBar = addToolBar(tr("Edit"));
	editToolBar->setMovable(false);
	editToolBar->addAction(copyAction);
	editToolBar->addAction(cutAction);
	editToolBar->addAction(pasteAction);
}


void MainWindow::createStatus()
{
	statusBarLabel = new QLabel("Ready");
	statusBarLabel->setAlignment(Qt::AlignHCenter);//设置对齐方式
	statusBarLabel->setMinimumSize(statusBarLabel->sizeHint());
	statusBar()->addWidget(statusBarLabel);
	statusBar()->setStyleSheet(QString ("QStatusBar::item{border:0px}"));
	connect(text,SIGNAL(cursorPositionChanged()),this,SLOT(slotMoveCursor()));


}


void MainWindow::loadFile(QString fileName)
{
	QFile file(fileName);//The QFile class provides an interface for reading from and writing to files
	if(file.open(QIODevice::ReadOnly|QIODevice::Text))
	{
		//Using Streams to Read Files
		QTextStream textStream(&file);
		while(!textStream.atEnd())
		{
			text->append(textStream.readLine());
		}
		
	}
	
}

void MainWindow::slotNewFile()
{

	MainWindow *newWin = new MainWindow;
	newWin->show();
	
}

void MainWindow::slotOpenFile()
{
	QString file = QFileDialog::getOpenFileName(this);
	if(!file.isEmpty())
	{
		if(text->document()->isEmpty())//当前text为空，就这这里打开
		{
			loadFile(file);
		}
		else
		{	
			MainWindow *newWin = new MainWindow;
			newWin->show();
			newWin->loadFile(file);
			
		}
	}

	
}

void MainWindow::slotSaveFile()
{

	
}

void MainWindow::slotCopy()
{
	text->copy();
	
}

void MainWindow::slotCut()
{
	text->cut();
}

void MainWindow::slotPaste()
{
	text->paste();
	
}



void MainWindow::slotAbout()
{
	QMessageBox::about(this,tr("About test window"),
						tr("<h2>TestWindow 1.1<h2>"
						"<p>hello world"));
	
		
	
}



void MainWindow::slotMoveCursor()
{
	int row,col;
	QTextCursor cursor = text->textCursor();
	row = cursor.blockNumber();
	col = cursor.columnNumber();
	statusBarLabel->setText(tr("%1 line,%2 col").arg(row).arg(col));
	
	
}





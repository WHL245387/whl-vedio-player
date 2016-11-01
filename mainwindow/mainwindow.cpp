#include <QtGui>

#include "QMenu"
#include "QAction"
#include "QTextEdit"
#include "QLabel"
#include "QWorkspace"

#include "mainwindow.h"

MainWindow::MainWindow()
{
	setWindowTitle("TestWindow");
	text = new QTextEdit("QTextEdit",this);
	setCentralWidget(text);
	
	createActions();
	createMenus();
	createTools();
	createStatus();
	// aboutAction = new QAction(tr("About"),this);
	// aboutAction->setCheckable(true);
	// aboutMenu = menuBar()->addMenu(tr("about"));
	// aboutMenu->addAction(aboutAction);
	// connect(aboutAction,SIGNAL(triggered()),this,SLOT(slotAbout()));

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
	connect(newFileAction,SIGNAL(triggered()),this,SLOT(slotNewFile()));
	openFileAction = new QAction(QIcon(":/images/open.png"),tr("Open"),this);
	connect(openFileAction,SIGNAL(triggered()),this,SLOT(slotOpenFile()));
	saveFileAction = new QAction(QIcon(":/images/save.png"),tr("Save"),this);
	connect(saveFileAction,SIGNAL(triggered()),this,SLOT(slotSaveFile()));
	exitAction = new QAction("Exit",this);
	connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
	
	//edit
	copyAction = new QAction(QIcon(":/images/copy.png"),tr("Copy"),this);
	connect(copyAction,SIGNAL(triggered()),this,SLOT(slotCopy()));
	cutAction = new QAction(QIcon(":/images/cut.png"),tr("Cut"),this);
	connect(cutAction,SIGNAL(triggered()),this,SLOT(slotCut()));
	pasteAction = new QAction(QIcon(":/images/paste.png"),tr("Paste"),this);
	connect(pasteAction,SIGNAL(triggered()),this,SLOT(slotPaste()));
	
	//help
	aboutAction = new QAction(tr("About"),this);
	connect(aboutAction,SIGNAL(triggered()),this,SLOT(slotAbout()));
	
}


void MainWindow::createTools()
{
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(newFileAction);
	fileToolBar->addAction(openFileAction);
	fileToolBar->addAction(saveFileAction);	
	
	editToolBar = addToolBar(tr("Edit"));
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


void MainWindow::slotNewFile()
{

	
}

void MainWindow::slotOpenFile()
{
    // MainWindow *newWin = new MainWindow();  
    // newWin->show();  
	
}

void MainWindow::slotSaveFile()
{
    // MainWindow *newWin = new MainWindow();  
    // newWin->show();  
	
}

void MainWindow::slotCopy()
{

	
}

void MainWindow::slotCut()
{
    // MainWindow *newWin = new MainWindow();  
    // newWin->show();  
	
}

void MainWindow::slotPaste()
{
    // MainWindow *newWin = new MainWindow();  
    // newWin->show();  
	
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



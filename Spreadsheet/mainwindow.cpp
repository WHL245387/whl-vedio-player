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

	
	spresdsheet = new Spreadsheet;//创建一个Spreadsheet
	setCentralWidget(spresdsheet);//把Spreadsheet设置为主窗口的中央窗口
	
	createActions();
	createMenus();
	createContextMenu();
	createToolsBar();
	createStatusBar();
	
	readSetting();
	findDialog = 0;
	
	setWindowIcon(":/iamges/icon.png");
	setCurrentFile();
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newFileAction);	
	fileMenu->addAction(openFileAction);
	fileMenu->addAction(saveFileAction);	
	fileMenu->addAction(saveAsFileAction);
	separatorAction = fileMenu->addSeparator();
	for(int i = 0; i < MaxRecentFiles; i++ )
	{
		fileMenu->addAction(recentFileActions[i]);
		
	}
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);
	
	editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(copyAction);
	editMenu->addAction(cutAction);
	editMenu->addAction(pasteAction);
	editMenu->addAction(deleteAction);
	
	selectSubMenu = editMenu->addMenu(tr("&Select");
	selectSubMenu->addAction(selectRowAction);
	selectSubMenu->addAction(selectColumnAction);
	selectSubMenu->addAction(selectAllAction);
	
	editMenu->addSeparator();
	editMenu->addAction(findAction);
	editMenu->addAction(goToCellAction);
	
	
	toolsMenu = menuBar()->addMenu(tr("&Tools"));
	toolsMenu->addAction(recalculateAction);
	toolsMenu->addAction(sortAction);	
	
	optionsMenu = menuBar()->addMenu(tr("&Options"));
	optionsMenu->addAction(showGridAction);
	optionsMenu->addAction(autoRecalcAction);	
	
	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAction);
	helpMenu->addAction(aboutQtAction);
}

void MainWindow::createActions()
{
	//file menu
	//New
	newFileAction = new QAction(QIcon(":/images/new.png"),tr("New"),this);
	newFileAction->setShortcut(tr("Ctrl+N"));  
	newFileAction->setStatusTip(tr("Create a new spresdsheet file"));  
	connect(newFileAction,SIGNAL(triggered()),this,SLOT(slotNewFile()));
	//Open
	openFileAction = new QAction(QIcon(":/images/open.png"),tr("Open"),this);
	openFileAction->setStatusTip(tr("Open File"));  
	connect(openFileAction,SIGNAL(triggered()),this,SLOT(slotOpenFile()));
	//Save
	saveFileAction = new QAction(QIcon(":/images/save.png"),tr("Save"),this);
	saveFileAction->setStatusTip(tr("Save File")); 	
	connect(saveFileAction,SIGNAL(triggered()),this,SLOT(slotSaveFile()));
	//Save As
	saveAsFileAction = new QAction(tr("Save As"),this);
	saveAsFileAction->setStatusTip(tr("Save As File")); 	
	connect(saveAsFileAction,SIGNAL(triggered()),this,SLOT(slotSaveAsFile()));
	//Recent File
	for(int i = 0;i < MaxRecentFiles; i++)
	{
		recentFileActions[i] = new QAction(this);
		recentFileActions[i]->setVisible(false);
		connect(recentFileActions[i],SIGNAL(triggered()),this,SLOT(slotOpenRecentFile()));
	}
	//Exit
	exitAction = new QAction("Exit",this);
	exitAction->setStatusTip(tr("Exit"));  
	connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
	/*********************end of file menu**************************/
	//edit menu
	copyAction = new QAction(QIcon(":/images/copy.png"),tr("Copy"),this);
	copyAction->setStatusTip(tr("Copy"));  	
	connect(copyAction,SIGNAL(triggered()),this,SLOT(slotCopy()));
	
	cutAction = new QAction(QIcon(":/images/cut.png"),tr("Cut"),this);
	cutAction->setStatusTip(tr("Cut"));  
	connect(cutAction,SIGNAL(triggered()),this,SLOT(slotCut()));
	
	pasteAction = new QAction(QIcon(":/images/paste.png"),tr("Paste"),this);
	pasteAction->setStatusTip(tr("Paste")); 
	connect(pasteAction,SIGNAL(triggered()),this,SLOT(slotPaste()));
	deleteAction = new QAction(tr("&Delete"),this);
	deleteAction->setShortcut(QKeySequence::Delete);
	deleteAction->setStatusTip(tr("Delete the current selection's contents ") );
	connect(deleteAction,SIGNAL(triggered()),this,SLOT(del()));
	
	selectRowAction = new QAction(tr("&Row"),this);
	selectRowAction->setStatusTip(tr("Select all the cells in the current row"));
	connect(selectRowAction,SIGNAL(triggered()),this,SLOT(slotSelectCurrentRow));
	
	selectColumnAction = new QAction(tr("&Column"),this);
	selectColumnAction->setStatusTip(tr("Select all the cells in the current column"));
	connect(selectColumnAction,SIGNAL(triggered()),this,SLOT(slotSelectCurrentColumn));
	
	selectAllAction = new Action(tr("&All"),this);
	selectAllAction->setShortcut(QKeySequence::SelectAll);
	selectAllAction->setStatusTip(tr("Select all the cell in the spreadsheet"));
	connect(selectAllAction,SIGNAL(triggered),this,SLOT(selectAll()));
	findAction = new QAction(tr("&Find..."),this);
	findAction->setIcon(":/images/find.png");
	findAction->setShortcut(QKeySequence::Find);
	findAction->setStatusTip(tr("Find a matching cell"));
	connect(findAction,SIGNAL(triggered()),this,SLOT(find()));
	
	goToCellAction = new QAction(tr("&Go to Cell..."), this);
    goToCellAction->setIcon(QIcon(":/images/gotocell.png"));
    goToCellAction->setShortcut(tr("Ctrl+G"));
    goToCellAction->setStatusTip(tr("Go to the specified cell"));
    connect(goToCellAction, SIGNAL(triggered()),this, SLOT(goToCell()));
	
	/*********************end of edit menu**************************/
	//tools menu
	recalculateAction = new QAction(tr("&Recalculate"),this);
	recalculateAction->setShortcut(tr("F9"));
	recalculateAction->setStatusTip("Recalculate all the spreadsheet's formulas");
	connect(recalculateAction,SIGNAL(triggered()),this,SLOT(slotRecalcilate()));
	sortAction = new QAction(tr("&Sort..."),this);
	sortAction->setStatusTip("Sort the selected cells or all the cells");
	
	/*********************end of tools menu**************************/
	//options menu
	showGridAction = new QAction(tr("&Show Grid"));
	showGridAction->setCheckable(true);
	showGridAction->setChecked(spreadsheet->showGrid());
	showGridAction->setStatusTip(tr("Show or hide the grid"));
	connect(showGridAction,SIGNAL(toggled(bool)),spreadsheet,SLOT(slotShowrid(bool)));
	autoRecalcAction = new QAction(tr("&Auto-Recalculate"), this);
    autoRecalcAction->setCheckable(true);
    autoRecalcAction->setChecked(spreadsheet->autoRecalculate());
    autoRecalcAction->setStatusTip(tr("Switch auto-recalculation on or "
                                      "off"));
    connect(autoRecalcAction, SIGNAL(toggled(bool)),
    spreadsheet, SLOT(setAutoRecalculate(bool)));
	
	
	
	/*****************end of options menu******************/	
	//help
	aboutAction = new QAction(tr("About"),this);
	aboutAction->setStatusTip(tr("About Qt")); 
	connect(aboutAction,SIGNAL(triggered()),this,SLOT(slotAbout()));
	
	aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
 //   connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	/*********************end of help menu**************************/	
}

void MainWindow::createContextMenu()
{
	spresdsheet->addAction(cutAction);
	spresdsheet->addAction(copyAction);	
	spresdsheet->addAction(pasteAction);
	spresdsheet->setContextMenuolicy(Qt::ActionsContextMenu);	
}

void MainWindow::createContextMenu()
{
	spreadsheet->addAction(cutAction);
	spreadsheet->addAction(copyAction);
	spreadsheet->addAction(pasteAction);
	spreadsheet->setContextMenuPolicy(Qt::ActionContextMenu);
}


void MainWindow::createToolsBar()
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
	editToolBar->addSeparator();
	editToolBar->addAction(findAction);
	editToolBar0->addAction(goToCellAction);
}

void MainWindow::createToolsBar()
{
	// statusBarLabel = new QLabel("Ready");
	// statusBarLabel->setAlignment(Qt::AlignHCenter);//设置对齐方式
	// statusBarLabel->setMinimumSize(statusBarLabel->sizeHint());
	// statusBar()->addWidget(statusBarLabel);
	// statusBar()->setStyleSheet(QString ("QStatusBar::item{border:0px}"));
	// connect(text,SIGNAL(cursorPositionChanged()),this,SLOT(slotMoveCursor()));
	
	locationLabel = new QLabel("W999");
	locationLabel->setAlignment(Qt::AlignHCenter);
	locationLabel->setMinimumSize(locationLabel->sizeHint());
	
	formulasLable = new QLabel;
	formulasLable->setIndent(3);
	statusBar->addWidget(locationLabel);
	statusBar->addWidget(formulasLable,1);
	connect(spreadsheet,SIGNAL(currentCellChanged(int ,int ,int ,int)),this,SLOT(updateStatusBar()));
	connect(spreadsheet,SIGNAL(modified()),this,SLOT(spreadsheetModified()));	
	
	updateStatusBar();
	
}

void MainWindow::updateStatusBar()
{
	locationLabel->setText(spreadsheet->currentLocation());
	formulasLable->setText(spreadsheet->currentFormula());
	
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
		setWindowTitle(fileName);
	}	
}

bool MainWindow::maybeSaveFile()
{
	
	
}

void  MainWindow::saveFile(QString fileName)
{
	QFile file(fileName);
	if(!file.open(QFile::WriteOnly|QFile::Text))
	{
		QMessageBox::critical(this,"critical","can not write file");
	}
	else
	{
		QTextStream out(&file);
		out<<text->toPlainText();
		//setFileName(fileName);
		setWindowTitle(fileName);
	}
}
void MainWindow::setFileName(QString fileName)
{
	currentFile = fileName;
	text->document()->setModified(false);
	this->setWindowModified(false);
	fileName.isEmpty()?this->setWindowFilePath("new.txt"):
	this->setWindowFilePath(fileName);
}


void MainWindow::slotNewFile()
{
	MainWindow *newWin = new MainWindow;
	newWin->show();
}

void MainWindow::slotOpenFile()
{
	QString file = QFileDialog::getOpenFileName(this);
//	currentFile = QFileDialog::getOpenFileName(this);
	if(!file.isEmpty())
	{

		if(text->document()->isEmpty())//当前text为空，就这这里打开
		{
			currentFile = file;
			loadFile(currentFile);
		}
		else
		{	
			MainWindow *newWin = new MainWindow;
			newWin->show();
			newWin->currentFile = file;
			newWin->loadFile(newWin->currentFile);
			
		}
	}

	
}

void MainWindow::slotSaveFile()
{
	//如果没有打开过文件直接另存为
	if(currentFile.isEmpty())
	{
		slotSaveAsFile();
	}
	else
	{
		saveFile(currentFile);
		
	}

	
}
void MainWindow::slotSaveAsFile()
{
	QString fileName = QFileDialog::getSaveFileName(this,tr("Save As File"),"./",tr("Text File(*.txt)"));
//	currentFile = QFileDialog::getSaveFileName(this,tr("Save File"));
	if(fileName.isEmpty())
	{
		
	}
	else
	{
		currentFile = fileName;
		saveFile(fileName);
	}
	
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





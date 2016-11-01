#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

class QMenu;
class QAction;
//class QTextCodec;
class QLabel;
class QTextEdit;


class QWorkspace;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow();
	
	void createMenus();
	void createActions();
	void createTools();
	void createStatus();
public slots:

	void slotNewFile();
	void slotOpenFile();
	void slotSaveFile();
	void slotCopy();
	void slotCut();
	void slotPaste();
	void slotAbout();
	void slotMoveCursor();

private:

//	QTextCodec *codec;
	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *helpMenu;
	
	QToolBar *fileToolBar;
	QToolBar *editToolBar;
	
	QAction *newFileAction;
	QAction *openFileAction;
	QAction *saveFileAction;
	QAction *exitAction;
	QAction *copyAction;
	QAction *cutAction;	
	QAction *pasteAction;	
	QAction *aboutAction;
	QLabel * statusBarLabel;
	
	QTextEdit *text;
	
	QWorkspace *workSpace;
};




#endif
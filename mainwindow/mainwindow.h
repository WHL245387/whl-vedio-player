#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

class QMenu;
class QAction;
//class QTextCodec;
class QTextEdit;
class QWorkspace;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow();
	
	void createMenus();
	void createActions();
public slots:

	void slotNewFile();
	void slotOpenFile();
	void slotSaveFile();
	void slotCopy();
	void slotCut();
	void slotPaste();
	void slotAbout();

private:

//	QTextCodec *codec;
	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *helpMenu;
	
	QAction *newFileAction;
	QAction *openFileAction;
	QAction *saveFileAction;
	QAction *exitAction;
	QAction *copyAction;
	QAction *cutAction;	
	QAction *pasteAction;	
	QAction *aboutAction;
	
	QTextEdit *text;
	
	QWorkspace *workSpace;
};




#endif
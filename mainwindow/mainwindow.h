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
	void loadFile(QString fileName);
	bool maybeSaveFile();
	void saveFile(QString fileName);
	void setFileName(QString fileName);
	
public slots:
	void slotNewFile();
	void slotOpenFile();
	void slotSaveFile();
	void slotSaveAsFile();
	void slotCopy();
	void slotCut();
	void slotPaste();
	void slotAbout();
	void slotMoveCursor();
private:
//	QTextCodec *codec;
	QString currentFile;
	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *helpMenu;
	
	QToolBar *fileToolBar;
	QToolBar *editToolBar;
	
	QAction *newFileAction;
	QAction *openFileAction;
	QAction *saveFileAction;
	QAction *saveAsFileAction;
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
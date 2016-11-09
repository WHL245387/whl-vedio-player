#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

class QMenu;
class QAction;
//class QTextCodec;
class QLabel;
class QTextEdit;
class Spreadsheet;
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
	
	void createContextMenu();
	void readSeting();
	void writeSetting();
	bool okTOContinue();
	void uodateCurrentFile();
	QString strippedName(const QString &fullFileName);
	
protected:
	void closeEvent(QCloseEvent *event);
	
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
	
	void slotFind();
	void slotGoToCell();
	void slotSort();
	void slotOpenRecentFile();
	void slotupdateStatusBar();
	void slotSpreadsheetModified();
	
private:
//	QTextCodec *codec;

	Spreadsheet * spreadsheet;
	FindDialog *findDialog;
	QLabel *locationLabel;
	QLabel *formulaLabel;
	enum {MaxRecentFile = 5};
	QAction * recentFileAction[MaxRecentFile];//近期文件
	QAction * separatorAction;


	QString currentFile;
	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *toolsMenu;
	QMenu *optionsMenu;
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
#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <Qt/QtGui>
#include "HistogramWindow.hh"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, Ui::MainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = NULL);
    virtual ~MainWindow(void);
                             
public slots:
    void displayPic(void);
    void openFile(void);
    void toGray(void);
    void toBinaryImage(void);
    void imageHistogram(void);
    void resetHistogram(void);
    void setDisplayPic(QImage pic);

    void undo(void);
    void redo(void);

protected slots:
    void disUndoAndRedo(void);
    
private:
    QString m_picName;
    QString m_recentDir;
    QImage *m_pic;
    QImage *m_prevPic;
    QPixmap *m_disPic;
    HistogramWindow *m_histogram;

    QString getDirOfFile(QString file);
};

#endif /* _MAINWINDOW_H_ */

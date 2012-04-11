#include <iostream>
#include "Grayscale.hh"
#include "ImageHistogram.hh"
#include "BinaryImage.hh"
#include "MainWindow.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), Ui::MainWindow(),
      m_recentDir("."), m_pic(NULL), m_prevPic(NULL), m_disPic(NULL),
      m_histogram(NULL)
{
    setupUi(this);
    connect(actionOpen, SIGNAL(triggered()),
            this, SLOT(openFile()));
    connect(actionUndo, SIGNAL(triggered()),
            this, SLOT(undo()));
    connect(actionRedo, SIGNAL(triggered()),
            this, SLOT(redo()));
    connect(actionGrayscale, SIGNAL(triggered()),
            this, SLOT(toGray()));
    connect(actionHistogram, SIGNAL(triggered()),
            this, SLOT(imageHistogram()));
    connect(actionBinary, SIGNAL(triggered()),
            this, SLOT(toBinaryImage()));
}

MainWindow::~MainWindow(void)
{
}

QString MainWindow::getDirOfFile(QString file)
{
    QString dir = file;
    int i = dir.lastIndexOf("/");
    dir.remove(i, file.size() - i);
    return dir;
}

void MainWindow::displayPic(void)
{
    if (m_pic->width() > imageDisplayer->size().width() ||
        m_pic->height() > imageDisplayer->size().height())
    {
        m_disPic = new QPixmap(
            QPixmap::fromImage(*m_pic).scaled(imageDisplayer->size(),
                                              Qt::KeepAspectRatio,
                                              Qt::SmoothTransformation));
    }
    else
    {
        m_disPic = new QPixmap(QPixmap::fromImage(*m_pic));
    }

    imageDisplayer->setPixmap(*m_disPic);
}

void MainWindow::openFile(void)
{
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Open Image"), m_recentDir, tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName.size() == 0)
        return;

    m_recentDir = getDirOfFile(fileName);
    
    m_picName = fileName;
    delete m_disPic;
    delete m_pic;
    m_pic = NULL;
    m_disPic = NULL;
    
    m_pic = new QImage(m_picName);
    displayPic();

    if (m_histogram != NULL)
    {
        resetHistogram();
    }
}

void MainWindow::toGray(void)
{
    if (m_pic == NULL || m_pic->isGrayscale())
        return;
    QImage pic(*m_pic);
    for (int i = 0; i < m_pic->width(); i++)
        for (int j = 0; j < m_pic->height(); j++)
        {
            QColor color = m_pic->pixel(i, j);
            int grayvalue = GrayScale::gray(qRed(color.rgb()),
                                            qGreen(color.rgb()),
                                            qBlue(color.rgb()));
            color = QColor(grayvalue, grayvalue, grayvalue);
            pic.setPixel(i, j, color.rgb());
        }
    setDisplayPic(pic);
}

void MainWindow::toBinaryImage(void)
{
    BinaryImage *dialog = new BinaryImage(m_pic, this, Qt::Window);
    connect(dialog, SIGNAL(imageConverted(QImage)),
            this, SLOT(setDisplayPic(QImage)));
    connect(dialog, SIGNAL(rejected()),
            this, SLOT(disUndoAndRedo()));
    dialog->exec();
}

void MainWindow::imageHistogram(void)
{
    delete m_histogram;
    m_histogram = new HistogramWindow(m_pic, this, Qt::Window);
    m_histogram->show();
}

void MainWindow::resetHistogram(void)
{
    if (m_histogram != NULL)
        m_histogram->resetHistogramPic(m_pic);
}

void MainWindow::setDisplayPic(QImage pic)
{
    delete m_prevPic;
    m_prevPic = new QImage(*m_pic);
    delete m_pic;
    m_pic = new QImage(pic);
    actionUndo->setEnabled(true);
    actionRedo->setEnabled(false);
    resetHistogram();
    displayPic();
}

void MainWindow::undo(void)
{
    setDisplayPic(*m_prevPic);
    actionUndo->setEnabled(false);
    actionRedo->setEnabled(true);
}

void MainWindow::redo(void)
{
    setDisplayPic(*m_prevPic);
    actionUndo->setEnabled(true);
    actionRedo->setEnabled(false);
}

void MainWindow::disUndoAndRedo(void)
{
    actionUndo->setEnabled(false);
    actionRedo->setEnabled(false);
}

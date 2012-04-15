#include <QtGui/QKeySequence>
#include "Grayscale.hh"
#include "PointOpDialog.hh"
#include "AlgebraicOp.hh"
#include "GeometricOpDialog.hh"
#include "ImageHistogram.hh"
#include "BinaryImage.hh"
#include "ConvolveImage.hh"
#include "GaussianFilterDialog.hh"
#include "MeanFilter.hh"
#include "MedianFilter.hh"
#include "MainWindow.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), Ui::MainWindow(),
      m_recentDir("."),
      m_pic(NULL), m_anotherPic(NULL), m_prevPic(NULL), m_disPic(NULL),
      m_histogram(NULL)
{
    setupUi(this);
    
    /* File menu. */
    connect(actionOpen, SIGNAL(triggered()),
            this, SLOT(openFile()));
    connect(actionSave, SIGNAL(triggered()),
            this, SLOT(saveFile()));
    connect(actionQuit, SIGNAL(triggered()),
            qApp, SLOT(quit()));
    actionOpen->setShortcut(QKeySequence(QKeySequence::Open));
    actionSave->setShortcut(QKeySequence(QKeySequence::Save));
    actionQuit->setShortcut(QKeySequence(QKeySequence::Quit));
    actionSave->setEnabled(false);
    
    /* Edit menu. */
    connect(actionUndo, SIGNAL(triggered()),
            this, SLOT(undo()));
    connect(actionRedo, SIGNAL(triggered()),
            this, SLOT(redo()));
    connect(actionPointOp, SIGNAL(triggered()),
            this, SLOT(pointOp()));
    connect(actionAddition, SIGNAL(triggered()),
            this, SLOT(algebraicOpAdd()));
    connect(actionSubtraction, SIGNAL(triggered()),
            this, SLOT(algebraicOpSub()));
    connect(actionMultiplication, SIGNAL(triggered()),
            this, SLOT(algebraicOpMul()));
    connect(actionDivision, SIGNAL(triggered()),
            this, SLOT(algebraicOpDiv()));
    connect(actionGeometricOp, SIGNAL(triggered()),
            this, SLOT(geometricOp()));
    actionUndo->setShortcut(QKeySequence(QKeySequence::Undo));
    actionRedo->setShortcut(QKeySequence(QKeySequence::Redo));
    actionUndo->setEnabled(false);
    actionRedo->setEnabled(false);
    actionPointOp->setEnabled(false);
    menuAlgebraicOp->setEnabled(false);
    actionAddition->setEnabled(false);
    actionSubtraction->setEnabled(false);
    actionMultiplication->setEnabled(false);
    actionDivision->setEnabled(false);
    actionGeometricOp->setEnabled(false);
    
    /* Convert menu. */
    connect(actionGrayscale, SIGNAL(triggered()),
            this, SLOT(toGray()));
    connect(actionBinary, SIGNAL(triggered()),
            this, SLOT(toBinaryImage()));
    connect(actionConvolved, SIGNAL(triggered()),
            this, SLOT(toConvolvedImage()));
    actionGrayscale->setEnabled(false);
    actionBinary->setEnabled(false);
    actionConvolved->setEnabled(false);
    
    /* Filter menu. */
    connect(actionGaussian, SIGNAL(triggered()),
            this, SLOT(gaussian()));
    connect(actionMean, SIGNAL(triggered()),
            this, SLOT(mean()));
    connect(actionMedian, SIGNAL(triggered()),
            this, SLOT(median()));
    actionGaussian->setEnabled(false);
    actionMean->setEnabled(false);
    actionMedian->setEnabled(false);
    
    /* Window menu. */
    connect(actionHistogram, SIGNAL(triggered()),
            this, SLOT(imageHistogram()));
    actionHistogram->setEnabled(false);
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

void MainWindow::setDisplayPic(QImage pic)
{
    delete m_prevPic;
    if (m_pic != NULL)
        m_prevPic = new QImage(*m_pic);
    delete m_pic;
    m_pic = new QImage(pic);
    
    if (m_prevPic != NULL)
        actionUndo->setEnabled(true);
    actionRedo->setEnabled(false);
    if (m_pic->isGrayscale())
    {
        actionGrayscale->setEnabled(false);
        actionBinary->setEnabled(true);
        actionConvolved->setEnabled(true);
    }
    else
    {
        actionGrayscale->setEnabled(true);
        actionBinary->setEnabled(false);
        actionConvolved->setEnabled(false);
    }
    resetHistogram();

    displayPic();
}

void MainWindow::displayPic(void)
{
    delete m_disPic;
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
    setDisplayPic(QImage(m_picName));
    displayPic();

    if (m_histogram != NULL)
        resetHistogram();

    actionSave->setEnabled(true);
    actionPointOp->setEnabled(true);
    menuAlgebraicOp->setEnabled(true);
    actionAddition->setEnabled(true);
    actionSubtraction->setEnabled(true);
    actionMultiplication->setEnabled(true);
    actionDivision->setEnabled(true);
    actionGeometricOp->setEnabled(true);
    actionGaussian->setEnabled(true);
    actionMean->setEnabled(true);
    actionMedian->setEnabled(true);
    actionHistogram->setEnabled(true);
}

void MainWindow::openAnotherFile(void)
{
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Open Image"), m_recentDir, tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName.size() == 0)
        return;

    m_recentDir = getDirOfFile(fileName);

    delete m_anotherPic;
    m_anotherPic = new QImage(fileName);
}

void MainWindow::saveFile(void)
{
    QString fileName = QFileDialog::getSaveFileName(
        this, tr("Save Image"), m_recentDir, tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName.size() == 0)
        return;

    m_recentDir = getDirOfFile(fileName);

    m_pic->save(fileName);
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

void MainWindow::pointOp(void)
{
    PointOpDialog *dialog = new PointOpDialog(m_pic);
    connect(dialog, SIGNAL(imageConverted(QImage)),
            this, SLOT(setDisplayPic(QImage)));
    connect(dialog, SIGNAL(rejected()),
            this, SLOT(disUndoAndRedo()));
    dialog->exec();
}

void MainWindow::algebraicOpAdd(void)
{
    openAnotherFile();
    setDisplayPic(AlgebraicOp::operate(*m_pic, *m_anotherPic, '+'));
}

void MainWindow::algebraicOpSub(void)
{
    openAnotherFile();
    setDisplayPic(AlgebraicOp::operate(*m_pic, *m_anotherPic, '-'));
}

void MainWindow::algebraicOpMul(void)
{
    openAnotherFile();
    setDisplayPic(AlgebraicOp::operate(*m_pic, *m_anotherPic, '*'));
}

void MainWindow::algebraicOpDiv(void)
{
    openAnotherFile();
    setDisplayPic(AlgebraicOp::operate(*m_pic, *m_anotherPic, '/'));
}

void MainWindow::geometricOp(void)
{
    GeometricOpDialog *dialog = new GeometricOpDialog(m_pic, this, Qt::Window);
    connect(dialog, SIGNAL(imageConverted(QImage)),
            this, SLOT(setDisplayPic(QImage)));
    connect(dialog, SIGNAL(rejected()),
            this, SLOT(disUndoAndRedo()));
    dialog->exec();
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

void MainWindow::toConvolvedImage(void)
{
    ConvolveImage *dialog = new ConvolveImage(m_pic, this, Qt::Window);
    connect(dialog, SIGNAL(imageConverted(QImage)),
            this, SLOT(setDisplayPic(QImage)));
    connect(dialog, SIGNAL(rejected()),
            this, SLOT(disUndoAndRedo()));
    dialog->exec();
}

void MainWindow::gaussian(void)
{
    GaussianFilterDialog *dialog = new GaussianFilterDialog(m_pic, this, Qt::Window);
    connect(dialog, SIGNAL(imageConverted(QImage)),
            this, SLOT(setDisplayPic(QImage)));
    connect(dialog, SIGNAL(rejected()),
            this, SLOT(disUndoAndRedo()));
    dialog->exec();
}

void MainWindow::mean(void)
{
    setDisplayPic(MeanFilter::filter(m_pic));
}

void MainWindow::median(void)
{
    setDisplayPic(MedianFilter::filter(m_pic));
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

#include "mainwindow.h"
#include "fractalwidget.h"

#include "ui.h"

#include <QtGui>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_fractalWidget = new FractalWidget();
    setCentralWidget(m_fractalWidget);

    readSettings();
}

MainWindow::~MainWindow()
{
}

void MainWindow::readSettings()
{
    QSettings settings;
    QPoint pos = settings.value("windowPosition", QPoint(200, 200)).toPoint();
    QSize size = settings.value("imageSize", QSize(640, 480)).toSize();
    resize(size);
    move(pos);
}

void MainWindow::writeSettings()
{
    QSettings settings;
    settings.setValue("windowPosition", pos());
    settings.setValue("imageSize", size());
}

void MainWindow::createImages()
{
    m_image[0] = new QImage(m_fractalWidget->width(), m_fractalWidget->height(), QImage::Format_RGB32);
    m_image[1] = new QImage(m_fractalWidget->width(), m_fractalWidget->height(), QImage::Format_RGB32);
    m_activeImage = 0;
}

void MainWindow::destroyImages()
{
    delete m_image[0];
    delete m_image[1];
}

char *MainWindow::imageBuffer1()
{
    return (char *)m_image[0]->bits();
}

char *MainWindow::imageBuffer2()
{
    return (char *)m_image[1]->bits();
}

int MainWindow::imageBytesPerLine()
{
    return m_image[0]->bytesPerLine();
}
QSize MainWindow::imageSize()
{
    return m_fractalWidget->size();
}

void MainWindow::switchActiveImage()
{
    m_activeImage ^= 1;
}

void MainWindow::redrawImage()
{
    m_fractalWidget->drawImage(m_image[m_activeImage]);
}

QPoint MainWindow::mousePosition()
{
    return m_fractalWidget->mousePosition();
}

int MainWindow::mouseButtons()
{
    int mouseButtons = 0;
    if (m_fractalWidget->mouseButtons() & Qt::LeftButton)
        mouseButtons |= BUTTON1;
    if (m_fractalWidget->mouseButtons() & Qt::MidButton)
        mouseButtons |= BUTTON2;
    if (m_fractalWidget->mouseButtons() & Qt::RightButton)
        mouseButtons |= BUTTON3;
    return mouseButtons;
}

void MainWindow::showMessage(const QString &message)
{
    statusBar()->showMessage(message, 5000);
}

void MainWindow::setCursorType(int type)
{
    /*
    switch (type) {
    case WAITMOUSE:
        setCursor(Qt::WaitCursor);
        break;

    case REPLAYMOUSE:
        m_fractalWidget->setCursor(Qt::BusyCursor);
        break;

    case NORMALMOUSE:
    default:
        setCursor(Qt::ArrowCursor);
        m_fractalWidget->setCursor(Qt::ArrowCursor);
        break;
    }
    */
}

void MainWindow::startMainLoop()
{
    ui_mainloop(0);
    QTimer::singleShot(0, this, SLOT(startMainLoop()));
}
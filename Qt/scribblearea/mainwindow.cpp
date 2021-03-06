#include <QtWidgets>

#include "mainwindow.h"
#include "scribblearea.h"


MainWindow::MainWindow()
{
    scribbleArea = new ScribbleArea;
    setCentralWidget(scribbleArea);
    createActions();
    createMenus();
    setWindowTitle(tr("Scribble"));
    resize(500, 500);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(maybeSave())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::open()
{
    if(maybeSave())
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open File"),
                                                        QDir::currentPath());
        if(!fileName.isEmpty()){
            scribbleArea->openImage(fileName);
        }
    }
}

void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray(); //verify
    saveFile(fileFormat);
}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(scribbleArea->penColor());
    if(newColor.isValid())
    {
        scribbleArea->setPenColor(newColor);
    }
}

void MainWindow::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this,
                                        tr("Scribble"),
                                        tr("Select pen width : "),
                                        scribbleArea->penWidth(),
                                        1,
                                        50,
                                        1,
                                        &ok);
    if(ok)
    {
        scribbleArea->setPenWidth(newWidth);
    }
}

void MainWindow::about()
{
    QMessageBox::about(this,
                       tr("About Scribble"),
                       tr("<p> The <b>Scribble</b> example is awesome</p>"));
}


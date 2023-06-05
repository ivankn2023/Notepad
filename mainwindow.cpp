
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "QPrintPreviewDialog"
#include "QFontDialog"
#include "QColorDialog"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly| QFile::Text)){
        QMessageBox::warning(this, "problem with file", "please, repeate"+file.errorString());
        return;

    }

    setWindowTitle(fileName);
    QTextStream in(&file);
    QString txt = in.readAll();
    ui->textEdit->setText(txt);
}


void MainWindow::on_actionSave_triggered()
{
    QString fileName;
    if(currentFile.isEmpty()){
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    }
    else{
        fileName = currentFile;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(this, "problem with file", "please, repeate "+file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString txt = ui->textEdit->toPlainText();
    out<<txt;
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, "Save file as");
    currentFile = fileName;
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(this, "problem with file", "please, repeate "+file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString txt = ui->textEdit->toPlainText();
    out<<txt;
    file.close();
}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter print;
    QPrintDialog dialog(&print, this);
    if(dialog.exec()==QDialog::Rejected) return;
    ui->textEdit->print(&print);
}


void MainWindow::on_actionPrint_Preview_triggered()
{
    QPrinter printer;
    QPrintPreviewDialog prev(&printer, this);
    prev.setWindowFlags(Qt::Window);
    connect(&prev, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printPreview(QPrinter *)));
    prev.exec();
}
void MainWindow::printPreview(QPrinter *printer)
{
    ui->textEdit->print(printer);
}



void MainWindow::on_actionExport_pdf_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as PDF");

    if(fileName != ' '){
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        printer.setPageMargins(QMarginsF(30,30,30,30));
        ui->textEdit->print(&printer);

    }



    currentFile = fileName;

}


void MainWindow::on_actionExit_triggered()
{
    this->close();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionBold_triggered()
{
    QFont font;
    font.setBold(true);
    ui->textEdit->setFont(font);
}


void MainWindow::on_actionItalic_triggered()
{
    QFont font;
    font.setItalic(true);
    ui->textEdit->setFont(font);
}


void MainWindow::on_actionUnderline_triggered()
{
    QFont font;
    font.setUnderline(true);
    ui->textEdit->setFont(font);
}




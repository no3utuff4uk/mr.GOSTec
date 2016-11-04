#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "keydialog.h"
#include "about.h"

#include "encrypt.h"
#include "ecb.h"
#include "cbc.h"
#include "cfb.h"
#include "ofb.h"
#include "ctr.h"

#include <QMessageBox>
#include <QFile>
#include "macgenerator.h"
#include <fstream>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, &MainWindow::pathReceived, this, &MainWindow::checkReceivedFilePath);
    modeChange = new QButtonGroup(this);
    modeChange->addButton(ui->mode0,0);
    modeChange->addButton(ui->mode1,1);
    modeChange->addButton(ui->mode2,2);
    modeChange->addButton(ui->mode3,3);
    modeChange->addButton(ui->mode4,4);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFile_clicked()
{
    openFile = new QFileDialog();
    filePath = openFile->getOpenFileName();
    emit pathReceived();
}

void MainWindow::checkReceivedFilePath()
{
    file = new QFile(filePath);

    if(file->open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, "Checked", filePath + "\nis ok!");
        ui->lineEdit->setText(filePath);
        ui->encryptButton->setEnabled(true);
        ui->decryptButton->setEnabled(true);
        ui->testButton->setEnabled(true);
        ui->generateMAC->setEnabled(true);

    }else
    {
        QMessageBox::warning(this, "Error", "Invalid file path: "+ filePath);
        delete file;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    openFile = new QFileDialog();
    filePath = openFile->getOpenFileName();
    emit pathReceived();
}

//----------Запуск режима генерации Имитовставки------------
void MainWindow::on_generateMAC_clicked()
{
    std::ifstream inputStream;
    inputStream.open(file->fileName().toStdString(),std::ifstream::binary);
    if(!inputStream.is_open())
        ui->lineMAC->setText("Error");
    else
    {
        uint32_t result = magmaGenerateMAC(key, inputStream);
        ui->lineMAC->setText( "0x" + QString::number(result, 16).toUpper());
        inputStream.close();
    }
}
//----------------------------------------------------------
//-------------- Запуск режима шифрования-------------------
void MainWindow::on_encryptButton_clicked()
{
    KeyDialog *keyChange = new KeyDialog(key, initL, initR, this);
    keyChange->show();
    connect(keyChange, &KeyDialog::okButtonClicked, this, &MainWindow::keyDialogOkClickedEncrypt);
}

void MainWindow::keyDialogOkClickedEncrypt()
{
    Encrypt *forMode = new Encrypt(modeChange->checkedId(),file, key, initL, initR,this);
    forMode->show();
}
//----------------------------------------------------------
//-------------Запуск режима расшифрования------------------
void MainWindow::on_decryptButton_clicked()
{
    KeyDialog *keyChange = new KeyDialog(key, this);
    keyChange->show();
    connect(keyChange, &KeyDialog::okButtonClicked, this, &MainWindow::keyDialogOkClickedDecrypt);
}

void MainWindow::keyDialogOkClickedDecrypt()
{
    std::ifstream source(file->fileName().toStdString(), std::ifstream::binary);
    std::ofstream destination(file->fileName().remove(".magma").toStdString(),std::ofstream::binary);
    int mode;
    source.read((char*) &mode, sizeof(int));
    switch (mode)
    {
        case 0:
        {
            magmaDecryptECB(key, source, destination);
            QMessageBox::information(this, "Complete", "Decryption cmplete [ECB]!");
        }break;
        case 1:
        {
            magmaDecryptCBC(key, source, destination);
            QMessageBox::information(this, "Complete", "Decryption cmplete [CBC]!");
        }break;
        case 2:
        {
            magmaDecryptCFB(key, source, destination);
            QMessageBox::information(this, "Complete", "Decryption cmplete [CFB]!");
        }break;
        case 3:
        {
            magmaDecryptOFB(key, source, destination);
            QMessageBox::information(this, "Complete", "Decryption cmplete [OFB]!");
        }break;
        case 4:
        {
            magmaDecryptOFB(key, source, destination);
            QMessageBox::information(this, "Complete", "Decryption cmplete [CTR]!");
        }break;
        default:
        {
            QMessageBox::warning(this, "Error", "Unknown mode!");
        }break;
    }
    source.close();
    destination.close();
}
//------------------------------------------------------------

void MainWindow::on_testButton_clicked()
{

}



void MainWindow::on_actionAbout_program_triggered()
{
    About *about = new About(this);
    about->show();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

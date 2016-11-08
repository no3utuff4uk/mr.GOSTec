#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mods\ecb.h"
#include "mods\cbc.h"
#include "mods\cfb.h"
#include "mods\ofb.h"
#include "mods\ctr.h"

#include <QMessageBox>
#include <QFile>
#include "mods\macgenerator.h"
#include <fstream>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openFile = new QFileDialog();
    encrypt = new Encrypt(this);
    keyDialog = new KeyDialog(this);
    about = new About(this);

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
    delete openFile;
    delete keyDialog;
    delete encrypt;
    delete about;
}

//-----------Получение пути к файлу и проверка корректности--------------
void MainWindow::on_openFile_clicked()
{
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
        //ui->testButton->setEnabled(true);
        ui->generateMAC->setEnabled(true);

    }else
    {
        QMessageBox::warning(this, "Error", "Invalid file path: "+ filePath);
        ui->lineEdit->clear();
        ui->encryptButton->setDisabled(true);
        ui->decryptButton->setDisabled(true);
        ui->generateMAC->setDisabled(true);
        delete file;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    openFile = new QFileDialog();
    filePath = openFile->getOpenFileName();
    emit pathReceived();
}
//----------------------------------------------------------

//----------Запуск режима генерации Имитовставки------------
void MainWindow::on_generateMAC_clicked()
{
    std::ifstream inputStream;
    inputStream.open(file->fileName().toLocal8Bit().toStdString(),std::ifstream::binary);
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
    keyDialog->setParams(key, initL, initR);
    keyDialog->show();
    connect(keyDialog, &KeyDialog::okButtonClickedEncrypt, this, &MainWindow::keyDialogOkClickedEncrypt);
}

void MainWindow::keyDialogOkClickedEncrypt()
{
    encrypt->setParams(modeChange->checkedId(),file, key, initL, initR);
    encrypt->show();
}
//----------------------------------------------------------
//-------------Запуск режима расшифрования------------------
void MainWindow::on_decryptButton_clicked()
{
    keyDialog->setParams(key);
    keyDialog->show();
    connect(keyDialog, &KeyDialog::okButtonClickedDecrypt, this, &MainWindow::keyDialogOkClickedDecrypt);
}

void MainWindow::keyDialogOkClickedDecrypt()
{
    //[]    Убрать записть режима из файла (Режим выбирать из меню)
    //[]    Переместить дешифрование в отдельный файл

    std::ifstream source(file->fileName().toLocal8Bit().toStdString(), std::ifstream::binary);
    QString outFile = file->fileName().remove(".magma");
    outFile.insert(outFile.lastIndexOf('.'),"[Decrypted]");

    std::ofstream destination(outFile.toLocal8Bit().toStdString(),std::ofstream::binary);
    unsigned short mode;
    source.read((char*) &mode, sizeof(unsigned short));

    uint32_t fromFileMAC;
    uint32_t generatedMAC;

    switch (mode)
    {
        case 0:
        {
            source.read((char*) &fromFileMAC, sizeof(uint32_t));
            magmaDecryptECB(key, source, destination);

            source.close();
            destination.close();

            source.open(outFile.toLocal8Bit().toStdString(), std::ifstream::binary);
            generatedMAC = magmaGenerateMAC(key, source);

            source.close();

            if(fromFileMAC == generatedMAC)
                QMessageBox::information(this, "Complete", "Decryption cmplete [ECB]!");
            else
                QMessageBox::warning(this, "Error", "Decryption error!");
        }break;
        case 1:
        {
            source.read((char*) &fromFileMAC, sizeof(uint32_t));
            magmaDecryptCBC(key, source, destination);

            source.close();
            destination.close();

            source.open(outFile.toLocal8Bit().toStdString(), std::ifstream::binary);
            generatedMAC = magmaGenerateMAC(key, source);

            source.close();

            if(fromFileMAC == generatedMAC)
                QMessageBox::information(this, "Complete", "Decryption cmplete [CBC]!");
            else
                QMessageBox::warning(this, "Error", "Decryption error!");
        }break;
        case 2:
        {
            source.read((char*) &fromFileMAC, sizeof(uint32_t));
            magmaDecryptCFB(key, source, destination);

            source.close();
            destination.close();

            source.open(outFile.toLocal8Bit().toStdString(), std::ifstream::binary);
            generatedMAC = magmaGenerateMAC(key, source);

            source.close();

            if(fromFileMAC == generatedMAC)
                QMessageBox::information(this, "Complete", "Decryption cmplete [CFB]!");
            else
                QMessageBox::warning(this, "Error", "Decryption error!");

        }break;
        case 3:
        {
            source.read((char*) &fromFileMAC, sizeof(uint32_t));
            magmaDecryptOFB(key, source, destination);

            source.close();
            destination.close();

            source.open(outFile.toLocal8Bit().toStdString(), std::ifstream::binary);
            generatedMAC = magmaGenerateMAC(key, source);

            source.close();

            if(fromFileMAC == generatedMAC)
                QMessageBox::information(this, "Complete", "Decryption cmplete [OFB]!");
            else
                QMessageBox::warning(this, "Error", "Decryption error!");
        }break;
        case 4:
        {
            source.read((char*) &fromFileMAC, sizeof(uint32_t));
            magmaDecryptCTR(key, source, destination);

            source.close();
            destination.close();

            source.open(outFile.toLocal8Bit().toStdString(), std::ifstream::binary);
            generatedMAC = magmaGenerateMAC(key, source);

            source.close();

            if(fromFileMAC == generatedMAC)
                QMessageBox::information(this, "Complete", "Decryption cmplete [CTR]!");
            else
                QMessageBox::warning(this, "Error", "Decryption error!");
        }break;
        default:
        {
            QMessageBox::warning(this, "Error", "Unknown mode!");
        }break;
    }
}
//------------------------------------------------------------

void MainWindow::on_actionAbout_program_triggered()
{
    about->show();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

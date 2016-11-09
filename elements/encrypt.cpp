#include "encrypt.h"
#include "ui_encrypt.h"
#include "mods\ecb.h"
#include "mods\cbc.h"
#include "mods\cfb.h"
#include "mods\ofb.h"
#include "mods\ctr.h"
#include "mods\macgenerator.h"
#include <fstream>
#include <QMessageBox>
//#include <QDebug>


Encrypt::Encrypt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Encrypt)
{
    ui->setupUi(this);
}

void Encrypt::setParams(int _mode, QFile *source, uint32_t _key[], uint64_t &_initL, uint64_t &_initR)
{
    mode=_mode;
    key = _key;
    initL = _initL;
    initR = _initR;
    file = source;
    fileInfo = new QFileInfo(*source);
    ui->lineEdit->setText(fileInfo->fileName());
}

Encrypt::~Encrypt()
{
    delete ui;
    delete fileInfo;
}



void Encrypt::on_okButton_clicked()
{
    std::ifstream source(file->fileName().toLocal8Bit().toStdString(), std::ifstream::binary);
    std::ofstream destination(
                fileInfo->absolutePath().toLocal8Bit().toStdString()+ "/" + ui->lineEdit->text().toLocal8Bit().toStdString()+ ".magma",
                std::ofstream::binary);

    //destination.write((char*) &mode, sizeof(unsigned short));
    uint32_t MAC = magmaGenerateMAC(key, source);
    destination.write((char*) &MAC, sizeof(uint32_t));
    source.seekg(0, std::ios::beg);

    switch(mode)
    {
        case 0:
        {
            magmaEncryptECB(key,source,destination);
        }break;
        case 1:
        {
            magmaEncryptCBC(key,initL, initR ,source,destination);
        };break;
        case 2:
        {
            magmaEncryptCFB(key,initL, initR, source, destination);
        };break;
        case 3:
        {
            magmaEncryptOFB(key,initL, initR, source, destination);
        };break;
        case 4:
        {
            magmaEncryptCTR(key, initL, source, destination);
        };break;
    }

    source.close();
    destination.close();

    QMessageBox::information(this, "Complete!", "Encryption complete");
    this->close();

}

void Encrypt::on_cancelButton_clicked()
{
    this->close();
}

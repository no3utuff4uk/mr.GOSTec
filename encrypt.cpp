#include "encrypt.h"
#include "ui_encrypt.h"
#include "ecb.h"
#include "cbc.h"
#include "cfb.h"
#include "ofb.h"
#include "ctr.h"
#include "macgenerator.h"
#include <fstream>
#include <QMessageBox>


Encrypt::Encrypt(int _mode, QFile *source, uint32_t _key[], uint64_t &_initL, uint64_t &_initR, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Encrypt), mode(_mode)
{
    key = _key;
    initL = _initL;
    initR = _initR;
    file = source;
    ui->setupUi(this);
    fileInfo = new QFileInfo(*source);
    ui->lineEdit->setText(fileInfo->fileName());
}

Encrypt::~Encrypt()
{
    delete ui;
}



void Encrypt::on_okButton_clicked()
{
    std::ifstream source(file->fileName().toStdString(), std::ifstream::binary);
    std::ofstream destination(
                fileInfo->absolutePath().toStdString()+ "/" + ui->lineEdit->text().toStdString()+ ".magma",
                std::ofstream::binary);
    //QMessageBox::information(this, "test" , fileInfo->absolutePath() + ui->lineEdit->text() + ".magma");

    destination.write((char*) &mode, sizeof(unsigned short));
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

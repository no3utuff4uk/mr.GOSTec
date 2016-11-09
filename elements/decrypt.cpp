#include "decrypt.h"
#include "ui_decrypt.h"

#include "mods\ecb.h"
#include "mods\cbc.h"
#include "mods\cfb.h"
#include "mods\ofb.h"
#include "mods\ctr.h"
#include "mods\macgenerator.h"

#include <fstream>
#include <QMessageBox>

Decrypt::Decrypt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Decrypt)
{
    ui->setupUi(this);
    outFile = new QFileDialog(this);
    outFile->setAcceptMode(QFileDialog::AcceptSave);
}

Decrypt::~Decrypt()
{
    delete ui;
    delete fileInfo;
    delete destinationFile;
}

void Decrypt::setParams(int _mode, QFile *source, uint32_t _key[])
{
    mode=_mode;
    key = _key;

    sourceFile = source;
    fileInfo = new QFileInfo(*source);
}



void Decrypt::on_fileDialogButton_clicked()
{
    QString filename = outFile->getSaveFileName();
    if(filename.compare("") != 0)
    {
        destinationFile = new QFile(filename);
        ui->decryptButton->setEnabled(true);
    }
    else
        QMessageBox::warning(this, "Error", "Empty file name!");
    ui->outFileName->setText(filename);
}

void Decrypt::on_decryptButton_clicked()
{
    std::ifstream source(sourceFile->fileName().toLocal8Bit().toStdString(), std::ifstream::binary);
    std::ofstream destination(destinationFile->fileName().toLocal8Bit().toStdString(),std::ofstream::binary);

    uint32_t fromFileMAC;
    source.read((char*) &fromFileMAC, sizeof(uint32_t));
    ui->decryptInfo->setEnabled(true);
    ui->decryptInfo->document()->setHtml("<b>MAC from file:</b>\t\t<i>0x"
                                              + QString::number(fromFileMAC,16) + "</i><br>");

    uint32_t generatedMAC;
    try
    {
        switch (mode)
        {
            case 0:
            {

                magmaDecryptECB(key, source, destination);

                source.close();
                destination.close();

                source.open(destinationFile->fileName().toLocal8Bit().toStdString(), std::ifstream::binary);
                generatedMAC = magmaGenerateMAC(key, source);


                source.close();

            }break;
            case 1:
            {
                magmaDecryptCBC(key, source, destination);

                source.close();
                destination.close();

                source.open(destinationFile->fileName().toLocal8Bit().toStdString(), std::ifstream::binary);
                generatedMAC = magmaGenerateMAC(key, source);

                source.close();
            }break;
            case 2:
            {
                magmaDecryptCFB(key, source, destination);

                source.close();
                destination.close();

                source.open(destinationFile->fileName().toLocal8Bit().toStdString(), std::ifstream::binary);
                generatedMAC = magmaGenerateMAC(key, source);

                source.close();

            }break;
            case 3:
            {
                magmaDecryptOFB(key, source, destination);

                source.close();
                destination.close();

                source.open(destinationFile->fileName().toLocal8Bit().toStdString(), std::ifstream::binary);
                generatedMAC = magmaGenerateMAC(key, source);

                source.close();
            }break;
            case 4:
            {
                magmaDecryptCTR(key, source, destination);

                source.close();
                destination.close();

                source.open(destinationFile->fileName().toLocal8Bit().toStdString(), std::ifstream::binary);
                generatedMAC = magmaGenerateMAC(key, source);

                source.close();
            }break;
            default:
            {
                QMessageBox::warning(this, "Error", "Unknown mode!");
            }break;
        }

        ui->decryptInfo->appendHtml("<b>Generated MAC:</b>\t<i>0x" + QString::number(generatedMAC,16) + "</i><br>");

        if(fromFileMAC == generatedMAC)
        {
            ui->decryptInfo->appendHtml(QString::number(fromFileMAC,16) + " == "
                                             + QString::number(generatedMAC,16) + "\n");
            ui->decryptInfo->appendHtml("<h1>Decryption complete!</h1>");
        }
        else
        {
            ui->decryptInfo->appendHtml(QString::number(fromFileMAC,16) + " != "
                                             + QString::number(generatedMAC,16) + "\n");
            ui->decryptInfo->appendHtml("<font color=\"red\"><h1>Decryption error!</h1></font>");

            ui->decryptButton->setEnabled(false);
        }

    }
    catch(...)
    {
        ui->decryptInfo->appendHtml("ERROR! IOException catched!");
    }

}

void Decrypt::reject()
{
    ui->decryptInfo->clear();
    //ui->decryptInfo->setEnabled();
    QDialog::reject();
}

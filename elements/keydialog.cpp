#include "keydialog.h"
#include "ui_keyDialog.h"
#include <QListWidgetItem>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>

KeyDialog::KeyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyDialog)
{
    ui->setupUi(this);
}

void KeyDialog::setParams(uint32_t _key[], uint64_t &_initL, uint64_t &_initR)
{
    key = _key;
    initL = &_initL;
    initR = &_initR;

    ui->initL->setEnabled(true);
    ui->initR->setEnabled(true);

    QRegExp hexRegInit("^[0-9a-f]{16}$");
    QRegExp hexRegKey("^[0-9a-f]{8}$");

    ui->initL->setValidator(new QRegExpValidator(hexRegInit));
    ui->initR->setValidator(new QRegExpValidator(hexRegInit));
    ui->initL->setText(QString::number(*initL,16));
    ui->initR->setText(QString::number(*initR,16));

    ui->k1->setValidator(new QRegExpValidator(hexRegKey));
    ui->k2->setValidator(new QRegExpValidator(hexRegKey));
    ui->k3->setValidator(new QRegExpValidator(hexRegKey));
    ui->k4->setValidator(new QRegExpValidator(hexRegKey));
    ui->k5->setValidator(new QRegExpValidator(hexRegKey));
    ui->k6->setValidator(new QRegExpValidator(hexRegKey));
    ui->k7->setValidator(new QRegExpValidator(hexRegKey));
    ui->k8->setValidator(new QRegExpValidator(hexRegKey));

    ui->k1->setText(QString::number(key[0], 16));
    ui->k2->setText(QString::number(key[1], 16));
    ui->k3->setText(QString::number(key[2], 16));
    ui->k4->setText(QString::number(key[3], 16));
    ui->k5->setText(QString::number(key[4], 16));
    ui->k6->setText(QString::number(key[5], 16));
    ui->k7->setText(QString::number(key[6], 16));
    ui->k8->setText(QString::number(key[7], 16));

    isEncrypt = true;
}


void KeyDialog::setParams(uint32_t _key[])
{
    key = _key;

    ui->initL->setDisabled(true);
    ui->initR->setDisabled(true);
    initR = new uint64_t;
    initL = new uint64_t;

    QRegExp hexRegKey("^[0-9a-f]{8}$");

    ui->k1->setValidator(new QRegExpValidator(hexRegKey));
    ui->k2->setValidator(new QRegExpValidator(hexRegKey));
    ui->k3->setValidator(new QRegExpValidator(hexRegKey));
    ui->k4->setValidator(new QRegExpValidator(hexRegKey));
    ui->k5->setValidator(new QRegExpValidator(hexRegKey));
    ui->k6->setValidator(new QRegExpValidator(hexRegKey));
    ui->k7->setValidator(new QRegExpValidator(hexRegKey));
    ui->k8->setValidator(new QRegExpValidator(hexRegKey));

    ui->k1->setText(QString::number(key[0], 16));
    ui->k2->setText(QString::number(key[1], 16));
    ui->k3->setText(QString::number(key[2], 16));
    ui->k4->setText(QString::number(key[3], 16));
    ui->k5->setText(QString::number(key[4], 16));
    ui->k6->setText(QString::number(key[5], 16));
    ui->k7->setText(QString::number(key[6], 16));
    ui->k8->setText(QString::number(key[7], 16));

    isEncrypt = false;
}

KeyDialog::~KeyDialog()
{
    delete ui;
}

void KeyDialog::on_okButton_clicked()
{
    //Мне немного стыдно за это:
    if(ui->initL->hasAcceptableInput() &&
       ui->initR->hasAcceptableInput() &&
       ui->k1->hasAcceptableInput() &&
       ui->k2->hasAcceptableInput() &&
       ui->k3->hasAcceptableInput() &&
       ui->k4->hasAcceptableInput() &&
       ui->k5->hasAcceptableInput() &&
       ui->k6->hasAcceptableInput() &&
       ui->k7->hasAcceptableInput() &&
       ui->k8->hasAcceptableInput())
    {
        *initL = ui->initL->text().toLongLong(nullptr, 16);
        *initR = ui->initR->text().toLongLong(nullptr, 16);

        key[0] = ui->k1->text().toLongLong(nullptr, 16);
        key[1] = ui->k2->text().toLongLong(nullptr, 16);
        key[2] = ui->k3->text().toLongLong(nullptr, 16);
        key[3] = ui->k4->text().toLongLong(nullptr, 16);
        key[4] = ui->k5->text().toLongLong(nullptr, 16);
        key[5] = ui->k6->text().toLongLong(nullptr, 16);
        key[6] = ui->k7->text().toLongLong(nullptr, 16);
        key[7] = ui->k8->text().toLongLong(nullptr, 16);

        //Попробую заменить это ужас потом

        if(isEncrypt)
            emit okButtonClickedEncrypt();
        else
            emit okButtonClickedDecrypt();
        this->close();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Init or key [1-7] is not correct");
    }
}

void KeyDialog::on_cancelButton_clicked()
{
    this->close();
}

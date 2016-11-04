#include "about.h"
#include "ui_about.h"

#include <QSize>


About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    movie = new QMovie(":/About/GOSTEC.gif");
    movie->setScaledSize(QSize(230,160));
    ui->label->setMovie(movie);
    movie->start();
    sound = new QSound(":/About/DUDEC.wav");
    sound->play();
    sound->setLoops(QSound::Infinite);
}

void About::reject()
{
    sound->stop();
    movie->stop();
    QDialog::reject();
}

About::~About()
{
    delete ui;
    delete movie;
    delete sound;
}

void About::on_pushButton_clicked()
{
    sound->stop();
    movie->stop();
    this->close();
}

void About::on_pushButton_2_clicked()
{
    sound->stop();
    movie->stop();
    this->close();
}

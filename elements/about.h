#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QSound>
#include <QMovie>
#include <QMouseEvent>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();

private slots:
    void showEvent(QShowEvent *event);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    void reject();
    QMovie *movie;
    QSound *sound;
    Ui::About *ui;
};

#endif // ABOUT_H

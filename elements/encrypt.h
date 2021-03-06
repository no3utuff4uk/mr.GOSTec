#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <QDialog>
#include <QFile>
#include <QFileInfo>

namespace Ui {
class Encrypt;
}

class Encrypt : public QDialog
{
    Q_OBJECT

public:
    explicit Encrypt(QWidget *parent = 0);
    ~Encrypt();

    void setParams(int _mode, QFile *source, uint32_t _key[], uint64_t &_initL, uint64_t &_initR);

private slots:

    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    unsigned short mode;
    uint32_t *key;
    uint64_t initL;
    uint64_t initR;
    Ui::Encrypt *ui;
    QFile *file;
    QFileInfo *fileInfo;
};

#endif // ENCRYPT_H

#ifndef DECRYPT_H
#define DECRYPT_H

#include <QDialog>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>

namespace Ui {
class Decrypt;
}

class Decrypt : public QDialog
{
    Q_OBJECT

public:
    explicit Decrypt(QWidget *parent = 0);
    ~Decrypt();

    void setParams(int _mode, QFile *source, uint32_t _key[]);

private slots:
    void on_fileDialogButton_clicked();

    void on_decryptButton_clicked();

private:

    void reject();

    Ui::Decrypt *ui;
    unsigned short mode;
    uint32_t *key;

    QFile *sourceFile;
    QFile *destinationFile;
    QFileInfo *fileInfo;
    QFileDialog *outFile;
};

#endif // DECRYPT_H

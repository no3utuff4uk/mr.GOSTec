#ifndef KEYDIALOG_H
#define KEYDIALOG_H

#include <QDialog>

namespace Ui {
class KeyDialog;
}

class KeyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeyDialog(QWidget *parent = 0);
    ~KeyDialog();

    void setParams(uint32_t _key[]);
    void setParams(uint32_t _key[], uint64_t &_initL, uint64_t &_initR);



signals:
    void okButtonClickedEncrypt();
    void okButtonClickedDecrypt();
private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:

    //KeyDialog(uint32_t _key[], uint64_t &_initL, uint64_t &_initR);
    //KeyDialog(uint32_t _key[]);

   // KeyDialog(QWidget *parent = 0);
    Ui::KeyDialog *ui;
    uint32_t *key;
    uint64_t *initL;
    uint64_t *initR;
    bool isEncrypt;
};

#endif // KEYDIALOG_H

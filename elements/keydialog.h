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
    explicit KeyDialog(uint32_t _key[], uint64_t &_initL, uint64_t &_initR, QWidget *parent = 0);
    explicit KeyDialog(uint32_t _key[] , QWidget *parent = 0);
    ~KeyDialog();
signals:
    void okButtonClicked();
private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
   // KeyDialog(QWidget *parent = 0);
    Ui::KeyDialog *ui;
    uint32_t *key;
    uint64_t *initL;
    uint64_t *initR;
};

#endif // KEYDIALOG_H

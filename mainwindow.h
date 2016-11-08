#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidget>
#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>

//#include "keydialog.h"
#include "elements\keydialog.h"
#include "elements\about.h"
#include "elements\encrypt.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:

   void pathReceived();
private slots:

    void on_openFile_clicked();

    void checkReceivedFilePath();

    void on_actionOpen_triggered();

    void on_generateMAC_clicked();

    void on_encryptButton_clicked();

    void keyDialogOkClickedEncrypt();

    void keyDialogOkClickedDecrypt();

    void on_decryptButton_clicked();

    void on_actionAbout_program_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
   //
    QFileDialog *openFile;
    QFile *file;
    QString filePath;
    QWidget *keyWidget;
    QListWidget *keyList;

    Encrypt *encrypt;
    About *about;
    KeyDialog *keyDialog;

    QPushButton *keyOk;
    QPushButton *keyCancel;
    QButtonGroup *modeChange;

    uint32_t key[8] =
    {
        0xffeeddcc,
        0xbbaa9988,
        0x77665544,
        0x33221100,
        0xf0f1f2f3,
        0xf4f5f6f7,
        0xf8f9fafb,
        0xfcfdfeff
    };

    uint64_t initL = 0x1234567890abcdef;
    uint64_t initR = 0x234567890abcdef1;
};

#endif // MAINWINDOW_H

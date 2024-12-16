#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow* getUi() const;

private slots:
    void on_getAndZip_triggered();

    void on_check_triggered();

    void on_generateToProcess_triggered();

    void on_generateToSend_triggered();

    void on_actionRemoveZipFiles_triggered();

    void on_transferToAkamai_triggered();

    void on_exit_triggered();

    void on_process_triggered();

    void on_actionUpdateSharePoint_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

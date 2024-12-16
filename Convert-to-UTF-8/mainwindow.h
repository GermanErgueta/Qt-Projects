#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_inputDirButton_clicked();
    void on_outputDirButton_clicked();

    void on_convertButton_clicked();

private:
    Ui::MainWindow *ui;
    QString inputDirPath;
    QString outputDirPath;

};
#endif // MAINWINDOW_H

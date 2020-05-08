#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSettings>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_inputPushButton_pressed();

    void on_outputPushButton_pressed();

private:
    Ui::MainWindow *ui;
    void loadSettings();
    void saveSettings();
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H

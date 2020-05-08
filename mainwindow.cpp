#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QMessageBox>
#include<QCloseEvent>
#include<opencv2/opencv.hpp>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inputPushButton_pressed()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open Input Image",
                                                    QDir::currentPath(),
                                                    "Images (*.jpg *.png *.bmp)"
                                                        );//手动点击选中图片之后 fileName就是这个图片文件的路径 是一个QString对象

    if (QFile::exists(fileName)){
        ui->inputLineEdit->setText(fileName);
    }


}

void MainWindow::closeEvent(QCloseEvent *event){
    int result = QMessageBox::warning(this,
                                      "Exit",
                                      "Are you sure you want to close this program?",
                                      QMessageBox::Yes,
                                      QMessageBox::No
                                      );
    if(result == QMessageBox::Yes){
        saveSettings();
        event->accept();
    }else {
    event->ignore();
}

}

void MainWindow::on_outputPushButton_pressed()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "select output image",
                                                    QDir::currentPath(),
                                                    "*.jpg;;*.png;;*.bmp");
    if(!fileName.isEmpty()){
        ui->outputLineEdit->setText(fileName);
        using namespace cv;

        Mat input_img,output_img;
        input_img  = imread(ui->inputLineEdit->text().toStdString());
        if(ui->medianBlurRadioButton->isChecked()){
            cv::medianBlur(input_img,output_img,5);
        }
        else if(ui->gaussianBlurRadioButton->isChecked()){
            cv::GaussianBlur(input_img,output_img,Size(5,5),1.25);
        }
        imwrite(fileName.toStdString(),output_img);
        if(ui->displayImagecheckBox->isChecked()){
            imshow("Output Image",output_img);
        }
    }

}
void MainWindow::loadSettings(){
    QSettings settings("packet","Hello_OpenCV_Qt",this);
    ui->inputLineEdit->setText(settings.value("inputLineEdit","").toString());
    ui->outputLineEdit->setText(settings.value("outputLineEdit","").toString());
    ui->medianBlurRadioButton->setChecked(settings.value("medianBlurRadioButton",true).toBool());
    ui->gaussianBlurRadioButton->setChecked(settings.value("gaussianBlurRadioButton",false).toBool());
    ui->displayImagecheckBox->setChecked(settings.value("displayImagecheckBox",true).toBool());
}
void MainWindow::saveSettings(){
    QSettings settings("packet","Hello_OpenCV_Qt",this);
    settings.setValue("inputLineEdit",ui->inputLineEdit->text());
    settings.setValue("outputLineEdit",ui->outputLineEdit->text());
    settings.setValue("medianBlurRadioButton",ui->medianBlurRadioButton->isChecked());
    settings.setValue("gaussianBlurRadioButton",ui->gaussianBlurRadioButton->isChecked());
    settings.setValue("displayImagecheckBox",ui->displayImagecheckBox->isChecked());


}

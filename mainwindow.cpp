#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include "QString"
#include "qstring.h"
#include "reader.h"
#include "writer.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->checkBox->hide();
    ui->checkBox_2->hide();
    ui->checkBox_3->hide();
    ui->checkBox_4->hide();
    ui->checkBox_5->hide();
    ui->checkBox_6->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->label_9->hide();
    ui->label_10->hide();
    ui->label_11->hide();
    ui->label_12->hide();
    ui->label_13->hide();
    ui->label_14->hide();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->lineEdit_5->hide();
    ui->lineEdit_6->hide();
    ui->lineEdit_7->hide();
    ui->lineEdit_8->hide();
    ui->lineEdit_9->hide();
    ui->lineEdit_10->hide();
    ui->lineEdit_11->hide();
    ui->lineEdit_12->hide();
    ui->lineEdit_13->hide();
    ui->lineEdit_14->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_6->hide();
    ui->pushButton_8->hide();
    ui->pushButton_10->hide();
    ui->pushButton_12->hide();
    ui->pushButton_14->hide();
    this->setFixedSize(500,200);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_14_clicked()
{
    if(ui->pushButton_14->text() == "Start")
    {

    ui->pushButton_14->setText("Stop");

    std::string ip,ip1,ip2,ip3,ip4,ip5,ip6;
    unsigned int port,port1,port2,port3,port4,port5,port6;
    char ipv[ip.length()], ipv1[ip1.length()], ipv2[ip2.length()];
    char ipv3[ip3.length()],ipv4[ip4.length()],ipv5[ip5.length()];
    char ipv6[ip6.length()];
    bool priority1,priority2,priority3,priority4,priority5,priority6;

    ip = ui->lineEdit->text().toStdString();
    port = ui->lineEdit_2->text().toUInt();

    ip1 = ui->lineEdit_3->text().toStdString();
    port1 = ui->lineEdit_4->text().toUInt();

    ip2 = ui->lineEdit_6->text().toStdString();
    port2 = ui->lineEdit_5->text().toUInt();

    ip3 = ui->lineEdit_8->text().toStdString();
    port3 = ui->lineEdit_7->text().toUInt();

    ip4 = ui->lineEdit_10->text().toStdString();
    port4 = ui->lineEdit_9->text().toUInt();

    ip5 = ui->lineEdit_12->text().toStdString();
    port5 = ui->lineEdit_11->text().toUInt();

    ip6 = ui->lineEdit_14->text().toStdString();
    port6 = ui->lineEdit_13->text().toUInt();

    //sharedVariables.numberOfThreads = ui->comboBox->currentIndex();
    int n = ui->comboBox->currentIndex();

    while(sharedVariables.empty.GetValue() < (sharedVariables.numberOfThreads * LIMITED_BUFFERSIZE))
        sharedVariables.empty.V();


    for(int i=0; i < ip.length(); i++)
    {
        ipv[i] = ip[i];
    }

    for(int i=0; i < ip1.length(); i++)
    {
        ipv1[i] = ip1[i];
    }

    for(int i=0; i < ip2.length(); i++)
    {
        ipv2[i] = ip2[i];
    }

    for(int i=0; i < ip3.length(); i++)
    {
        ipv3[i] = ip3[i];
    }

    for(int i=0; i < ip4.length(); i++)
    {
        ipv4[i] = ip4[i];
    }

    for(int i=0; i < ip5.length(); i++)
    {
        ipv5[i] = ip5[i];
    }

    for(int i=0; i < ip6.length(); i++)
    {
        ipv6[i] = ip6[i];
    }

    if(ui->checkBox->isChecked())
        priority1 = true;
    else
        priority1 = false;

    if(ui->checkBox_2->isChecked())
        priority2 = true;
    else
        priority2 = false;

    if(ui->checkBox_3->isChecked())
        priority3 = true;
    else
        priority3 = false;

    if(ui->checkBox_4->isChecked())
        priority4 = true;
    else
        priority4 = false;

    if(ui->checkBox_5->isChecked())
        priority5 = true;
    else
        priority5 = false;

    if(ui->checkBox_6->isChecked())
        priority6 = true;
    else
        priority6 = false;


    Writer *mainWriter;
    Reader **readers;
    //readers = new Reader*[sharedVariables.numberOfThreads];
    readers = new Reader*[n];

    mainWriter = new Writer(ipv, port, sharedVariables);
    mainWriter->Start();

    if(/*sharedVariables.numberOfThreads*/ n == 1)
    {
        readers[0] = new Reader(ipv1, port1 , sharedVariables, priority1);
        readers[0]->Start();
    }
    else if(/*sharedVariables.numberOfThreads*/ n == 2)
    {
        readers[0] = new Reader(ipv1, port1 , sharedVariables, priority1);
        readers[0]->Start();
        readers[1] = new Reader(ipv2, port2 , sharedVariables, priority2);
        readers[1]->Start();
    }
    else if(/*sharedVariables.numberOfThreads*/ n == 3)
    {
        readers[0] = new Reader(ipv1, port1 , sharedVariables, priority1);
        readers[0]->Start();
        readers[1] = new Reader(ipv2, port2 , sharedVariables, priority2);
        readers[1]->Start();
        readers[2] = new Reader(ipv3, port3 , sharedVariables, priority3);
        readers[2]->Start();
    }
    else if(/*sharedVariables.numberOfThreads*/ n == 4)
    {
        readers[0] = new Reader(ipv1, port1 , sharedVariables, priority1);
        readers[0]->Start();
        readers[1] = new Reader(ipv2, port2 , sharedVariables, priority2);
        readers[1]->Start();
        readers[2] = new Reader(ipv3, port3 , sharedVariables, priority3);
        readers[2]->Start();
        readers[3] = new Reader(ipv4, port4 , sharedVariables, priority4);
        readers[3]->Start();
    }
    else if(/*sharedVariables.numberOfThreads*/ n == 5)
    {
        readers[0] = new Reader(ipv1, port1 , sharedVariables, priority1);
        readers[0]->Start();
        readers[1] = new Reader(ipv2, port2 , sharedVariables, priority2);
        readers[1]->Start();
        readers[2] = new Reader(ipv3, port3 , sharedVariables, priority3);
        readers[2]->Start();
        readers[3] = new Reader(ipv4, port4 , sharedVariables, priority4);
        readers[3]->Start();
        readers[4] = new Reader(ipv5, port5 , sharedVariables, priority5);
        readers[4]->Start();
    }
    else if(/*sharedVariables.numberOfThreads*/ n == 6)
    {
        readers[0] = new Reader(ipv1, port1 , sharedVariables, priority1);
        readers[0]->Start();
        readers[1] = new Reader(ipv2, port2 , sharedVariables, priority2);
        readers[1]->Start();
        readers[2] = new Reader(ipv3, port3 , sharedVariables, priority3);
        readers[2]->Start();
        readers[3] = new Reader(ipv4, port4 , sharedVariables, priority4);
        readers[3]->Start();
        readers[4] = new Reader(ipv5, port5 , sharedVariables, priority5);
        readers[4]->Start();
        readers[5] = new Reader(ipv6, port6 , sharedVariables, priority6);
        readers[5]->Start();
    }
    writer = mainWriter;
    readerArray = readers;
    constNumberThreads = sharedVariables.numberOfThreads;
    }
    else{
        this->close();
    }



}

void MainWindow::on_comboBox_activated(int index)
{
    if(index == 0)
    {
        this->setFixedSize(500,200);
        ui->label_4->hide();
        ui->lineEdit_3->hide();
        ui->label_3->hide();
        ui->lineEdit_4->hide();
        ui->checkBox->hide();
        ui->pushButton_3->hide();
        ui->pushButton_14->hide();
        ui->label_6->hide();
        ui->lineEdit_5->hide();
        ui->label_5->hide();
        ui->lineEdit_6->hide();
        ui->checkBox_2->hide();
        ui->pushButton_4->hide();
        ui->checkBox_3->hide();
        ui->lineEdit_7->hide();
        ui->pushButton_6->hide();
        ui->label_7->hide();
        ui->lineEdit_8->hide();
        ui->label_8->hide();
        ui->lineEdit_9->hide();
        ui->lineEdit_10->hide();
        ui->label_9->hide();
        ui->label_10->hide();
        ui->checkBox_4->hide();
        ui->pushButton_8->hide();
        ui->lineEdit_11->hide();
        ui->lineEdit_12->hide();
        ui->label_11->hide();
        ui->label_12->hide();
        ui->pushButton_10->hide();
        ui->checkBox_5->hide();
        ui->label_13->hide();
        ui->label_14->hide();
        ui->lineEdit_13->hide();
        ui->lineEdit_14->hide();
        ui->checkBox_6->hide();
        ui->pushButton_12->hide();

    }
    else if(index == 1)
    {
        this->setFixedSize(600,310);
        ui->label_4->show();
        ui->lineEdit_3->show();
        ui->label_3->show();
        ui->lineEdit_4->show();
        ui->checkBox->show();
        ui->pushButton_3->show();
        ui->pushButton_14->move(250,240);
        ui->pushButton_14->show();
        ui->label_6->hide();
        ui->lineEdit_5->hide();
        ui->label_5->hide();
        ui->lineEdit_6->hide();
        ui->checkBox_2->hide();
        ui->pushButton_4->hide();
        ui->checkBox_3->hide();
        ui->lineEdit_7->hide();
        ui->pushButton_6->hide();
        ui->label_7->hide();
        ui->lineEdit_8->hide();
        ui->label_8->hide();
        ui->lineEdit_9->hide();
        ui->lineEdit_10->hide();
        ui->label_9->hide();
        ui->label_10->hide();
        ui->checkBox_4->hide();
        ui->pushButton_8->hide();
        ui->lineEdit_11->hide();
        ui->lineEdit_12->hide();
        ui->label_11->hide();
        ui->label_12->hide();
        ui->pushButton_10->hide();
        ui->checkBox_5->hide();
        ui->label_13->hide();
        ui->label_14->hide();
        ui->lineEdit_13->hide();
        ui->lineEdit_14->hide();
        ui->checkBox_6->hide();
        ui->pushButton_12->hide();

    }
    else if(index == 2)
    {
        this->setFixedSize(600,350);
        ui->label_4->show();
        ui->lineEdit_3->show();
        ui->label_3->show();
        ui->lineEdit_4->show();
        ui->checkBox->show();
        ui->pushButton_3->show();
        ui->label_6->show();
        ui->lineEdit_5->show();
        ui->label_5->show();
        ui->lineEdit_6->show();
        ui->checkBox_2->show();
        ui->pushButton_4->show();
        ui->pushButton_14->move(250,270);
        ui->pushButton_14->show();
        ui->checkBox_3->hide();
        ui->lineEdit_7->hide();
        ui->pushButton_6->hide();
        ui->label_7->hide();
        ui->lineEdit_8->hide();
        ui->label_8->hide();
        ui->lineEdit_9->hide();
        ui->lineEdit_10->hide();
        ui->label_9->hide();
        ui->label_10->hide();
        ui->checkBox_4->hide();
        ui->pushButton_8->hide();
        ui->lineEdit_11->hide();
        ui->lineEdit_12->hide();
        ui->label_11->hide();
        ui->label_12->hide();
        ui->pushButton_10->hide();
        ui->checkBox_5->hide();
        ui->label_13->hide();
        ui->label_14->hide();
        ui->lineEdit_13->hide();
        ui->lineEdit_14->hide();
        ui->checkBox_6->hide();
        ui->pushButton_12->hide();
    }
    else if(index == 3)
    {
        this->setFixedSize(600,420);
        ui->label_4->show();
        ui->lineEdit_3->show();
        ui->label_3->show();
        ui->lineEdit_4->show();
        ui->checkBox->show();
        ui->pushButton_3->show();
        ui->label_6->show();
        ui->lineEdit_5->show();
        ui->label_5->show();
        ui->lineEdit_6->show();
        ui->checkBox_2->show();
        ui->pushButton_4->show();
        ui->checkBox_3->show();
        ui->lineEdit_7->show();
        ui->pushButton_6->show();
        ui->label_7->show();
        ui->lineEdit_8->show();
        ui->label_8->show();
        ui->pushButton_14->move(250,300);
        ui->pushButton_14->show();
        ui->lineEdit_9->hide();
        ui->lineEdit_10->hide();
        ui->label_9->hide();
        ui->label_10->hide();
        ui->checkBox_4->hide();
        ui->pushButton_8->hide();
        ui->lineEdit_11->hide();
        ui->lineEdit_12->hide();
        ui->label_11->hide();
        ui->label_12->hide();
        ui->pushButton_10->hide();
        ui->checkBox_5->hide();
        ui->label_13->hide();
        ui->label_14->hide();
        ui->lineEdit_13->hide();
        ui->lineEdit_14->hide();
        ui->checkBox_6->hide();
        ui->pushButton_12->hide();
    }
    else if(index == 4)
    {
        this->setFixedSize(600,440);
        ui->label_4->show();
        ui->lineEdit_3->show();
        ui->label_3->show();
        ui->lineEdit_4->show();
        ui->checkBox->show();
        ui->pushButton_3->show();
        ui->label_6->show();
        ui->lineEdit_5->show();
        ui->label_5->show();
        ui->lineEdit_6->show();
        ui->checkBox_2->show();
        ui->pushButton_4->show();
        ui->checkBox_3->show();
        ui->lineEdit_7->show();
        ui->pushButton_6->show();
        ui->label_7->show();
        ui->lineEdit_8->show();
        ui->label_8->show();
        ui->lineEdit_9->show();
        ui->lineEdit_10->show();
        ui->label_9->show();
        ui->label_10->show();
        ui->checkBox_4->show();
        ui->pushButton_8->show();
        ui->pushButton_14->move(250,340);
        ui->pushButton_14->show();
        ui->lineEdit_11->hide();
        ui->lineEdit_12->hide();
        ui->label_11->hide();
        ui->label_12->hide();
        ui->pushButton_10->hide();
        ui->checkBox_5->hide();
        ui->label_13->hide();
        ui->label_14->hide();
        ui->lineEdit_13->hide();
        ui->lineEdit_14->hide();
        ui->checkBox_6->hide();
        ui->pushButton_12->hide();
    }
    else if(index == 5)
    {
        this->setFixedSize(600,460);
        ui->label_4->show();
        ui->lineEdit_3->show();
        ui->label_3->show();
        ui->lineEdit_4->show();
        ui->checkBox->show();
        ui->pushButton_3->show();
        ui->label_6->show();
        ui->lineEdit_5->show();
        ui->label_5->show();
        ui->lineEdit_6->show();
        ui->checkBox_2->show();
        ui->pushButton_4->show();
        ui->checkBox_3->show();
        ui->lineEdit_7->show();
        ui->pushButton_6->show();
        ui->label_7->show();
        ui->lineEdit_8->show();
        ui->label_8->show();
        ui->lineEdit_9->show();
        ui->lineEdit_10->show();
        ui->label_9->show();
        ui->label_10->show();
        ui->checkBox_4->show();
        ui->pushButton_8->show();
        ui->lineEdit_11->show();
        ui->lineEdit_12->show();
        ui->label_11->show();
        ui->label_12->show();
        ui->pushButton_10->show();
        ui->checkBox_5->show();
        ui->pushButton_14->move(250,380);
        ui->pushButton_14->show();
        ui->label_13->hide();
        ui->label_14->hide();
        ui->lineEdit_13->hide();
        ui->lineEdit_14->hide();
        ui->checkBox_6->hide();
        ui->pushButton_12->hide();
    }
    else if(index == 6)
    {
        this->setFixedSize(600,480);
        ui->label_4->show();
        ui->lineEdit_3->show();
        ui->label_3->show();
        ui->lineEdit_4->show();
        ui->checkBox->show();
        ui->pushButton_3->show();
        ui->label_6->show();
        ui->lineEdit_5->show();
        ui->label_5->show();
        ui->lineEdit_6->show();
        ui->checkBox_2->show();
        ui->pushButton_4->show();
        ui->checkBox_3->show();
        ui->lineEdit_7->show();
        ui->pushButton_6->show();
        ui->label_7->show();
        ui->lineEdit_8->show();
        ui->label_8->show();
        ui->lineEdit_9->show();
        ui->lineEdit_10->show();
        ui->label_9->show();
        ui->label_10->show();
        ui->checkBox_4->show();
        ui->pushButton_8->show();
        ui->lineEdit_11->show();
        ui->lineEdit_12->show();
        ui->label_11->show();
        ui->label_12->show();
        ui->pushButton_10->show();
        ui->checkBox_5->show();
        ui->label_13->show();
        ui->label_14->show();
        ui->lineEdit_13->show();
        ui->lineEdit_14->show();
        ui->checkBox_6->show();
        ui->pushButton_12->show();
        ui->pushButton_14->move(250,410);
        ui->pushButton_14->show();
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    if(ui->pushButton_3->text() == "Pause"){
        readerArray[0]->isPaused = true;
        ui->pushButton_3->setText("Play");
    }
    else{
        readerArray[0]->isPaused = false;
        readerArray[0]->pauseSemaphore.V();
         ui->pushButton_3->setText("Pause");
    }

}

void MainWindow::on_pushButton_4_clicked()
{
    if(ui->pushButton_4->text() == "Pause"){
        readerArray[1]->isPaused = true;
        ui->pushButton_4->setText("Play");
    }
    else{
        readerArray[1]->isPaused = false;
        readerArray[1]->pauseSemaphore.V();
         ui->pushButton_4->setText("Pause");
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    if(ui->pushButton_6->text() == "Pause"){
        readerArray[2]->isPaused = true;
        ui->pushButton_6->setText("Play");
    }
    else{
        readerArray[2]->isPaused = false;
        readerArray[2]->pauseSemaphore.V();
         ui->pushButton_6->setText("Pause");
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    if(ui->pushButton_8->text() == "Pause"){
        readerArray[3]->isPaused = true;
        ui->pushButton_8->setText("Play");
    }
    else{
        readerArray[3]->isPaused = false;
        readerArray[3]->pauseSemaphore.V();
         ui->pushButton_8->setText("Pause");
    }
}

void MainWindow::on_pushButton_10_clicked()
{
    if(ui->pushButton_10->text() == "Pause"){
        readerArray[4]->isPaused = true;
        ui->pushButton_10->setText("Play");
    }
    else{
        readerArray[4]->isPaused = false;
        readerArray[4]->pauseSemaphore.V();
         ui->pushButton_10->setText("Pause");
    }
}

void MainWindow::on_pushButton_12_clicked()
{
    if(ui->pushButton_12->text() == "Pause"){
        readerArray[5]->isPaused = true;
        ui->pushButton_12->setText("Play");
    }
    else{
        readerArray[5]->isPaused = false;
        readerArray[5]->pauseSemaphore.V();
         ui->pushButton_12->setText("Pause");
    }
}

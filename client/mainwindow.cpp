#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextBrowser>
#include <QPushButton>
#include <QComboBox>
#include "client_socket.h"

#define NAME_SERVER "/home/vboxuser/Public/server_socket.server"
#define COMMAND_RANGE "set_range"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , client(new ClientSocket(this))
{
    ui->setupUi(this);

    sendBtn = ui->sendButton;
    browser = ui->outputBrowser;

    commandComBox = ui->commandComBox;
    rangeComBox = ui->rangeComBox;

    connect(client, &ClientSocket::logToBrowser, this, &MainWindow::logToBrowser);
    connect(sendBtn, SIGNAL(clicked(bool)), this, SLOT(sendData()));

    connect(commandComBox, SIGNAL(currentIndexChanged(int)), this, SLOT(commandChanged(int)));

    disableRange();
}

MainWindow::~MainWindow()
{
    delete client;
    delete ui;
}

void MainWindow::commandChanged(int) {
    disableRange();
}

void MainWindow::disableRange() {
    rangeComBox->setDisabled(!isRangeCommand());
}

bool MainWindow::isRangeCommand() {
    return commandComBox->currentText() == COMMAND_RANGE;
}

void MainWindow::sendData() {

    QString data = ui->commandComBox->currentText();
    data += " " + ui->channelComBox->currentText();
    data += isRangeCommand() ? " " + rangeComBox->currentText() : "";

    client->setData(data);
    client->connectToServer();
}

void MainWindow::logToBrowser(const QString& text) {
    browser->append(text);
}









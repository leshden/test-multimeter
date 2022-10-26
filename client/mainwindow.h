#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTextBrowser;
class QPushButton;
class QComboBox;
class ClientSocket;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ClientSocket* client = nullptr;

    QPushButton* sendBtn = nullptr;
    QTextBrowser* browser = nullptr;

    QComboBox* commandComBox = nullptr;
    QComboBox* rangeComBox = nullptr;

private:
    void disableRange();
    bool isRangeCommand();

private slots:
    void logToBrowser(const QString& text);
    void sendData();

    void commandChanged(int index);

};
#endif // MAINWINDOW_H

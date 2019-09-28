#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <string>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>
#include <QInputDialog>
#include <QFile>
#include <QTextEdit>

#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QDataStream>
#include <QByteArray>
#include <QTimer>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void shoow(int in = 900);
    const QPixmap moveable;
    const QPixmap select;
    const QPixmap danger;
    const QPixmap dark;
    const QPixmap white;
public slots:
    void chess_pressed(int);

private slots:
    void on_showPossible_clicked();
    void printOut();
    void prepareStart();
    void connectSuccess();

private:
    Ui::MainWindow *ui;
    QVector<QPushButton*> buttons;
    QVector<QPushButton*> backGround;
    QVector<QPixmap> chessPic;
    QVector<QPushButton*> level;
    QVector<QLabel*> levelBackground;
    QVector<QLabel*> victoryLabel;
    QVector<int> debugg;
    bool possiblePressed;
    int issetboard;
    QVector<bool> kingAppear;
    bool moved;
    void uiManage(int);

    QTcpServer* tcpServer;
    QTcpSocket* tcpSocket;
    QTimer* checkConnect = new QTimer(this);
    int id = 0;
    QVector<int> clientId;
    bool netMove = false;
    QDataStream& dataStreamInt(QDataStream&, QByteArray&, int);
    bool who = false;       // determine whether you can change the board

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H

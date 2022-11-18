#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "litesqlmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void tryOperation(QString const& text,bool);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    LiteSqlManager m_sqlManager;
};
#endif // MAINWINDOW_H

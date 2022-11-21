#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlTableModel>

static const QString path("Scoreboard.sql");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_sqlManager(path)
{
    ui->setupUi(this);
    m_sqlManager.loaded();
    if(!m_sqlManager.tables(QSql::Tables).contains("CeleryTable"))
        m_sqlManager.createTable();
    QStringList lst;
    lst<<"Michael"<<"Luca"<<"Mattia"<<"Mauro"<<"Stefano";
    for(QString const& it: lst)
        m_sqlManager.addAccount(it);
    ui->comboBox->addItems(lst);



    //Model
    QSqlTableModel * model = new QSqlTableModel(ui->tableView,m_sqlManager);
    model->setTable("CeleryTable");
    model->select();
    ui->tableView->setModel(model);

}

MainWindow::~MainWindow()
{
    m_sqlManager.close();
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    m_sqlManager.celeryFounded(ui->comboBox->currentText());
    QSqlTableModel * qmodel = dynamic_cast<QSqlTableModel*>(ui->tableView->model());
    if(qmodel) qmodel->select();
}


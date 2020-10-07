#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtSql>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString& databaseLogin, const QString& databasePassword, QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_retry_database_connection_clicked();

    void on_pushButton_change_mode_clicked();

private:
    Ui::MainWindow* mMain_ui = nullptr;

    QString mDatabaseLogin, mDatabasePassword;
    QSqlDatabase mDatabase;

    QSqlQueryModel* mQueryModel = nullptr;
    QSqlTableModel* mTableModel = nullptr;
};

#endif // MAINWINDOW_H

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

    void on_pushButton_search_clicked();

private:
    void setup_select_all_queryModel(QSqlQueryModel* const queryModel) const;
    void setup_select_all_tableModel(QSqlTableModel* const tableModel) const;

    void setup_search_queryModel(QSqlQueryModel* const queryModel, const QString& searchRequest) const;
    void setup_search_tableModel(QSqlTableModel* const tableModel, const QString& searchRequest) const;

    void setup_headers_queryModel(QSqlQueryModel* const queryModel) const;
    void setup_headers_tableModel(QSqlTableModel* const tableModel) const;

    Ui::MainWindow* mMain_ui = nullptr;

    QSqlQueryModel* mQueryModel = nullptr;
    QSqlTableModel* mTableModel = nullptr;

    QString mHosteName = "localhost", mDatabaseName = "information_system", mDatabaseLogin, mDatabasePassword;
    QSqlDatabase mDatabase;
};

#endif // MAINWINDOW_H

#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "addNewItemWindow.h"

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
    void on_pushButton_update_database_clicked();

    void on_pushButton_change_mode_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_insert_new_record_clicked();

private:
    void setup_select_all_queryModel(QSqlQueryModel* const queryModel) const;
    void setup_select_all_tableModel(QSqlTableModel* const tableModel) const;

    void setup_search_queryModel(QSqlQueryModel* const queryModel, const QString& searchRequest) const;
    void setup_search_tableModel(QSqlTableModel* const tableModel, const QString& searchRequest) const;

    void setup_headers_queryModel(QSqlQueryModel* const queryModel) const;
    void setup_headers_tableModel(QSqlTableModel* const tableModel) const;

    Ui::MainWindow* mMain_ui = nullptr;
    AddNewItemWindow* mAddNewItemWindow = nullptr;

    QSqlQueryModel* mQueryModel = nullptr;
    QSqlTableModel* mTableModel = nullptr;

    QString mHosteName = "localhost", mDatabaseLogin, mDatabasePassword, mDatabaseName = "information_system";
    QSqlDatabase mDatabase;
};

#endif // MAINWINDOW_H

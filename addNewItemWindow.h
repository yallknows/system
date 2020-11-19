#pragma once

#ifndef ADDNEWITEMWINDOW_H
#define ADDNEWITEMWINDOW_H

#include <QDialog>

#include <QtSql>

namespace Ui
{
    class AddNewItemWindow;
}

class AddNewItemWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewItemWindow(const QString& hosteName, const QString& databaseLogin,
        const QString& databasePassword, const QString& databaseName, QWidget* parent = nullptr);
    ~AddNewItemWindow();

private slots:
    void on_pushButton_addItem_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::AddNewItemWindow* mAddNewItem_ui = nullptr;

    QSqlDatabase mDatabase;
};

#endif // ADDNEWITEMWINDOW_H

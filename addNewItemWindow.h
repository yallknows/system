#pragma once

#ifndef ADDNEWITEMWINDOW_H
#define ADDNEWITEMWINDOW_H

#include <QDialog>

namespace Ui
{
    class AddNewItemWindow;
}

class AddNewItemWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewItemWindow(QWidget* parent = nullptr);
    ~AddNewItemWindow();

private:
    Ui::AddNewItemWindow* mAddNewItem_ui = nullptr;
};

#endif // ADDNEWITEMWINDOW_H

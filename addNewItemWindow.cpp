#include "addNewItemWindow.h"
#include "ui_addNewItemWindow.h"

AddNewItemWindow::AddNewItemWindow(QWidget* parent)
    : QDialog(parent), mAddNewItem_ui(new Ui::AddNewItemWindow)
{
    mAddNewItem_ui->setupUi(this);
}

AddNewItemWindow::~AddNewItemWindow()
{
    if (mAddNewItem_ui != nullptr)
    {
        delete mAddNewItem_ui;
        mAddNewItem_ui = nullptr;
    }
}

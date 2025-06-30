#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->confirm, &QPushButton::clicked, this, &QDialog::accept);

    connect(ui->cancel, &QPushButton::clicked, this, &QDialog::reject);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::setTitle(const QString &title)
{
    ui->DialogTitle->setText(title);
}
void Dialog::setLabel(const QString &desc)
{
    ui->DialogLabel->setText(desc);
}
void Dialog::setConfirmButtonText(const QString &text)
{
    ui->confirm->setText(text);
}
void Dialog::setCancelButtonText(const QString &text)
{
    ui->cancel->setText(text);
}
void Dialog::setIcon(const QPixmap &pixmap)
{
    ui->DialogTitleIcon->setPixmap(pixmap);
}


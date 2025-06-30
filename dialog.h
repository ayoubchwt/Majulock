#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void setTitle(const QString &title);
    void setLabel(const QString &desc);
    void setConfirmButtonText(const QString &text);
    void setCancelButtonText(const QString &text);
    void setIcon(const QPixmap &pixmap);
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H

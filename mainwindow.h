#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>
#include <QMainWindow>
#include <QFile>
#include<QGraphicsDropShadowEffect>
#include <QListWidgetItem>
#include <QPainter>
#include <QSvgRenderer>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QClipboard>
#include <QToolTip>
#include "connection.h"
#include "Password.h"
#include "dialog.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initInputs();
    void initLists();
    void setActivateButton(QPushButton* activeButton);
    QWidget* createPasswordItem(const QString& title, const QString& email, const QPixmap& icon);
    void showPasswordDetails(const Password &password);
    QPixmap FromSvgToPixmap(const QSize &ImageSize,const QString &SvgFile);
    QString generatePassword(int length);
private slots:
    void on_passwordsAdd_clicked();
    void on_passwordsAddDiscard_clicked();
    void on_passwordsAddConfirm_clicked();    
    void on_passwordsList_itemClicked(QListWidgetItem *item);
    void on_passwordDelete_clicked();
    void on_passwordEdit_clicked();
    void on_passwordsEditDiscard_clicked();
    void on_passwordsEditConfirm_clicked();
    void on_passwordsSearch_textChanged(const QString &arg1);
    void on_passwordGenrate_clicked();
    void on_passwordGenrate_2_clicked();
    void on_showPassword_clicked();
    void on_emailCopy_clicked();
    void on_usernameCopy_clicked();
    void on_passwordCopy_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsDropShadowEffect *effect;
    Password *p;
};
#endif // MAINWINDOW_H

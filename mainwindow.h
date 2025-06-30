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
private slots:
    void on_passwordsAdd_clicked();
    void on_passwordsAddDiscard_clicked();
    void on_passwordsAddConfirm_clicked();    
    void on_passwordsList_itemClicked(QListWidgetItem *item);

    void on_passwordDelete_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsDropShadowEffect *effect;
    Password *p;
};
#endif // MAINWINDOW_H

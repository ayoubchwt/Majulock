#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    connection::createConnection();
    ui->setupUi(this);
    connect(ui->passwordsBtn, &QPushButton::clicked, this,[=](){
        ui->mainwidget->setCurrentIndex(0);
        this->setActivateButton(ui->passwordsBtn);
    });
    connect(ui->personalInfosBtn, &QPushButton::clicked, this,[=](){
        ui->mainwidget->setCurrentIndex(1);
        this->setActivateButton(ui->personalInfosBtn);
    });
    connect(ui->creditCardsBtn, &QPushButton::clicked, this,[=](){
        ui->mainwidget->setCurrentIndex(2);
        this->setActivateButton(ui->creditCardsBtn);
    });
    connect(ui->notesBtn, &QPushButton::clicked, this,[=](){
        ui->mainwidget->setCurrentIndex(3);
        this->setActivateButton(ui->notesBtn);
    });
    connect(ui->picturesBtn, &QPushButton::clicked, this,[=](){
        ui->mainwidget->setCurrentIndex(4);
        this->setActivateButton(ui->picturesBtn);
    });
    connect(ui->settingsBtn, &QPushButton::clicked, this,[=](){
        ui->mainwidget->setCurrentIndex(5);
        this->setActivateButton(ui->settingsBtn);
    });
    connect(ui->logoutBtn, &QPushButton::clicked, this,[=](){

    });
    auto createShadowEffect = [](QObject* parent) -> QGraphicsDropShadowEffect* {
        auto effect = new QGraphicsDropShadowEffect(parent);
        effect->setBlurRadius(20);
        effect->setOffset(0, 6);
        effect->setColor(QColor(0, 0, 0, 7));
        return effect;
    };
    ui->passwordsTop->setGraphicsEffect(createShadowEffect(this));
    ui->passwordsMain->setGraphicsEffect(createShadowEffect(this));
    initLists();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setActivateButton(QPushButton* activeButton){
    QList<QPushButton*> buttons = { ui->passwordsBtn, ui->personalInfosBtn, ui->creditCardsBtn ,ui->notesBtn ,ui->picturesBtn ,ui->settingsBtn};
    for(QPushButton * button : buttons){
        if(button == activeButton){
            button->setStyleSheet(
                "background-color: #212d40;"
            );
        }
        else{
            button->setStyleSheet(
                "QPushButton {"
                "background-color: #172133;"
                "color: #cbd5e1;"
                "padding: 8px 17px;"
                "font-weight: bold;"
                "font-size: 14px;"
                "margin : 0px;"
                "border : none;"
                "text-align: left;"
                "}"
                "QPushButton:hover {"
                "background-color: #212d40;"
                "}"
            );
        }
    }
}
void MainWindow::initInputs(){
    ui->addLoginLabel->clear();
    ui->addLoginEmail->clear();
    ui->addLoginPassword->clear();
    ui->addLoginUsername->clear();
    ui->showLoginLabel->clear();
    ui->showLoginEmail->clear();
    ui->showLoginUsername->clear();
    ui->showLoginPassword->clear();
    ui->showLoginCreated->clear();
    ui->showLoginLastModified->clear();
}
void MainWindow::initLists(){
    int passwordsCount = 0 ;
    ui->passwordsList->clear();
    ui->passwordsList->setIconSize(QSize(32, 32));
    QList<Password> passwords = p->listPassword();
    for (const Password& pwd : passwords) {
        QListWidgetItem* item = new QListWidgetItem();
        item->setText(QString("%1\n%2").arg(pwd.getLabel(), pwd.getEmail()));
        item->setData(Qt::UserRole, pwd.getId());
        QString labelLower = pwd.getLabel().toLower().trimmed();
        labelLower.replace(" ", "");
        QString iconPath = QString(":/Assets/PasswordIcons/%1.svg").arg(labelLower);
        if (QFile::exists(iconPath)) {
            item->setIcon(QIcon(iconPath));
        } else {
            item->setIcon(QIcon(":/Assets/PasswordIcons/default.svg"));
        }
        item->setSizeHint(QSize(200, 70));
        ui->passwordsList->addItem(item);
        passwordsCount ++;
    }
    ui->passwordsCount->setText(QString("%1 Items").arg(passwordsCount));
    if (ui->passwordsList->count() > 0) {
        ui->passwordsList->setCurrentRow(0);
        showPasswordDetails(passwords.at(0));
    }
}
void MainWindow::showPasswordDetails(const Password &password) {
    QString labelLower = password.getLabel().toLower().trimmed();
    labelLower.replace(" ", "");
    QString iconPath = QString(":/Assets/PasswordIcons/%1.svg").arg(labelLower);
    if (!QFile::exists(iconPath)) {
        iconPath = ":/Assets/PasswordIcons/default.svg";
    }
    QPixmap pix = this->FromSvgToPixmap(QSize(64,64), iconPath);
    ui->showLoginLabelLogo->setPixmap(pix);
    ui->showLoginLabel->setText(password.getLabel());
    ui->showLoginEmail->setText(password.getEmail());
    ui->showLoginUsername->setText(password.getUsername());
    ui->showLoginPassword->setText(password.getPass());
    ui->showLoginCreated->setText(QString("Created : %1").arg(password.getCreated()));
    ui->showLoginLastModified->setText(QString("Last Modified : %1").arg(password.getLastModified()));
}
QPixmap MainWindow::FromSvgToPixmap(const QSize &ImageSize,const QString &SvgFile) {
    QSvgRenderer SvgRenderer(SvgFile);
    QPixmap Image(ImageSize);
    QPainter Painter;
    Image.fill(Qt::transparent);
    Painter.begin(&Image);
    SvgRenderer.render(&Painter);
    Painter.end();
    return Image;
}
void MainWindow::on_passwordsAdd_clicked()
{
    ui->passwordsForm->setCurrentIndex(1);
}
void MainWindow::on_passwordsAddDiscard_clicked()
{
    ui->passwordsForm->setCurrentIndex(0);
    this->initInputs();
    this->initLists();
}
void MainWindow::on_passwordsAddConfirm_clicked()
{
    QString label = ui->addLoginLabel->text();
    QString username = ui->addLoginUsername->text();
    QString email = ui->addLoginEmail->text();
    QString pass = ui->addLoginPassword->text();
    QString created = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString lastModified = created;
    Password password("",label,email,username,pass,created,lastModified);
    if(p->createPassword(password)){
        initLists();
        initInputs();
    }
    else {
        qDebug() << "ooooh not Zebbi";
    }
}
void MainWindow::on_passwordsList_itemClicked(QListWidgetItem *item)
{
    this->initInputs();
    ui->passwordsForm->setCurrentIndex(0);
    QString passwordId = item->data(Qt::UserRole).toString();
    Password password = p->searchPassword(passwordId);
    showPasswordDetails(password);
}
void MainWindow::on_passwordDelete_clicked()
{
    QListWidgetItem *currentItem = ui->passwordsList->currentItem();
    if (currentItem) {
        QString passwordId = currentItem->data(Qt::UserRole).toString();
        QString label = currentItem->text().split('\n').first();
        Dialog dialog(this);
        dialog.setTitle("Delete Login");
        dialog.setLabel(QString("Are you sure you want to delete the login \"%1\" ?").arg(label));
        dialog.setConfirmButtonText(" Yes, Delete");
        dialog.setCancelButtonText(" No, Cancel");
        dialog.setIcon(this->FromSvgToPixmap(QSize(30,30), ":/Assets/Icons/trash.svg"));

        if (dialog.exec() == QDialog::Accepted) {
            p->deletePassword(passwordId);
            initLists();
        }
    }
}


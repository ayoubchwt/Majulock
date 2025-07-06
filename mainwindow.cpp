#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    connection::createConnection();
    ui->setupUi(this);
    pawnedChecker = new PawnedChecker(this);
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
    connect(pawnedChecker, &PawnedChecker::passwordPwned, this, [=](int count){
        ui->vulnerableLabel->setText(QString("Warning: Password found %1 times in breaches!").arg(count));
        ui->vulnerableLabel->show();
        ui->vulnerableIcon->show();
    });
    connect(pawnedChecker, &PawnedChecker::passwordSafe, this, [=](){
        ui->vulnerableLabel->hide();
        ui->vulnerableIcon->hide();
    });
    connect(pawnedChecker, &PawnedChecker::checkFailed, this, [=](const QString &error){
        qDebug() << "Pawned check failed:" << error;
        ui->vulnerableLabel->hide();
        ui->vulnerableIcon->hide();
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
    this->setActivateButton(ui->passwordsBtn);
    ui->mainwidget->setCurrentIndex(0);
    initInputs();
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
    ui->showLoginPassword->setEchoMode(QLineEdit::Password);
    ui->showLoginCreated->clear();
    ui->showLoginLastModified->clear();
    ui->vulnerableLabel->hide();
    ui->vulnerableIcon->hide();
    ui->addLabelError->clear();
    ui->addEmailError->clear();
    ui->addPasswordError->clear();
    ui->editLabelError->clear();
    ui->editEmailError->clear();
    ui->editPasswordError->clear();
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
    ui->showLoginPassword->setEchoMode(QLineEdit::Password);
    pawnedChecker->checkPassword(password.getPass());
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
QString MainWindow::generatePassword(int length){
    const QString chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "!@#$%^&*()_+-=<>?";
    QString password;
    for (int i = 0; i < length; ++i)
    {
        int idx = QRandomGenerator::global()->bounded(chars.length());
        password.append(chars.at(idx));
    }
    return password;
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
    bool isValid = true;

    ui->addLabelError->clear();
    ui->addEmailError->clear();
    ui->addPasswordError->clear();

    QString label = ui->addLoginLabel->text();
    QString email = ui->addLoginEmail->text();
    QString pass = ui->addLoginPassword->text();
    QString username = ui->addLoginUsername->text();
    QString created = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString lastModified = created;

    if (!Validator::validateLabel(label)) {
        qDebug() << Validator::validateLabel(label);
        ui->addLabelError->setText("Label should be at least 2 characters");
        isValid = false;
    }
    if (!Validator::validateEmail(email)) {
        ui->addEmailError->setText("Invalid email format");
        isValid = false;
    }
    if (!Validator::validatePassword(pass)) {
        ui->addPasswordError->setText("Password should be at least 8 characters");
        isValid = false;
    }
    if (!isValid) {
        return;
    }
    Password password("", label, email, username, pass, created, lastModified);
    if (p->createPassword(password)) {
        initLists();
        initInputs();
    } else {
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
void MainWindow::on_passwordEdit_clicked()
{
    QListWidgetItem *currentItem = ui->passwordsList->currentItem();
    if (currentItem) {
        QString passwordId = currentItem->data(Qt::UserRole).toString();
        Password pass = p->searchPassword(passwordId);
        ui->editLoginLabel->setText(pass.getLabel());
        ui->editLoginEmail->setText(pass.getEmail());
        ui->editLoginUsername->setText(pass.getUsername());
        ui->editLoginPassword->setText(pass.getPass());
        ui->passwordsForm->setCurrentIndex(2);
    }
}
void MainWindow::on_passwordsEditDiscard_clicked()
{
    ui->passwordsForm->setCurrentIndex(0);
    this->initInputs();
    this->initLists();
}
void MainWindow::on_passwordsEditConfirm_clicked()
{
    bool isValid = true;

    ui->editLabelError->clear();
    ui->editEmailError->clear();
    ui->editPasswordError->clear();

    QString label = ui->editLoginLabel->text();
    QString email = ui->editLoginEmail->text();
    QString pass = ui->editLoginPassword->text();

    if (!Validator::validateLabel(label)) {
        qDebug() << Validator::validateLabel(label);
        ui->editLabelError->setText("Label should be at least 2 characters");
        isValid = false;
    }
    if (!Validator::validateEmail(email)) {
        ui->editEmailError->setText("Invalid email format");
        isValid = false;
    }
    if (!Validator::validatePassword(pass)) {
        ui->editPasswordError->setText("Password should be at least 8 characters");
        isValid = false;
    }
    if (!isValid) {
        return;
    }
    Dialog dialog(this);
    dialog.setTitle("Edit Login");
    dialog.setLabel(QString("Are you sure you want to edit the login \"%1\" ?").arg(label));
    dialog.setConfirmButtonText(" Yes, Edit");
    dialog.setCancelButtonText(" No, Cancel");
    dialog.setIcon(this->FromSvgToPixmap(QSize(30,30), ":/Assets/Icons/pen.svg"));
    if (dialog.exec() == QDialog::Accepted) {
        QListWidgetItem *currentItem = ui->passwordsList->currentItem();
        if (currentItem) {
            QString passwordId = currentItem->data(Qt::UserRole).toString();
            QString username = ui->editLoginUsername->text();
            QString lastModified = QDateTime::currentDateTime().toString("yyyy-MM-dd");
            Password password(passwordId, label, email, username, pass, "", lastModified);
            if(p->updatePassword(password)){
                initLists();
                initInputs();
                qDebug() << "ooooh yes Zebbi";
            }
            else {
                qDebug() << "ooooh not Zebbi";
            }
        }
    }
    ui->passwordsForm->setCurrentIndex(0);
    this->initInputs();
    this->initLists();
}
void MainWindow::on_passwordsSearch_textChanged(const QString &arg1)
{
    for (int i = 0; i < ui->passwordsList->count(); ++i)
    {
        QListWidgetItem *item = ui->passwordsList->item(i);
        QString labelText = item->text().split('\n').first().toLower();
        QString searchLower = arg1.toLower();
        if (labelText.contains(searchLower))
            item->setHidden(false);
        else
            item->setHidden(true);
    }
}
void MainWindow::on_passwordGenrate_clicked()
{
    ui->addLoginPassword->setText(this->generatePassword(12));
}
void MainWindow::on_passwordGenrate_2_clicked()
{
    ui->editLoginPassword->setText(this->generatePassword(12));
}
void MainWindow::on_showPassword_clicked()
{
    if (ui->showLoginPassword->echoMode() == QLineEdit::Password) {
        ui->showLoginPassword->setEchoMode(QLineEdit::Normal);
        ui->showPassword->setIcon(QIcon(":/Assets/Icons/eye-off.svg"));
    } else {
        ui->showLoginPassword->setEchoMode(QLineEdit::Password);
        ui->showPassword->setIcon(QIcon(":/Assets/Icons/eye.svg"));
    }
}
void MainWindow::on_emailCopy_clicked()
{
    QString password = ui->showLoginEmail->text();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(password);
    QToolTip::showText(ui->emailCopy->mapToGlobal(QPoint()), "Copied!");
}
void MainWindow::on_usernameCopy_clicked()
{
    QString username = ui->showLoginUsername->text();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(username);
    QToolTip::showText(ui->usernameCopy->mapToGlobal(QPoint()), "Copied!");
}
void MainWindow::on_passwordCopy_clicked()
{
    QString password = ui->showLoginPassword->text();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(password);
    QToolTip::showText(ui->passwordCopy->mapToGlobal(QPoint()), "Copied!");
}


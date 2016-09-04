#include "asktabname.h"
#include "ui_asktabname.h"

AskTabName::AskTabName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AskTabName)
{
    ui->setupUi(this);
}

AskTabName::~AskTabName()
{
    delete ui;
}

void AskTabName::on_buttonBox_accepted()
{
    //TODO: проверить корректность ввода
    tab_name = ui->lineEdit->text();
}

QString AskTabName::getTabName()
{
    return tab_name;
}

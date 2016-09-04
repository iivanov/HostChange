#ifndef ASKTABNAME_H
#define ASKTABNAME_H

#include <QDialog>

namespace Ui {
class AskTabName;
}

class AskTabName : public QDialog
{
    Q_OBJECT

public:
    explicit AskTabName(QWidget *parent = 0);
    ~AskTabName();
    QString getTabName();
private slots:
    void on_buttonBox_accepted();

private:
    Ui::AskTabName *ui;
    QString tab_name;
};

#endif // ASKTABNAME_H

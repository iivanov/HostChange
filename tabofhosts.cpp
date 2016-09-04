#include "tabofhosts.h"
#include <QDebug>

TabOfHosts::TabOfHosts(QTabWidget * tab, QString tab_name, QObject *parent) : QObject(parent)
{
    tab_widget = tab;
    name = tab_name;
    initTab();
}

TabOfHosts::TabOfHosts(TabOfHosts* for_copy_tab, QString tab_name, QObject* parent) : QObject(parent)
{
    tab_widget = for_copy_tab->tab_widget;
    name = tab_name;
    initTab();
    if (for_copy_tab->is_pattern_checkbox->isChecked()) {
        showPattern();
    }
    pattern_text_edit->setPlainText(for_copy_tab->pattern_text_edit->toPlainText());
    plain_text_edit->setPlainText(for_copy_tab->plain_text_edit->toPlainText());
}

TabOfHosts::TabOfHosts(QTabWidget * tab, QString tab_name, QString file_name, QObject *parent) : QObject(parent)
{

    tab_widget = tab;
    name = tab_name;

    initTab();

    QFile file(file_name);

    if (file.open(QFile::ReadOnly | QFile::Text)) {

        QTextStream ReadFile(&file);
        QString is_pattern = ReadFile.readLine();

        if (is_pattern.compare("pattern") == 0) {
            pattern_text_edit->setPlainText(ReadFile.readAll());
            showPattern();

            //TODO: распарсить шаблон

        } else {
            is_pattern = is_pattern.append("\n");
            plain_text_edit->setPlainText(is_pattern.append(ReadFile.readAll()));
        }



    } else {
        //TODO: нормально описать причину ошибки
        QMessageBox::critical(currentTab, tr("Errore"), tr("Can not get hosts file"));
    }


}


void TabOfHosts::initTab()
{
    currentTab = new QWidget(tab_widget);

    plain_text_edit = new QPlainTextEdit(currentTab);
    connect(plain_text_edit, SIGNAL (textChanged()), this, SLOT (changedHostTab()));
    plain_text_edit->move(0, 20);

    pattern_text_edit = new QPlainTextEdit(currentTab);
    connect(pattern_text_edit, SIGNAL (textChanged()), this, SLOT (changedHostTab()));
    pattern_text_edit->move(320, 20);
    pattern_text_edit->hide();

    is_pattern_checkbox = new QCheckBox(currentTab);
    is_pattern_checkbox->setText("Use pattern");
    connect(is_pattern_checkbox, SIGNAL (stateChanged(int)), this, SLOT (patternCheckboxChanged(int)));
    is_pattern_checkbox->move(0, 0);

    apply_button = new QPushButton(currentTab);
    apply_button->setText("Set this hosts");
    apply_button->move(0, 230);
    connect(apply_button, SIGNAL (pressed()), this, SLOT (setCurrentHosts()));

    tab_widget->addTab(currentTab, name);
}


void TabOfHosts::setCurrentHosts()
{

    QFile file(hosts_file_path);

    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        QString hosts_text;

        if (is_pattern_checkbox->isChecked()) {
            //TODO:!!!!!!!
        } else {
            hosts_text = plain_text_edit->toPlainText();
        }

        stream << hosts_text;

        file.flush();
        file.close();
    } else {
        //TODO: нормально описать причину ошибки
        QMessageBox::critical(currentTab, tr("Errore"), tr("Can not save file"));
    }
    apply_button->setEnabled(false);
}

void TabOfHosts::changedHostTab()
{
    apply_button->setEnabled(true);
}

QString TabOfHosts::getFilePath()
{
    QString file_path = "";
    if (name.compare("/etc/hosts") == 0) {
        file_path = hosts_file_path;
    } else {
        file_path.append("./");
        file_path.append(name).append(".hosts");
    }

    return file_path;
}

void TabOfHosts::save()
{
    QString file_path = getFilePath();
    QFile file(file_path);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);

        if (is_pattern_checkbox->isChecked()) {
            stream << "pattern" << endl;
            stream << pattern_text_edit->toPlainText();
        } else {
            stream << plain_text_edit->toPlainText();
        }
        file.flush();
        file.close();
    } else {
        //TODO: нормально описать причину ошибки
        QMessageBox::critical(currentTab, tr("Errore"), file_path.append(" Can not save file"));
    }
}

bool TabOfHosts::remove()
{
    QMessageBox msgBox;
    msgBox.setText("Delete file");
    msgBox.setInformativeText("Do you want delete current host files?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    bool result = false;
    if (msgBox.exec() == QMessageBox::Ok) {
        QFile(getFilePath()).remove();
        result = true;
    }
    return result;
}


void TabOfHosts::showPattern()
{
    pattern_text_edit->show();
    plain_text_edit->setReadOnly(true);
    if (plain_text_edit->toPlainText().length() > 0) {
        pattern_text_edit->setPlainText(plain_text_edit->toPlainText());
    }
    is_pattern_checkbox->setChecked(true);
}

void TabOfHosts::hidePatter()
{
    pattern_text_edit->hide();
    plain_text_edit->setReadOnly(false);
    is_pattern_checkbox->setChecked(false);
}


void TabOfHosts::patternCheckboxChanged(int i)
{
    if (is_pattern_checkbox->isChecked()) {
        showPattern();
    } else {
        hidePatter();
    }
}

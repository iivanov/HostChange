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

    loadFromFile(file_name);

}


void TabOfHosts::loadFromFile(QString file_name)
{
    QFile file(file_name);

    if (file.open(QFile::ReadOnly | QFile::Text)) {

        QTextStream ReadFile(&file);
        QString is_pattern = ReadFile.readLine();

        if (is_pattern.compare("pattern") == 0) {
            pattern_text_edit->setPlainText(ReadFile.readAll());
            showPattern();

            showPattern();
            showPatternElements();
            parsePattern();

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
    pattern_parser = new PatternParser();

    currentTab = new QWidget(tab_widget);

    plain_text_edit = new QPlainTextEdit(currentTab);
    connect(plain_text_edit, SIGNAL (textChanged()), this, SLOT (changedHostTab()));
    plain_text_edit->move(5, 40);
    plain_text_edit->setFixedWidth(400);
    plain_text_edit->setFixedHeight(300);

    pattern_text_edit = new QPlainTextEdit(currentTab);
    connect(pattern_text_edit, SIGNAL (textChanged()), this, SLOT (patternChanged()));
    pattern_text_edit->move(420, 40);
    pattern_text_edit->setFixedWidth(400);
    pattern_text_edit->setFixedHeight(300);
    pattern_text_edit->hide();

    is_pattern_checkbox = new QCheckBox(currentTab);
    is_pattern_checkbox->setText("Use pattern");
    connect(is_pattern_checkbox, SIGNAL (stateChanged(int)), this, SLOT (patternCheckboxChanged(int)));
    is_pattern_checkbox->move(5, 10);

    apply_button = new QPushButton(currentTab);
    apply_button->setText("Set this hosts");
    apply_button->move(5, 360);
    connect(apply_button, SIGNAL (pressed()), this, SLOT (setCurrentHosts()));

    tab_widget->addTab(currentTab, name);
}


void TabOfHosts::setCurrentHosts()
{

    QFile file(hosts_file_path);
    file.open(QIODevice::QIODevice::WriteOnly | QIODevice::Truncate);
    file.close();
    if (file.open(QIODevice::QIODevice::ReadWrite)) {

        QTextStream stream(&file);
        QString hosts_text;

        if (is_pattern_checkbox->isChecked()) {
            parsePattern();
            hosts_text = plain_text_edit->toPlainText();
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
    emit setActiveHostTab();
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

void TabOfHosts::hidePattern()
{
    pattern_text_edit->hide();
    plain_text_edit->setReadOnly(false);
    is_pattern_checkbox->setChecked(false);
}


void TabOfHosts::patternCheckboxChanged(int i)
{
    if (is_pattern_checkbox->isChecked()) {
        showPattern();
        parsePattern();
    } else {
        hidePattern();
    }
}

void TabOfHosts::patternChanged()
{
    pattern_parser->setText(pattern_text_edit->toPlainText());
    pattern_variables = pattern_parser->getVariables();
    changedHostTab();
    showPatternElements();
    parsePattern();
}

void TabOfHosts::showPatternElements()
{
    for (int i = 0; i < pattern_variables_edit.size(); ++i) {
           QLineEdit* var = pattern_variables_edit.at(i);
           pattern_variables_edit.removeAt(i);
           delete var;
           QLabel* label = pattern_labels.at(i);
           pattern_labels.removeAt(i);
           delete label;
    }

    int position = 0;
    QListIterator<QString> iterator(pattern_variables);
    while (iterator.hasNext()) {
        QString variable_name = iterator.next();
        pattern_labels.append(new QLabel(currentTab));
        QLabel* add_label = pattern_labels.last();
        add_label->setText(variable_name);


        pattern_variables_edit.append(new QLineEdit(currentTab));
        QLineEdit* variable_text_edit = pattern_variables_edit.last();
        variable_text_edit->setObjectName(variable_name);
        variable_text_edit->setAccessibleName(variable_name);
        variable_text_edit->setFixedWidth(100);
        if (variables_map.contains(variable_name)) {
            variable_text_edit->setText(variables_map[variable_name]);
        }

        connect(variable_text_edit, SIGNAL (editingFinished()), this, SLOT (variableDataChanged()));
        //TODO: fix size
        variable_text_edit->move(170 + position * (5 + 150), 10);
        variable_text_edit->show();
        add_label->move(120 + position *  (5 + 150), 12);
        add_label->show();

        position++;
    }
}

QString TabOfHosts::getName()
{
    return name;
}

void TabOfHosts::variableDataChanged()
{
    QLineEdit* edit = qobject_cast<QLineEdit*>(sender());
    variables_map[edit->accessibleName()] = edit->text();
    parsePattern();
}


void TabOfHosts::parsePattern()
{
    pattern_parser -> setText(pattern_text_edit->toPlainText());
    plain_text_edit->setPlainText(pattern_parser->parseTemplate(variables_map));
}

void TabOfHosts::onChangeActiveTab()
{
    apply_button->setEnabled(true);
    if (name.compare("/etc/hosts") == 0) {
        loadFromFile(getFilePath());
    }
}

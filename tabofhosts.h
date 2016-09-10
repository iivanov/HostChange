#ifndef TABOFHOSTS_H
#define TABOFHOSTS_H

#include <QObject>
#include <QTabWidget>
#include <QPlainTextEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QTextStream>
#include <QMessageBox>
#include <QLineEdit>
#include <patternparser.h>
#include <QLabel>
#include <QCoreApplication>
#include <QEvent>


class TabOfHosts : public QObject
{
    Q_OBJECT
public:
    explicit TabOfHosts(QTabWidget * tab, QString tab_name, QObject *parent = 0);
    explicit TabOfHosts(QTabWidget * tab, QString tab_name, QString file_name, QObject *parent = 0);
    explicit TabOfHosts(TabOfHosts* for_copy_tab, QString tab_name, QObject* parent = 0);
    void initTab();
    void save();
    bool remove();
    QString getName();

signals:
    void setActiveHostTab();
public slots:
    void setCurrentHosts();
    void changedHostTab();
    void patternChanged();
    void patternCheckboxChanged(int i);
    void variableDataChanged();
    void onChangeActiveTab();
private:
    QTabWidget* tab_widget;
    QString name;
    QPlainTextEdit* plain_text_edit;
    QPlainTextEdit* pattern_text_edit;
    QCheckBox* is_pattern_checkbox;
    QPushButton* apply_button;
    QWidget *currentTab;
    PatternParser *pattern_parser;
    const QString hosts_file_path = "/etc/hosts";
    QString getFilePath();
    void showPattern();
    void hidePattern();
    QList<QString> pattern_variables;
    QList<QLineEdit *> pattern_variables_edit;
    QList<QLabel *> pattern_labels;
    QMap<QString,QString> variables_map;
    void showPatternElements();
    void parsePattern();
    void loadFromFile(QString file_name);
};

#endif // TABOFHOSTS_H

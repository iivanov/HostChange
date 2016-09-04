#ifndef TABOFHOSTS_H
#define TABOFHOSTS_H

#include <QObject>
#include <QTabWidget>
#include <QPlainTextEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QTextStream>
#include <QMessageBox>


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

signals:

public slots:
    void setCurrentHosts();
    void changedHostTab();
    void patternCheckboxChanged(int i);
private:
    QTabWidget* tab_widget;
    QString name;
    QPlainTextEdit* plain_text_edit;
    QPlainTextEdit* pattern_text_edit;
    QCheckBox* is_pattern_checkbox;
    QPushButton* apply_button;
    QWidget *currentTab;
    const QString hosts_file_path = "/var/www/testhost";
    QString getFilePath();
    void showPattern();
    void hidePatter();
};

#endif // TABOFHOSTS_H

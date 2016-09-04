#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tabofhosts.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addButton_pressed();

    void on_tabWidget_tabCloseRequested(int index);

    void on_pushButtonSave_clicked();

    void on_copyButton_clicked();

private:
    Ui::MainWindow *ui;
    QList<TabOfHosts *> tab_list;
    void loadTabs();
};

#endif // MAINWINDOW_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "asktabname.h"
#include <QMessageBox>
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tab_list.append(new TabOfHosts(ui->tabWidget, "/etc/hosts", "/etc/hosts"));
    connectEvent(tab_list.last());
    loadTabs();
}

void MainWindow::connectEvent(TabOfHosts* tab)
{
    connect(tab, SIGNAL (setActiveHostTab()), this, SLOT (onSetActiveHostTab()));

    QListIterator<TabOfHosts*> iterator(tab_list);
    while (iterator.hasNext()) {
        TabOfHosts* other_tab = iterator.next();
        if (other_tab != tab) {
            connect(tab, SIGNAL (setActiveHostTab()), other_tab, SLOT (onChangeActiveTab()));
            connect(other_tab, SIGNAL (setActiveHostTab()), tab, SLOT (onChangeActiveTab()));
        }
    }
}

void MainWindow::onSetActiveHostTab()
{
    TabOfHosts* tab = qobject_cast<TabOfHosts*>(sender());
    emit changedActiveTab(tab);
    //TODO: set current t
    ui->activeTabLabel->setText(tab->getName());
    qDebug() << "test";
}

void MainWindow::loadTabs()
{
    QDir dir("./");
    QFileInfoList dirContent = dir.entryInfoList(QStringList()
        << "*.hosts",
        QDir::Files | QDir::NoDotAndDotDot
    );

    for (int i = 0; i < dirContent.size(); ++i) {
           QFileInfo fileInfo = dirContent.at(i);
           QString file_name = fileInfo.fileName();
           file_name = file_name.mid(0, file_name.length() - 6);//5 = len of ".hosts"
           tab_list.append(new TabOfHosts(ui->tabWidget, file_name, fileInfo.filePath()));
           connectEvent(tab_list.last());

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_pressed()
{

    AskTabName* dialog = new AskTabName();
    dialog->exec();

    QString tab_name = dialog->getTabName();

    if (!tab_name.isEmpty()) {
        tab_list.append(new TabOfHosts(ui->tabWidget, tab_name));
        connectEvent(tab_list.last());
    }

    delete(dialog);

}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{

    if (index != 0) {
        if (tab_list.at(index)->remove()) {
            tab_list.removeAt(index);
            ui->tabWidget->removeTab(index);
        }
    } else {
        QMessageBox msgBox;
        msgBox.setText("Can not delete hosts tab.");
        msgBox.exec();
    }


}

void MainWindow::on_pushButtonSave_clicked()
{

    QListIterator<TabOfHosts *> iterator(tab_list);
    while (iterator.hasNext()) {
        TabOfHosts * tab = iterator.next();
        tab->save();
    }
    QMessageBox msgBox;
    msgBox.setText("Tabs was saved.");
    msgBox.exec();

}

void MainWindow::on_copyButton_clicked()
{
    AskTabName* dialog = new AskTabName();
    dialog->exec();

    QString tab_name = dialog->getTabName();

    if (!tab_name.isEmpty()) {
        TabOfHosts* current_tab = tab_list.at(ui->tabWidget->currentIndex());
        tab_list.append(new TabOfHosts(current_tab, tab_name));
        connectEvent(tab_list.last());
    }

    delete(dialog);
}

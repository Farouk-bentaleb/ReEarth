#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "centre.h"
#include "employe.h"
#include "client.h"
#include "centre.h"
#include "produit.h"
#include "smtp.h"
#include "num_deleguate.h"
#include "arduino.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include<QPalette>
#include <QColor>
#include<QDebug>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <qdebug.h>
#include <QPrinter>
#include <QPainter>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QCalendarWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QtWidgets/QMessageBox>
#include <QFileDialog>
#include <QPrintDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //centre
    void on_home_clicked();

    void on_main_slct_clicked();

    void on_quizz_clicked();

    void on_contacts_clicked();

    void on_chatbox_clicked();

    void on_about_clicked();

    void on_gestion_employes_clicked();

    void on_gestion_client_clicked();

    void on_gestion_produit_clicked();

    void on_gestion_centre_clicked();

    void on_back_2_clicked();

    void on_back_clicked();

    void on_back_3_clicked();

    void on_back_4_clicked();

    void on_pushButton_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_sort_clicked();

    void on_export_2_clicked();

    void on_pb_stats_clicked();

    void on_search_textChanged();

    void on_pushButton_modifier_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_11_clicked();

    void on_calendrier_clicked();

    void addTask();
    void removeTask();
    void completeTask();
    void updateTaskDetails(QListWidgetItem *item);
    void saveTasks();
    void loadTasks();
    void exittasks();
    void exitApplication();

    void on_todo_clicked();
    void handleDateSelection(const QDate &date);

    //client
    void on_ajouterclient_clicked();

    void on_pb_modifierclient_clicked();

    void on_pbsuppclient_clicked();

    void on_trierclient_clicked();

    void on_pdf_clicked();

    void loadHistoryToTableView();

    void on_statistiquepartype_clicked();

    void sendMail();

    void mailSent(QString);

    void browse();

    void on_pushButton_22_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_19_clicked();

    void on_rechercherclient_clicked();

    //produit
    void on_pushButton_OK_clicked();

    void on_UPDATE_clicked();

    void on_tab_produit_activated(const QModelIndex &index);

    void on_SELL_clicked();

    void createChart();

    void performFilteredSearch();

    void on_SEARCH1_textChanged();

    void on_EXPORT_clicked();

    void on_comboBox_TRI_currentIndexChanged();

    void on_animation_clicked();

    void on_animation_2_clicked();

    void on_animation_3_clicked();

    void on_pushButton_VALIDER_clicked();

    void on_pushButton_VALIDER_2_clicked();

    void on_pushButton_VALIDER_3_clicked();

    void on_stats_clicked();

    void on_pushButton_30_clicked();

    void on_SEARCH_textChanged();

    void on_supp_clicked();
    //Employe
    void on_tableView_activated(const QModelIndex &index);

    void on_add_main_clicked();

    void on_refresh_main_clicked();

    void on_Add_clicked();

    void on_sort_main_clicked();

    void on_Export_main_clicked();

    void on_modify_clicked();

    void on_Delete_modf_clicked();

    void on_search_for_main_textChanged();

    void on_SIGNIN_clicked();

    void recordTime(const QString &filename, const QString &event, const QString &userName);

    void on_disconnect_clicked();

    QString generate_Code();

    void on_chatbox_2_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_33_clicked();

    void on_reset_clicked();

    void on_next_clicked();

    void on_next_3_clicked();

    void on_next_2_clicked();

    void on_confirm_clicked();

    void set_Code(QString val){
        Code=val;
    }
    QString get_Code(){
        return Code;
    }

    void on_back_5_clicked();

    void on_back_6_clicked();

    void on_back_7_clicked();

    void update_label();

    void on_back_8_clicked();

    void on_SIGNUP_clicked();

private:
    Ui::MainWindow *ui;

    ////centre
    centre c;
    QListWidget *taskListWidget;
    QLineEdit *taskLineEdit;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *completeButton;
    QPushButton *exit;
    QDateTimeEdit *dueDateEdit;
    QCalendarWidget *calendarWidget;
    QLabel *selectedDateLabel;
    QPushButton *exitButton;
    void setupUi();

    ////client
    Client Cdupe;
    QSqlTableModel *model;
    QStringList files;

    ////produit
    QPropertyAnimation *animation;
    QPropertyAnimation *animation_2;
    QPropertyAnimation *animation_3;
    Produit P;
    int ETOILES=0;
    int score=0;
    int ANSWERS=0;
    int nb_fois_dereponses=0;
    int random_quizz;
    ////Employe
    employe EMP;
    QByteArray data;
    arduino A;
    QString Code;
};
#endif // MAINWINDOW_H

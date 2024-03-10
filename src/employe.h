#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QSortFilterProxyModel>
#include <QDebug>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QTextCursor>
#include <QFileDialog>
#include <QDir>
class employe
{
private:
    int CIN;
    QString Nom,Prenom;
    float Salaire;
    QDate Date;
    QString Depart,Poste;
    QString login,password;
    QString card_uid;
public:
    //contructors
    employe();
    employe(int,QString,QString,float,QDate,QString,QString,QString,QString,QString);
    //Getters
    QString getNom();
    QString getPrenom();
    QDate getDate();
    QString getDepart();
    QString getPoste();
    QString getlogin();
    QString getpassword();
    int getCIN();
    float getSalaire();
    //setters
    void setCIN(int CIN1);
    void setNom(QString Nom1);
    void setPrenom(QString Prenom1);
    void setDate(QDate Date1);
    void setDepart(QString Depart1);
    void setPoste(QString Poste1);
    void setSalaire(float Salaire1);
    void setlogin(QString login1);
    void setpassword(QString password1);
    //methods
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int CIN);
    bool modifier();
    QSqlQueryModel * trier(QString);
    QSqlQueryModel * rechercher(QString);
    bool search(QString,QString);

};

#endif // EMPLOYE_H

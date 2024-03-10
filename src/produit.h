#ifndef PRODUIT_H
#define PRODUIT_H
#include <QString>
#include <QSqlQueryModel>

class Produit
{
public:
    //constructeurs
    Produit();
    Produit(QString,QString,QString,int,int);
    //getters
    QString getref();
    QString gettype();
    QString getetat();
    int getqt();
    int getprix();
    //setters
    void setref(QString);
    void settype(QString);
    void setetat(QString);
    void setqt(int);
    void setprix(int);
    //QString getnb_recy(){return nb_recy;}//QString getetat(){return etat;}//QString getprix(){return prix;}
    //void setnb_recy(QString a){nb_recy=a;}//void setetat(QString d){etat=d;} //void setprix(float c){prix=c;}

    //Fonctionnalités de base relatives a l'entité produits
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier();
    void trierEtAfficher(const QString& reference, QSqlQueryModel& model);
    QSqlQueryModel *trier_ref();
    QSqlQueryModel *trier_type();
    QSqlQueryModel *trier_etat();
    QSqlQueryModel *trier_quantite();
    QSqlQueryModel *trier_prix();
    //arduino////////////////////////////////////////////////////////////////////////////////////////
    bool rfidExists(QString uid);
    QString rfidName(QString uid);

 private:
    QString ref,type,etat;
    int qt,prix;
};

#endif // PRODUIT_H

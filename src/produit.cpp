#include "produit.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
Produit::Produit()
{
ref=" ";
type=" ";
etat=" ";
qt=0;
prix=0;
}
Produit::Produit(QString ref,QString type,QString etat,int qt,int prix)
{
    this->ref=ref;this->type=type;this->etat=etat;
    this->qt=qt;this->prix=prix;
}
//getters
QString Produit::getref(){return ref;}
QString Produit::gettype(){return type;}
QString Produit::getetat(){return etat;}
int Produit::getqt(){return qt;}
int Produit::getprix(){return prix;}

//setters
void Produit::setref(QString ref){this->ref=ref;}
void Produit::settype(QString type){this->type=type;}
void Produit::setetat(QString etat){this->etat=etat;}
void Produit::setqt(int qt){this->qt=qt;}
void Produit::setprix(int prix){this->prix=prix;}

bool Produit:: ajouter(){
    QSqlQuery query;
   QString qt_string=QString::number(qt);
   QString prix_string=QString::number(prix);
         query.prepare("INSERT INTO produit (ref, type, etat, qt, prix) "
                       "VALUES (:ref, :type,:etat,:qt,:prix)");
         query.bindValue(":ref", ref);
         query.bindValue(":type",type);
         query.bindValue(":etat",etat);
         query.bindValue(":qt",qt_string);
         query.bindValue(":prix",prix_string);
         return query.exec();
}
bool Produit::supprimer(QString ref){
    QSqlQuery query;
        query.prepare("DELETE FROM produit WHERE ref = :ref ");
        query.bindValue(":ref", ref);
        return query.exec();
}
bool Produit::modifier(){
    QSqlQuery update_query;
     QString qt_string=QString::number(qt);
     QString prix_string=QString::number(prix);
    update_query.prepare("UPDATE produit SET ref=:ref,type=:type,etat=:etat,qt =:qt,prix=:prix WHERE ref =:ref");
    update_query.bindValue(":ref",ref);
    update_query.bindValue(":type",type);
    update_query.bindValue(":etat",etat);
    update_query.bindValue(":qt",qt_string);
    update_query.bindValue(":prix",prix_string);
    return update_query.exec();
}


QSqlQueryModel * Produit:: afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();
        model->setQuery("SELECT * FROM produit");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ref"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));

    return model;
}
void Produit::trierEtAfficher(const QString& reference, QSqlQueryModel& model) {
    QSqlQuery query;
    query.prepare("SELECT * FROM produit WHERE ref = :ref");
    query.bindValue(":ref", reference);
    query.exec();
    model.setQuery(query);
}
QSqlQueryModel *Produit::trier_ref() // m sghir lel kbir
 {
     QSqlQuery * q = new  QSqlQuery ();
            QSqlQueryModel * model = new  QSqlQueryModel ();
            q->prepare("SELECT * FROM PRODUIT order by ref ASC");
            q->exec();
            model->setQuery(*q);
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETAT"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
            return model;
}
QSqlQueryModel *Produit::trier_type() // m sghir lel kbir
 {
     QSqlQuery * q = new  QSqlQuery ();
            QSqlQueryModel * model = new  QSqlQueryModel ();
            q->prepare("SELECT * FROM PRODUIT order by TYPE ASC");
            q->exec();
            model->setQuery(*q);
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETAT"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
            return model;
}
QSqlQueryModel *Produit::trier_etat() // m sghir lel kbir
 {
     QSqlQuery * q = new  QSqlQuery ();
            QSqlQueryModel * model = new  QSqlQueryModel ();
            q->prepare("SELECT * FROM PRODUIT order by ETAT ASC");
            q->exec();
            model->setQuery(*q);
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETAT"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
            return model;
}
QSqlQueryModel *Produit::trier_quantite() // m sghir lel kbir
 {
     QSqlQuery * q = new  QSqlQuery ();
            QSqlQueryModel * model = new  QSqlQueryModel ();
            q->prepare("SELECT * FROM PRODUIT order by QT DESC");
            q->exec();
            model->setQuery(*q);
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETAT"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
            return model;
}
QSqlQueryModel *Produit::trier_prix() // m sghir lel kbir
 {
     QSqlQuery * q = new  QSqlQuery ();
            QSqlQueryModel * model = new  QSqlQueryModel ();
            q->prepare("SELECT * FROM PRODUIT order by PRIX DESC");
            q->exec();
            model->setQuery(*q);
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETAT"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
            return model;
}
bool Produit::rfidExists(QString uid)
{
    QSqlQuery query;
        query.prepare("SELECT RFID FROM PRODUIT WHERE RFID = ?");
        query.addBindValue(uid);
        if (query.exec() && query.next()) {
            // If a row is returned, the uid exists in the database
            return true;
        }
    // If no row is returned, the uid does not exist in the database
    return false;
}

QString Produit::rfidName(QString uid)
{
    QSqlQuery query;
        query.prepare("SELECT ref FROM PRODUIT WHERE RFID = ?");
        query.addBindValue(uid);
        if (query.exec() && query.next()) {
            // If a row is returned, extract the value of the NOM attribute
            return query.value(0).toString();
        }
        // If no row is returned, return an empty string to indicate failure
        return "";
}

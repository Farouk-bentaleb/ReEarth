#include "centre.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QSqlQueryModel>
centre::centre (int  identifiant, QString nom,QString lieu,int surface)
{
this->identifiant=identifiant;this->nom=nom;this->surface=surface;this->lieu=lieu;
}
bool centre::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(identifiant);
     QString surface_string=QString::number(surface);



    query.prepare("INSERT INTO CENTRE (ID, NOM, surface,lieu) VALUES (:ID, :NOM, :surface,:lieu)");
    query.bindValue(":ID", id_string);
    query.bindValue(":NOM", nom);
    query.bindValue(":surface",surface_string);
    query.bindValue(":lieu",lieu);
    return query.exec();
}
bool centre::supprimer(int identifiant) {
    QSqlQuery query;
    query.prepare("DELETE FROM CENTRE WHERE ID=:ID");
    query.bindValue(":ID", identifiant);

    if (query.exec() && query.numRowsAffected() > 0) {
        // La requête a réussi et au moins un enregistrement a été supprimé
        return true;
    } else {
        // Aucun enregistrement correspondant n'a été supprimé
        return false;
    }
}



QSqlQueryModel* centre:: afficher(){
 QSqlQueryModel* model=new QSqlQueryModel();
       model->setQuery("SELECT* FROM CENTRE");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Lieu"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("Surface"));

    return model;
}

bool centre::modifier(int){
    QSqlQuery query;
    query.prepare("UPDATE CENTRE SET NOM=:NOM, SURFACE=:SURFACE, LIEU=:LIEU WHERE ID=:ID");
    query.bindValue(":ID", identifiant);
    query.bindValue(":NOM", nom);
    query.bindValue(":SURFACE",surface);
    query.bindValue(":LIEU",lieu);


    return query.exec();
}

QSqlQueryModel *centre::trier(QString x)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    qDebug()<<x<<endl;
    if(x=="ID"){
        model->setQuery("select ID, NOM, surface,lieu from CENTRE order by ID");
        QMessageBox::information(nullptr, QObject::tr("Sort Done"),QObject::tr("Sorted By CIN\n"),QMessageBox::Ok);
    }
    else if(x=="Nom"){
        model->setQuery("select ID, NOM, surface,lieu from CENTRE order by Nom");
        QMessageBox::information(nullptr, QObject::tr("Sort Done"),QObject::tr("Sorted By Nom\n"),QMessageBox::Ok);
    }
    else if (x=="Lieu"){
        model->setQuery("select ID, NOM, surface,lieu from CENTRE order by Lieu");
        QMessageBox::information(nullptr, QObject::tr("Sort Done"),QObject::tr("Sorted By Lieu\n"),QMessageBox::Ok);
    }
    else if (x=="Surface"){
        model->setQuery("select ID, NOM, surface,lieu from CENTRE order by Surface");
        QMessageBox::information(nullptr, QObject::tr("Sort Done"),QObject::tr("Sorted By Surfcae\n"),QMessageBox::Ok);
    }
    return model;
}

QSqlQueryModel* centre::rechercher(QString a)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    qDebug()<<a<<endl;
    model->setQuery("select * from CENTRE where (Nom LIKE lower('%"+a+"%') or Lieu LIKE lower('%"+a+"%') or (Nom LIKE upper('%"+a+"%') or Lieu LIKE upper('%"+a+"%')))");
    return model;
}


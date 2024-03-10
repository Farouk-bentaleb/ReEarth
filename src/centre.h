#ifndef CENTRE_H
#define CENTRE_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>
class centre
{
    int identifiant,surface;
   QString nom,lieu;

public:
   centre(){}
   centre(int,QString,QString,int);
    int  get_identifinat(){return identifiant;}
   QString get_nom(){return nom;}
   QString get_lieu(){return lieu;}
    int  get_surface(){return surface;}
   void setidentifiant (int n){identifiant =n;}
   void setnom (QString n){nom=n;}
   void setlieu (QString n){lieu=n;}
   void setsurface (int n){surface=n;}
   bool ajouter();
   QSqlQueryModel* afficher();
   bool supprimer(int );
   bool modifier(int);
   QSqlQueryModel* trier(QString);
   QSqlQueryModel* rechercher(QString a);
};

#endif // ZONE_H

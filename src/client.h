#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include<QSqlQueryModel>
#include<QDate>

class Client
{
public:
    Client();
    Client(int,QString,QString,QString,QString,QString,float,int,int,QDate );
      Client(QString,QString,QString,QString,QString,QString,float,int,int,QDate );
    int getid();
    QString getnom();
    QString getprenom ();
    QString gettypec ();
    QString getadresse ();
    float getrevenus ();
    QString getmail();
    int getRIB ();
    int getREF ();
    QDate getdate_payement();





    void setid (int);
    void setnom (QString);
    void setprenom(QString);
    void settypec(QString);
    void setadresse (QString);
    void setrevenus (float);
    void setmail (QString);
    void setRIB(int);
    void setREF(int);
    void setdate_payement(QDate);

 bool ajouterclient();
 QSqlQueryModel* afficher();
 bool supprimer(int);
bool modifierclient(int,QString,QString,QString,QString,QString,float,int,int,QDate);
//bool modifierclient(QString,QString,QString,QString,QString,QString,float,int,int,QDate);
QSqlQueryModel *  rechercher(int);
QSqlQueryModel * trier();
QSqlQueryModel * afficher_choix_client(QString choix);
QSqlQueryModel * afficher_REF(QString ch);
QSqlQueryModel * afficher_ADRESSE(QString ch);
QSqlQueryModel * afficher_TYPEC(QString ch);
QSqlQueryModel * afficher_DATE_PAYEMENT(QString ch);
QSqlQueryModel * afficher_MAIL(QString ch);
QSqlQueryModel * afficher_RIB(QString ch);
QSqlQueryModel * afficher_NOM(QString ch);
QSqlQueryModel * afficher_PRENOM(QString ch);
QSqlQueryModel * afficher_REVENUS(QString ch);
QSqlQueryModel * afficher_ID(QString ch);
//QSqlQueryModel * stat();
QStringList getSearchHistory();
// Fonction pour ajouter une recherche à l'historique
//void addSearchToHistory(const QString &searchQuery);
void addToHistory(QString action, Client c);
Client getClientById(int id);
bool  rfidExists(QString uid);
QString rfidName(QString uid);







private:
    int id, RIB , REF;
    float revenus ;
    QString nom , prenom , adresse , typec , mail,id1 ;
    QDate date_payement ;
};
#endif // CLIENT_H

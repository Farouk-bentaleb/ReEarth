#include "client.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QFile>
Client::Client()
{
  id=0 ;
  nom="";
  prenom="" ;
  typec="" ;
  adresse="";
  mail="";
  revenus=0;
  RIB=0;
  REF=0;
}
Client::Client(int id ,QString nom , QString prenom,QString adresse ,QString typec ,QString mail , float revenus, int RIB , int REF , QDate date_payement)
{
  this->id=id ;
  this->nom=nom;
  this->prenom=prenom ;
  this->typec=typec;
  this->adresse=adresse;
  this->mail=mail;
  this->revenus=revenus;
  this->RIB=RIB;
  this->REF=REF;
  this->date_payement=date_payement;
    QFile historyFile("historique.txt");
    if (historyFile.open(QIODevice::Append |QIODevice::Text))
            historyFile.close();

}


Client::Client(QString id ,QString nom , QString prenom,QString adresse ,QString typec ,QString mail , float revenus, int RIB , int REF , QDate date_payement)
{
  id1=id ;
  this->nom=nom;
  this->prenom=prenom ;
  this->typec=typec;
  this->adresse=adresse;
  this->mail=mail;
  this->revenus=revenus;
  this->RIB=RIB;
  this->REF=REF;
  this->date_payement=date_payement;
  QFile historyFile("historique.txt");
  if (historyFile.open(QIODevice::Append |QIODevice::Text))
          historyFile.close();

}
int Client::getid (){return id;}
QString Client::getnom(){return nom ;}
QString Client :: getprenom (){return prenom ;}
QString Client :: gettypec (){return typec ;}
QString Client :: getadresse (){return adresse;}
QString Client :: getmail (){return mail;}
float Client :: getrevenus (){return revenus ;}
int Client :: getRIB (){return RIB ;}
int Client :: getREF(){return REF ;}
QDate Client ::getdate_payement(){return date_payement;}

void Client::setid (int id){this->id=id;}
void Client :: setnom (QString nom ){this->nom=nom;}
void Client :: setprenom(QString prenom ){this->prenom=prenom;}
void Client :: settypec(QString typec){this->typec=typec;}
void Client :: setadresse(QString adresse){this->adresse=adresse;}
void Client :: setmail (QString mail){this->mail=mail;}
void Client :: setrevenus(float revenus){this->revenus=revenus;}
void Client :: setRIB (int RIB){this->RIB=RIB;}
void Client :: setREF (int REF){this->REF=REF;}
void Client :: setdate_payement(QDate date_payement){this->date_payement=date_payement;}





bool Client ::ajouterclient()
{


    QSqlQuery query ;
    QString id_string=QString:: number(id);
    QString revenus_string=QString:: number(revenus);
    QString REF_string=QString:: number(REF);
    QString RIB_string=QString:: number(RIB);
    query.prepare("INSERT INTO CLIENT(nom, prenom, id, typec, adresse, mail, revenus, RIB, REF, date_payement)"
                  "VALUES (:nom, :prenom, :id, :typec, :adresse, :mail, :revenus, :RIB, :REF, :date_payement)");
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":id",id_string);
    query.bindValue(":typec", typec);
    query.bindValue(":adresse", adresse);
    query.bindValue(":mail",mail);
    query.bindValue(":revenus",revenus_string);
    query.bindValue(":RIB",RIB_string);
    query.bindValue(":REF",REF_string);
    query.bindValue(":date_payement",date_payement);

    return query.exec();

}



QSqlQueryModel* Client::afficher()
{

    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT* FROM CLIENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typec"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("revenus"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("RIB"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("REF"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("date_payement"));

    return model ;

}
bool Client::supprimer(int id)
{
    QSqlQuery query ;
     Client modifiedClient = getClientById(id);

    QString res=QString::number(id);


    query.prepare(" Delete from CLIENT where ID= :id");
    query.bindValue(":id",res);

    addToHistory("SUPPRESSION",modifiedClient);

    return query.exec();

}





/*bool Client::modifierclient(QString id,QString nom ,QString prenom ,QString adresse ,QString  mail ,QString typec ,float revenus ,int ref,int rib,QDate date_payement){

     QSqlQuery query ;
     QString revenus_string=QString::number(revenus);
     QString ref_string=QString::number(ref);
     QString rib_string=QString::number(rib);

    query.prepare("UPDATE CLIENT SET nom = :nom, prenom = :prenom, typec = :typec, adresse = :adresse, mail = :mail, revenus = :revenus, rib = :rib, ref = :ref, date_payement = :date_payement WHERE id = :id");
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":id",id );
    query.bindValue(":typec", typec);
    query.bindValue(":adresse", adresse);
    query.bindValue(":mail",mail);
    query.bindValue(":revenus",revenus_string);
    query.bindValue(":rib",rib_string);
    query.bindValue(":ref",ref_string);
    query.bindValue(":date_payement",date_payement);
    Client modifiedClient = getClientById(RIB);
    addToHistory("modification",modifiedClient);

   return query.exec();
      }*/
bool Client::modifierclient(int id,QString nom ,QString prenom ,QString adresse ,QString  mail ,QString typec ,float revenus ,int ref,int rib,QDate date_payement){

     QSqlQuery query ;
     //Client modifiedClient = getClientById(id);
     Client modifiedClient = getClientById(id);
     QString revenus_string=QString::number(revenus);
     QString ref_string=QString::number(ref);
     QString rib_string=QString::number(rib);
     QString id_string=QString::number(id);

    query.prepare("UPDATE CLIENT SET  nom = :nom, prenom = :prenom, id = :id, typec = :typec, adresse = :adresse, mail = :mail, revenus = :revenus, rib = :rib, ref = :ref, date_payement = :date_payement WHERE id = :id");

    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":id",id_string );
    query.bindValue(":typec", typec);
    query.bindValue(":adresse", adresse);
    query.bindValue(":mail",mail);
    query.bindValue(":revenus",revenus_string);
    query.bindValue(":rib",rib_string);
    query.bindValue(":ref",ref_string);
    query.bindValue(":date_payement",date_payement);

    addToHistory("modification",modifiedClient);

   return query.exec();
      }


/*bool Client:: modifierclient(int id,QString nouvnom ,QString nouvprenom ,QString nouvadresse ,QString  nouvmail ,QString nouvtypec ,float nouvrevenus ,int nouvref,int nouvrib,QDate nouvdate_payement)
{

     QSqlQuery query;

     Client modifiedClient = getClientById(id);
     QString revenus_string=QString::number(revenus);
     QString REF_string=QString::number(REF);
      QString RIB_string=QString::number(RIB);
     QString id_string=QString::number(id);



     query.prepare("UPDATE CLIENTS SET nom = :nouvnom, prenom = :nouvprenom,  typec = :nouvtypec, adresse = :nouvadresse, mail = :nouvmail, revenus = :nouvrevenus, rib = :nouvrib, ref = :nouvref, date_payement = :nouvdate_payement WHERE id = :id_string");
     query.bindValue(":id",id_string );
     query.bindValue(":nouvnom",nouvnom);
     query.bindValue(":nouvprenom",nouvprenom);

     query.bindValue(":nouvtypec", nouvtypec);
     query.bindValue(":nouvadresse", nouvadresse);
     query.bindValue(":nouvmail",nouvmail);
     query.bindValue(":nouvrevenus",nouvrevenus);
     query.bindValue(":nouvrib",nouvrib);
     query.bindValue(":nouvref",nouvref);
     query.bindValue(":nouvdate_payement",nouvdate_payement);

     addToHistory("modification",modifiedClient);





        return query.exec();
}*/





QSqlQueryModel* Client::afficher_choix_client(QString choix)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query;

    if (choix == "NOM")
    {
        query = "SELECT * FROM CLIENT ORDER BY NOM;";
    }
    else if (choix == "PRENOM")
    {
        query = "SELECT * FROM CLIENT ORDER BY PRENOM;";
    }
    else if (choix == "ID")
    {
        query = "SELECT * FROM CLIENT ORDER BY ID;";
    }
    else if (choix == "TYPEC")
    {
        query = "SELECT * FROM CLIENT ORDER BY TYPEC;";
    }
    else if (choix == "ADRESSE")
    {
        query = "SELECT * FROM CLIENT ORDER BY ADRESSE;";
    }
    else if (choix == "MAIL")
    {
        query = "SELECT * FROM CLIENT ORDER BY MAIL;";
    }
    else if (choix == "REVENUS")
    {
        query = "SELECT * FROM CLIENT ORDER BY REVENUS;";
    }
    else if (choix == "RIB")
    {
        query = "SELECT * FROM CLIENT ORDER BY RIB;";
    }
    else if (choix == "REF")
    {
        query = "SELECT * FROM CLIENT ORDER BY REF;";
    }
    else if (choix == "DATE_PAYEMENET")
    {
        query = "SELECT * FROM CLIENT ORDER BY DATE_PAYEMENT;";
    }
    else
    {
        // Gérer le cas par défaut ici (par exemple, trier par CIN ou toute autre logique)
        query = "SELECT * FROM CLIENT;";
    }

    model->setQuery(query);

    // Assurez-vous d'adapter les noms des colonnes ci-dessous à votre schéma de base de données

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typec"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("revenus"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("RIB"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("REF"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("date_payement"));

    return model;
}
//******************************affichage recherche*****************************************************
QSqlQueryModel * Client::afficher_NOM(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT where NOM= '"+ch+"' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typec"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("revenus"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("RIB"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("REF"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("date_payement"));



    return model;
}
QSqlQueryModel *Client::afficher_PRENOM(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT where PRENOM= '"+ch+"' ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typec"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("revenus"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("RIB"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("REF"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("date_payement"));


    return model;
}
QSqlQueryModel *Client::afficher_ID(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT where ID= '"+ch+"' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typec"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("revenus"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("RIB"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("REF"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("date_payement"));
    return model;
}

QSqlQueryModel *Client::afficher_TYPEC(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT where TYPEC= '"+ch+"' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typec"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("revenus"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("RIB"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("REF"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("date_payement"));
    return model;
}
QSqlQueryModel *Client::afficher_ADRESSE(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT where ADRESSE= '"+ch+"' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN_CLIENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_CLIENT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_CLIENT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO_CLIENT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("MAIL_CLIENT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ADRESSE_CLIENT"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("VILLE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("CODE_POSTAL_CLIENT"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    return model;
}
QSqlQueryModel *Client::afficher_MAIL(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT where MAIL= '"+ch+"' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typec"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("revenus"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("RIB"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("REF"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("date_payement"));
    return model;
}
QSqlQueryModel *Client::afficher_REVENUS(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT where REVENUS= '"+ch+"' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typec"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("revenus"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("RIB"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("REF"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("date_payement"));
    return model;
}
QSqlQueryModel *Client::afficher_RIB(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT where RIB= '"+ch+"' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typec"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("revenus"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("RIB"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("REF"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("date_payement"));
    return model;
}
QSqlQueryModel *Client::afficher_REF(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT where REF= '"+ch+"' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typec"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("revenus"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("RIB"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("REF"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("date_payement"));
    return model;
}
QSqlQueryModel *Client::afficher_DATE_PAYEMENT(QString ch)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENT where DATE_PAYEMENT= '"+ch+"' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("typec"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("revenus"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("RIB"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("REF"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("date_payement"));
    return model;
}
void Client::addToHistory( QString action,  Client c)
{
    QFile historyFile("historique.txt");

        if (historyFile.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&historyFile);

            // Create a new entry
            QString entry = QString("%1 - Date: %2\n")
                                .arg(action)
                                .arg(QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss"));

            // Concatenate the modification and suppression entries
            entry += QString("ID: %1, Nom: %2, Prenom: %3, adresse: %4, typec: %5, mail: %6, revenus: %7, RIB: %8, REF: %9 ,date_payement: %10")
                         .arg(c.getid())
                         .arg(c.getnom())
                         .arg(c.getprenom())
                         .arg(c.getadresse())
                         .arg(c.gettypec())
                         .arg(c.getmail())
                         .arg(c.getrevenus())
                         .arg(c.getRIB())
                         .arg(c.getREF())
                         .arg(c.getdate_payement().toString("dd/MM/yyyy"))  // Adjust attributes accordingly

                         ;


            // Write the entry to the file
            out << entry << endl;

            historyFile.close();
        }
}

/*Client Client::getClientById(int RIB)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT WHERE RIB = :RIB");
    query.bindValue(":RIB", RIB );

    if (query.exec() && query.next()) {
         QString selectedTypec = query.value("typec").toString();
        return Client(
                    query.value("id ").toString(),
                    query.value("nom").toString(),
                    query.value("prenom").toString(),
                    query.value("adresse").toString(),
                    selectedTypec,
                    query.value("mail").toString(),
                    query.value("revenus").toInt(),
                    query.value("RIB").toInt(),
                    query.value("REF").toInt(),
                     query.value("date_payements").toDate()






                       );
    }}*/

Client Client::getClientById(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT WHERE id = :id");
    query.bindValue(":id", id );

    if (query.exec() && query.next()) {
         QString selectedTypec = query.value("typec").toString();
        return Client(
                    query.value("id").toInt(),
                    query.value("nom").toString(),
                    query.value("prenom").toString(),
                    query.value("adresse").toString(),
                    selectedTypec,
                    query.value("mail").toString(),
                    query.value("revenus").toInt(),
                    query.value("RIB").toInt(),
                    query.value("REF").toInt(),
                    query.value("date_payement").toDate()






                       );
    }}

bool Client ::rfidExists(QString uid)
{
    QSqlQuery query;
        query.prepare("SELECT RFID FROM CLIENT WHERE RFID = ?");
        query.addBindValue(uid);
        if (query.exec() && query.next()) {
            // If a row is returned, the uid exists in the database
            return true;}
    // If no row is returned, the uid does not exist in the database
    return false;
}

QString Client::rfidName(QString uid)
{
    QSqlQuery query;
        query.prepare("SELECT NOM FROM  CLIENT WHERE RFID = ?");
        query.addBindValue(uid);
        if (query.exec() && query.next()) {
            // If a row is returned, extract the value of the NOM attribute
            return query.value(0).toString();
        }
        // If no row is returned, return an empty string to indicate failure
        return "";

// Return an invalid client if not found
//return Client;
}

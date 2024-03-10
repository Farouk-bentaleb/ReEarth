#include "employe.h"
QString employe::getNom(){return Nom;}
QString employe::getPrenom(){return Prenom;}
QDate employe::getDate(){return Date;}
QString employe::getDepart(){return Depart;}
QString employe::getPoste(){return Poste;}
int employe::getCIN(){return CIN;}
float employe::getSalaire(){return Salaire;}
//setters
void employe::setCIN(int CIN1){CIN=CIN1;}
void employe::setNom(QString Nom1){Nom=Nom1;}
void employe::setPrenom(QString Prenom1){Prenom=Prenom1;}
void employe::setDate(QDate Date1){Date=Date1;}
void employe::setDepart(QString Depart1){Depart=Depart1;}
void employe::setPoste(QString Poste1){Poste=Poste1;}
void employe::setSalaire(float Salaire1){Salaire=Salaire1;}

employe::employe()
{
    Nom="";
    Prenom="";
    CIN=0;
}
employe::employe(int CIN1,QString Nom1,QString Prenom1,float salaire1,QDate date1,QString poste1,QString depart1,QString login1,QString password1,QString uid){
    CIN=CIN1;
    Nom=Nom1;
    Prenom=Prenom1;
    Salaire=salaire1;
    Date=date1;
    Poste=poste1;
    Depart=depart1;
    login=login1;
    password=password1;
    card_uid=uid;
}
bool employe::ajouter(){
    QSqlQuery query;
    QString res=QString::number(CIN);
    QString res2=QString::number(Salaire);
    query.prepare("INSERT INTO EMPLOYE (CIN,Nom,Prenom,Datenaiss,salaire,poste,depart,login,password,CARD_UID)"
                  "VALUES(:CIN,:Nom,:Prenom,:Datenaiss,:salaire,:poste,:depart,:login,:password,:CARD_UID)");
    query.bindValue(":CIN",res);
    query.bindValue(":Nom",Nom);
    query.bindValue(":Prenom",Prenom);
    query.bindValue(":Datenaiss",Date);
    query.bindValue(":salaire",res2);
    query.bindValue(":poste",Poste);
    query.bindValue(":depart",Depart);
    query.bindValue(":login",res);
    query.bindValue(":password","0000");
    query.bindValue(":CARD_UID",card_uid);
    return query.exec();
}
bool employe::supprimer(int CIN){
    QSqlQuery query;
    QString res=QString::number(CIN);
    query.prepare("DELETE FROM EMPLOYE WHERE CIN=:CIN");
    query.bindValue(":CIN",res);
    return query.exec();
}
bool employe::modifier(){
    QSqlQuery query;
    QString res=QString::number(CIN);
    QString res2=QString::number(Salaire);
    query.prepare("UPDATE EMPLOYE SET NOM=:NOM, PRENOM=:PRENOM,DATENAISS=:DATENAISS,SALAIRE=:SALAIRE,POSTE=:POSTE,DEPART=:DEPART,LOGIN=:LOGIN,PASSWORD=:PASSWORD,CARD_UID=:CARD_UID WHERE CIN=:CIN");
    query.bindValue(":CIN",CIN);
    query.bindValue(":NOM",Nom);
    query.bindValue(":PRENOM",Prenom);
    query.bindValue(":DATENAISS",Date);
    query.bindValue(":SALAIRE",res2);
    query.bindValue(":POSTE",Poste);
    query.bindValue(":DEPART",Depart);
    query.bindValue(":LOGIN",res);
    query.bindValue(":PASSWORD",password);
    query.bindValue(":CARD_UID",card_uid);
    return query.exec();
}

QSqlQueryModel* employe::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT CIN, Nom, Prenom, DATENAISS, Poste, Depart, Salaire FROM employe");

    // Set headers
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Datenaiss"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Depart"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Salaire"));

    // Format the date in the model
    for (int row = 0; row < model->rowCount()-2; ++row) {
        QDateTime dateTime = model->data(model->index(row, 3)).toDateTime();
        QString formattedDate = dateTime.date().toString("dd/MM/yyyy");
        model->setData(model->index(row, 3), formattedDate);
    }
    return model;
}


QSqlQueryModel *employe::trier(QString x)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    qDebug()<<x<<endl;
    if(x=="CIN"){
        model->setQuery("select CIN,Nom,Prenom,Datenaiss,salaire,poste,depart,login,password from employe order by CIN");
        QMessageBox::information(nullptr, QObject::tr("Sort Done"),QObject::tr("Sorted By CIN\n"),QMessageBox::Ok);
    }
    else if(x=="Nom"){
        model->setQuery("select CIN,Nom,Prenom,Datenaiss,salaire,poste,depart,login,password from employe order by Nom");
        QMessageBox::information(nullptr, QObject::tr("Sort Done"),QObject::tr("Sorted By Nom\n"),QMessageBox::Ok);
    }
    else if (x=="Prenom"){
        model->setQuery("select CIN,Nom,Prenom,Datenaiss,salaire,poste,depart,login,password from employe order by Prenom");
        QMessageBox::information(nullptr, QObject::tr("Sort Done"),QObject::tr("Sorted By Prenom\n"),QMessageBox::Ok);
    }
    else if (x=="Date de naissance"){
        model->setQuery("select CIN,Nom,Prenom,Datenaiss,salaire,poste,depart,login,password from employe order by Datenaiss");
        QMessageBox::information(nullptr, QObject::tr("Sort Done"),QObject::tr("Sorted By Datenaiss\n"),QMessageBox::Ok);
    }
    else if (x=="Departement"){
        model->setQuery("select CIN,Nom,Prenom,Datenaiss,salaire,poste,depart,login,password from employe order by depart");
        QMessageBox::information(nullptr, QObject::tr("Sort Done"),QObject::tr("Sorted By departement\n"),QMessageBox::Ok);
    }
    else if (x=="Poste"){
        model->setQuery("select CIN,Nom,Prenom,Datenaiss,salaire,poste,depart,login,password from employe order by poste");
        QMessageBox::information(nullptr, QObject::tr("Sort Done"),QObject::tr("Sorted By poste\n"),QMessageBox::Ok);
    }
    else if (x=="Salaire"){
        model->setQuery("select CIN,Nom,Prenom,Datenaiss,salaire,poste,depart,login,password from employe order by salaire");
        QMessageBox::information(nullptr, QObject::tr("Sort Done"),QObject::tr("Sorted By salaire\n"),QMessageBox::Ok);
    }
    return model;
}
QSqlQueryModel* employe::rechercher(QString a)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    qDebug()<<a<<endl;
    model->setQuery("select * from employe where (Nom LIKE lower('%"+a+"%') or Prenom LIKE lower('%"+a+"%') or (Nom LIKE upper('%"+a+"%') or Prenom LIKE upper('%"+a+"%')))");
    return model;
}
bool employe::search(QString log, QString pass) {
    QSqlQuery query;
    query.prepare("SELECT * FROM employe WHERE login = :login AND password = :password");
    query.bindValue(":login", log);
    query.bindValue(":password", pass);

    if (query.exec() && query.next()) {
        return true;
    }
    else {
        return false;
    }
}




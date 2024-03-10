#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QApplication>
#include <QSqlError>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_main->setCurrentIndex(0);
    ui->stackedWidget_3->setCurrentIndex(0);
    ui->stackedWidget_4->setCurrentIndex(0);
    ui->stackedWidget_5->setCurrentIndex(0);
    ui->stackedWidget_6->setCurrentIndex(0);
    //client
    ui->leidclient->setValidator(new QIntValidator(1000000,999999999,this));
    //ui->leRIBclient->setValidator(new QIntValidator(1000000,999999999,this));
    ui->lesrevenusclient->setValidator(new QIntValidator(1000000,999999999,this));
//////////////////////////////////////////Add ref validator////////////////??????????????????

    ui->leidclient_modif->setValidator(new QIntValidator(1000000,999999999,this));
    //ui->leRIBclient_modif->setValidator(new QIntValidator(1000000,999999999,this));
    ui->lesrevenusclient_modif->setValidator(new QIntValidator(1000000,999999999,this));

    connect(ui->lemailclient, &QLineEdit::editingFinished, [this](){
            QString mail = ui->lemailclient->text();
            QRegExp rxEmail("[A-Za-z0-9.]{1,30}@[A-Za-z.]{1,30}$");

            if (mail.length() > 35) {
                // Adresse e-mail dÃ©passe la taille maximale
                QMessageBox::critical(this, "Validation Ã©chouÃ©e", "Adresse e-mail dÃ©passe la taille maximale de 30 caractÃ¨res. Veuillez entrer une adresse e-mail valide de 30 caractÃ¨res ou moins.");
            } else if (!rxEmail.exactMatch(mail)) {
                // Adresse e-mail non valide
                QMessageBox::critical(this, "Validation Ã©chouÃ©e", "Adresse e-mail non valide. Veuillez entrer une adresse e-mail valide.");
            } else {

                QMessageBox::information(this, "Validation rÃ©ussie", "Adresse e-mail valide.");
            }
        });
   connect(ui->leRIBclient, &QLineEdit::editingFinished, [this]() {
        QString RIB = ui->leRIBclient->text();
        QRegExp rxRIB("\\d{13}");

        if (RIB.length() != 13 || !rxRIB.exactMatch(RIB)) {

            QMessageBox::critical(this, "Le RIB doit contenir exactement 13 chiffres", "Le RIB doit contenir exactement 13 chiffres. Veuillez entrer un RIB valide.");
        } else {

            QMessageBox::information(this, "RIB valide.", "RIB valide.");
        }
    });
    connect(ui->lemailclient_modif, &QLineEdit::editingFinished, [this]() {
            QString mail = ui->lemailclient_modif->text();
            QRegExp rxEmail("[A-Za-z0-9.]{1,30}@[A-Za-z.]{1,30}$");

            if (mail.length() > 35) {

                QMessageBox::critical(this, "adresse mail depasse la taille maximale", "Adresse e-mail dÃ©passe la taille maximale de 30 caractÃ¨res. Veuillez entrer une adresse e-mail valide de 30 caractÃ¨res ou moins.");
            } else if (!rxEmail.exactMatch(mail)) {

                QMessageBox::critical(this, "adresse mail non valide", "Adresse e-mail non valide. Veuillez entrer une adresse e-mail valide.");
            } else {

                QMessageBox::information(this, "adresse mail non valide ", "Adresse e-mail valide.");
            }
        });
    connect(ui->leRIBclient_modif, &QLineEdit::editingFinished, [this]() {
        QString RIB = ui->leRIBclient_modif->text();
        QRegExp rxRIB("\\d{13}");

        if (RIB.length() != 13 || !rxRIB.exactMatch(RIB)) {

            QMessageBox::critical(this, "le RIB doit contenir exactement 13 chiffres ", "Le RIB doit contenir exactement 13 chiffres. Veuillez entrer un RIB valide.");
        } else {

            QMessageBox::information(this, "RIB validee", "RIB valide.");
        }
    });
    loadHistoryToTableView();
    ui->tabclient->setModel(Cdupe.afficher());
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
    ///////////////////////////////////////Produits///////////////////////////////////////
    ui->lineEdit_QUANTITE->setValidator(new QIntValidator(0, 9999,this));
    ui->lineEdit_PRIX->setValidator(new QIntValidator(0, 9999,this));
    QRegExp regExp("^(RECY|NON RECY)$"); // Expression régulière pour "R" ou "NR" en majuscules ou minuscules
    ui->lineEdit_ETAT->setValidator(new QRegExpValidator(regExp, this));
    QRegExp regExp1("^(PL|pl|FE|fe|VE|ve|ME|me|PAP|pap)$");
    ui->lineEdit_TYPE->setValidator(new QRegExpValidator(regExp1, this));
    QRegExp regExp2("^#[A-Z]{2}\\d{1}[A-Z]{1}$");
    ui->lineEdit_REF->setValidator(new QRegExpValidator(regExp2, this));
    ui->tab_produit->setModel(P.afficher());
    createChart();
    QString valeur0 = "PAS DE TRI";
    QString valeur1 = "REFERENCE";
    QString valeur2 = "TYPE";
    QString valeur3 = "ETAT";
    QString valeur4 = "QUANTITE";
    QString valeur5 = "PRIX";
    ui->comboBox_TRI->addItem(valeur0);
    ui->comboBox_TRI->addItem(valeur1);
    ui->comboBox_TRI->addItem(valeur2);
    ui->comboBox_TRI->addItem(valeur3);
    ui->comboBox_TRI->addItem(valeur4);
    ui->comboBox_TRI->addItem(valeur5);
    ////////////Employe
    ui->tableView->setModel(EMP.afficher());
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // selects a whole row
    ui->tableView->setItemDelegateForColumn(0,new num_deleguate(this));
    ui->search_for_main->setPlaceholderText("Nom/Prenom");
    ui->search_for_main->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]{0,255}"),this));
    ui->tableView->setModel(EMP.afficher());
    ui->login->setMaxLength(8);
    //Add
    ui->nom->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]{0,255}"),this));
    ui->prenom->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]{0,255}"),this));
    ui->CIN->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,255}"),this));
    ui->CIN->setValidator(new QIntValidator(0,99999999));
    ui->id_reset->setValidator(new QRegExpValidator(QRegExp("[0-9]{0,255}"),this));
    ui->id_reset->setValidator(new QIntValidator(0,99999999));
    ui->salaire->setValidator(new QRegExpValidator(QRegExp("[0-9.]{0,255}"),this));
    QDate max(2003,12,31);
    ui->date->setMaximumDate(max);
    ui->CIN->setPlaceholderText("CIN");
    ui->nom->setPlaceholderText("Nom");
    ui->prenom->setPlaceholderText("Prenom");
    ui->salaire->setPlaceholderText("Salaire");
    //Modif
    ui->CIN_modf->setDisabled(true);
    ui->nom_modf->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]{0,255}"),this));
    ui->prenom_modf->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]{0,255}"),this));
    ui->salaire_modf->setValidator(new QRegExpValidator(QRegExp("[0-9.]{0,255}"),this));
    ui->date->setMaximumDate(max);
    // Initialize the network manager
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
/////////////////////////////////////////////buttons/////////////////////////////////////////////

void MainWindow::on_home_clicked()
{

    ui->home->setStyleSheet("QPushButton{font: 1000 15pt 'Segoe UI';""background-color: rgba(0,0,0,0%);""color: rgb(5, 26, 43);""border: none;}");
    QString UsedStyleSheet = "QPushButton{font: 500 14.5pt 'Segoe UI'; color: rgb(218, 218, 218); background-color: rgba(0,0,0,0%); border:none;}"
                               "QPushButton:hover {font: 500 15pt 'Segoe UI'; background-color: rgba(0,0,0,0%); border:none;}"
                               "QPushButton:pressed {font: 500 14pt 'Segoe UI'; background-color: rgba(0,0,0,0%); border:none; color: rgb(130, 207, 216);}";
    ui->main_slct->setStyleSheet(UsedStyleSheet);
    ui->quizz->setStyleSheet(UsedStyleSheet);
    ui->contacts->setStyleSheet(UsedStyleSheet);
    ui->chatbox->setStyleSheet(UsedStyleSheet);
    ui->about->setStyleSheet(UsedStyleSheet);
    ui->stackedWidget->setCurrentIndex(0);
    ui->fleche->setGeometry(150,90,30,30);
}
void MainWindow::on_main_slct_clicked()
{
    ui->main_slct->setStyleSheet("QPushButton{font: 1000 15pt 'Segoe UI';""background-color: rgba(0,0,0,0%);""color: rgb(5, 26, 43);""border: none;}");
    QString UsedStyleSheet = "QPushButton{font: 500 14.5pt 'Segoe UI'; color: rgb(218, 218, 218); background-color: rgba(0,0,0,0%); border:none;}"
                               "QPushButton:hover {font: 500 15pt 'Segoe UI'; background-color: rgba(0,0,0,0%); border:none;}"
                               "QPushButton:pressed {font: 500 14pt 'Segoe UI'; background-color: rgba(0,0,0,0%); border:none; color: rgb(130, 207, 216);}";

    ui->home->setStyleSheet(UsedStyleSheet);
    ui->quizz->setStyleSheet(UsedStyleSheet);
    ui->contacts->setStyleSheet(UsedStyleSheet);
    ui->chatbox->setStyleSheet(UsedStyleSheet);
    ui->about->setStyleSheet(UsedStyleSheet);
    ui->stackedWidget->setCurrentIndex(1);
    ui->fleche->setGeometry(150,170,30,30);
}

void MainWindow::on_quizz_clicked()
{
    ui->quizz->setStyleSheet("QPushButton{font: 1000 15pt 'Segoe UI';""background-color: rgba(0,0,0,0%);""color: rgb(5, 26, 43);""border: none;}");
    QString UsedStyleSheet = "QPushButton{font: 500 14.5pt 'Segoe UI'; color: rgb(218, 218, 218); background-color: rgba(0,0,0,0%); border:none;}"
                               "QPushButton:hover {font: 500 15pt 'Segoe UI'; background-color: rgba(0,0,0,0%); border:none;}"
                               "QPushButton:pressed {font: 500 14pt 'Segoe UI'; background-color: rgba(0,0,0,0%); border:none; color: rgb(130, 207, 216);}";

    ui->home->setStyleSheet(UsedStyleSheet);
    ui->main_slct->setStyleSheet(UsedStyleSheet);
    ui->contacts->setStyleSheet(UsedStyleSheet);
    ui->chatbox->setStyleSheet(UsedStyleSheet);
    ui->about->setStyleSheet(UsedStyleSheet);
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_7->setCurrentIndex(0);
    ui->fleche->setGeometry(150,250,30,30);

    ui->animation->setGeometry(230, 40, 140, 150);
    animation=new QPropertyAnimation(ui->animation,"geometry");
    animation->setDuration(2000);
    animation->setStartValue(ui->animation->geometry());
    animation->setEndValue(QRect(740,210,180,190));
    QEasingCurve curve;
    curve.setType(QEasingCurve::InOutCubic);
    animation->setEasingCurve(curve);
    animation->setLoopCount(1);
    curve.setAmplitude(2.00);
    curve.setOvershoot(1.30);
    curve.setPeriod(0.5);
    animation->start();
    /////////////animation2/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ui->animation_2->setGeometry(540, 40, 140, 150);
    animation_2=new QPropertyAnimation(ui->animation_2,"geometry");
    animation_2->setDuration(2000);
    animation_2->setStartValue(ui->animation_2->geometry());
    animation_2->setEndValue(QRect(480,210,180,190));
    QEasingCurve curve2;
    curve2.setType(QEasingCurve::InOutBounce);
    animation_2->setEasingCurve(curve2);
    animation_2->setLoopCount(1);
    curve2.setAmplitude(2.00);
    curve2.setOvershoot(1.30);
    curve2.setPeriod(0.5);
    animation_2->start();
    /////////////animation3/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ui->animation_3->setGeometry(530,300,140,150);
    animation_3=new QPropertyAnimation(ui->animation_3,"geometry");
    animation_3->setDuration(2000);
    animation_3->setStartValue(ui->animation_3->geometry());
    animation_3->setEndValue(QRect(220,210,180,190));
    QEasingCurve curve3;
    curve3.setType(QEasingCurve::InOutBack);
    animation_3->setEasingCurve(curve3);
    animation_3->setLoopCount(1);
    curve3.setAmplitude(2.00);
    curve3.setOvershoot(1.30);
    curve3.setPeriod(0.5);
    animation_3->start();

    score=0;
    ANSWERS=0;
    ui->radioButton_A1->setChecked(false);
    ui->radioButton_A2->setChecked(false);
    ui->radioButton_A3->setChecked(false);
    ui->radioButton_B1->setChecked(false);
    ui->radioButton_B2->setChecked(false);
    ui->radioButton_B3->setChecked(false);
    ui->radioButton_C1->setChecked(false);
    ui->radioButton_C2->setChecked(false);
    ui->radioButton_C3->setChecked(false);
    ui->radioButton_D1->setChecked(false);
    ui->radioButton_D2->setChecked(false);
    ui->radioButton_D3->setChecked(false);
    ui->label_RESULT->clear();
    ui->radioButton_A1_2->setChecked(false);
    ui->radioButton_A2_2->setChecked(false);
    ui->radioButton_A3_2->setChecked(false);
    ui->radioButton_B1_2->setChecked(false);
    ui->radioButton_B2_2->setChecked(false);
    ui->radioButton_B3_2->setChecked(false);
    ui->radioButton_C1_2->setChecked(false);
    ui->radioButton_C2_2->setChecked(false);
    ui->radioButton_C3_2->setChecked(false);
    ui->radioButton_D1_2->setChecked(false);
    ui->radioButton_D2_2->setChecked(false);
    ui->radioButton_D3_2->setChecked(false);
    ui->label_RESULT_2->clear();
    ui->radioButton_A1_3->setChecked(false);
    ui->radioButton_A2_3->setChecked(false);
    ui->radioButton_A3_3->setChecked(false);
    ui->radioButton_B1_3->setChecked(false);
    ui->radioButton_B2_3->setChecked(false);
    ui->radioButton_B3_3->setChecked(false);
    ui->radioButton_C1_3->setChecked(false);
    ui->radioButton_C2_3->setChecked(false);
    ui->radioButton_C3_3->setChecked(false);
    ui->radioButton_D1_3->setChecked(false);
    ui->radioButton_D2_3->setChecked(false);
    ui->radioButton_D3_3->setChecked(false);
    ui->label_RESULT_3->clear();
}

void MainWindow::on_contacts_clicked()
{
    ui->contacts->setStyleSheet("QPushButton{font: 1000 15pt 'Segoe UI';""background-color: rgba(0,0,0,0%);""color: rgb(5, 26, 43);""border: none;}");
    QString UsedStyleSheet = "QPushButton{font: 500 14.5pt 'Segoe UI'; color: rgb(218, 218, 218); background-color: rgba(0,0,0,0%); border:none;}"
                               "QPushButton:hover {font: 500 15pt 'Segoe UI'; background-color: rgba(0,0,0,0%); border:none;}"
                               "QPushButton:pressed {font: 500 14pt 'Segoe UI'; background-color: rgba(0,0,0,0%); border:none; color: rgb(130, 207, 216);}";

    ui->home->setStyleSheet(UsedStyleSheet);
    ui->main_slct->setStyleSheet(UsedStyleSheet);
    ui->quizz->setStyleSheet(UsedStyleSheet);
    ui->chatbox->setStyleSheet(UsedStyleSheet);
    ui->about->setStyleSheet(UsedStyleSheet);
    ui->stackedWidget->setCurrentIndex(3);
    ui->fleche->setGeometry(150,330,30,30);
}

void MainWindow::on_chatbox_clicked()
{
    ui->chatbox->setStyleSheet("QPushButton{font: 1000 15pt 'Segoe UI';""background-color: rgba(0,0,0,0%);""color: rgb(5, 26, 43);""border: none;}");
    QString UsedStyleSheet = "QPushButton{font: 500 14.5pt 'Segoe UI'; color: rgb(218, 218, 218); background-color: rgba(0,0,0,0%); border:none;}"
                               "QPushButton:hover {font: 500 15pt 'Segoe UI'; background-color: rgba(0,0,0,0%); border:none;}"
                               "QPushButton:pressed {font: 500 14pt 'Segoe UI'; background-color: rgba(0,0,0,0%); border:none; color: rgb(130, 207, 216);}";

    ui->home->setStyleSheet(UsedStyleSheet);
    ui->main_slct->setStyleSheet(UsedStyleSheet);
    ui->quizz->setStyleSheet(UsedStyleSheet);
    ui->contacts->setStyleSheet(UsedStyleSheet);
    ui->about->setStyleSheet(UsedStyleSheet);
    ui->stackedWidget->setCurrentIndex(4);
    ui->fleche->setGeometry(150,410,30,30);

}

void MainWindow::on_about_clicked()
{
    ui->about->setStyleSheet("QPushButton{font: 1000 15pt 'Segoe UI';""background-color: rgba(0,0,0,0%);""color: rgb(5, 26, 43);""border: none;}");
    QString UsedStyleSheet = "QPushButton{font: 500 14.5pt 'Segoe UI'; color: rgb(218, 218, 218); background-color: rgba(0,0,0,0%); border:none;}"
                               "QPushButton:hover {font: 500 15pt 'Segoe UI'; background-color: rgba(0,0,0,0%); border:none;}"
                               "QPushButton:pressed {font: 500 14pt 'Segoe UI'; background-color: rgba(0,0,0,0%); border:none; color: rgb(130, 207, 216);}";

    ui->home->setStyleSheet(UsedStyleSheet);
    ui->main_slct->setStyleSheet(UsedStyleSheet);
    ui->quizz->setStyleSheet(UsedStyleSheet);
    ui->contacts->setStyleSheet(UsedStyleSheet);
    ui->chatbox->setStyleSheet(UsedStyleSheet);
    ui->stackedWidget->setCurrentIndex(5);
    ui->fleche->setGeometry(150,490,30,30);
}


void MainWindow::on_gestion_employes_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->stackedWidget_3->setCurrentIndex(0);
}

void MainWindow::on_gestion_client_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    ui->stackedWidget_4->setCurrentIndex(4);
}

void MainWindow::on_gestion_produit_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->stackedWidget_5->setCurrentIndex(0);
}

void MainWindow::on_gestion_centre_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
    ui->stackedWidget_6->setCurrentIndex(1);
}

void MainWindow::on_back_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_back_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_back_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}




/////////////////////////////////////////////integration/////////////////////////////////////////////

/////////////////////////////////////////////centre/////////////////////////////////////////////

void MainWindow::on_pushButton_ajouter_clicked()
{
    int  identifiant=ui->lineEdit_identifiant->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    int  surface=ui->lineEdit_surface->text().toInt();
    QString lieu=ui->lineEdit_lieu->text();
    centre c(identifiant,nom,lieu,surface);
    bool test =c.ajouter();
    if (test)

  {
      QMessageBox::information(nullptr, QObject::tr("OK"),
                  QObject::tr("ajout effectué.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
      ui->tableauzones->setModel(c.afficher());
}
  else
      QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                  QObject::tr("Ajout non effectué.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_modifier_clicked()
{
    int  identifiant=ui->lineEdit_identifiant_2->text().toInt();
    QString nom = ui->lineEdit_nom_2->text();
    QString lieu= ui->lineEdit_lieu_3->text();
    int  surface=ui->lineEdit_surface_2->text().toInt();
    centre c(identifiant,nom,lieu,surface);
    bool test=c.modifier(c.get_identifinat());
    if (test)
    {
         centre c;
         ui->tableauzones->setModel(c.afficher());
         QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Modification effectuée.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);



   }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("MODIFICATION non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
void MainWindow::on_pb_supprimer_clicked()
{
    centre c1;
    c1.setidentifiant(ui->lineEdit_idsupp->text().toInt());
   bool test=c1.supprimer(c1.get_identifinat());
   if (test)
   {
       QMessageBox::information(nullptr, QObject::tr("OK"),
                   QObject::tr("Suppression effectué avec succés.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
       ui->tableauzones->setModel(c.afficher());
  }
   else
       QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                   QObject::tr("Suppression non effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_sort_clicked()
{
    ui->tableauzones->setModel(c.trier(ui->choice->currentText()));
}

void MainWindow::on_export_2_clicked()
{
    QString defaultFileName = "Centre.pdf"; // Default file name
    QString saveFilePath = QFileDialog::getSaveFileName(this, tr("Export PDF"), QDir::homePath() + "/" + defaultFileName, tr("PDF Files (*.pdf)"));

    if (!saveFilePath.isEmpty()) {
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFileName(saveFilePath);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFormat(QPrinter::PdfFormat);

        QPainter painter(&printer);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

        QAbstractItemModel* model = ui->tableauzones->model();

        if (model) {
            int rowCount = model->rowCount();
            int columnCount = model->columnCount();

            // Create a QTextDocument to format the data as an HTML table
            QTextDocument doc;
            QTextCursor cursor(&doc);

            // Adjust the font size to make the text larger
            QString tableHtml = "<table style=\"border-collapse: collapse; width: 100%; border: 1px solid black; font-size: 4px;\">";

            // Add table header
            tableHtml += "<tr style=\"background-color: #ccc;\">";
            for (int col = 0; col < columnCount ; ++col) { // Exclude the last 2 columns
                QVariant data = model->headerData(col, Qt::Horizontal);
                tableHtml += "<th style=\"border: 1px solid black; padding: 8px;\">" + data.toString() + "</th>";
            }
            tableHtml += "</tr>";

            // Loop through the rows and columns to populate the table
            for (int row = 0; row < rowCount; ++row) {
                tableHtml += "<tr>";
                for (int col = 0; col < columnCount ; ++col) { // Exclude the last 2 columns
                    QModelIndex index = model->index(row, col);
                    QVariant data = model->data(index);

                    // Append the data to the table cell with border and adjusted font size
                    tableHtml += "<td style=\"border: 1px solid black; padding: 8px;\">" + data.toString() + "</td>";
                }
                tableHtml += "</tr>";
            }

            tableHtml += "</table>";

            // Set the HTML content for the QTextDocument
            doc.setHtml(tableHtml);

            // Manually scale the painter by a factor of 100
            painter.scale(30.0, 30.0);

            // Render the QTextDocument onto the PDF
            doc.setPageSize(printer.pageRect().size());
            doc.drawContents(&painter);
        }

        painter.end();
    }
}

void MainWindow::on_pb_stats_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from CENTRE where lieu='tunis'");
    int number1 = model->rowCount();
    model->setQuery("select * from CENTRE where lieu='jerba'");
    int number2 = model->rowCount();
    model->setQuery("select * from CENTRE where lieu='sousse'");
    int number3 = model->rowCount();
    model->setQuery("select * from CENTRE where lieu='beja'");
    int number4 = model->rowCount();
    QPieSeries *series = new QPieSeries();
    QStringList colors = {"#04BBFF", "#0594D0", "#007198", "#003C57"}; // Couleurs pour chaque tranche
    QStringList labels = {"tunis", "jerba", "sousse", "beja"}; // Labels pour chaque tranche
    QVector<int> numbers = {number1, number2, number3, number4}; // Nombre d'éléments dans chaque catégorie
    for (int i = 0; i < 4; ++i)
    {
        QString color = colors.at(i);
        QString label = labels.at(i);
        QPieSlice *slice = new QPieSlice(label, numbers.at(i));
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::black, 2));
        slice->setLabelFont(QFont("Arial", 12));
        //Animation au survol
        slice->setExploded();
        // Explosion au clic
        connect(slice, &QPieSlice::clicked, this, [slice, series]() {
            if (slice->isExploded()){
                slice->setExploded(false);
            }
            else {
                slice->setExploded();
            }
            for (QPieSlice *otherSlice : series->slices()){
                if (otherSlice != slice) {
                    otherSlice->setExploded(false);
                }
            }
        });
        // Définition de la couleur de la tranche
        slice->setBrush(QColor(color));
        // Ajout de la tranche au QPieSeries
        series->append(slice);
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Pourcentage des centres selon le lieu");
    chart->legend()->setFont(QFont("Arial", 10));
    chart->setBackgroundBrush(QColor("#D6D9DA")); // Couleur de fond
   // Thème du graphique
    //chart->setTheme(QChart::ChartThemeBrownSand);
    // Animation
    QChart::AnimationOptions options = QChart::AllAnimations;
    chart->setAnimationOptions(options);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setTitleFont(QFont("Arial", 25));
    chartView->resize(1000, 500);
    chartView->chart()->legend()->setAlignment(Qt::AlignBottom);
    chartView->show();
}

void MainWindow::on_search_textChanged()
{
    ui->tableauzones->setModel(c.rechercher(ui->search->text()));
}
void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget_6->setCurrentIndex(1);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget_6->setCurrentIndex(3);
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget_6->setCurrentIndex(2);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget_6->setCurrentIndex(0);
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget_6->setCurrentIndex(3);
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget_6->setCurrentIndex(1);
}

void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget_6->setCurrentIndex(0);
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget_6->setCurrentIndex(2);
}
void MainWindow::addTask()
{
    QString taskDescription = taskLineEdit->text().trimmed();
    if (!taskDescription.isEmpty()) {
        QString dueDate = dueDateEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
        QString taskText = taskDescription + " (Due: " + dueDate + ")";
        QListWidgetItem *taskItem = new QListWidgetItem(taskText);
        taskItem->setData(Qt::UserRole, taskDescription);
        taskListWidget->addItem(taskItem);
        taskLineEdit->clear();
        dueDateEdit->clear();
    }
}
void MainWindow::removeTask()
{
    qDeleteAll(taskListWidget->selectedItems());
}
void MainWindow::completeTask()
{
    QListWidgetItem *item = taskListWidget->currentItem();
    if (item) {
        QString taskDescription = item->data(Qt::UserRole).toString();
        QString completedTaskText = taskDescription + " (Completed)";
        item->setText(completedTaskText);
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    }
}
void MainWindow::updateTaskDetails(QListWidgetItem *item)
{
    QString taskDescription = item->data(Qt::UserRole).toString();
    taskLineEdit->setText(taskDescription);

    QString taskText = item->text();
    QString dueDateText = taskText.mid(taskText.indexOf("(Due: ") + 6, 19);
    QDateTime dueDateTime = QDateTime::fromString(dueDateText, "yyyy-MM-dd hh:mm:ss");
    dueDateEdit->setDateTime(dueDateTime);
}
void MainWindow::saveTasks()
{
    QFile file(QDir::homePath() + "/tasks.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (int i = 0; i < taskListWidget->count(); ++i) {
            QListWidgetItem *item = taskListWidget->item(i);
            out << item->data(Qt::UserRole).toString() << " | " << item->text() << "\n";
        }
        file.close();
    } else {
        QMessageBox::critical(this, "Error", "Could not save tasks to file.");
    }
}


void MainWindow::loadTasks()
{
    QFile file(QDir::homePath() + "/tasks.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        taskListWidget->clear();
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(" | ");
            if (parts.length() == 2) {
                QString taskDescription = parts[0];
                QString taskText = parts[1];
                QListWidgetItem *taskItem = new QListWidgetItem(taskText);
                taskItem->setData(Qt::UserRole, taskDescription);
                taskListWidget->addItem(taskItem);
            }
        }
        file.close();
    }
}
void MainWindow::on_todo_clicked(){
    taskListWidget = new QListWidget(this);
        taskLineEdit = new QLineEdit(this);
        addButton = new QPushButton("Add Task", this);
        removeButton = new QPushButton("Remove Task", this);
        completeButton = new QPushButton("Complete Task", this);
        exit = new QPushButton("Exit", this);
        dueDateEdit = new QDateTimeEdit(this);
        connect(addButton, &QPushButton::clicked, this, &MainWindow::addTask);
           connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeTask);
           connect(completeButton, &QPushButton::clicked, this, &MainWindow::completeTask);
           connect(exit, &QPushButton::clicked, this, &MainWindow::exittasks);
           connect(taskListWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::updateTaskDetails);
           QVBoxLayout *layout = new QVBoxLayout;
           layout->addWidget(taskLineEdit);
           layout->addWidget(dueDateEdit);
           layout->addWidget(addButton);
           layout->addWidget(removeButton);
           layout->addWidget(completeButton);
           layout->addWidget(taskListWidget);
           layout->addWidget(exit);
           QWidget *centralWidget = new QWidget(this);
           centralWidget->setLayout(layout);
           setCentralWidget(centralWidget);
           loadTasks();
}
void MainWindow::setupUi()
{
    // Create a QCalendarWidget
    calendarWidget = new QCalendarWidget(this);

    // Set the calendar to navigate by month and year
    calendarWidget->setNavigationBarVisible(true);

    // Create a label to display the selected date
    selectedDateLabel = new QLabel("Selected Date: ", this);
    exitButton = new QPushButton("Exit", this);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::exitApplication);

    // Create a layout to arrange widgets
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(calendarWidget);
    mainLayout->addWidget(selectedDateLabel);
     mainLayout->addWidget(exitButton);

    // Set the layout as the central widget
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connect the dateClicked signal to the handleDateSelection slot
    connect(calendarWidget, &QCalendarWidget::clicked, this, &MainWindow::handleDateSelection);

}

void MainWindow::handleDateSelection(const QDate &date)
{
    // Display the selected date in the label
    selectedDateLabel->setText("Selected Date: " + date.toString(Qt::TextDate));
}
void MainWindow::exitApplication()
{

    ui->setupUi(this);
    ui->tableauzones->setModel(c.afficher());
}

void MainWindow::on_calendrier_clicked()
{
    // Create a QCalendarWidget
    calendarWidget = new QCalendarWidget(this);
    calendarWidget->setGridVisible(true);

    // Set the calendar to navigate by month and year
    calendarWidget->setNavigationBarVisible(true);

    // Create a label to display the selected date
    selectedDateLabel = new QLabel("Selected Date: ", this);
    exitButton = new QPushButton("Exit", this);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::exitApplication);

    // Create a layout to arrange widgets
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(calendarWidget);
    mainLayout->addWidget(selectedDateLabel);
     mainLayout->addWidget(exitButton);

    // Set the layout as the central widget
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connect the dateClicked signal to the handleDateSelection slot
    connect(calendarWidget, &QCalendarWidget::clicked, this, &MainWindow::handleDateSelection);
}
void MainWindow::exittasks(){
    ui->setupUi(this);
    ui->tableauzones->setModel(c.afficher());
}
/////////////////////////////////////////////clients/////////////////////////////////////////////
void MainWindow::on_pushButton_22_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(1);
}

void MainWindow::on_pushButton_21_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(7);
}

void MainWindow::on_pushButton_24_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(2);
}

void MainWindow::on_pushButton_23_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(0);
}

void MainWindow::on_pushButton_26_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(3);
}

void MainWindow::on_pushButton_25_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(1);
}

void MainWindow::on_pushButton_28_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(4);
}

void MainWindow::on_pushButton_27_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(2);
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(5);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(3);
}

void MainWindow::on_pushButton_16_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(6);
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(4);
}

void MainWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(7);
}

void MainWindow::on_pushButton_17_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(5);
}

void MainWindow::on_pushButton_20_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(0);
}

void MainWindow::on_pushButton_19_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(6);
}


void MainWindow::on_ajouterclient_clicked()
{       int id=ui->leidclient->text().toInt();
        QString nom=ui->lenomclient->text();
        QString prenom=ui->leprenomclient->text();
        QString adresse=ui->ladresseclient->text();
        QString typec=ui->letypeclient->currentText();
        QString mail=ui->lemailclient->text();
        float revenus=ui->lesrevenusclient->text().toFloat();
        int RIB=ui->leRIBclient->text().toInt();
        int REF=ui->leREFclient->text().toInt() ;
         QDate date_payement=ui->date_payementclient->date();





        Client c(id ,nom, prenom,adresse,typec,mail,revenus,RIB,REF,date_payement);
            if(c.ajouterclient()){
                QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("ajout effectue"),QMessageBox::Cancel);
            ui->tabclient->setModel(Cdupe.afficher());
            c.addToHistory("ajoutclient",c);
            }
            else{
                QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("ajout effectue"),QMessageBox::Cancel);
            }

}


void MainWindow::on_pbsuppclient_clicked()
{
    int id =ui->idsuppclient->text().toInt();
    bool test=Cdupe.supprimer(id);
    QMessageBox msgBox;
    if(test)
       {
        ui->tabclient->setModel(Cdupe.afficher());
        QMessageBox :: information(nullptr,QObject::tr("OK"),
                QObject::tr("suppresion effectuer\n"
                            "click cancel to exit."),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                              QObject::tr("suppresion non effectué.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
    }



}



void MainWindow::on_pb_modifierclient_clicked()
{       int id=ui->leidclient_modif->text().toInt();
        QString nom=ui->lenomclient_modif->text();
        QString prenom=ui->leprenomclient_modif->text();
        QString adresse=ui->ladresseclient_modif->text();
        QString typec=ui->letypeclient_modif->currentText();
        QString mail=ui->lemailclient_modif->text();
        float revenus=ui->lesrevenusclient_modif->text().toFloat();
        int RIB=ui->leRIBclient_modif->text().toInt();
        int REF=ui->leREFclient_modif->text().toInt() ;
         QDate date_payement=ui->date_payementclient_modif->date();
         Client Cdupe( id,nom , prenom ,adresse , mail ,typec , revenus , REF,  RIB, date_payement);



                 bool test = Cdupe.modifierclient(id, nom, prenom,  adresse, mail, typec, revenus, REF,  RIB, date_payement);

         if (test){

                QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("modification effectue"),QMessageBox::Cancel);
  ui->tabclient->setModel(Cdupe.afficher());
            }
            else{
                QMessageBox::critical(nullptr,QObject::tr("ok"),QObject::tr("modification non effectue"),QMessageBox::Cancel);
            }

}
void MainWindow::on_trierclient_clicked()

{  Client E;
    // Récupérez le choix de tri de l'utilisateur, par exemple à partir d'un menu déroulant (QComboBox)
    QString choixTri = ui->check_tri->currentText();
    // Appelez la fonction d'affichage avec le choix de tri
    ui->tabclients->setModel(Cdupe.afficher_choix_client(choixTri));
}
void MainWindow::on_pdf_clicked()
{
    QString strStream,strTitle;
    QTextStream out(&strStream);
    const int rowCount = ui->tabclient->model()->rowCount();
    const int columnCount = ui->tabclient->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>clients</title>\n").arg(strTitle)
        <<  "<head> Les amendes non payés</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<table border=1 cellspacing=0 cellpadding=2 style='width:100%;'>\n";

    // headers
    out << "h1 {" <<
            "   text-align: center;" // Center-align the h1 element
           << "}";
    out << "<h1> Liste des clients</h1>";
    out << "<br>";
    out << "<br>";
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tabclient->isColumnHidden(column))
            out << "<th>" << ui->tabclient->model()->headerData(column, Qt::Horizontal).toString() << "</th>";
    out << "</tr></thead>\n";


    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tabclient->isColumnHidden(column)) {
                QString data = ui->tabclient->model()->data(ui->tabclient->model()->index(row, column)).toString().simplified();
                out << QString("<td style='width:200px' bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;

}
void MainWindow::loadHistoryToTableView()
{
    QFile historyFile("historique.txt");


    if (!historyFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open the history file";
        return;
    }

    QTextStream in(&historyFile);

    QStandardItemModel *model = new QStandardItemModel();


    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');

        QList<QStandardItem *> rowItems;
        for (const QString &part : parts) {
            rowItems.append(new QStandardItem(part));
        }

        model->appendRow(rowItems);
    }

    historyFile.close();

    ui->historique->setModel(model);
}

void MainWindow::on_statistiquepartype_clicked()
{
       QSqlQueryModel *model = new QSqlQueryModel();
       model->setQuery("select * from CLIENT where typec='client fidele'");
       int number1 = model->rowCount();
       model->setQuery("select * from CLIENT where typec='client nouveau'");
       int number2 = model->rowCount();
       QPieSeries *series = new QPieSeries();
       QStringList colors = {"#0594D0", "#003C57"}; // Couleurs pour chaque tranche
       QStringList labels = {"client fidele", "client nouveau"};
       QVector<int> numbers = {number1, number2}; // Nombre d'éléments dans chaque catégorie
       for (int i = 0; i < 2; ++i)
       {
           QString color = colors.at(i);
           QString label = labels.at(i);
           QPieSlice *slice = new QPieSlice(label, numbers.at(i));
           slice->setLabelVisible();
           slice->setPen(QPen(Qt::black, 2));
           slice->setLabelFont(QFont("Arial", 12));
           //Animation au survol
           slice->setExploded();
           // Explosion au clic
           connect(slice, &QPieSlice::clicked, this, [slice, series]() {
               if (slice->isExploded()){
                   slice->setExploded(false);
               }
               else {
                   slice->setExploded();
               }
               for (QPieSlice *otherSlice : series->slices()){
                   if (otherSlice != slice) {
                       otherSlice->setExploded(false);
                   }
               }
           });
           // Définition de la couleur de la tranche
           slice->setBrush(QColor(color));
           // Ajout de la tranche au QPieSeries
           series->append(slice);
       }
       QChart *chart = new QChart();
       chart->addSeries(series);
       chart->setTitle("Pourcentage des centres selon le type du client");
       chart->legend()->setFont(QFont("Arial", 10));
       chart->setBackgroundBrush(QColor("#D6D9DA")); // Couleur de fond
      // Thème du graphique
       //chart->setTheme(QChart::ChartThemeBrownSand);
       // Animation
       QChart::AnimationOptions options = QChart::AllAnimations;
       chart->setAnimationOptions(options);
       QChartView *chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->chart()->setTitleFont(QFont("Arial", 25));
       chartView->resize(1000, 500);
       chartView->chart()->legend()->setAlignment(Qt::AlignBottom);
       chartView->show();

}
void MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}


void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}


void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}
void MainWindow::on_rechercherclient_clicked()

    {

        QString val=ui->lineEdit_rechercheclient->text();

        QString option=ui->check_rechclient->currentText();

        if((val!="")&&(option=="NOM"))

              {ui->tab_client_2->setModel(Cdupe.afficher_NOM(val));}

        else if((val!="")&&(option=="PRENOM"))

        {

             ui->tab_client_2->setModel(Cdupe.afficher_PRENOM(val));

        }

        else if((val!="")&&(option=="ADRESSE"))

        {

             ui->tab_client_2->setModel(Cdupe.afficher_ADRESSE(val));

        }
        else if((val!="")&&(option=="ID"))

        {

             ui->tab_client_2->setModel(Cdupe.afficher_ID(val));

        }
        else if((val!="")&&(option=="TYPEC"))

        {

             ui->tab_client_2->setModel(Cdupe.afficher_TYPEC(val));

        }
        else if((val!="")&&(option=="MAIL"))

        {

             ui->tab_client_2->setModel(Cdupe.afficher_MAIL(val));

        }
        else if((val!="")&&(option=="DATE_PAYEMENT"))

        {

             ui->tab_client_2->setModel(Cdupe.afficher_DATE_PAYEMENT(val));

        }
        else if((val!="")&&(option=="REF"))

        {

             ui->tab_client_2->setModel(Cdupe.afficher_REF(val));

        }
        else if((val!="")&&(option=="RIB"))

        {

             ui->tab_client_2->setModel(Cdupe.afficher_RIB(val));

        }
        else if((val!="")&&(option=="REVENUS"))

        {

             ui->tab_client_2->setModel(Cdupe.afficher_REVENUS(val));

        }

        ui->lineEdit_rechercheclient->setText("");

}
/////////////////////////////////////////////produit/////////////////////////////////////////////

void MainWindow::on_tab_produit_activated(const QModelIndex &index)
{
    QString  VAL = ui->tab_produit->model()->data(index).toString();
    QSqlQuery QRY;
    QSqlQuery QRY1;
    QRY.prepare("SELECT * FROM PRODUIT WHERE refUIT='"+VAL+"'OR TYPE='"+ VAL +"'OR ETAT='"+VAL+"'");
    QRY1.prepare("SELECT * FROM PRODUIT WHERE  QT='"+VAL+"'OR PRIX='"+VAL+"'");
    if(QRY.exec() ){
        while(QRY.next() ){
            ui->lineEdit_REF->setText(QRY.value(0).toString());
            ui->lineEdit_TYPE->setText(QRY.value(1).toString());
            ui->lineEdit_ETAT->setText(QRY.value(2).toString());
            ui->lineEdit_QUANTITE->setText(QRY.value(3).toString());
            ui->lineEdit_PRIX->setText(QRY.value(4).toString());
        }
        }
    if(QRY1.exec() ){
        while(QRY1.next()){
            ui->lineEdit_REF->setText(QRY1.value(0).toString());
            ui->lineEdit_TYPE->setText(QRY1.value(1).toString());
            ui->lineEdit_ETAT->setText(QRY1.value(2).toString());
            ui->lineEdit_QUANTITE->setText(QRY1.value(3).toString());
            ui->lineEdit_PRIX->setText(QRY1.value(4).toString());
        }}

}
void MainWindow::on_UPDATE_clicked()
{
    QString REF_CHOISI=ui->lineEdit_REF->text();
    QString type=ui->lineEdit_TYPE->text();
    QString etat=ui->lineEdit_ETAT->text();
    int qt=ui->lineEdit_QUANTITE->text().toInt();
    int prix=ui->lineEdit_PRIX->text().toInt();
    Produit pm(REF_CHOISI,type,etat,qt,prix);
    bool test = pm.modifier();
    if(test){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("modification effectué\n"),QMessageBox::Cancel);
        ui->tab_produit->setModel(P.afficher());
        ui->lineEdit_REF->clear();
        ui->lineEdit_TYPE->clear();
        ui->lineEdit_ETAT->clear();
        ui->lineEdit_PRIX->clear();
        ui->lineEdit_QUANTITE->clear();
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                              QObject::tr("modification non effectué"),QMessageBox::Cancel);
    }
    createChart();

}
void MainWindow::on_SELL_clicked()
{
    QString REF_CHOISI = ui->lineEdit_REF->text();
    QString type=ui->lineEdit_TYPE->text();
    QString etat=ui->lineEdit_ETAT->text();
    int qt=ui->lineEdit_QUANTITE->text().toInt();
    int prix=ui->lineEdit_PRIX->text().toInt();
    if((etat=="recy" || etat=="RECY") && qt>=100){// QT soit >= 100(parcequ'on ne veut pas une quantite negative et on est entrain de diminuer par100 et le produit deja recyclable
        qt=qt-100;//chaque vente diminue de 100 de son stock
        Produit pvendu(REF_CHOISI,type,etat,qt,prix);
        bool test = pvendu.modifier();
        if(test){
            ETOILES=ETOILES + 1;//l'employe va gagner une etoile de plus
            QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
            trayIcon->setIcon(QIcon(":/path/to/icon.png"));  // Remplacez par le chemin de votre icône
            trayIcon->show();
            QString message = "FELECITATIONS VOUS AVEZ " + QString::number(ETOILES) + "etoiles";
            trayIcon->showMessage("Nouvelle Notification", message, QSystemTrayIcon::Information, 10000);  // 10000 millisecondes (5 secondes)
            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("VENDU ET QT DIMINUE \n"),QMessageBox::Cancel);
            if(ETOILES!=3){
                if(qt==0){
                     QString message = "FELECITATIONS VOUS AVEZ GAGNE UN BADGE" ;
                     //ui->label_NOTIFICATIONS->setText(message);
                     QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
                     trayIcon->setIcon(QIcon(":/path/to/icon.png"));  // Remplacez par le chemin de votre icône
                     trayIcon->show();
                     QString notificationMessage = "FÉLICITATIONS VOUS AVEZ GAGNÉ UN BADGE";
                     trayIcon->showMessage("Nouvelle Notification", notificationMessage, QSystemTrayIcon::Information, 10000);  // 10000 millisecondes (5 secondes)
                        }
            }//fin verifi etoiles
            else if(ETOILES==3){
                QString message = "FELECITATIONS VOUS AVEZ GAGNE UN BADGE" ;
               // ui->label_NOTIFICATIONS->setText(message);
                ETOILES=0;
                QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
                trayIcon->setIcon(QIcon(":/path/to/icon.png"));  // Remplacez par le chemin de votre icône
                trayIcon->show();
                QString notificationMessage = "FÉLICITATIONS VOUS AVEZ GAGNÉ UN BADGE";
                trayIcon->showMessage("Nouvelle Notification", notificationMessage, QSystemTrayIcon::Information, 10000);  // 10000 millisecondes (5 secondes)
            }
        }
        }
        else{QMessageBox::critical(nullptr,QObject::tr("NOT OK"),QObject::tr("STOCK LIMITE OU NON RECYCLABLE CHOISISSEZ UN AUTRE PRODUIT"),QMessageBox::Cancel); }
        ui->lineEdit_REF->clear();
        ui->lineEdit_TYPE->clear();
        ui->lineEdit_ETAT->clear();
        ui->lineEdit_PRIX->clear();
        ui->lineEdit_QUANTITE->clear();
ui->tab_produit->setModel(P.afficher());
createChart();
}

void MainWindow::createChart() {
    QtCharts::QChart *chart = new QtCharts::QChart;
      chart->removeAllSeries();
         QSqlQuery query("SELECT type, etat FROM PRODUIT"); // Extraction des données de la base de données
          QMap<QString, QPair<int, int>> data; // <Type, <R_Count, NR_Count>> // Organiser les données pour le barchart (exemple simplifié)
          while (query.next()) {
                  QString type = query.value("type").toString();
                  QString etat = query.value("etat").toString();
                  if (!data.contains(type)) {
                      data[type] = qMakePair(0, 0);
                  }

                  if (etat == "RECY") {
                      data[type].first++;
                  } else if (etat == "NON RECY") {
                      data[type].second++;
                  }
              }
          // Création du barchart avec Qt Charts
             QtCharts::QBarSeries *series = new QtCharts::QBarSeries;

             for (auto it = data.begin(); it != data.end(); ++it) {
                 QtCharts::QBarSet *set = new QtCharts::QBarSet(it.key());
                 *set << it.value().first << it.value().second;
                 series->append(set);
             }


             chart->setTitle("STATISTIQUES TYPES PRODUITS ETATS");

             QBarCategoryAxis *xAxis = new QBarCategoryAxis();
             QStringList categories;
             categories <<"RECYCLABLE" << "NON RECYCLABLE";// Set the x-axis label
             xAxis->append(categories);
             chart->setAxisX(xAxis, series); // Set the x-axis as a category axis
             chart->axisX()->setTitleText("TYPE");

             QtCharts::QValueAxis *yAxis = new QtCharts::QValueAxis();
             yAxis->setRange(0,8);
             yAxis->setTickCount(9);
             yAxis->setLabelFormat("%d");
             chart->setAxisY(yAxis, series);
             chart->axisY()->setTitleText("STOCK DE PRODUITS");
            chart->addSeries(series);

             QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
             chartView->setRenderHint(QPainter::Antialiasing);
             QWidget *widget = ui->widget_STATISTIQUE;// Create a widget to contain the chartView
             QVBoxLayout *layout = new QVBoxLayout(widget);// Create a layout for the widget (using QVBoxLayout in this case)
             layout->addWidget(chartView);// Add the chartView to the layout
             widget->show();


}

void MainWindow::on_comboBox_TRI_currentIndexChanged()
{
    QString TRI_CHOISI = ui->comboBox_TRI->currentText();
    if(TRI_CHOISI=="REFERENCE"){ui->tab_produit->setModel(P.trier_ref());}
    if(TRI_CHOISI=="TYPE"){ui->tab_produit->setModel(P.trier_type());}
    if(TRI_CHOISI=="ETAT"){ui->tab_produit->setModel(P.trier_etat());}
    if(TRI_CHOISI=="QUANTITE"){ui->tab_produit->setModel(P.trier_quantite());}
    if(TRI_CHOISI=="PRIX"){ui->tab_produit->setModel(P.trier_prix());}

}

void MainWindow::performFilteredSearch()
{
    QString searchText = ui->SEARCH1->text();
    QSqlQueryModel *model = new QSqlQueryModel();
    QString query = "SELECT * FROM produit WHERE";
    bool hasCondition = false;
    // Vérifiez si le texte saisi est un nombre
    bool isNumber;
    int numericValue = searchText.toInt(&isNumber);
    if (isNumber) {
        // Si c'est un nombre, recherchez dans les colonnes numériques
        query += " prix = " + QString::number(numericValue);
        query += " OR qt = " + QString::number(numericValue);
        hasCondition = true;
    } else if (!searchText.isEmpty()) {
        // Si c'est une chaîne de caractères, recherchez dans les colonnes de texte
        query += " ref LIKE '%" + searchText + "%'";
        query += " OR etat LIKE '%" + searchText + "%'";
        query += " OR type LIKE '%" + searchText + "%'";
        hasCondition = true;
    }

    if (!hasCondition) {
        // Si aucune condition n'est spécifiée, afficher tous les produits
        query = "SELECT * FROM produit";
    }

    model->setQuery(query);
    ui->tab_produit->setModel(model);
}
void MainWindow::on_SEARCH1_textChanged()
{
  performFilteredSearch();
}

void MainWindow::on_EXPORT_clicked()
{

    QString filePath = QFileDialog::getSaveFileName(this, tr("Save PDF"), QDir::homePath(), tr("PDF Files (*.pdf)"));

       if (filePath.isEmpty()) {
           // User canceled the operation or didn't choose a file
           return;
       }
       Produit P;
        QPdfWriter pdf(filePath);
          QPainter painter(&pdf);
         int i = 4000;
          painter.setPen(Qt::red);
          painter.setFont(QFont("Arial", 25));
          painter.drawText(1500,1100,"Liste des Produits");
          painter.setPen(Qt::black);
          painter.setFont(QFont("Arial", 15));

          painter.drawRect(100,100,7300,2600);
          painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/ACERPC/Downloads/GUI/logo.png"));
          painter.drawRect(0,3000,9600,500);
          painter.setFont(QFont("Arial", 9));
          painter.drawText(200,3300,"#REF");
          painter.drawText(1300,3300,"TYPE");
          painter.drawText(2200,3300,"ETAT");
          painter.drawText(3000,3300,"PRIX");
          painter.drawText(4400,3300,"QUANTITE");

          QSqlQuery query;
          query.prepare("select * from produit");
          query.exec();
          while (query.next())
          {
              painter.drawText(200,i,query.value(0).toString());
              painter.drawText(1300,i,query.value(1).toString());
              painter.drawText(2300,i,query.value(2).toString());
              painter.drawText(3600,i,query.value(3).toString());
              painter.drawText(4500,i,query.value(4).toString());
              painter.drawText(6200,i,query.value(5).toString());
              i = i + 500;
          }
          P.afficher();
                  QMessageBox::information(nullptr,QObject::tr("Export PDF"),QObject::tr("Export effectué avec succès \n click cancel to exit")
                          ,QMessageBox::Cancel);
}
void MainWindow::on_animation_clicked()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    random_quizz = std::rand() % 3 + 7;
    qDebug()<<random_quizz;
    ui->stackedWidget_7->setCurrentIndex(random_quizz);
}

void MainWindow::on_animation_2_clicked()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    random_quizz = std::rand() % 3+1;
    qDebug()<<random_quizz;
    ui->stackedWidget_7->setCurrentIndex(random_quizz);
}

void MainWindow::on_animation_3_clicked()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    random_quizz = std::rand() % 3+1;
    qDebug()<<random_quizz;
    ui->stackedWidget_7->setCurrentIndex(random_quizz);
}
void MainWindow::on_pushButton_VALIDER_clicked()
{
    if (ui->radioButton_B1->isChecked()) {// Réponse correcte
           score=score+1;
           ANSWERS=ANSWERS+1;
       }
    else{
        if (ui->radioButton_A1->isChecked() ||ui->radioButton_C1->isChecked() || ui->radioButton_D1->isChecked() ) {
                 ANSWERS=ANSWERS+1;// Assurez-vous de déclarer "int score;" dans la classe MainWindow
           }
    }
    if (ui->radioButton_A2->isChecked()) {
           score=score+1;
           ANSWERS=ANSWERS+1;
       }
    else{
        if (ui->radioButton_B2->isChecked() ||ui->radioButton_C2->isChecked() || ui->radioButton_D2->isChecked() ) {// Réponse correcte
                 ANSWERS=ANSWERS+1;
           }
    }
    if (ui->radioButton_C3->isChecked()) {
           score=score+1;
           ANSWERS=ANSWERS+1;
       }
    else{
        if (ui->radioButton_A3->isChecked() ||ui->radioButton_B3->isChecked() || ui->radioButton_D3->isChecked() ) {// Réponse correcte
                 ANSWERS=ANSWERS+1;// Assurez-vous de déclarer "int score;" dans la classe MainWindow
           }
    }
    if (ANSWERS >= 3) {
        nb_fois_dereponses=nb_fois_dereponses+1;
           QString message = "VOUS OBTENEZ :" + QString::number(score) + "/3.";
           ui->label_RESULT->setText(message);
           if (score == 3) {
               ui->label_RESULT->setText(message + "\nFélicitations ! Vous avez répondu correctement à toutes les questions.");
           }
           else {
               if(nb_fois_dereponses==1 || nb_fois_dereponses==2){
                   ui->label_RESULT->setText(message + "\nVOUS AVEZ ENCORE " +  QString::number(3-nb_fois_dereponses) + " ESSAIS");


                   ui->label_RESULT->setText(message + "\nVOUS AVEZ ENCORE " +  QString::number(3-nb_fois_dereponses) + " ESSAIS");
               }
               if(nb_fois_dereponses>=3){
                   ui->label_RESULT->setText(message + "\nNEXT TIME"
                                                       "\nVOICI LES BONNES REPONSES,"
                                                       "\nContinuez à vous informer sur le recyclage !");
                   ui->radioButton_B1->setChecked(true);
                   ui->radioButton_A2->setChecked(true);
                   ui->radioButton_C3->setChecked(true);
                   //QString styleActuel = ui->R2->styleSheet();
                   ui->R2->setStyleSheet("QLabel { color : green; }");
                   //ui->R2->setStyleSheet("color: #00ff00;");
                   ui->R1_2->setStyleSheet("color: #00ff00;");
                   ui->R3_3->setStyleSheet("color: #00ff00;");
                   nb_fois_dereponses=0;}

               }
           ANSWERS=0;

           score=0;

    }
    else{
        QString message = "CONTINUEZ A REPONDRE S'IL VOUS PLAIT";
        ui->label_RESULT->setText(message);
    }
}

void MainWindow::on_pushButton_OK_clicked()
{
    QString ref=ui->lineEdit_REF->text();
    QString type=ui->lineEdit_TYPE->text();
    QString etat=ui->lineEdit_ETAT->text();
    int qt=ui->lineEdit_QUANTITE->text().toInt();
    int prix=ui->lineEdit_PRIX->text().toInt();
    Produit p (ref,type,etat,qt,prix);
    if(p.ajouter() && ! (ui->lineEdit_REF->text().isEmpty() && ui->lineEdit_TYPE->text().isEmpty() && ui->lineEdit_ETAT->text().isEmpty() && ui->lineEdit_PRIX->text().isEmpty() && ui->lineEdit_QUANTITE->text().isEmpty() )){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"),QMessageBox::Cancel);
         ui->tab_produit->setModel(P.afficher());
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                              QObject::tr("Ajout non effectué"),QMessageBox::Cancel);
    }
    ui->lineEdit_REF->clear();
    ui->lineEdit_TYPE->clear();
    ui->lineEdit_ETAT->clear();
    ui->lineEdit_PRIX->clear();
    ui->lineEdit_QUANTITE->clear();
}
void MainWindow::on_pushButton_VALIDER_2_clicked()
{
    if (ui->radioButton_C1_2->isChecked()) {// Réponse correcte
           score=score+1;
           ANSWERS=ANSWERS+1;
       }
    else{
        if (ui->radioButton_A1_2->isChecked() ||ui->radioButton_B1_2->isChecked() || ui->radioButton_D1_2->isChecked() ) {
                 ANSWERS=ANSWERS+1;// Assurez-vous de déclarer "int score;" dans la classe MainWindow
           }}

    if (ui->radioButton_A2_2->isChecked()) {
           score=score+1;
           ANSWERS=ANSWERS+1;
       }
    else{
        if (ui->radioButton_B2_2->isChecked() ||ui->radioButton_C2_2->isChecked() || ui->radioButton_D2_2->isChecked() ) {// Réponse correcte
                 ANSWERS=ANSWERS+1;
           }
    }
    if (ui->radioButton_C3_2->isChecked()) {
           score=score+1;
           ANSWERS=ANSWERS+1;
       }
    else{
        if (ui->radioButton_A3_2->isChecked() ||ui->radioButton_B3_2->isChecked() || ui->radioButton_D3_2->isChecked() ) {// Réponse correcte
                 ANSWERS=ANSWERS+1;// Assurez-vous de déclarer "int score;" dans la classe MainWindow
           }
    }
    if (ANSWERS >= 3) {
        nb_fois_dereponses=nb_fois_dereponses+1;
           QString message = "VOUS OBTENEZ :" + QString::number(score) + "/3.";
           ui->label_RESULT_2->setText(message);
           if (score == 3) {
               ui->label_RESULT_2->setText(message + "\nFélicitations ! Vous avez répondu correctement à toutes les questions.");
           }
           else {
               if(nb_fois_dereponses==1 || nb_fois_dereponses==2){
                   ui->label_RESULT_2->setText(message + "\nVOUS AVEZ ENCORE " +  QString::number(3-nb_fois_dereponses) + " ESSAIS");


                   ui->label_RESULT_2->setText(message + "\nVOUS AVEZ ENCORE " +  QString::number(3-nb_fois_dereponses) + " ESSAIS");
               }
               if(nb_fois_dereponses>=3){
                   ui->label_RESULT_2->setText(message + "\nNEXT TIME"
                                                       "\nVOICI LES BONNES REPONSES,"
                                                       "\nContinuez à vous informer sur le recyclage !");
                   ui->radioButton_C1_2->setChecked(true);
                   ui->radioButton_A2_2->setChecked(true);
                   ui->radioButton_C3_2->setChecked(true);
                   /*QString styleActuel = ui->R2->styleSheet();
                   ui->R2->setStyleSheet("QLabel { color : green; }");
                   //ui->R2->setStyleSheet("color: #00ff00;");
                   ui->R1_2->setStyleSheet("color: #00ff00;");
                   ui->R3_3->setStyleSheet("color: #00ff00;");*/
                   nb_fois_dereponses=0;}

               }
           score=0;
           ANSWERS=0;


    }
    else{
        QString message = "CONTINUEZ A REPONDRE S'IL VOUS PLAIT";
        ui->label_RESULT_2->setText(message);
    }
}
void MainWindow::on_pushButton_VALIDER_3_clicked()
{
    if (ui->radioButton_D1_3->isChecked()) {// Réponse correcte
           score=score+1;
           ANSWERS=ANSWERS+1;
       }
    else{
        if (ui->radioButton_A1_3->isChecked() ||ui->radioButton_B1_3->isChecked() || ui->radioButton_C1_3->isChecked() ) {
                 ANSWERS=ANSWERS+1;// Assurez-vous de déclarer "int score;" dans la classe MainWindow
           }
    }

    if (ui->radioButton_D2_3->isChecked()) {
           score=score+1;
           ANSWERS=ANSWERS+1;
       }
    else{
        if (ui->radioButton_B2_3->isChecked() ||ui->radioButton_C2_3->isChecked() || ui->radioButton_A2_3->isChecked() ) {// Réponse correcte
                 ANSWERS=ANSWERS+1;
           }
    }
    if (ui->radioButton_B3_3->isChecked()) {
           score=score+1;
           ANSWERS=ANSWERS+1;
       }
    else{
        if (ui->radioButton_A3_3->isChecked() ||ui->radioButton_C3_3->isChecked() || ui->radioButton_D3_3->isChecked() ) {// Réponse correcte
                 ANSWERS=ANSWERS+1;// Assurez-vous de déclarer "int score;" dans la classe MainWindow
           }
    }
    if (ANSWERS >= 3) {
        nb_fois_dereponses=nb_fois_dereponses+1;
           QString message = "VOUS OBTENEZ :" + QString::number(score) + "/3.";
           ui->label_RESULT_3->setText(message);
           if (score == 3) {
               ui->label_RESULT_2->setText(message + "\nFélicitations ! Vous avez répondu correctement à toutes les questions.");
           }
           else {
               if(nb_fois_dereponses==1 || nb_fois_dereponses==2){
                   ui->label_RESULT_3->setText(message + "\nVOUS AVEZ ENCORE " +  QString::number(3-nb_fois_dereponses) + " ESSAIS");


                   ui->label_RESULT_3->setText(message + "\nVOUS AVEZ ENCORE " +  QString::number(3-nb_fois_dereponses) + " ESSAIS");
               }
               if(nb_fois_dereponses>=3){
                   ui->label_RESULT_3->setText(message + "\nNEXT TIME"
                                                       "\nVOICI LES BONNES REPONSES,"
                                                       "\nContinuez à vous informer sur le recyclage !");
                   ui->radioButton_D1_3->setChecked(true);
                   ui->radioButton_D2_3->setChecked(true);
                   ui->radioButton_B3_3->setChecked(true);
                   /*QString styleActuel = ui->R2->styleSheet();
                   ui->R2->setStyleSheet("QLabel { color : green; }");
                   //ui->R2->setStyleSheet("color: #00ff00;");
                   ui->R1_2->setStyleSheet("color: #00ff00;");
                   ui->R3_3->setStyleSheet("color: #00ff00;");*/
                   nb_fois_dereponses=0;}

               }

           score=0;
           ANSWERS=0;

    }
    else{
        QString message = "CONTINUEZ A REPONDRE S'IL VOUS PLAIT";
        ui->label_RESULT_3->setText(message);
    }
}
void MainWindow::on_stats_clicked()
{
    createChart();
    ui->stackedWidget_5->setCurrentIndex(1);
}

void MainWindow::on_pushButton_30_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(0);
}
void MainWindow::on_SEARCH_textChanged()
{
    performFilteredSearch();
}

void MainWindow::on_supp_clicked()
{
    Produit p1;
    QString REF_CHOISI = ui->lineEdit_REF->text();
    p1.setref(REF_CHOISI);
    bool test = p1.supprimer(p1.getref());
    if(test ){
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("suppression effectué\n"),QMessageBox::Cancel);
        ui->tab_produit->setModel(P.afficher());
        ui->lineEdit_REF->clear();
        ui->lineEdit_TYPE->clear();
        ui->lineEdit_ETAT->clear();
        ui->lineEdit_PRIX->clear();
        ui->lineEdit_QUANTITE->clear();
    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                              QObject::tr("suppression non effectué"),QMessageBox::Cancel);
    }
    createChart();
}


////////////////////////////employe////////////////////////////

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
       int row = index.row();
       QString cinValue = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toString();
       QSqlQuery query;
       query.prepare("SELECT Nom,Prenom,Datenaiss,salaire,poste,depart FROM employe WHERE CIN = :val");
       query.bindValue(":val", cinValue);
       if (query.exec() && query.next()) {
           ui->CIN_modf->setText(cinValue);
           ui->nom_modf->setText(query.value(0).toString());
           ui->prenom_modf->setText(query.value(1).toString());
           ui->date_modf->setDate(query.value(2).toDate());
           ui->salaire_modf->setText(query.value(3).toString());
           ui->poste_modf->setCurrentText(query.value(4).toString());
           ui->depart_modf->setCurrentText(query.value(5).toString());
           ui->stackedWidget_3->setCurrentIndex(2);
       }
}


void MainWindow::on_add_main_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
    A.write_to_arduino("6");
}

void MainWindow::on_refresh_main_clicked()
{
    ui->tableView->setModel(EMP.afficher());
}


void MainWindow::on_Add_clicked()
{
    int CIN=ui->CIN->text().toInt();
    QString Nom=ui->nom->text();
    QString Prenom=ui->prenom->text();
    QDate date=ui->date->date();
    QString poste=ui->poste->currentText();
    QString depart=ui->depart->currentText();
    float salaire=ui->salaire->text().toFloat();
    QByteArray card = A.read_from_arduino();
    QString log=ui->CIN->text();
    if((CIN<1000000) | (CIN>99999999)){
        QMessageBox::critical(nullptr, QObject::tr("Error detected"),QObject::tr("Verify your CIN !!\n"),QMessageBox::Ok);
    }
    else{
        employe E(CIN,Nom,Prenom,salaire,date,poste,depart,log,"0000",card);
        if(card==""){
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),QObject::tr("Please insert your rfid card !!\n"),QMessageBox::Ok);
        }
        else{
            QSqlQuery quer;
            quer.prepare("select * from employe where CARD_UID like '"+card+"'");
            if(quer.exec() && quer.next()){
                QMessageBox::critical(nullptr, QObject::tr("ERROR"),QObject::tr("CARD ALREADY EXISTS!!\n"),QMessageBox::Ok);
            }
            else{
                ui->card_uid->setText(card);
                if(E.ajouter()){
                    QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Ajout effectué\n"),QMessageBox::Ok);
                    ui->CIN->clear();
                    ui->nom->clear();
                    ui->prenom->clear();
                    QDate D(2000,1,1);
                    ui->date->setDate(D);
                    ui->poste->setCurrentIndex(0);
                    ui->depart->setCurrentIndex(0);
                    ui->salaire->clear();
                    ui->card_uid->clear();
                    ui->tableView->setModel(EMP.afficher());
                    ui->stackedWidget_3->setCurrentIndex(0);
                }
                else{
                    QMessageBox::critical(nullptr, QObject::tr("NOT OK"),QObject::tr("Ajout non effectué !!\n"),QMessageBox::Ok);
                }
            }
        }
    }
}

void MainWindow::on_sort_main_clicked()
{
    ui->tableView->setModel(EMP.trier(ui->sort_option_main->currentText()));
}

void MainWindow::on_Export_main_clicked()
{
    QString defaultFileName = "Employee.pdf"; // Default file name
    QString saveFilePath = QFileDialog::getSaveFileName(this, tr("Export PDF"), QDir::homePath() + "/" + defaultFileName, tr("PDF Files (*.pdf)"));

    if (!saveFilePath.isEmpty()) {
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFileName(saveFilePath);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFormat(QPrinter::PdfFormat);

        QPainter painter(&printer);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

        QAbstractItemModel* model = ui->tableView->model();

        if (model) {
            int rowCount = model->rowCount();
            int columnCount = model->columnCount();

            // Create a QTextDocument to format the data as an HTML table
            QTextDocument doc;
            QTextCursor cursor(&doc);

            // Adjust the font size to make the text larger
            QString tableHtml = "<table style=\"border-collapse: collapse; width: 100%; border: 1px solid black; font-size: 4px;\">";

            // Add table header
            tableHtml += "<tr style=\"background-color: #ccc;\">";
            for (int col = 0; col < columnCount - 2; ++col) { // Exclude the last 2 columns
                QVariant data = model->headerData(col, Qt::Horizontal);
                tableHtml += "<th style=\"border: 1px solid black; padding: 8px;\">" + data.toString() + "</th>";
            }
            tableHtml += "</tr>";

            // Loop through the rows and columns to populate the table
            for (int row = 0; row < rowCount; ++row) {
                tableHtml += "<tr>";
                for (int col = 0; col < columnCount - 2; ++col) { // Exclude the last 2 columns
                    QModelIndex index = model->index(row, col);
                    QVariant data = model->data(index);

                    // Append the data to the table cell with border and adjusted font size
                    tableHtml += "<td style=\"border: 1px solid black; padding: 8px;\">" + data.toString() + "</td>";
                }
                tableHtml += "</tr>";
            }

            tableHtml += "</table>";

            // Set the HTML content for the QTextDocument
            doc.setHtml(tableHtml);

            // Manually scale the painter by a factor of 100
            painter.scale(30.0, 30.0);

            // Render the QTextDocument onto the PDF
            doc.setPageSize(printer.pageRect().size());
            doc.drawContents(&painter);
        }

        painter.end();
    }
}

void MainWindow::on_modify_clicked()
{
    int CIN=ui->CIN_modf->text().toInt();
    QString Nom=ui->nom_modf->text();
    QString Prenom=ui->prenom_modf->text();
    QDate date=ui->date_modf->date();
    QString poste=ui->poste_modf->currentText();
    QString depart=ui->depart_modf->currentText();
    float salaire=ui->salaire_modf->text().toFloat();
    QString log=ui->CIN->text();
    employe E(CIN,Nom,Prenom,salaire,date,poste,depart,log,"0000","");
    if(E.modifier()){
        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Modification effectué\n"),QMessageBox::Ok);
        ui->tableView->setModel(EMP.afficher());
        ui->stackedWidget_3->setCurrentIndex(0);
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),QObject::tr("Modification non effectué !!\n"),QMessageBox::Ok);
    }
}

void MainWindow::on_Delete_modf_clicked()
{
    int CIN=ui->CIN_modf->text().toInt();
    QString Nom=ui->nom_modf->text();
    QString Prenom=ui->prenom_modf->text();
    QDate date=ui->date_modf->date();
    QString poste=ui->poste_modf->currentText();
    QString depart=ui->depart_modf->currentText();
    float salaire=ui->salaire_modf->text().toFloat();
    QString log=ui->CIN_modf->text();
    employe E(CIN,Nom,Prenom,salaire,date,poste,depart,log,"0000","");
    if(E.supprimer(CIN)){
        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Suppression effectué\n"),QMessageBox::Ok);
        ui->tableView->setModel(EMP.afficher());
        ui->stackedWidget_3->setCurrentIndex(0);
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),QObject::tr("Suppression non effectué !!\n"),QMessageBox::Ok);
    }
}

void MainWindow::on_search_for_main_textChanged()
{
    ui->tableView->setModel(EMP.rechercher(ui->search_for_main->text()));
}
void MainWindow::on_SIGNIN_clicked()
{
    QString log=ui->login->text();
    QString pass=ui->password->text();
    if(EMP.search(log,pass)){
        QMessageBox::information(nullptr, QObject::tr("Connected Successfully"),QObject::tr("Welcome\n"),QMessageBox::Ok);
        recordTime("connection_log.txt", "User connected",log);
        ui->stackedWidget_main->setCurrentIndex(1);
        /////////////////////////////////////////////////////////////droits d'access/////////////////////////////////////////////////////////
        QSqlQuery query, query1;
        query.prepare("SELECT poste,nom FROM employe WHERE login=:login AND password=:password");//+nom
        query.bindValue(":login", log);
        query.bindValue(":password", pass);

        if (query.exec() && query.next()) {
            ui->login->clear();
            ui->password->clear();
            // Retrieve values
            QString poste = query.value(0).toString();
            QString nom = query.value(1).toString();
            qDebug() << "Nom:" << nom;
            query1.prepare("SELECT depart FROM employe WHERE login=:login AND password=:password");
            query1.bindValue(":login", log);
            query1.bindValue(":password", pass);
            qDebug() << "Poste:" << poste;
            if (query1.exec() && query1.next()) {
                // Retrieve values
                QString depart = query1.value(0).toString();
                qDebug() << "Department:" << depart;
                ui->gestion_employes->setDisabled(true);
                ui->gestion_centre->setDisabled(true);
                ui->gestion_produit->setDisabled(true);
                ui->gestion_client->setDisabled(true);
                QString commonStylesheet = "QPushButton {"
                                           "    color: rgb(218, 218, 218);"
                                           "    background-color: rgba(0, 0, 0, 0.3%);"
                                           "    border-radius: 25px;"
                                           "    font: 500 15pt 'Segoe UI';"
                                           "}";
                    ui->gestion_employes->setStyleSheet(commonStylesheet);
                    ui->gestion_produit->setStyleSheet(commonStylesheet);
                    ui->gestion_client->setStyleSheet(commonStylesheet);
                    ui->gestion_centre->setStyleSheet(commonStylesheet);
                ui->username->setText(nom);
                if (poste == "Employe") {
                    if (depart == "Gestion des employes") {
                        ui->gestion_employes->setDisabled(false);
                        ui->gestion_employes->setStyleSheet("QPushButton { background-color: rgba(26, 180, 240, 125); color: rgb(0, 255, 255); border-radius: 25px; border: 2px solid rgb(170, 255, 255); font: 500 15pt 'Segoe UI'; } QPushButton:pressed { color: rgb(0, 255, 255); background-color: rgba(26, 180, 240, 180); border: 2px solid rgb(120, 200, 220); }");

                    }
                    else if (depart == "Gestion des clients") {
                        ui->gestion_client->setDisabled(false);
                        ui->gestion_client->setStyleSheet("QPushButton { background-color: rgba(26, 180, 240, 125); color: rgb(0, 255, 255); border-radius: 25px; border: 2px solid rgb(170, 255, 255); font: 500 15pt 'Segoe UI'; } QPushButton:pressed { color: rgb(0, 255, 255); background-color: rgba(26, 180, 240, 180); border: 2px solid rgb(120, 200, 220); }");

                    }
                    else if (depart == "Gestion des produits") {
                        ui->gestion_produit->setDisabled(false);
                        ui->gestion_produit->setStyleSheet("QPushButton { background-color: rgba(26, 180, 240, 125); color: rgb(0, 255, 255); border-radius: 25px; border: 2px solid rgb(170, 255, 255); font: 500 15pt 'Segoe UI'; } QPushButton:pressed { color: rgb(0, 255, 255); background-color: rgba(26, 180, 240, 180); border: 2px solid rgb(120, 200, 220); }");

                    }
                    else if (depart == "Gestion des centres de collectes") {
                        ui->gestion_centre->setDisabled(false);
                        ui->gestion_centre->setStyleSheet("QPushButton { background-color: rgba(26, 180, 240, 125); color: rgb(0, 255, 255); border-radius: 25px; border: 2px solid rgb(170, 255, 255); font: 500 15pt 'Segoe UI'; } QPushButton:pressed { color: rgb(0, 255, 255); background-color: rgba(26, 180, 240, 180); border: 2px solid rgb(120, 200, 220); }");

                    }
                }
                else if(poste == "Administrateur"){
                    ui->gestion_employes->setDisabled(false);
                    ui->gestion_centre->setDisabled(false);
                    ui->gestion_produit->setDisabled(false);
                    ui->gestion_client->setDisabled(false);
                    ui->gestion_centre->setStyleSheet("QPushButton { background-color: rgba(26, 180, 240, 125); color: rgb(0, 255, 255); border-radius: 25px; border: 2px solid rgb(170, 255, 255); font: 500 15pt 'Segoe UI'; } QPushButton:pressed { color: rgb(0, 255, 255); background-color: rgba(26, 180, 240, 180); border: 2px solid rgb(120, 200, 220); }");

                    ui->gestion_client->setStyleSheet("QPushButton { background-color: rgba(26, 180, 240, 125); color: rgb(0, 255, 255); border-radius: 25px; border: 2px solid rgb(170, 255, 255); font: 500 15pt 'Segoe UI'; } QPushButton:pressed { color: rgb(0, 255, 255); background-color: rgba(26, 180, 240, 180); border: 2px solid rgb(120, 200, 220); }");

                    ui->gestion_produit->setStyleSheet("QPushButton { background-color: rgba(26, 180, 240, 125); color: rgb(0, 255, 255); border-radius: 25px; border: 2px solid rgb(170, 255, 255); font: 500 15pt 'Segoe UI'; } QPushButton:pressed { color: rgb(0, 255, 255); background-color: rgba(26, 180, 240, 180); border: 2px solid rgb(120, 200, 220); }");

                    ui->gestion_employes->setStyleSheet("QPushButton { background-color: rgba(26, 180, 240, 125); color: rgb(0, 255, 255); border-radius: 25px; border: 2px solid rgb(170, 255, 255); font: 500 15pt 'Segoe UI'; } QPushButton:pressed { color: rgb(0, 255, 255); background-color: rgba(26, 180, 240, 180); border: 2px solid rgb(120, 200, 220); }");

                }
            } else {
                qDebug() << "Query failed for depart:" << query1.lastError().text();
            }
        } else {
            qDebug() << "Query failed for poste:" << query.lastError().text();
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Connected error"),QObject::tr("Check your login\n"),QMessageBox::Ok);
    }
}

void MainWindow::recordTime(const QString &filename, const QString &event, const QString &userName) {
    // Get the current date and time
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString timeEvent = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

    // Open the file in append mode
    QFile file(filename);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);

        // Write the time event and user name to the file
        out << event << " at: " << timeEvent << " by user: " << userName << "\n";

        // Close the file
        file.close();
    } else {
        qDebug() << "Error opening the file for writing";
    }
}

void MainWindow::on_disconnect_clicked()
{
    ui->stackedWidget_main->setCurrentIndex(0);
    recordTime("connection_log.txt", "User disconnected",ui->login->text());
}
QString MainWindow::generate_Code(){
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    // Generate a random number between 100000 and 999999
    int code = std::rand() % 900000 + 100000;
    return QString::number(code);
}

void MainWindow::on_chatbox_2_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(3);
}

void MainWindow::on_pushButton_31_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0);
}
void MainWindow::on_pushButton_32_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0);
}

void MainWindow::on_pushButton_33_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0);
}

/////////////////////////arduino/////////////////////////////////////



void MainWindow::on_reset_clicked()
{
    ui->stackedWidget_main->setCurrentIndex(2);
    A.write_to_arduino("1");
}

void MainWindow::on_next_clicked()
{
    if(ui->id_reset->text()!=""){
        QSqlQuery query;
        QString CIN=ui->id_reset->text();
        query.prepare("select * from employe where CIN like '%"+CIN+"%'");
        if(query.exec() && query.next()){
            ui->stackedWidget_main->setCurrentIndex(3);
            A.write_to_arduino("2");
        }
        else{
            QMessageBox::critical(nullptr, QObject::tr("ERROR"),QObject::tr("User not found!!\n"),QMessageBox::Ok);
        }
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("ERROR"),QObject::tr("Invalid CIN!!\n"),QMessageBox::Ok);
    }
}
void MainWindow::on_next_3_clicked()
{
    QByteArray receivedData = A.read_from_arduino();
    QSqlQuery query;
    query.prepare("select CARD_UID from employe where CIN like '%"+ui->id_reset->text()+"%'");
    if(query.exec() && query.next()){
        if(query.value(0)==receivedData){
            ui->stackedWidget_main->setCurrentIndex(4);
            set_Code(generate_Code());
            A.write_to_arduino("5" + Code.toUtf8() + "\n");
            QMessageBox::information(nullptr, QObject::tr("Done"),QObject::tr("Welcome!!!\n"),QMessageBox::Ok);
        }
        else{
            QMessageBox::critical(nullptr, QObject::tr("ERROR"),QObject::tr("CARD UID not compatible with the given CIN\n"),QMessageBox::Ok);
        }
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("ERROR"),QObject::tr("Couldn't find your CARD UID\n"),QMessageBox::Ok);
    }
}
void MainWindow::on_next_2_clicked()
{
    if(ui->code->text()==Code){
        ui->stackedWidget_main->setCurrentIndex(5);
        ui->code->clear();
        A.write_to_arduino("3");
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("ERROR"),QObject::tr("Invalid code!!\n"),QMessageBox::Ok);
    }
}

void MainWindow::on_confirm_clicked()
{
    if(ui->new_pass->text()==ui->confirm_pass->text()){
        QString password=ui->new_pass->text();
        if (password.isEmpty()) {
            qDebug() << "Password is empty!";
            return;
        }
        QSqlQuery query;
        QString CIN=ui->id_reset->text();
        query.prepare("UPDATE EMPLOYE SET PASSWORD=:PASSWORD WHERE CIN=:CIN");
        query.bindValue(":CIN",CIN);
        query.bindValue(":PASSWORD",password);
        query.exec();
        ui->new_pass->clear();
        ui->confirm_pass->clear();
        ui->id_reset->clear();
        A.write_to_arduino("4");
        QMessageBox::information(nullptr, QObject::tr("Done"),QObject::tr("Password changed successfully\n"),QMessageBox::Ok);
        ui->stackedWidget_main->setCurrentIndex(0);
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("ERROR"),QObject::tr("Check your password!!\n"),QMessageBox::Ok);
    }
}

void MainWindow::on_back_5_clicked()
{
    ui->stackedWidget_main->setCurrentIndex(0);
}

void MainWindow::on_back_6_clicked()
{
    ui->stackedWidget_main->setCurrentIndex(2);
}

void MainWindow::on_back_7_clicked()
{
    ui->stackedWidget_main->setCurrentIndex(3);
}

void MainWindow::update_label(){
    QByteArray card = A.read_from_arduino();
    QSqlQuery quer;
    quer.prepare("select * from employe where CARD_UID like '"+card+"'");
    if(quer.exec() && quer.next()){
        QMessageBox::critical(nullptr, QObject::tr("ERROR"),QObject::tr("CARD ALREADY EXISTS!!\n"),QMessageBox::Ok);
    }
    else{
        ui->card_uid->setText(card);
    }

}

void MainWindow::on_back_8_clicked()
{
    ui->stackedWidget_main->setCurrentIndex(0);
}

void MainWindow::on_SIGNUP_clicked()
{
    ui->stackedWidget_main->setCurrentIndex(6);
}

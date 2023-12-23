#include "bookroomdialog.h"
#include "ui_bookroomdialog.h"

// Constructeur de la classe BookRoomDialog
BookRoomDialog::BookRoomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookRoomDialog)
{
    // Initialise l'interface utilisateur
    ui->setupUi(this);

    // Fixe la taille de la fenêtre à 320x240 pixels
    this->setFixedSize(320,240);

    // Chemin de l'icône à utiliser pour la fenêtre
    QString iconPath = "C:/Users/aziz/Desktop/Hotel_Management_in_QT/icons8-hôtel-emoji-48.png";

                       // Définir l'icône de la fenêtre principale
    this->setWindowIcon(QIcon(iconPath));
}

// Méthode pour lire les données des chambres
void BookRoomDialog::readData()
{
    qDebug()<<"BookRoomDialog:readData";

    // Obtient la liste des numéros de chambre disponibles (filtrées par "y")
    std::vector<int> rooms = Hotel::getInstance()->getRoomList("y");

    // Efface la liste déroulante des chambres
    this->ui->cmbRoomList->clear();

    // Ajoute chaque numéro de chambre à la liste déroulante
    for(std::vector<int>::iterator it = rooms.begin(); it!=rooms.end(); it++ )
    {
        this->ui->cmbRoomList->addItem(QString::number(*it));
    }
}

// Destructeur de la classe BookRoomDialog
BookRoomDialog::~BookRoomDialog()
{
    // Libère la mémoire occupée par l'interface utilisateur
    delete ui;
}

// Slot déclenché lorsqu'on clique sur le bouton d'annulation
void BookRoomDialog::on_btnCancel_clicked()
{
    // Cache la fenêtre de dialogue
    this->hide();
}

// Slot déclenché lorsqu'on clique sur le bouton de soumission
void BookRoomDialog::on_btnSubmit_clicked()
{
    // Récupère les données saisies par l'utilisateur
    int roomno = ui->cmbRoomList->currentText().toInt();
    QString name = ui->txtName->text();
    QString contactno = ui->txtContactNumber->text();
    QString address = ui->txtAddress->toPlainText();
    QString govtid = ui->txtIdProof->text();

    // Vérifie si le numéro de chambre est valide
    if(roomno < 1)
    {
        // Affiche un avertissement si aucune chambre n'est disponible
        QMessageBox::information(
            this,
            tr("Warning!"),
            tr("We are sold out. No room is available") );
        return;
    }

    // Appelle la méthode BookRoom de l'objet Hotel avec les données fournies
    int ret = Hotel::getInstance()->BookRoom(roomno, name, contactno, govtid, address);

    // Affiche un message indiquant le succès ou l'échec de la réservation
    QString msg = "";
    ret == 0 ? msg = "Success!" : msg = "Failure!";

    // Cache la fenêtre de dialogue
    this->hide();

    // Affiche un message d'information en cas de succès
    if(ret == 0)
    {
        QMessageBox::information(
            this,
            tr("Success!"),
            tr("Room has been booked! Please ask for Govt. Id from customer") );
    }
}

#include "checkoutdialog.h"
#include "ui_checkoutdialog.h"
#include "QDebug"

// Constructeur de la classe CheckOutDialog
CheckOutDialog::CheckOutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckOutDialog)
{
    // Initialise l'interface utilisateur
    ui->setupUi(this);

    // Fixe la taille de la fenêtre à 320x180 pixels
    this->setFixedSize(320,180);

    // Affiche un message de débogage dans la console
    qDebug()<<"in constructor of CheckOutDialog";

    // Chemin de l'icône à utiliser pour la fenêtre
    QString iconPath = "C:/Users/aziz/Desktop/Hotel_Management_in_QT/icons8-hôtel-emoji-48.png";

                       // Définir l'icône de la fenêtre principale
                       this->setWindowIcon(QIcon(iconPath));
}

// Méthode pour lire les données des chambres pour le check-out
void CheckOutDialog::readData()
{
    // Obtient la liste des numéros de chambre occupées (filtrées par "n")
    std::vector<int> rooms = Hotel::getInstance()->getRoomList("n");

    // Efface la liste déroulante des chambres
    this->ui->cmbRoomList->clear();

    // Variable pour indiquer si des chambres sont disponibles
    char flag = 0;

    // Ajoute chaque numéro de chambre occupée à la liste déroulante
    for(std::vector<int>::iterator it = rooms.begin(); it!=rooms.end(); it++ )
    {
        this->ui->cmbRoomList->addItem(QString::number(*it));
        flag = 1;
    }

    // Active le bouton de check-out s'il y a des chambres disponibles
    if(flag == 1)
        this->ui->btnCheckout->setEnabled(true);
}

// Destructeur de la classe CheckOutDialog
CheckOutDialog::~CheckOutDialog()
{
    // Libère la mémoire occupée par l'interface utilisateur
    delete ui;
}

// Slot déclenché lorsqu'on clique sur le bouton d'annulation
void CheckOutDialog::on_btnCancel_clicked()
{
    // Cache la fenêtre de dialogue
    this->hide();
}

// Slot déclenché lorsqu'on clique sur le bouton de check-out
void CheckOutDialog::on_btnCheckout_clicked()
{
    // Récupère le numéro de chambre sélectionné
    int roomno = ui->cmbRoomList->currentText().toInt();

    // Vérifie si le numéro de chambre est valide
    if(roomno < 1)
    {
        // Affiche un avertissement s'il n'y a pas de chambre à vérifier
        QMessageBox::information(
            this,
            tr("Warning!"),
            tr("No room to Check out") );
        return;
    }

    // Appelle la méthode CheckOut de l'objet Hotel avec le numéro de chambre
    int ret = Hotel::getInstance()->CheckOut(roomno);

    // Affiche un message indiquant le succès ou l'échec du check-out
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
            tr("Room has been Check-out! Say thank you to Customer") );
    }
}

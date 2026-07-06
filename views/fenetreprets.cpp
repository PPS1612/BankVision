#include "FenetrePrets.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QFrame>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QFont>
#include <QVector>
#include <cmath>

FenetrePrets::FenetrePrets(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("BankVision - Prêts");
    resize(1200, 720);

    construireInterface();
    appliquerStyle();
    chargerDonneesTest();
}

void FenetrePrets::construireInterface()
{
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(34, 34, 34, 34);
    layoutPrincipal->setSpacing(18);

    QLabel* titre = new QLabel("Gestion des prêts");
    titre->setObjectName("titre");

    labelNombrePrets = new QLabel("0 prêt enregistré");
    labelNombrePrets->setObjectName("nombrePrets");

    champRecherche = new QLineEdit;
    champRecherche->setPlaceholderText("🔍  Rechercher un prêt (client ou statut)...");
    champRecherche->setFixedHeight(54);

    boutonNouveauPret = new QPushButton("+  Nouveau prêt");
    boutonNouveauPret->setFixedHeight(54);
    boutonNouveauPret->setFixedWidth(230);
    boutonNouveauPret->setCursor(Qt::PointingHandCursor);
    boutonNouveauPret->setObjectName("boutonPrincipal");

    QHBoxLayout* layoutRecherche = new QHBoxLayout;
    layoutRecherche->setSpacing(22);
    layoutRecherche->addWidget(champRecherche);
    layoutRecherche->addWidget(boutonNouveauPret);

    QFrame* carteTable = new QFrame;
    carteTable->setObjectName("carteTable");

    QGraphicsDropShadowEffect* shadowTable = new QGraphicsDropShadowEffect;
    shadowTable->setBlurRadius(22);
    shadowTable->setOffset(0, 6);
    shadowTable->setColor(QColor(15, 23, 42, 30));
    carteTable->setGraphicsEffect(shadowTable);

    QVBoxLayout* layoutTable = new QVBoxLayout(carteTable);
    layoutTable->setContentsMargins(0, 0, 0, 0);
    layoutTable->setSpacing(0);

    tablePrets = new QTableWidget;
    tablePrets->setColumnCount(7);
    tablePrets->setRowCount(0);

    tablePrets->setHorizontalHeaderLabels({
        "ID", "Client", "Montant", "Taux annuel", "Durée (mois)", "Mensualité", "Statut"
    });

    tablePrets->verticalHeader()->setVisible(false);
    tablePrets->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tablePrets->horizontalHeader()->setFixedHeight(56);
    tablePrets->verticalHeader()->setDefaultSectionSize(62);

    tablePrets->setSelectionBehavior(QAbstractItemView::SelectRows);
    tablePrets->setSelectionMode(QAbstractItemView::SingleSelection);
    tablePrets->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tablePrets->setShowGrid(false);
    tablePrets->setAlternatingRowColors(true);
    tablePrets->setFocusPolicy(Qt::NoFocus);

    layoutTable->addWidget(tablePrets);

    boutonAccepter = new QPushButton("✔  Accepter");
    boutonRefuser = new QPushButton("✕  Refuser");
    boutonRembourser = new QPushButton("↺  Rembourser");
    boutonSupprimer = new QPushButton("🗑  Supprimer");
    boutonFermer = new QPushButton("●  Fermer");
    boutonActualiser = new QPushButton("↻  Actualiser");

    boutonAccepter->setObjectName("boutonAccepter");
    boutonRefuser->setObjectName("boutonDanger");
    boutonRembourser->setObjectName("boutonModifier");
    boutonSupprimer->setObjectName("boutonDanger");
    boutonFermer->setObjectName("boutonDanger");
    boutonActualiser->setObjectName("boutonActualiser");

    boutonAccepter->setFixedSize(150, 54);
    boutonRefuser->setFixedSize(140, 54);
    boutonRembourser->setFixedSize(170, 54);
    boutonSupprimer->setFixedSize(160, 54);
    boutonFermer->setFixedSize(140, 54);
    boutonActualiser->setFixedSize(180, 54);

    boutonAccepter->setCursor(Qt::PointingHandCursor);
    boutonRefuser->setCursor(Qt::PointingHandCursor);
    boutonRembourser->setCursor(Qt::PointingHandCursor);
    boutonSupprimer->setCursor(Qt::PointingHandCursor);
    boutonFermer->setCursor(Qt::PointingHandCursor);
    boutonActualiser->setCursor(Qt::PointingHandCursor);

    QHBoxLayout* layoutBoutons = new QHBoxLayout;
    layoutBoutons->setSpacing(14);
    layoutBoutons->addWidget(boutonAccepter);
    layoutBoutons->addWidget(boutonRefuser);
    layoutBoutons->addWidget(boutonRembourser);
    layoutBoutons->addWidget(boutonSupprimer);
    layoutBoutons->addWidget(boutonFermer);
    layoutBoutons->addStretch();
    layoutBoutons->addWidget(boutonActualiser);

    layoutPrincipal->addWidget(titre);
    layoutPrincipal->addWidget(labelNombrePrets);
    layoutPrincipal->addLayout(layoutRecherche);
    layoutPrincipal->addSpacing(12);
    layoutPrincipal->addWidget(carteTable);
    layoutPrincipal->addSpacing(12);
    layoutPrincipal->addLayout(layoutBoutons);

    connect(boutonNouveauPret, &QPushButton::clicked,
            this, &FenetrePrets::ouvrirFormulaireNouveauPret);

    connect(boutonAccepter, &QPushButton::clicked,
            this, &FenetrePrets::accepterPretSelectionne);

    connect(boutonRefuser, &QPushButton::clicked,
            this, &FenetrePrets::refuserPretSelectionne);

    connect(boutonRembourser, &QPushButton::clicked,
            this, &FenetrePrets::rembourserPretSelectionne);

    connect(boutonSupprimer, &QPushButton::clicked,
            this, &FenetrePrets::supprimerPretSelectionne);

    connect(boutonFermer, &QPushButton::clicked,
            this, &QWidget::close);

    connect(boutonActualiser, &QPushButton::clicked,
            this, &FenetrePrets::chargerDonneesTest);

    connect(champRecherche, &QLineEdit::textChanged,
            this, &FenetrePrets::filtrerPrets);
}

void FenetrePrets::appliquerStyle()
{
    setStyleSheet(
        "QWidget {"
        "   background: #F4F7FB;"
        "   font-family: 'Segoe UI';"
        "   color: #0F172A;"
        "}"

        "QLabel { background: transparent; }"

        "QLabel#titre {"
        "   color: #0057B8;"
        "   font-size: 34px;"
        "   font-weight: 900;"
        "}"

        "QLabel#nombrePrets {"
        "   color: #6B7280;"
        "   font-size: 16px;"
        "}"

        "QLineEdit, QComboBox {"
        "   background: #FFFFFF;"
        "   color: #111827;"
        "   border: 1px solid #D9E2EC;"
        "   border-radius: 14px;"
        "   padding-left: 22px;"
        "   padding-right: 22px;"
        "   font-size: 16px;"
        "}"

        "QLineEdit:focus, QComboBox:focus { border: 2px solid #0057B8; }"

        "QPushButton {"
        "   color: white;"
        "   border: none;"
        "   border-radius: 14px;"
        "   font-size: 16px;"
        "   font-weight: 800;"
        "}"

        "QPushButton#boutonPrincipal,"
        "QPushButton#boutonModifier,"
        "QPushButton#boutonActualiser {"
        "   background: #0057B8;"
        "}"

        "QPushButton#boutonPrincipal:hover,"
        "QPushButton#boutonModifier:hover,"
        "QPushButton#boutonActualiser:hover {"
        "   background: #00459A;"
        "}"

        "QPushButton#boutonAccepter { background: #16A34A; }"
        "QPushButton#boutonAccepter:hover { background: #15803D; }"

        "QPushButton#boutonDanger { background: #DC2626; }"
        "QPushButton#boutonDanger:hover { background: #B91C1C; }"

        "QFrame#carteTable {"
        "   background: white;"
        "   border: 1px solid #D9E2EC;"
        "   border-radius: 18px;"
        "}"

        "QTableWidget {"
        "   background: white;"
        "   alternate-background-color: #F9FAFB;"
        "   color: #111827;"
        "   border: none;"
        "   border-radius: 18px;"
        "   font-size: 16px;"
        "   selection-background-color: #D9EBFF;"
        "   selection-color: #111827;"
        "}"

        "QHeaderView::section {"
        "   background: #0057B8;"
        "   color: white;"
        "   border: none;"
        "   padding: 14px;"
        "   font-size: 16px;"
        "   font-weight: 900;"
        "}"

        "QTableWidget::item {"
        "   padding-left: 10px;"
        "   border-bottom: 1px solid #E5E7EB;"
        "}"

        "QTableWidget::item:selected {"
        "   background: #D9EBFF;"
        "   color: #111827;"
        "}"
        );
}

double FenetrePrets::calculerMensualite(double montant, double tauxAnnuel, int dureeMois) const
{
    double tauxMensuel = tauxAnnuel / 100.0 / 12.0;

    if (tauxMensuel == 0)
    {
        return montant / dureeMois;
    }

    return montant *
           tauxMensuel /
           (1 - std::pow(1 + tauxMensuel, -dureeMois));
}

void FenetrePrets::mettreAJourStatutLigne(int ligne, const QString& statut)
{
    QTableWidgetItem* item = new QTableWidgetItem(statut);
    item->setTextAlignment(Qt::AlignCenter);

    QFont font = item->font();
    font.setBold(true);
    item->setFont(font);

    if (statut.contains("Accepté"))
        item->setForeground(QColor("#16A34A"));
    else if (statut.contains("Refusé"))
        item->setForeground(QColor("#DC2626"));
    else if (statut.contains("Remboursé"))
        item->setForeground(QColor("#0057B8"));
    else
        item->setForeground(QColor("#D97706"));

    tablePrets->setItem(ligne, 6, item);
}

void FenetrePrets::chargerDonneesTest()
{
    struct DonneePret
    {
        QString id;
        QString client;
        double montant;
        double taux;
        int duree;
        QString statut;
    };

    QVector<DonneePret> donnees = {
        {"1", "Jean Dupont", 2000000, 6.5, 24, "En attente"},
        {"2", "Marie Martin", 5000000, 5.0, 36, "Accepté"},
        {"3", "Fatou Diop", 1000000, 7.0, 12, "Remboursé"},
        {"4", "Cheikh Ba", 3000000, 6.0, 48, "Refusé"},
    };

    tablePrets->setRowCount(donnees.size());

    for (int i = 0; i < donnees.size(); i++)
    {
        const DonneePret& d = donnees[i];
        double mensualite = calculerMensualite(d.montant, d.taux, d.duree);

        QTableWidgetItem* itemId = new QTableWidgetItem(d.id);
        QTableWidgetItem* itemClient = new QTableWidgetItem(d.client);
        QTableWidgetItem* itemMontant = new QTableWidgetItem(
            QString::number(d.montant, 'f', 0) + " FCFA");
        QTableWidgetItem* itemTaux = new QTableWidgetItem(
            QString::number(d.taux, 'f', 2) + " %");
        QTableWidgetItem* itemDuree = new QTableWidgetItem(QString::number(d.duree));
        QTableWidgetItem* itemMensualite = new QTableWidgetItem(
            QString::number(mensualite, 'f', 0) + " FCFA");

        itemId->setTextAlignment(Qt::AlignCenter);
        itemClient->setTextAlignment(Qt::AlignCenter);
        itemMontant->setTextAlignment(Qt::AlignCenter);
        itemTaux->setTextAlignment(Qt::AlignCenter);
        itemDuree->setTextAlignment(Qt::AlignCenter);
        itemMensualite->setTextAlignment(Qt::AlignCenter);

        tablePrets->setItem(i, 0, itemId);
        tablePrets->setItem(i, 1, itemClient);
        tablePrets->setItem(i, 2, itemMontant);
        tablePrets->setItem(i, 3, itemTaux);
        tablePrets->setItem(i, 4, itemDuree);
        tablePrets->setItem(i, 5, itemMensualite);

        mettreAJourStatutLigne(i, "●  " + d.statut);
    }

    labelNombrePrets->setText(
        QString::number(tablePrets->rowCount()) + " prêt(s) enregistré(s)"
        );
}

void FenetrePrets::ouvrirFormulaireNouveauPret()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Nouveau prêt");
    dialog.setFixedWidth(420);
    dialog.setStyleSheet(
        "QDialog { background: #F4F7FB; font-family: 'Segoe UI'; }"
        "QLabel { color: #374151; font-size: 14px; font-weight: 700; background: transparent; }"
        "QLineEdit, QComboBox {"
        "   background: white; color: #111827; border: 1px solid #D9E2EC;"
        "   border-radius: 12px; padding: 10px 14px; font-size: 15px;"
        "}"
        "QLineEdit:focus, QComboBox:focus { border: 2px solid #0057B8; }"
        "QPushButton {"
        "   border: none; border-radius: 12px; padding: 10px 20px;"
        "   font-size: 14px; font-weight: 800; color: white;"
        "}"
        );

    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    layout->setSpacing(14);
    layout->setContentsMargins(26, 26, 26, 26);

    QLabel* labelClient = new QLabel("Client");
    QComboBox* comboClient = new QComboBox;
    comboClient->addItems({"Jean Dupont", "Marie Martin", "Fatou Diop", "Cheikh Ba"});

    QLabel* labelMontant = new QLabel("Montant (FCFA)");
    QLineEdit* champMontant = new QLineEdit;
    champMontant->setPlaceholderText("Ex : 2000000");

    QLabel* labelTaux = new QLabel("Taux annuel (%)");
    QLineEdit* champTaux = new QLineEdit;
    champTaux->setPlaceholderText("Ex : 6.5");

    QLabel* labelDuree = new QLabel("Durée (mois)");
    QLineEdit* champDuree = new QLineEdit;
    champDuree->setPlaceholderText("Ex : 24");

    layout->addWidget(labelClient);
    layout->addWidget(comboClient);
    layout->addWidget(labelMontant);
    layout->addWidget(champMontant);
    layout->addWidget(labelTaux);
    layout->addWidget(champTaux);
    layout->addWidget(labelDuree);
    layout->addWidget(champDuree);

    QDialogButtonBox* boutons = new QDialogButtonBox;
    QPushButton* boutonAnnuler = boutons->addButton("Annuler", QDialogButtonBox::RejectRole);
    QPushButton* boutonValider = boutons->addButton("Créer le prêt", QDialogButtonBox::AcceptRole);
    boutonAnnuler->setStyleSheet("background:#9CA3AF;");
    boutonValider->setStyleSheet("background:#0057B8;");

    layout->addSpacing(6);
    layout->addWidget(boutons);

    connect(boutons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(boutons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted)
        return;

    bool ok1 = false, ok2 = false, ok3 = false;
    double montant = champMontant->text().trimmed().toDouble(&ok1);
    double taux = champTaux->text().trimmed().toDouble(&ok2);
    int duree = champDuree->text().trimmed().toInt(&ok3);

    if (!ok1 || !ok2 || !ok3 || montant <= 0 || duree <= 0)
    {
        QMessageBox::warning(this, "Champs invalides",
                              "Veuillez saisir un montant, un taux et une durée valides.");
        return;
    }

    double mensualite = calculerMensualite(montant, taux, duree);

    int ligne = tablePrets->rowCount();
    tablePrets->insertRow(ligne);

    QTableWidgetItem* itemId = new QTableWidgetItem(QString::number(ligne + 1));
    QTableWidgetItem* itemClient = new QTableWidgetItem(comboClient->currentText());
    QTableWidgetItem* itemMontant = new QTableWidgetItem(QString::number(montant, 'f', 0) + " FCFA");
    QTableWidgetItem* itemTaux = new QTableWidgetItem(QString::number(taux, 'f', 2) + " %");
    QTableWidgetItem* itemDuree = new QTableWidgetItem(QString::number(duree));
    QTableWidgetItem* itemMensualite = new QTableWidgetItem(QString::number(mensualite, 'f', 0) + " FCFA");

    itemId->setTextAlignment(Qt::AlignCenter);
    itemClient->setTextAlignment(Qt::AlignCenter);
    itemMontant->setTextAlignment(Qt::AlignCenter);
    itemTaux->setTextAlignment(Qt::AlignCenter);
    itemDuree->setTextAlignment(Qt::AlignCenter);
    itemMensualite->setTextAlignment(Qt::AlignCenter);

    tablePrets->setItem(ligne, 0, itemId);
    tablePrets->setItem(ligne, 1, itemClient);
    tablePrets->setItem(ligne, 2, itemMontant);
    tablePrets->setItem(ligne, 3, itemTaux);
    tablePrets->setItem(ligne, 4, itemDuree);
    tablePrets->setItem(ligne, 5, itemMensualite);

    mettreAJourStatutLigne(ligne, "●  En attente");

    labelNombrePrets->setText(
        QString::number(tablePrets->rowCount()) + " prêt(s) enregistré(s)"
        );
}

void FenetrePrets::accepterPretSelectionne()
{
    int ligne = tablePrets->currentRow();

    if (ligne < 0)
    {
        QMessageBox::information(this, "Aucune sélection", "Veuillez sélectionner un prêt.");
        return;
    }

    mettreAJourStatutLigne(ligne, "●  Accepté");
}

void FenetrePrets::refuserPretSelectionne()
{
    int ligne = tablePrets->currentRow();

    if (ligne < 0)
    {
        QMessageBox::information(this, "Aucune sélection", "Veuillez sélectionner un prêt.");
        return;
    }

    mettreAJourStatutLigne(ligne, "●  Refusé");
}

void FenetrePrets::rembourserPretSelectionne()
{
    int ligne = tablePrets->currentRow();

    if (ligne < 0)
    {
        QMessageBox::information(this, "Aucune sélection", "Veuillez sélectionner un prêt.");
        return;
    }

    mettreAJourStatutLigne(ligne, "●  Remboursé");
}

void FenetrePrets::supprimerPretSelectionne()
{
    int ligne = tablePrets->currentRow();

    if (ligne < 0)
    {
        QMessageBox::information(this, "Aucune sélection", "Veuillez sélectionner un prêt.");
        return;
    }

    QMessageBox::StandardButton reponse = QMessageBox::question(
        this, "Confirmer la suppression",
        "Voulez-vous vraiment supprimer ce prêt ?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reponse != QMessageBox::Yes)
        return;

    tablePrets->removeRow(ligne);

    labelNombrePrets->setText(
        QString::number(tablePrets->rowCount()) + " prêt(s) enregistré(s)"
        );
}

void FenetrePrets::filtrerPrets(const QString& texte)
{
    for (int i = 0; i < tablePrets->rowCount(); i++)
    {
        bool correspond = false;

        for (int j = 1; j < tablePrets->columnCount(); j++)
        {
            QTableWidgetItem* item = tablePrets->item(i, j);

            if (item && item->text().contains(texte, Qt::CaseInsensitive))
            {
                correspond = true;
                break;
            }
        }

        tablePrets->setRowHidden(i, !correspond && !texte.isEmpty());
    }
}

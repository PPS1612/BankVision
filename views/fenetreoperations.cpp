#include "FenetreOperations.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QColor>

FenetreOperations::FenetreOperations(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("BankVision - Opérations");
    resize(1100, 720);

    construireInterface();
    appliquerStyle();
    chargerDonneesTest();
}

void FenetreOperations::construireInterface()
{
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(34, 34, 34, 34);
    layoutPrincipal->setSpacing(20);

    QLabel* titre = new QLabel("Opérations bancaires");
    titre->setObjectName("titre");

    QLabel* sousTitre = new QLabel("Effectuer un dépôt, un retrait ou un virement");
    sousTitre->setObjectName("sousTitre");

    QFrame* carte = new QFrame;
    carte->setObjectName("carteOperation");

    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(24);
    shadow->setOffset(0, 6);
    shadow->setColor(QColor(15, 23, 42, 30));
    carte->setGraphicsEffect(shadow);

    QVBoxLayout* layoutCarte = new QVBoxLayout(carte);
    layoutCarte->setContentsMargins(34, 34, 34, 34);
    layoutCarte->setSpacing(20);

    QGridLayout* grille = new QGridLayout;
    grille->setHorizontalSpacing(22);
    grille->setVerticalSpacing(18);

    QLabel* labelType = new QLabel("Type d'opération");
    QLabel* labelSource = new QLabel("Compte source");
    QLabel* labelDestination = new QLabel("Compte destination");
    QLabel* labelMontant = new QLabel("Montant (FCFA)");
    QLabel* labelDescription = new QLabel("Description");

    labelType->setObjectName("labelChamp");
    labelSource->setObjectName("labelChamp");
    labelDestination->setObjectName("labelChamp");
    labelMontant->setObjectName("labelChamp");
    labelDescription->setObjectName("labelChamp");

    comboTypeOperation = new QComboBox;
    comboCompteSource = new QComboBox;
    comboCompteDestination = new QComboBox;

    champMontant = new QLineEdit;
    champMontant->setPlaceholderText("Ex : 50000");

    champDescription = new QTextEdit;
    champDescription->setPlaceholderText("Motif de l'opération...");
    champDescription->setFixedHeight(110);

    comboTypeOperation->setFixedHeight(48);
    comboCompteSource->setFixedHeight(48);
    comboCompteDestination->setFixedHeight(48);
    champMontant->setFixedHeight(48);

    grille->addWidget(labelType, 0, 0);
    grille->addWidget(comboTypeOperation, 1, 0);

    grille->addWidget(labelSource, 0, 1);
    grille->addWidget(comboCompteSource, 1, 1);

    grille->addWidget(labelDestination, 2, 0);
    grille->addWidget(comboCompteDestination, 3, 0);

    grille->addWidget(labelMontant, 2, 1);
    grille->addWidget(champMontant, 3, 1);

    layoutCarte->addLayout(grille);

    layoutCarte->addWidget(labelDescription);
    layoutCarte->addWidget(champDescription);

    labelMessage = new QLabel("");
    labelMessage->setObjectName("labelMessage");
    labelMessage->setAlignment(Qt::AlignCenter);
    labelMessage->setMinimumHeight(28);

    boutonValider = new QPushButton("Valider l'opération");
    boutonAnnuler = new QPushButton("Réinitialiser");

    boutonValider->setFixedHeight(52);
    boutonAnnuler->setFixedHeight(52);

    boutonValider->setObjectName("boutonValider");
    boutonAnnuler->setObjectName("boutonAnnuler");

    boutonValider->setCursor(Qt::PointingHandCursor);
    boutonAnnuler->setCursor(Qt::PointingHandCursor);

    QHBoxLayout* layoutBoutons = new QHBoxLayout;
    layoutBoutons->setSpacing(18);
    layoutBoutons->addStretch();
    layoutBoutons->addWidget(boutonAnnuler);
    layoutBoutons->addWidget(boutonValider);

    layoutCarte->addWidget(labelMessage);
    layoutCarte->addLayout(layoutBoutons);

    layoutPrincipal->addWidget(titre);
    layoutPrincipal->addWidget(sousTitre);
    layoutPrincipal->addSpacing(10);
    layoutPrincipal->addWidget(carte);
    layoutPrincipal->addStretch();

    connect(boutonValider, &QPushButton::clicked,
            this, &FenetreOperations::validerOperation);
}

void FenetreOperations::appliquerStyle()
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

        "QLabel#sousTitre {"
        "   color: #6B7280;"
        "   font-size: 16px;"
        "}"

        "QLabel#labelChamp {"
        "   color: #374151;"
        "   font-size: 14px;"
        "   font-weight: 700;"
        "}"

        "QFrame#carteOperation {"
        "   background: white;"
        "   border: 1px solid #D9E2EC;"
        "   border-radius: 20px;"
        "}"

        "QLineEdit, QComboBox, QTextEdit {"
        "   background: white;"
        "   color: #111827;"
        "   border: 1px solid #D9E2EC;"
        "   border-radius: 12px;"
        "   padding-left: 14px;"
        "   padding-right: 14px;"
        "   font-size: 15px;"
        "}"

        "QLineEdit:focus, QComboBox:focus, QTextEdit:focus {"
        "   border: 2px solid #0057B8;"
        "}"

        "QTextEdit {"
        "   padding-top: 12px;"
        "}"

        "QPushButton {"
        "   border: none;"
        "   border-radius: 14px;"
        "   padding-left: 24px;"
        "   padding-right: 24px;"
        "   font-size: 15px;"
        "   font-weight: 800;"
        "}"

        "QPushButton#boutonValider {"
        "   background: #16A34A;"
        "   color: white;"
        "}"

        "QPushButton#boutonValider:hover {"
        "   background: #15803D;"
        "}"

        "QPushButton#boutonAnnuler {"
        "   background: #0057B8;"
        "   color: white;"
        "}"

        "QPushButton#boutonAnnuler:hover {"
        "   background: #00459A;"
        "}"

        "QLabel#labelMessage {"
        "   font-size: 14px;"
        "   font-weight: 700;"
        "}"
        );
}

void FenetreOperations::chargerDonneesTest()
{
    comboTypeOperation->addItems({
        "Dépôt",
        "Retrait",
        "Virement"
    });

    comboCompteSource->addItems({
        "SN001-COURANT - Jean Dupont",
        "SN002-EPARGNE - Jean Dupont",
        "SN003-PRO - Marie Martin"
    });

    comboCompteDestination->addItems({
        "SN002-EPARGNE - Jean Dupont",
        "SN003-PRO - Marie Martin",
        "SN004-COURANT - Fatou Diop"
    });
}

void FenetreOperations::validerOperation()
{
    QString montantTexte = champMontant->text().trimmed();

    if (montantTexte.isEmpty())
    {
        labelMessage->setStyleSheet("color:#DC2626;background:transparent;");
        labelMessage->setText("Veuillez saisir un montant.");
        return;
    }

    bool ok = false;
    double montant = montantTexte.toDouble(&ok);

    if (!ok || montant <= 0)
    {
        labelMessage->setStyleSheet("color:#DC2626;background:transparent;");
        labelMessage->setText("Montant invalide.");
        return;
    }

    labelMessage->setStyleSheet("color:#16A34A;background:transparent;");
    labelMessage->setText("Opération validée avec succès.");
}

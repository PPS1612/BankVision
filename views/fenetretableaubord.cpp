#include "FenetreTableauBord.h"
#include "FenetreConnexion.h"
#include "FenetreClients.h"
#include "FenetreComptes.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include "FenetreOperations.h"
#include "fenetrestatistiques.h"
#include "fenetreprets.h"

FenetreTableauBord::FenetreTableauBord(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("BankVision - Tableau de bord");
    resize(1200, 750);

    construireInterface();
    appliquerStyle();
}

void FenetreTableauBord::construireInterface()
{
    QHBoxLayout* layoutPrincipal = new QHBoxLayout(this);
    layoutPrincipal->setContentsMargins(0, 0, 0, 0);
    layoutPrincipal->setSpacing(0);

    QFrame* menu = new QFrame(this);
    menu->setObjectName("menuLateral");
    menu->setFixedWidth(240);

    QVBoxLayout* layoutMenu = new QVBoxLayout(menu);
    layoutMenu->setContentsMargins(25, 30, 25, 30);
    layoutMenu->setSpacing(18);

    QLabel* titreMenu = new QLabel("BANKVISION", menu);
    titreMenu->setObjectName("titreMenu");

    QPushButton* boutonAccueil = new QPushButton("Tableau de bord", menu);
    QPushButton* boutonClients = new QPushButton("Clients", menu);
    QPushButton* boutonComptes = new QPushButton("Comptes", menu);
    QPushButton* boutonOperations = new QPushButton("Opérations", menu);
    QPushButton* boutonPrets = new QPushButton("Prêts", menu);
    QPushButton* boutonStats = new QPushButton("Statistiques", menu);

    boutonDeconnexion = new QPushButton("Déconnexion", menu);

    layoutMenu->addWidget(titreMenu);
    layoutMenu->addSpacing(25);
    layoutMenu->addWidget(boutonAccueil);
    layoutMenu->addWidget(boutonClients);
    layoutMenu->addWidget(boutonComptes);
    layoutMenu->addWidget(boutonOperations);
    layoutMenu->addWidget(boutonPrets);
    layoutMenu->addWidget(boutonStats);
    layoutMenu->addStretch();
    layoutMenu->addWidget(boutonDeconnexion);

    QFrame* contenu = new QFrame(this);
    contenu->setObjectName("contenuPrincipal");

    QVBoxLayout* layoutContenu = new QVBoxLayout(contenu);
    layoutContenu->setContentsMargins(40, 35, 40, 35);
    layoutContenu->setSpacing(25);

    labelBienvenue = new QLabel("Bienvenue dans BankVision", contenu);
    labelBienvenue->setObjectName("titrePage");

    QLabel* sousTitre = new QLabel("Vue d'ensemble de votre activité bancaire", contenu);
    sousTitre->setObjectName("sousTitrePage");

    QGridLayout* grilleStats = new QGridLayout;
    grilleStats->setSpacing(25);

    auto creerCarte = [](const QString& titre, const QString& valeur) -> QFrame*
    {
        QFrame* carte = new QFrame;
        carte->setObjectName("carteStat");

        QVBoxLayout* layout = new QVBoxLayout(carte);
        layout->setContentsMargins(25, 25, 25, 25);

        QLabel* titreLabel = new QLabel(titre, carte);
        titreLabel->setObjectName("titreCarte");

        QLabel* valeurLabel = new QLabel(valeur, carte);
        valeurLabel->setObjectName("valeurCarte");

        layout->addWidget(titreLabel);
        layout->addWidget(valeurLabel);

        return carte;
    };

    QFrame* carteClients = creerCarte("Clients", "128");
    QFrame* carteComptes = creerCarte("Comptes", "312");
    QFrame* carteSolde = creerCarte("Solde total", "845 000 €");
    QFrame* cartePrets = creerCarte("Prêts actifs", "24");

    grilleStats->addWidget(carteClients, 0, 0);
    grilleStats->addWidget(carteComptes, 0, 1);
    grilleStats->addWidget(carteSolde, 1, 0);
    grilleStats->addWidget(cartePrets, 1, 1);

    layoutContenu->addWidget(labelBienvenue);
    layoutContenu->addWidget(sousTitre);
    layoutContenu->addLayout(grilleStats);
    layoutContenu->addStretch();

    layoutPrincipal->addWidget(menu);
    layoutPrincipal->addWidget(contenu);

    connect(boutonDeconnexion, &QPushButton::clicked,
            this, &FenetreTableauBord::seDeconnecter);

    connect(boutonClients, &QPushButton::clicked,
            this, &FenetreTableauBord::ouvrirClients);

    connect(boutonComptes, &QPushButton::clicked,
            this, &FenetreTableauBord::ouvrirComptes);

    connect(boutonOperations, &QPushButton::clicked,
            this, &FenetreTableauBord::ouvrirOperations);

    connect(boutonStats, &QPushButton::clicked,
        this, &FenetreTableauBord::ouvrirStatistiques);
    
    connect(boutonPrets,
        &QPushButton::clicked,
        this,
        &FenetreTableauBord::ouvrirPrets);
}

void FenetreTableauBord::appliquerStyle()
{
    setStyleSheet(
        "QWidget {"
        "   background-color: #F4F7FB;"
        "   font-family: 'Segoe UI';"
        "   color: #1F2937;"
        "}"

        "QFrame#menuLateral {"
        "   background-color: #0057B8;"
        "}"

        "QLabel {"
        "   background: transparent;"
        "}"

        "QLabel#titreMenu {"
        "   color: white;"
        "   font-size: 22px;"
        "   font-weight: 800;"
        "   letter-spacing: 1px;"
        "}"

        "QPushButton {"
        "   background-color: transparent;"
        "   color: white;"
        "   border: none;"
        "   text-align: left;"
        "   padding: 12px;"
        "   border-radius: 8px;"
        "   font-size: 14px;"
        "   font-weight: 600;"
        "}"

        "QPushButton:hover {"
        "   background-color: #00459A;"
        "}"

        "QFrame#contenuPrincipal {"
        "   background-color: #F4F7FB;"
        "}"

        "QLabel#titrePage {"
        "   color: #111827;"
        "   font-size: 28px;"
        "   font-weight: 800;"
        "}"

        "QLabel#sousTitrePage {"
        "   color: #6B7280;"
        "   font-size: 15px;"
        "}"

        "QFrame#carteStat {"
        "   background-color: white;"
        "   border: 1px solid #D9E2EC;"
        "   border-radius: 18px;"
        "}"

        "QLabel#titreCarte {"
        "   color: #6B7280;"
        "   font-size: 14px;"
        "   font-weight: 600;"
        "}"

        "QLabel#valeurCarte {"
        "   color: #0057B8;"
        "   font-size: 30px;"
        "   font-weight: 800;"
        "}"
        );
}

void FenetreTableauBord::seDeconnecter()
{
    FenetreConnexion* fenetreConnexion = new FenetreConnexion();
    fenetreConnexion->show();
    this->close();
}

void FenetreTableauBord::ouvrirClients()
{
    FenetreClients* fenetreClients = new FenetreClients();
    fenetreClients->show();
}

void FenetreTableauBord::ouvrirComptes()
{
    FenetreComptes* fenetreComptes = new FenetreComptes();
    fenetreComptes->show();
}


void FenetreTableauBord::ouvrirOperations()
{
    FenetreOperations* fenetreOperations = new FenetreOperations();
    fenetreOperations->show();
}
void FenetreTableauBord::ouvrirStatistiques()
{
    FenetreStatistiques* f = new FenetreStatistiques();
    f->show();
}
void FenetreTableauBord::ouvrirPrets()
{
    FenetrePrets* f = new FenetrePrets();
    f->show();
}
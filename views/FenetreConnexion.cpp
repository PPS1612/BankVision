#include "FenetreConnexion.h"
#include "FenetreTableauBord.h"
#include "FenetreClients.h"

#include <QVBoxLayout>
#include <QFrame>

FenetreConnexion::FenetreConnexion(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("BankVision - Connexion");
    resize(1000, 650);

    construireInterface();
    appliquerStyle();
}

void FenetreConnexion::construireInterface()
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setAlignment(Qt::AlignCenter);

    QFrame *carte = new QFrame;
    carte->setObjectName("carteConnexion");
    carte->setFixedSize(430, 470);

    QVBoxLayout *layout = new QVBoxLayout(carte);
    layout->setContentsMargins(40, 35, 40, 35);
    layout->setSpacing(16);

    QLabel *titre = new QLabel("BANKVISION");
    titre->setObjectName("titreApplication");
    titre->setAlignment(Qt::AlignCenter);

    QLabel *sousTitre = new QLabel("Système de gestion bancaire");
    sousTitre->setObjectName("sousTitreApplication");
    sousTitre->setAlignment(Qt::AlignCenter);

    QLabel *bienvenue = new QLabel("Connexion à votre espace");
    bienvenue->setObjectName("labelBienvenue");
    bienvenue->setAlignment(Qt::AlignCenter);

    QLabel *labelLogin = new QLabel("Identifiant");
    labelLogin->setObjectName("labelChamp");

    champLogin = new QLineEdit;
    champLogin->setPlaceholderText("Entrez votre identifiant");
    champLogin->setFixedHeight(48);

    QLabel *labelMdp = new QLabel("Mot de passe");
    labelMdp->setObjectName("labelChamp");

    champMotDePasse = new QLineEdit;
    champMotDePasse->setPlaceholderText("Entrez votre mot de passe");
    champMotDePasse->setEchoMode(QLineEdit::Password);
    champMotDePasse->setFixedHeight(48);

    boutonConnexion = new QPushButton("SE CONNECTER");
    boutonConnexion->setFixedHeight(48);
    boutonConnexion->setCursor(Qt::PointingHandCursor);

    labelMessage = new QLabel;
    labelMessage->setObjectName("labelMessage");
    labelMessage->setAlignment(Qt::AlignCenter);
    labelMessage->setMinimumHeight(25);

    layout->addWidget(titre);
    layout->addWidget(sousTitre);
    layout->addSpacing(15);
    layout->addWidget(bienvenue);
    layout->addSpacing(10);
    layout->addWidget(labelLogin);
    layout->addWidget(champLogin);
    layout->addWidget(labelMdp);
    layout->addWidget(champMotDePasse);
    layout->addSpacing(10);
    layout->addWidget(boutonConnexion);
    layout->addWidget(labelMessage);

    layoutPrincipal->addWidget(carte);

    connect(
        boutonConnexion,
        &QPushButton::clicked,
        this,
        &FenetreConnexion::seConnecter
        );


}

void FenetreConnexion::appliquerStyle()
{
    setStyleSheet(
        "QWidget{"
        "background:#F4F7FB;"
        "font-family:'Segoe UI';"
        "color:#1F2937;"
        "}"

        "QFrame#carteConnexion{"
        "background:white;"
        "border:1px solid #DCE4EC;"
        "border-radius:20px;"
        "}"

        "QLabel{"
        "background:transparent;"
        "}"

        "QLabel#titreApplication{"
        "font-size:30px;"
        "font-weight:800;"
        "color:#0057B8;"
        "}"

        "QLabel#sousTitreApplication{"
        "font-size:14px;"
        "color:#6B7280;"
        "}"

        "QLabel#labelBienvenue{"
        "font-size:18px;"
        "font-weight:600;"
        "color:#1F2937;"
        "}"

        "QLabel#labelChamp{"
        "font-size:13px;"
        "font-weight:600;"
        "color:#374151;"
        "}"

        "QLineEdit{"
        "background:white;"
        "color:#111827;"
        "border:2px solid #D6DEE7;"
        "border-radius:10px;"
        "padding-left:14px;"
        "padding-right:14px;"
        "font-size:14px;"
        "}"

        "QLineEdit:focus{"
        "border:2px solid #0057B8;"
        "}"

        "QLineEdit::placeholder{"
        "color:#9CA3AF;"
        "}"

        "QPushButton{"
        "background:#0057B8;"
        "color:white;"
        "border:none;"
        "border-radius:10px;"
        "font-size:14px;"
        "font-weight:700;"
        "}"

        "QPushButton:hover{"
        "background:#00459A;"
        "}"

        "QPushButton:pressed{"
        "background:#003C84;"
        "}"

        "QLabel#labelMessage{"
        "font-size:13px;"
        "font-weight:600;"
        "}"
        );
}

void FenetreConnexion::seConnecter()
{
    QString login = champLogin->text().trimmed();
    QString mdp = champMotDePasse->text();

    if (login.isEmpty() || mdp.isEmpty())
    {
        labelMessage->setStyleSheet("color:#E53935;background:transparent;");
        labelMessage->setText("Veuillez remplir tous les champs.");
        return;
    }

    if (login == "admin" && mdp == "admin123")
    {
        labelMessage->setStyleSheet("color:#2E7D32;background:transparent;");
        labelMessage->setText("Connexion réussie.");

        FenetreTableauBord* tableauBord = new FenetreTableauBord();
        tableauBord->show();

        this->close();
    }
    else
    {
        labelMessage->setStyleSheet("color:#E53935;background:transparent;");
        labelMessage->setText("Identifiant ou mot de passe incorrect.");
    }
}
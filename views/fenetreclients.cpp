#include "FenetreClients.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QFont>

FenetreClients::FenetreClients(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("BankVision - Clients");
    resize(1200, 720);

    construireInterface();
    appliquerStyle();
    chargerDonneesTest();
}

void FenetreClients::construireInterface()
{
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(34, 34, 34, 34);
    layoutPrincipal->setSpacing(18);

    QLabel* titre = new QLabel("Gestion des clients");
    titre->setObjectName("titre");

    labelNombreClients = new QLabel("4 clients enregistrés");
    labelNombreClients->setObjectName("nombreClients");

    champRecherche = new QLineEdit;
    champRecherche->setPlaceholderText("🔍  Rechercher un client...");
    champRecherche->setFixedHeight(54);

    boutonAjouter = new QPushButton("+  Nouveau client");
    boutonAjouter->setFixedHeight(54);
    boutonAjouter->setFixedWidth(230);
    boutonAjouter->setCursor(Qt::PointingHandCursor);
    boutonAjouter->setObjectName("boutonPrincipal");

    QHBoxLayout* layoutRecherche = new QHBoxLayout;
    layoutRecherche->setSpacing(22);
    layoutRecherche->addWidget(champRecherche);
    layoutRecherche->addWidget(boutonAjouter);

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

    tableClients = new QTableWidget;
    tableClients->setColumnCount(6);
    tableClients->setRowCount(4);

    tableClients->setHorizontalHeaderLabels({
        "ID", "Nom", "Email", "Téléphone", "Comptes", "Statut"
    });

    tableClients->verticalHeader()->setVisible(false);
    tableClients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableClients->horizontalHeader()->setFixedHeight(56);
    tableClients->verticalHeader()->setDefaultSectionSize(62);

    tableClients->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableClients->setSelectionMode(QAbstractItemView::SingleSelection);
    tableClients->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableClients->setShowGrid(false);
    tableClients->setAlternatingRowColors(true);
    tableClients->setFocusPolicy(Qt::NoFocus);

    layoutTable->addWidget(tableClients);

    boutonModifier = new QPushButton("✎  Modifier");
    boutonSupprimer = new QPushButton("●  Désactiver");
    boutonActualiser = new QPushButton("↻  Actualiser");

    boutonModifier->setObjectName("boutonModifier");
    boutonSupprimer->setObjectName("boutonDanger");
    boutonActualiser->setObjectName("boutonActualiser");

    boutonModifier->setFixedSize(160, 54);
    boutonSupprimer->setFixedSize(190, 54);
    boutonActualiser->setFixedSize(180, 54);

    boutonModifier->setCursor(Qt::PointingHandCursor);
    boutonSupprimer->setCursor(Qt::PointingHandCursor);
    boutonActualiser->setCursor(Qt::PointingHandCursor);

    QHBoxLayout* layoutBoutons = new QHBoxLayout;
    layoutBoutons->setSpacing(18);
    layoutBoutons->addWidget(boutonModifier);
    layoutBoutons->addWidget(boutonSupprimer);
    layoutBoutons->addStretch();
    layoutBoutons->addWidget(boutonActualiser);

    layoutPrincipal->addWidget(titre);
    layoutPrincipal->addWidget(labelNombreClients);
    layoutPrincipal->addLayout(layoutRecherche);
    layoutPrincipal->addSpacing(12);
    layoutPrincipal->addWidget(carteTable);
    layoutPrincipal->addSpacing(12);
    layoutPrincipal->addLayout(layoutBoutons);
}

void FenetreClients::appliquerStyle()
{
    setStyleSheet(
        "QWidget {"
        "   background: #F4F7FB;"
        "   font-family: 'Segoe UI';"
        "   color: #0F172A;"
        "}"

        "QLabel {"
        "   background: transparent;"
        "}"

        "QLabel#titre {"
        "   color: #0057B8;"
        "   font-size: 34px;"
        "   font-weight: 900;"
        "}"

        "QLabel#nombreClients {"
        "   color: #6B7280;"
        "   font-size: 16px;"
        "}"

        "QLineEdit {"
        "   background: #FFFFFF;"
        "   color: #111827;"
        "   border: 1px solid #D9E2EC;"
        "   border-radius: 14px;"
        "   padding-left: 22px;"
        "   padding-right: 22px;"
        "   font-size: 16px;"
        "}"

        "QLineEdit:focus {"
        "   border: 2px solid #0057B8;"
        "}"

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

        "QPushButton#boutonDanger {"
        "   background: #DC2626;"
        "}"

        "QPushButton#boutonDanger:hover {"
        "   background: #B91C1C;"
        "}"

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

void FenetreClients::chargerDonneesTest()
{
    QString donnees[4][6] =
        {
            {"1", "Jean Dupont", "jean@gmail.com", "770000001", "2", "●  Actif"},
            {"2", "Marie Martin", "marie@gmail.com", "770000002", "1", "●  Actif"},
            {"3", "Ali Ndiaye", "ali@gmail.com", "770000003", "3", "●  Actif"},
            {"4", "Fatou Diop", "fatou@gmail.com", "770000004", "2", "●  Inactif"}
        };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem(donnees[i][j]);
            item->setTextAlignment(Qt::AlignCenter);

            if (j == 5)
            {
                QFont font = item->font();
                font.setBold(true);
                item->setFont(font);

                if (donnees[i][j].contains("Actif") && !donnees[i][j].contains("Inactif"))
                    item->setForeground(QColor("#16A34A"));
                else
                    item->setForeground(QColor("#DC2626"));
            }

            tableClients->setItem(i, j, item);
        }
    }

    labelNombreClients->setText(
        QString::number(tableClients->rowCount()) + " clients enregistrés"
        );
}
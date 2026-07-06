#include "FenetreComptes.h"

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

FenetreComptes::FenetreComptes(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("BankVision - Comptes");
    resize(1200, 720);

    construireInterface();
    appliquerStyle();
    chargerDonneesTest();
}

void FenetreComptes::construireInterface()
{
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(34, 34, 34, 34);
    layoutPrincipal->setSpacing(18);

    QLabel* titre = new QLabel("Gestion des comptes");
    titre->setObjectName("titre");

    labelNombreComptes = new QLabel("4 comptes enregistrés");
    labelNombreComptes->setObjectName("nombreComptes");

    champRecherche = new QLineEdit;
    champRecherche->setPlaceholderText("🔍  Rechercher un compte...");
    champRecherche->setFixedHeight(54);

    boutonAjouter = new QPushButton("+  Nouveau compte");
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

    tableComptes = new QTableWidget;
    tableComptes->setColumnCount(6);
    tableComptes->setRowCount(4);

    tableComptes->setHorizontalHeaderLabels({
        "IBAN", "Client", "Type", "Solde", "Découvert/Taux", "Statut"
    });

    tableComptes->verticalHeader()->setVisible(false);
    tableComptes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableComptes->horizontalHeader()->setFixedHeight(56);
    tableComptes->verticalHeader()->setDefaultSectionSize(62);

    tableComptes->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableComptes->setSelectionMode(QAbstractItemView::SingleSelection);
    tableComptes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableComptes->setShowGrid(false);
    tableComptes->setAlternatingRowColors(true);
    tableComptes->setFocusPolicy(Qt::NoFocus);

    layoutTable->addWidget(tableComptes);

    boutonModifier = new QPushButton("✎  Modifier");
    boutonFermer = new QPushButton("●  Fermer");
    boutonActualiser = new QPushButton("↻  Actualiser");

    boutonModifier->setObjectName("boutonModifier");
    boutonFermer->setObjectName("boutonDanger");
    boutonActualiser->setObjectName("boutonActualiser");

    boutonModifier->setFixedSize(160, 54);
    boutonFermer->setFixedSize(160, 54);
    boutonActualiser->setFixedSize(180, 54);

    boutonModifier->setCursor(Qt::PointingHandCursor);
    boutonFermer->setCursor(Qt::PointingHandCursor);
    boutonActualiser->setCursor(Qt::PointingHandCursor);

    QHBoxLayout* layoutBoutons = new QHBoxLayout;
    layoutBoutons->setSpacing(18);
    layoutBoutons->addWidget(boutonModifier);
    layoutBoutons->addWidget(boutonFermer);
    layoutBoutons->addStretch();
    layoutBoutons->addWidget(boutonActualiser);

    layoutPrincipal->addWidget(titre);
    layoutPrincipal->addWidget(labelNombreComptes);
    layoutPrincipal->addLayout(layoutRecherche);
    layoutPrincipal->addSpacing(12);
    layoutPrincipal->addWidget(carteTable);
    layoutPrincipal->addSpacing(12);
    layoutPrincipal->addLayout(layoutBoutons);
}

void FenetreComptes::appliquerStyle()
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

        "QLabel#nombreComptes {"
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

        "QLineEdit:focus { border: 2px solid #0057B8; }"

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

void FenetreComptes::chargerDonneesTest()
{
    QString donnees[4][6] =
        {
            {"FR001-COURANT", "Jean Dupont", "Courant", "1 000 000 FCFA", "300 000 FCFA", "●  Actif"},
            {"FR002-EPARGNE", "Jean Dupont", "Épargne", "2 000 000 FCFA", "3.5 %", "●  Actif"},
            {"FR003-PRO", "Marie Martin", "Professionnel", "5 000 000 FCFA", "2 500 000 FCFA", "●  Actif"},
            {"FR004-COURANT", "Fatou Diop", "Courant", "750 000 FCFA", "100 000 FCFA", "●  Fermé"}
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

                if (donnees[i][j].contains("Actif"))
                    item->setForeground(QColor("#16A34A"));
                else
                    item->setForeground(QColor("#DC2626"));
            }

            tableComptes->setItem(i, j, item);
        }
    }

    labelNombreComptes->setText(
        QString::number(tableComptes->rowCount()) + " comptes enregistrés"
        );
}

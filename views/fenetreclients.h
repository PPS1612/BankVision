#ifndef FENETRECLIENTS_H
#define FENETRECLIENTS_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;
class QTableWidget;

class FenetreClients : public QWidget
{
    Q_OBJECT

private:
    QLabel* labelNombreClients;
    QLineEdit* champRecherche;
    QPushButton* boutonAjouter;
    QPushButton* boutonModifier;
    QPushButton* boutonSupprimer;
    QPushButton* boutonActualiser;
    QTableWidget* tableClients;

    void construireInterface();
    void appliquerStyle();
    void chargerDonneesTest();

public:
    explicit FenetreClients(QWidget *parent = nullptr);
};

#endif
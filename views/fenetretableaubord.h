#ifndef FENETRETABLEAUBORD_H
#define FENETRETABLEAUBORD_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class FenetreTableauBord : public QWidget
{
    Q_OBJECT

private:
    QLabel* labelBienvenue;
    QLabel* labelClients;
    QLabel* labelComptes;
    QLabel* labelSolde;
    QLabel* labelPrets;

    QPushButton* boutonDeconnexion;

    void construireInterface();
    void appliquerStyle();

private slots:
    void ouvrirClients();
    void ouvrirComptes();
    void seDeconnecter();
    void ouvrirOperations();

public:
    explicit FenetreTableauBord(QWidget *parent = nullptr);


};

#endif
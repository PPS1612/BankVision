#include <QCoreApplication>
#include <QDebug>

#include "data/datamanager.h"
#include "models/Client.h"
#include "models/comptecourant.h"
#include "models/compteepargne.h"
#include "models/compteprofessionnel.h"

#include "services/compteservice.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    DataManager& dataManager = DataManager::getInstance();

    if (!dataManager.initialiser("banque.db"))
        return 1;

    Client client(
        1,
        "Jean Dupont",
        "jean@gmail.com",
        "0123456789"
        );

    dataManager.sauvegarderClient(client);

    CompteCourant courant(
        "FR001-COURANT",
        1000.0,
        300.0
        );

    CompteEpargne epargne(
        "FR002-EPARGNE",
        2000.0,
        3.5
        );

    CompteProfessionnel pro(
        "FR003-PRO",
        5000.0,
        "TechVision SARL",
        1000.0,
        2500.0
        );

    dataManager.sauvegarderCompte(courant, client.getId(), "COURANT");
    dataManager.sauvegarderCompte(epargne, client.getId(), "EPARGNE");
    dataManager.sauvegarderCompte(pro, client.getId(), "PROFESSIONNEL");

    CompteService compteService;

    qDebug() << "===== RECHERCHE COMPTE SERVICE =====";

    CompteBancaire* compteLu =
        compteService.rechercherCompteParIBAN("FR001-COURANT");

    if (compteLu != nullptr)
    {
        qDebug() << compteLu->getIBAN()
        << compteLu->getSolde();

        delete compteLu;
    }

    qDebug() << "===== LISTE COMPTES SERVICE =====";

    QVector<CompteBancaire*> comptes =
        compteService.getTousLesComptes();

    qDebug() << "Nombre comptes :" << comptes.size();

    for (CompteBancaire* compte : comptes)
    {
        qDebug() << compte->getIBAN()
        << compte->getSolde();

        delete compte;
    }

    qDebug() << "===== MODIFICATION COMPTE SERVICE =====";

    CompteCourant courantModifie(
        "FR001-COURANT",
        1800.0,
        300.0
        );

    compteService.modifierCompte(courantModifie, "COURANT");

    CompteBancaire* compteModifie =
        compteService.rechercherCompteParIBAN("FR001-COURANT");

    if (compteModifie != nullptr)
    {
        qDebug() << "Après modification :"
                 << compteModifie->getIBAN()
                 << compteModifie->getSolde();

        delete compteModifie;
    }

    qDebug() << "===== SUPPRESSION LOGIQUE COMPTE SERVICE =====";

    compteService.supprimerCompte("FR001-COURANT");

    CompteBancaire* compteFerme =
        compteService.rechercherCompteParIBAN("FR001-COURANT");

    if (compteFerme != nullptr)
    {
        qDebug() << "Après fermeture :"
                 << compteFerme->getIBAN()
                 << compteFerme->getSolde();

        delete compteFerme;
    }

    dataManager.fermer();

    return 0;
}
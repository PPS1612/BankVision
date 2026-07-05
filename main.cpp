#include <QCoreApplication>
#include <QDebug>

#include "models/banque.h"
#include "models/Client.h"
#include "models/comptecourant.h"
#include "models/compteepargne.h"
#include "models/compteprofessionnel.h"

#include "services/statservice.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Banque banque("BankVision");

    // ================= CLIENT 1 =================

    Client* client1 = new Client(
        1,
        "Jean Dupont",
        "jean@gmail.com",
        "0600000000"
        );

    client1->ajouterCompte(new CompteCourant(
        "FR001",
        1000,
        500));

    client1->ajouterCompte(new CompteEpargne(
        "FR002",
        2000,
        3.5));

    banque.ajouterClient(client1);

    // ================= CLIENT 2 =================

    Client* client2 = new Client(
        2,
        "Marie Martin",
        "marie@gmail.com",
        "0700000000"
        );

    client2->ajouterCompte(new CompteProfessionnel(
        "FR003",
        5000,
        "Entreprise Martin",
        3000,
        10000));

    banque.ajouterClient(client2);

    // ================= STAT SERVICE =================

    StatService stats;

    qDebug() << "===== STATISTIQUES =====";

    qDebug() << "Nombre clients :"
             << stats.getNombreClients(banque);

    qDebug() << "Nombre comptes :"
             << stats.getNombreComptes(banque);

    qDebug() << "Solde total :"
             << stats.getSoldeTotalBanque(banque);

    qDebug() << "Solde moyen/client :"
             << stats.getSoldeMoyenParClient(banque);

    qDebug() << "Solde moyen/compte :"
             << stats.getSoldeMoyenParCompte(banque);

    Client* riche = stats.getClientPlusRiche(banque);

    if (riche != nullptr)
    {
        qDebug() << "Client le plus riche :"
                 << riche->getNom()
                 << riche->getSoldeTotal();
    }

    Client* plusComptes = stats.getClientAvecPlusDeComptes(banque);

    if (plusComptes != nullptr)
    {
        qDebug() << "Client avec le plus de comptes :"
                 << plusComptes->getNom()
                 << plusComptes->getComptes().size();
    }

    return 0;
}
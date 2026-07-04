#include <QCoreApplication>
#include <QDebug>

#include "models/banque.h"
#include "models/client.h"
#include "models/comptecourant.h"
#include "models/compteepargne.h"

#include "controllers/statcontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Banque banque("BankVision");

    // -------------------- Client 1 --------------------

    Client client1(
        1,
        "Jean Dupont",
        "jean@gmail.com",
        "0123456789"
        );

    CompteCourant* courant1 = new CompteCourant(
        "FR001",
        1000.0,
        300.0
        );

    CompteEpargne* epargne1 = new CompteEpargne(
        "FR002",
        2500.0,
        3.5
        );

    client1.ajouterCompte(courant1);
    client1.ajouterCompte(epargne1);

    // -------------------- Client 2 --------------------

    Client client2(
        2,
        "Marie Martin",
        "marie@gmail.com",
        "0987654321"
        );

    CompteCourant* courant2 = new CompteCourant(
        "FR003",
        4000.0,
        500.0
        );

    client2.ajouterCompte(courant2);

    // -------------------- Banque --------------------

    banque.ajouterClient(&client1);
    banque.ajouterClient(&client2);

    // -------------------- Statistiques --------------------

    StatController stats;

    qDebug() << "Nombre clients :"
             << stats.getNombreClients(banque);

    qDebug() << "Nombre comptes :"
             << stats.getNombreComptes(banque);

    qDebug() << "Solde total banque :"
             << stats.getSoldeTotalBanque(banque);

    qDebug() << "Solde moyen par client :"
             << stats.getSoldeMoyenClient(banque);

    return 0;
}
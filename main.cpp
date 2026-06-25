#include <QCoreApplication>
#include <QDebug>

#include "models/banque.h"
#include "models/client.h"

#include "services/clientservice.h"
#include "services/banqueservice.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Banque banque("BankVision");

    ClientService clientService;
    BanqueService banqueService;

    Client client1(
        1,
        "Jean Dupont",
        "jean@gmail.com",
        "0123456789"
        );

    clientService.ajouterClient(banque, &client1);

    banqueService.ouvrirCompteCourant(
        client1,
        "FR001-COURANT",
        1000.0,
        300.0
        );

    banqueService.ouvrirCompteEpargne(
        client1,
        "FR002-EPARGNE",
        2000.0,
        3.5
        );

    banqueService.ouvrirCompteProfessionnel(
        client1,
        "FR003-PRO",
        5000.0,
        "TechVision SARL",
        1000.0,
        2500.0
        );

    qDebug() << "Nom banque :" << banque.getNom();
    qDebug() << "Nombre de clients :" << banque.getNombreClients();
    qDebug() << "Nombre de comptes du client :" << client1.getComptes().size();
    qDebug() << "Solde total du client :" << client1.getSoldeTotal();
    qDebug() << "Solde total banque :" << banqueService.calculerSoldeTotalBanque(banque);

    return 0;
}
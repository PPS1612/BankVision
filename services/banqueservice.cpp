#include "banqueservice.h"

BanqueService::BanqueService()
{
}

bool BanqueService::ajouterClient(Banque& banque, Client* client)
{
    if (client == nullptr)
        return false;

    banque.ajouterClient(client);
    return true;
}

bool BanqueService::supprimerClient(Banque& banque, int idClient)
{
    Client* client = banque.rechercherClientParId(idClient);

    if (client == nullptr)
        return false;

    client->setStatut(StatutClient::INACTIF);
    return true;
}

Client* BanqueService::rechercherClient(Banque& banque, int idClient)
{
    return banque.rechercherClientParId(idClient);
}

int BanqueService::getNombreClients(const Banque& banque) const
{
    return banque.getNombreClients();
}

int BanqueService::getNombreComptes(const Banque& banque) const
{
    int total = 0;

    for (Client* client : banque.getClients())
    {
        if (client != nullptr)
            total += client->getComptes().size();
    }

    return total;
}

double BanqueService::calculerSoldeTotalBanque(const Banque& banque) const
{
    return banque.getSoldeTotalBanque();
}

CompteCourant* BanqueService::ouvrirCompteCourant(
    Client& client,
    const QString& iban,
    double soldeInitial,
    double decouvertAutorise
    )
{
    CompteCourant* compte = new CompteCourant(
        iban,
        soldeInitial,
        decouvertAutorise
        );

    client.ajouterCompte(compte);

    return compte;
}

CompteEpargne* BanqueService::ouvrirCompteEpargne(
    Client& client,
    const QString& iban,
    double soldeInitial,
    double tauxInteret
    )
{
    CompteEpargne* compte = new CompteEpargne(
        iban,
        soldeInitial,
        tauxInteret
        );

    client.ajouterCompte(compte);

    return compte;
}

CompteProfessionnel* BanqueService::ouvrirCompteProfessionnel(
    Client& client,
    const QString& iban,
    double soldeInitial,
    const QString& nomEntreprise,
    double plafondRetrait,
    double plafondVirement
    )
{
    CompteProfessionnel* compte = new CompteProfessionnel(
        iban,
        soldeInitial,
        nomEntreprise,
        plafondRetrait,
        plafondVirement
        );

    client.ajouterCompte(compte);

    return compte;
}
#include "banqueservice.h"

BanqueService::BanqueService()
{
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

double BanqueService::calculerSoldeTotalBanque(const Banque& banque) const
{
    return banque.getSoldeTotalBanque();
}

#ifndef BANQUESERVICE_H
#define BANQUESERVICE_H

#include "../models/banque.h"
#include "../models/client.h"
#include "../models/comptecourant.h"
#include "../models/compteepargne.h"
#include "../models/compteprofessionnel.h"

class BanqueService
{
public:
    BanqueService();

    CompteCourant* ouvrirCompteCourant(
        Client& client,
        const QString& iban,
        double soldeInitial,
        double decouvertAutorise
        );

    CompteEpargne* ouvrirCompteEpargne(
        Client& client,
        const QString& iban,
        double soldeInitial,
        double tauxInteret
        );

    CompteProfessionnel* ouvrirCompteProfessionnel(
        Client& client,
        const QString& iban,
        double soldeInitial,
        const QString& nomEntreprise,
        double plafondRetrait,
        double plafondVirement
        );

    double calculerSoldeTotalBanque(const Banque& banque) const;
};

#endif
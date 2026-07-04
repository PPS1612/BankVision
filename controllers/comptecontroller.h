#ifndef COMPTECONTROLLER_H
#define COMPTECONTROLLER_H

#include <QString>

#include "../models/client.h"
#include "../models/comptebancaire.h"
#include "../models/comptecourant.h"
#include "../models/compteepargne.h"
#include "../models/compteprofessionnel.h"

#include "../services/compteservice.h"
#include "../services/banqueservice.h"

class CompteController
{
private:
    CompteService compteService;
    BanqueService banqueService;

public:
    CompteController();

    bool deposer(
        CompteBancaire& compte,
        double montant,
        const QString& description
        );

    bool retirer(
        CompteBancaire& compte,
        double montant,
        const QString& description
        );

    bool virer(
        CompteBancaire& source,
        CompteBancaire& destination,
        double montant,
        const QString& description
        );

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
};

#endif
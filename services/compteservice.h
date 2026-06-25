#ifndef COMPTESERVICE_H
#define COMPTESERVICE_H

#include "../models/comptebancaire.h"
#include "../models/compteepargne.h"

class CompteService
{
public:
    CompteService();

    bool deposer(
        CompteBancaire& compte,
        double montant,
        const QString& description = ""
        );

    bool retirer(
        CompteBancaire& compte,
        double montant,
        const QString& description = ""
        );

    bool virer(
        CompteBancaire& source,
        CompteBancaire& destination,
        double montant,
        const QString& description = ""
        );

    bool appliquerInterets(CompteEpargne& compte);
};

#endif

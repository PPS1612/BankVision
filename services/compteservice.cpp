#include "compteservice.h"

CompteService::CompteService()
{
}

bool CompteService::deposer(
    CompteBancaire& compte,
    double montant,
    const QString& description
    )
{
    return compte.deposer(montant, description);
}

bool CompteService::retirer(
    CompteBancaire& compte,
    double montant,
    const QString& description
    )
{
    return compte.retirer(montant, description);
}

bool CompteService::virer(
    CompteBancaire& source,
    CompteBancaire& destination,
    double montant,
    const QString& description
    )
{
    return source.virer(destination, montant, description);
}

bool CompteService::appliquerInterets(CompteEpargne& compte)
{
    compte.appliquerInterets();
    return true;
}
#include "compteservice.h"
#include "../data/datamanager.h"

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

CompteBancaire* CompteService::rechercherCompteParIBAN(const QString& iban)
{
    return DataManager::getInstance().rechercherCompteParIBAN(iban);
}

QVector<CompteBancaire*> CompteService::getTousLesComptes()
{
    return DataManager::getInstance().getTousLesComptes();
}

bool CompteService::modifierCompte(const CompteBancaire& compte, const QString& type)
{
    return DataManager::getInstance().modifierCompte(compte, type);
}

bool CompteService::supprimerCompte(const QString& iban)
{
    return DataManager::getInstance().supprimerCompte(iban);
}
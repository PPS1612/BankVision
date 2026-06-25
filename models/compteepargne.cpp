#include "compteepargne.h"

CompteEpargne::CompteEpargne(
    const QString& iban,
    double soldeInitial,
    double tauxInteret
    )
    : CompteBancaire(iban, soldeInitial),
    tauxInteret(tauxInteret)
{
}

double CompteEpargne::getTauxInteret() const
{
    return tauxInteret;
}

bool CompteEpargne::retirer(double montant, const QString& description)
{
    if (montant <= 0 || statut != StatutCompte::ACTIF)
        return false;

    if (montant > solde)
        return false;

    solde -= montant;
    enregistrerTransaction("RETRAIT", montant, description);

    return true;
}

void CompteEpargne::appliquerInterets()
{
    if (statut != StatutCompte::ACTIF)
        return;

    double interets = solde * tauxInteret / 100.0;
    solde += interets;

    enregistrerTransaction(
        "INTERETS",
        interets,
        "Application des intérêts"
        );
}
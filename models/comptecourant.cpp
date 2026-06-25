#include "comptecourant.h"

CompteCourant::CompteCourant(
    const QString& iban,
    double soldeInitial,
    double decouvertAutorise
    )
    : CompteBancaire(iban, soldeInitial),
    decouvertAutorise(decouvertAutorise)
{
}

double CompteCourant::getDecouvertAutorise() const
{
    return decouvertAutorise;
}

bool CompteCourant::retirer(double montant, const QString& description)
{
    if (montant <= 0 || statut != StatutCompte::ACTIF)
        return false;

    if (montant > solde + decouvertAutorise)
        return false;

    solde -= montant;
    enregistrerTransaction("RETRAIT", montant, description);

    return true;
}
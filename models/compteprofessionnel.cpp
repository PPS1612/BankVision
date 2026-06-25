#include "compteprofessionnel.h"

CompteProfessionnel::CompteProfessionnel(
    const QString& iban,
    double soldeInitial,
    const QString& nomEntreprise,
    double plafondRetrait,
    double plafondVirement
    )
    : CompteBancaire(iban, soldeInitial),
    nomEntreprise(nomEntreprise),
    plafondRetrait(plafondRetrait),
    plafondVirement(plafondVirement)
{
}

QString CompteProfessionnel::getNomEntreprise() const
{
    return nomEntreprise;
}

double CompteProfessionnel::getPlafondRetrait() const
{
    return plafondRetrait;
}

double CompteProfessionnel::getPlafondVirement() const
{
    return plafondVirement;
}

bool CompteProfessionnel::retirer(double montant, const QString& description)
{
    if (montant <= 0 || statut != StatutCompte::ACTIF)
        return false;

    if (montant > plafondRetrait)
        return false;

    if (montant > solde)
        return false;

    solde -= montant;
    enregistrerTransaction("RETRAIT", montant, description);

    return true;
}

bool CompteProfessionnel::virer(
    CompteBancaire& destination,
    double montant,
    const QString& description
    )
{
    if (montant > plafondVirement)
        return false;

    return CompteBancaire::virer(destination, montant, description);
}
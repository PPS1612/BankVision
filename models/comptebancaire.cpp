#include "comptebancaire.h"

CompteBancaire::CompteBancaire(
    const QString& iban,
    double soldeInitial
    )
    : iban(iban),
    statut(StatutCompte::ACTIF),
    solde(soldeInitial)
{
    if (soldeInitial > 0)
    {
        enregistrerTransaction(
            "OUVERTURE",
            soldeInitial,
            "Solde initial du compte"
            );
    }
}

CompteBancaire::~CompteBancaire()
{
}

QString CompteBancaire::getIBAN() const
{
    return iban;
}

StatutCompte CompteBancaire::getStatut() const
{
    return statut;
}

double CompteBancaire::getSolde() const
{
    return solde;
}

QVector<Transaction> CompteBancaire::getHistorique() const
{
    return historique;
}

bool CompteBancaire::deposer(
    double montant,
    const QString& description
    )
{
    if (montant <= 0)
        return false;

    if (statut != StatutCompte::ACTIF)
        return false;

    solde += montant;

    enregistrerTransaction(
        "DEPOT",
        montant,
        description
        );

    return true;
}

bool CompteBancaire::virer(
    CompteBancaire& destination,
    double montant,
    const QString& description
    )
{
    if (montant <= 0)
        return false;

    if (statut != StatutCompte::ACTIF)
        return false;

    if (retirer(montant, "Virement sortant : " + description))
    {
        destination.deposer(
            montant,
            "Virement entrant : " + description
            );

        return true;
    }

    return false;
}

void CompteBancaire::enregistrerTransaction(
    const QString& type,
    double montant,
    const QString& description
    )
{
    int id = historique.size() + 1;

    Transaction transaction(
        id,
        type,
        montant,
        solde,
        description
        );

    historique.append(transaction);
}
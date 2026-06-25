#ifndef COMPTEBANCAIRE_H
#define COMPTEBANCAIRE_H

#include <QString>
#include <QVector>

#include "transaction.h"

enum class StatutCompte
{
    ACTIF,
    BLOQUE,
    FERME
};

class CompteBancaire
{
protected:
    QString iban;
    StatutCompte statut;
    double solde;
    QVector<Transaction> historique;

    void enregistrerTransaction(
        const QString& type,
        double montant,
        const QString& description
        );

    CompteBancaire(
        const QString& iban,
        double soldeInitial = 0.0
        );

public:
    virtual ~CompteBancaire();

    QString getIBAN() const;
    StatutCompte getStatut() const;
    double getSolde() const;
    QVector<Transaction> getHistorique() const;

    bool deposer(
        double montant,
        const QString& description = ""
        );

    virtual bool retirer(
        double montant,
        const QString& description = ""
        ) = 0;

    virtual bool virer(
        CompteBancaire& destination,
        double montant,
        const QString& description = ""
        );
};

#endif
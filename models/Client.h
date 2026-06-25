#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include "comptebancaire.h"

enum class StatutClient
{
    ACTIF,
    INACTIF
};

class Client
{
private:
    int id;
    QString nom;
    QString email;
    QString telephone;
    QVector<CompteBancaire*> comptes;
    StatutClient statut;

public:
    Client(
        int id,
        const QString& nom,
        const QString& email,
        const QString& telephone
    );

    int getId() const;
    QString getNom() const;
    QString getEmail() const;
    QString getTelephone() const;
    void ajouterCompte(CompteBancaire* compte);
    QVector<CompteBancaire*> getComptes() const;
    double getSoldeTotal() const;
    StatutClient getStatut() const;
    void setStatut(StatutClient statut);
    bool estActif() const;
};
#endif
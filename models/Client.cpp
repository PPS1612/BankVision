#include "Client.h"

Client::Client(
    int id,
    const QString& nom,
    const QString& email,
    const QString& telephone)
    : id(id),
    nom(nom),
    email(email),
    telephone(telephone),
    statut(StatutClient::ACTIF)
{
}

int Client::getId() const
{
    return id;
}

QString Client::getNom() const
{
    return nom;
}

QString Client::getEmail() const
{
    return email;
}

QString Client::getTelephone() const
{
    return telephone;
}

void Client::ajouterCompte(CompteBancaire* compte)
{
    if (compte != nullptr)
    {
        comptes.append(compte);
    }
}

QVector<CompteBancaire*> Client::getComptes() const
{
    return comptes;
}

double Client::getSoldeTotal() const
{
    double total = 0.0;

    for (CompteBancaire* compte : comptes)
    {
        if (compte != nullptr)
        {
            total += compte->getSolde();
        }
    }

    return total;


}

StatutClient Client::getStatut() const
{
    return statut;
}

void Client::setStatut(StatutClient statut)
{
    this->statut = statut;
}

bool Client::estActif() const
{
    return statut == StatutClient::ACTIF;
}
#include "banque.h"

Banque::Banque(const QString& nom)
    : nom(nom)
{
}

QString Banque::getNom() const
{
    return nom;
}

QVector<Client*> Banque::getClients() const
{
    return clients;
}

void Banque::ajouterClient(Client* client)
{
    if (client != nullptr)
    {
        clients.append(client);
    }
}

Client* Banque::rechercherClientParId(int id) const
{
    for (Client* client : clients)
    {
        if (client != nullptr && client->getId() == id)
        {
            return client;
        }
    }

    return nullptr;
}

int Banque::getNombreClients() const
{
    return clients.size();
}

double Banque::getSoldeTotalBanque() const
{
    double total = 0.0;

    for (Client* client : clients)
    {
        if (client != nullptr)
        {
            total += client->getSoldeTotal();
        }
    }

    return total;
}

bool Banque::desactiverClient(int id)
{
    Client* client = rechercherClientParId(id);

    if (client == nullptr)
        return false;

    client->setStatut(StatutClient::INACTIF);
    return true;
}

bool Banque::reactiverClient(int id)
{
    Client* client = rechercherClientParId(id);

    if (client == nullptr)
        return false;

    client->setStatut(StatutClient::ACTIF);
    return true;
}
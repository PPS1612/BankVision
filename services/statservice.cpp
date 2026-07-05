#include "statservice.h"

StatService::StatService()
{
}

int StatService::getNombreClients(const Banque& banque) const
{
    return banque.getNombreClients();
}

int StatService::getNombreComptes(const Banque& banque) const
{
    int total = 0;

    for (Client* client : banque.getClients())
    {
        if (client != nullptr)
            total += client->getComptes().size();
    }

    return total;
}

double StatService::getSoldeTotalBanque(const Banque& banque) const
{
    return banque.getSoldeTotalBanque();
}

double StatService::getSoldeMoyenParClient(const Banque& banque) const
{
    int nbClients = getNombreClients(banque);

    if (nbClients == 0)
        return 0.0;

    return getSoldeTotalBanque(banque) / nbClients;
}

double StatService::getSoldeMoyenParCompte(const Banque& banque) const
{
    int nbComptes = getNombreComptes(banque);

    if (nbComptes == 0)
        return 0.0;

    return getSoldeTotalBanque(banque) / nbComptes;
}

Client* StatService::getClientPlusRiche(const Banque& banque) const
{
    Client* meilleurClient = nullptr;
    double meilleurSolde = -1.0;

    for (Client* client : banque.getClients())
    {
        if (client != nullptr && client->getSoldeTotal() > meilleurSolde)
        {
            meilleurSolde = client->getSoldeTotal();
            meilleurClient = client;
        }
    }

    return meilleurClient;
}

Client* StatService::getClientAvecPlusDeComptes(const Banque& banque) const
{
    Client* meilleurClient = nullptr;
    int maxComptes = -1;

    for (Client* client : banque.getClients())
    {
        if (client != nullptr && client->getComptes().size() > maxComptes)
        {
            maxComptes = client->getComptes().size();
            meilleurClient = client;
        }
    }

    return meilleurClient;
}
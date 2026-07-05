#include "clientservice.h"
#include "../data/datamanager.h"
ClientService::ClientService()
{
}

bool ClientService::ajouterClient(Banque& banque, Client* client)
{
    if (client == nullptr)
        return false;

    banque.ajouterClient(client);
    return true;
}

Client* ClientService::rechercherClientParId(const Banque& banque, int id)
{
    return banque.rechercherClientParId(id);
}

bool ClientService::desactiverClient(Banque& banque, int id)
{
    return banque.desactiverClient(id);
}

bool ClientService::reactiverClient(Banque& banque, int id)
{
    return banque.reactiverClient(id);
}

QVector<Client*> ClientService::getTousLesClients()
{
    return DataManager::getInstance().getTousLesClients();
}

bool ClientService::modifierClient(const Client& client)
{
    return DataManager::getInstance().modifierClient(client);
}

bool ClientService::supprimerClient(int id)
{
    return DataManager::getInstance().supprimerClient(id);
}

Client* ClientService::rechercherClientParId(int id)
{
    return DataManager::getInstance().rechercherClientParId(id);
}

bool ClientService::ajouterClient(const Client& client)
{
    return DataManager::getInstance().sauvegarderClient(client);
}
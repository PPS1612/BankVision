#include "clientservice.h"

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
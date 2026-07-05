#ifndef CLIENTSERVICE_H
#define CLIENTSERVICE_H

#include "../models/banque.h"
#include "../models/client.h"
#include <QVector>
#include "../models/Client.h"

class ClientService
{
public:
    ClientService();

    bool ajouterClient(Banque& banque, Client* client);
    Client* rechercherClientParId(const Banque& banque, int id);

    bool desactiverClient(Banque& banque, int id);
    bool reactiverClient(Banque& banque, int id);

    QVector<Client*> getTousLesClients();
    bool modifierClient(const Client& client);
    bool supprimerClient(int id);
    Client* rechercherClientParId(int id);
    bool ajouterClient(const Client& client);
};

#endif
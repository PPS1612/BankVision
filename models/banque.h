#ifndef BANQUE_H
#define BANQUE_H

#include <QString>
#include <QVector>

#include "client.h"

class Banque
{
private:
    QString nom;
    QVector<Client*> clients;

public:
    Banque(const QString& nom);

    QString getNom() const;

    QVector<Client*> getClients() const;

    void ajouterClient(Client* client);

    Client* rechercherClientParId(int id) const;

    int getNombreClients() const;

    double getSoldeTotalBanque() const;

    bool desactiverClient(int id);

    bool reactiverClient(int id);
};

#endif
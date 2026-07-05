#ifndef STATSERVICE_H
#define STATSERVICE_H

#include "../models/banque.h"

class StatService
{
public:
    StatService();

    int getNombreClients(const Banque& banque) const;
    int getNombreComptes(const Banque& banque) const;

    double getSoldeTotalBanque(const Banque& banque) const;
    double getSoldeMoyenParClient(const Banque& banque) const;
    double getSoldeMoyenParCompte(const Banque& banque) const;

    Client* getClientPlusRiche(const Banque& banque) const;
    Client* getClientAvecPlusDeComptes(const Banque& banque) const;
};

#endif
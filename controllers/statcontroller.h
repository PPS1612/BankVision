#ifndef STATCONTROLLER_H
#define STATCONTROLLER_H

#include "../models/banque.h"

class StatController
{
public:
    StatController();

    int getNombreClients(const Banque& banque) const;
    int getNombreComptes(const Banque& banque) const;
    double getSoldeTotalBanque(const Banque& banque) const;
    double getSoldeMoyenClient(const Banque& banque) const;
};

#endif
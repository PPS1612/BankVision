#include "statcontroller.h"

StatController::StatController()
{
}

int StatController::getNombreClients(const Banque& banque) const
{
    return banque.getNombreClients();
}

int StatController::getNombreComptes(const Banque& banque) const
{
    int total = 0;

    for (Client* client : banque.getClients())
    {
        if (client != nullptr)
        {
            total += client->getComptes().size();
        }
    }

    return total;
}

double StatController::getSoldeTotalBanque(const Banque& banque) const
{
    return banque.getSoldeTotalBanque();
}

double StatController::getSoldeMoyenClient(const Banque& banque) const
{
    int nombreClients = banque.getNombreClients();

    if (nombreClients == 0)
        return 0.0;

    return banque.getSoldeTotalBanque() / nombreClients;
}
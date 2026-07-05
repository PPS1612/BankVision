#include "transactionservice.h"
#include "../data/datamanager.h"

TransactionService::TransactionService()
{

}

bool TransactionService::ajouterTransaction(
    const Transaction& transaction,
    const QString& ibanCompte)
{
    return DataManager::getInstance()
    .sauvegarderTransaction(transaction, ibanCompte);
}

QVector<Transaction> TransactionService::getHistoriqueCompte(
    const QString& ibanCompte)
{
    return DataManager::getInstance().getHistoriqueCompte(ibanCompte);
}
#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client
{
private:
    int id;
    std::string nom;
    std::string email;
    std::string telephone;

public:

    Client(
        int id,
        const std::string& nom,
        const std::string& email,
        const std::string& telephone)
        :
        id(id),
        nom(nom),
        email(email),
        telephone(telephone)
    {
    }

    int getId() const
    {
        return id;
    }

    const std::string& getNom() const
    {
        return nom;
    }

    const std::string& getEmail() const
    {
        return email;
    }

    const std::string& getTelephone() const
    {
        return telephone;
    }
};

#endif
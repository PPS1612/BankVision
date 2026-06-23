#include <iostream>
#include "models/Client.h"

int main() {
    Client client(1,"sage","sagpoaty16@gmail.com","185233261");

    std::cout<<"nom: "<<client.getNom()<<std::endl;
    std::cout<<"Email: "<<client.getEmail()<<std::endl;
    return 0;
}
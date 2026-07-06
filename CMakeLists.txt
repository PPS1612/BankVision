cmake_minimum_required(VERSION 3.16)

project(BankVision VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.11.1/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

add_executable(BankVision
    main.cpp

    models/Client.h
    models/Client.cpp

    models/transaction.h
    models/transaction.cpp

    models/comptebancaire.h
    models/comptebancaire.cpp

    models/comptecourant.h
    models/comptecourant.cpp

    models/compteepargne.h
    models/compteepargne.cpp

    models/compteprofessionnel.h
    models/compteprofessionnel.cpp
    models/banque.h models/banque.cpp
    services/clientservice.h services/clientservice.cpp
    services/compteservice.h services/compteservice.cpp
    services/banqueservice.h services/banqueservice.cpp
    data/datamanager.h data/datamanager.cpp
    models/pret.h models/pret.cpp
    models/utilisateur.h models/utilisateur.cpp
    controllers/authcontroller.h controllers/authcontroller.cpp
    controllers/comptecontroller.h controllers/comptecontroller.cpp
    controllers/statcontroller.h controllers/statcontroller.cpp
    services/transactionservice.h services/transactionservice.cpp
    services/pretservice.h services/pretservice.cpp
    services/statservice.h services/statservice.cpp

    views/FenetreConnexion.h
    views/FenetreConnexion.cpp

    resources/style.qss
    views/fenetretableaubord.h views/fenetretableaubord.cpp
    views/fenetreclients.h views/fenetreclients.cpp
    views/fenetrecomptes.h views/fenetrecomptes.cpp
    views/fenetreoperations.h views/fenetreoperations.cpp
)
target_link_libraries(BankVision PRIVATE Qt6::Core Qt6::Widgets Qt6::Sql)
#ifndef FENETRECONNEXION_H
#define FENETRECONNEXION_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class FenetreConnexion : public QWidget
{
    Q_OBJECT

private:
    QLineEdit* champLogin;
    QLineEdit* champMotDePasse;
    QPushButton* boutonConnexion;
    QLabel* labelMessage;

    void construireInterface();
    void appliquerStyle();

private slots:
    void seConnecter();

public:
    explicit FenetreConnexion(QWidget *parent = nullptr);
};

#endif
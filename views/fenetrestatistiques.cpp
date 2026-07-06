#include "fenetrestatistiques.h"

#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QtMath>
#include <algorithm>

// ════════════════════════════════════════════════════════════════════════════
//  GraphiqueCourbe  —  Courbe d'évolution du solde sur 12 mois
// ════════════════════════════════════════════════════════════════════════════

GraphiqueCourbe::GraphiqueCourbe(QWidget* parent) : QWidget(parent)
{
    setMinimumHeight(220);
}

void GraphiqueCourbe::setDonnees(const QVector<double>& v, const QVector<QString>& e)
{
    valeurs    = v;
    etiquettes = e;
    update();
}

void GraphiqueCourbe::paintEvent(QPaintEvent*)
{
    if (valeurs.size() < 2) return;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const int W = width(), H = height();
    const int MG_G = 14, MG_D = 14, MG_H = 20, MG_B = 36;
    const int largeurTrace = W - MG_G - MG_D;
    const int hauteurTrace = H - MG_H - MG_B;

    // Fond transparent (le QFrame parent gère la couleur)
    p.fillRect(rect(), Qt::transparent);

    double maxV = *std::max_element(valeurs.begin(), valeurs.end());
    double minV = *std::min_element(valeurs.begin(), valeurs.end());
    if (maxV == minV) { maxV = minV + 1; }
    double plage = maxV - minV;

    int n = valeurs.size();

    auto xPt = [&](int i) -> double {
        return MG_G + (double)i / (n - 1) * largeurTrace;
    };
    auto yPt = [&](double v) -> double {
        return MG_H + (1.0 - (v - minV) / plage) * hauteurTrace;
    };

    // ── Lignes de grille horizontales ────────────────────────────────────
    p.setPen(QPen(QColor(210, 225, 245), 1, Qt::DashLine));
    for (int k = 0; k <= 4; ++k) {
        int y = MG_H + k * hauteurTrace / 4;
        p.drawLine(MG_G, y, W - MG_D, y);
    }

    // ── Zone remplie sous la courbe ───────────────────────────────────────
    QPainterPath aire;
    aire.moveTo(xPt(0), H - MG_B);
    for (int i = 0; i < n; ++i)
        aire.lineTo(xPt(i), yPt(valeurs[i]));
    aire.lineTo(xPt(n - 1), H - MG_B);
    aire.closeSubpath();

    QLinearGradient fillGrad(0, MG_H, 0, H - MG_B);
    fillGrad.setColorAt(0.0, QColor(0, 87, 184, 80));
    fillGrad.setColorAt(1.0, QColor(0, 87, 184, 0));
    p.fillPath(aire, fillGrad);

    // ── Courbe principale ─────────────────────────────────────────────────
    QPainterPath courbe;
    courbe.moveTo(xPt(0), yPt(valeurs[0]));
    for (int i = 1; i < n; ++i) {
        double cx = (xPt(i - 1) + xPt(i)) / 2.0;
        courbe.cubicTo(cx, yPt(valeurs[i - 1]), cx, yPt(valeurs[i]), xPt(i), yPt(valeurs[i]));
    }
    p.setPen(QPen(QColor(0, 87, 184), 2.5));
    p.drawPath(courbe);

    // ── Points sur la courbe ──────────────────────────────────────────────
    for (int i = 0; i < n; ++i) {
        double x = xPt(i), y = yPt(valeurs[i]);
        p.setBrush(QColor(255, 255, 255));
        p.setPen(QPen(QColor(0, 87, 184), 2));
        p.drawEllipse(QPointF(x, y), 4.5, 4.5);
    }

    // ── Étiquettes des mois en bas ────────────────────────────────────────
    p.setPen(QColor(107, 114, 128));
    p.setFont(QFont("Segoe UI", 8));
    for (int i = 0; i < n && i < etiquettes.size(); ++i) {
        QRectF rect(xPt(i) - 18, H - MG_B + 6, 36, 20);
        p.drawText(rect, Qt::AlignCenter, etiquettes[i]);
    }
}

// ════════════════════════════════════════════════════════════════════════════
//  GraphiqueCamembert  —  Répartition dépenses par catégorie
// ════════════════════════════════════════════════════════════════════════════

GraphiqueCamembert::GraphiqueCamembert(QWidget* parent) : QWidget(parent)
{
    setMinimumHeight(220);
    couleurs = {
        QColor(0,   87, 184),
        QColor(22, 163,  74),
        QColor(234, 179,   8),
        QColor(220,  38,  38),
        QColor(139,  92, 246),
        QColor(14,  165, 233)
    };
}

void GraphiqueCamembert::setDonnees(const QVector<QString>& l, const QVector<double>& pts)
{
    labels = l;
    parts  = pts;
    update();
}

void GraphiqueCamembert::paintEvent(QPaintEvent*)
{
    if (parts.isEmpty()) return;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const int W = width(), H = height();
    p.fillRect(rect(), Qt::transparent);

    double total = 0;
    for (double v : parts) total += v;
    if (total <= 0) return;

    // Zone disque  (moitié gauche)
    int diam   = qMin(W / 2 - 20, H - 40);
    int cx     = W / 4;
    int cy     = H / 2;
    QRectF disque(cx - diam / 2, cy - diam / 2, diam, diam);

    double angle = -90.0 * 16;   // format Qt : 1/16 de degré

    for (int i = 0; i < parts.size(); ++i) {
        double span = parts[i] / total * 360.0 * 16;
        p.setBrush(couleurs[i % couleurs.size()]);
        p.setPen(QPen(Qt::white, 2));
        p.drawPie(disque, (int)angle, (int)span);
        angle += span;
    }

    // Trou central (donut)
    int trouDiam = diam / 2;
    p.setBrush(Qt::white);
    p.setPen(Qt::NoPen);
    p.drawEllipse(QPointF(cx, cy), trouDiam / 2.0, trouDiam / 2.0);

    // Légende  (moitié droite)
    int legendeX = W / 2 + 10;
    int legendeY = cy - (parts.size() * 24) / 2;

    p.setFont(QFont("Segoe UI", 9));
    for (int i = 0; i < labels.size() && i < parts.size(); ++i) {
        QColor c = couleurs[i % couleurs.size()];
        p.setBrush(c);
        p.setPen(Qt::NoPen);
        p.drawRoundedRect(legendeX, legendeY + i * 26, 12, 12, 3, 3);

        p.setPen(QColor(55, 65, 81));
        double pct = parts[i] / total * 100.0;
        p.drawText(legendeX + 18, legendeY + i * 26,
                   W - legendeX - 18, 18,
                   Qt::AlignVCenter | Qt::AlignLeft,
                   QString("%1  %2%").arg(labels[i]).arg(pct, 0, 'f', 1));
    }
}

// ════════════════════════════════════════════════════════════════════════════
//  GraphiqueHistogramme  —  Recettes vs Dépenses
// ════════════════════════════════════════════════════════════════════════════

GraphiqueHistogramme::GraphiqueHistogramme(QWidget* parent) : QWidget(parent)
{
    setMinimumHeight(220);
}

void GraphiqueHistogramme::setDonnees(const QVector<double>& r, const QVector<double>& d,
                                      const QVector<QString>& m)
{
    recettes = r;
    depenses = d;
    mois     = m;
    update();
}

void GraphiqueHistogramme::paintEvent(QPaintEvent*)
{
    if (recettes.isEmpty()) return;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const int W = width(), H = height();
    const int MG_G = 10, MG_D = 10, MG_H = 20, MG_B = 36;
    p.fillRect(rect(), Qt::transparent);

    int n = recettes.size();
    double maxV = 0;
    for (int i = 0; i < n; ++i) {
        maxV = qMax(maxV, qMax(recettes[i], depenses[i]));
    }
    if (maxV <= 0) return;

    const int hauteurTrace = H - MG_H - MG_B;
    const int largeurZone  = (W - MG_G - MG_D) / n;
    const int largeurBarre = qMax(6, largeurZone / 3 - 4);

    // Lignes de grille
    p.setPen(QPen(QColor(210, 225, 245), 1, Qt::DashLine));
    for (int k = 1; k <= 4; ++k) {
        int y = MG_H + k * hauteurTrace / 4;
        p.drawLine(MG_G, y, W - MG_D, y);
    }

    for (int i = 0; i < n; ++i) {
        int cx = MG_G + i * largeurZone + largeurZone / 2;

        // Barre recettes (bleu)
        int hR = (int)(recettes[i] / maxV * hauteurTrace);
        QRectF barreR(cx - largeurBarre - 2, H - MG_B - hR, largeurBarre, hR);
        QLinearGradient gR(barreR.topLeft(), barreR.bottomLeft());
        gR.setColorAt(0, QColor(0, 87, 184));
        gR.setColorAt(1, QColor(0, 87, 184, 160));
        p.setBrush(gR);
        p.setPen(Qt::NoPen);
        p.drawRoundedRect(barreR, 4, 4);

        // Barre dépenses (rouge)
        int hD = (int)(depenses[i] / maxV * hauteurTrace);
        QRectF barreD(cx + 2, H - MG_B - hD, largeurBarre, hD);
        QLinearGradient gD(barreD.topLeft(), barreD.bottomLeft());
        gD.setColorAt(0, QColor(220, 38, 38));
        gD.setColorAt(1, QColor(220, 38, 38, 160));
        p.setBrush(gD);
        p.drawRoundedRect(barreD, 4, 4);

        // Mois
        p.setPen(QColor(107, 114, 128));
        p.setFont(QFont("Segoe UI", 8));
        p.drawText(cx - 18, H - MG_B + 6, 36, 20, Qt::AlignCenter,
                   i < mois.size() ? mois[i] : "");
    }

    // Légende
    p.setFont(QFont("Segoe UI", 9, QFont::Bold));
    p.setBrush(QColor(0, 87, 184));
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(W - 165, 4, 12, 12, 3, 3);
    p.setPen(QColor(55, 65, 81));
    p.drawText(W - 150, 4, 80, 14, Qt::AlignVCenter | Qt::AlignLeft, "Recettes");

    p.setBrush(QColor(220, 38, 38));
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(W - 80, 4, 12, 12, 3, 3);
    p.setPen(QColor(55, 65, 81));
    p.drawText(W - 65, 4, 70, 14, Qt::AlignVCenter | Qt::AlignLeft, "Dépenses");
}

// ════════════════════════════════════════════════════════════════════════════
//  FenetreStatistiques
// ════════════════════════════════════════════════════════════════════════════

FenetreStatistiques::FenetreStatistiques(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("BankVision - Statistiques");
    resize(1200, 780);
    construireInterface();
    appliquerStyle();
    chargerDonneesTest();
}

static QFrame* creerCarteGraphique(const QString& titre, QWidget* graphique, int hauteur = 250)
{
    QFrame* carte = new QFrame;
    carte->setObjectName("carteGraphique");

    QGraphicsDropShadowEffect* ombre = new QGraphicsDropShadowEffect;
    ombre->setBlurRadius(20);
    ombre->setOffset(0, 4);
    ombre->setColor(QColor(15, 23, 42, 25));
    carte->setGraphicsEffect(ombre);

    QVBoxLayout* layout = new QVBoxLayout(carte);
    layout->setContentsMargins(22, 18, 22, 18);
    layout->setSpacing(12);

    QLabel* labelTitre = new QLabel(titre);
    labelTitre->setObjectName("titreCarte");
    layout->addWidget(labelTitre);

    graphique->setMinimumHeight(hauteur);
    layout->addWidget(graphique);

    return carte;
}

static QFrame* creerIndicateur(const QString& label, const QString& valeur,
                                const QString& couleurValeur = "#0057B8")
{
    QFrame* carte = new QFrame;
    carte->setObjectName("carteIndicateur");

    QGraphicsDropShadowEffect* ombre = new QGraphicsDropShadowEffect;
    ombre->setBlurRadius(16);
    ombre->setOffset(0, 3);
    ombre->setColor(QColor(15, 23, 42, 20));
    carte->setGraphicsEffect(ombre);

    QVBoxLayout* layout = new QVBoxLayout(carte);
    layout->setContentsMargins(20, 16, 20, 16);
    layout->setSpacing(6);

    QLabel* lbl = new QLabel(label);
    lbl->setObjectName("labelIndicateur");

    QLabel* val = new QLabel(valeur);
    val->setObjectName("valeurIndicateur");
    val->setStyleSheet(QString("color: %1;").arg(couleurValeur));

    layout->addWidget(lbl);
    layout->addWidget(val);

    return carte;
}

void FenetreStatistiques::construireInterface()
{
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(34, 28, 34, 28);
    layoutPrincipal->setSpacing(20);

    // ── En-tête ───────────────────────────────────────────────────────────
    QLabel* titre = new QLabel("Statistiques & Analyses");
    titre->setObjectName("titre");

    QLabel* sousTitre = new QLabel("Vue d'ensemble de l'activité financière — 12 derniers mois");
    sousTitre->setObjectName("sousTitre");

    layoutPrincipal->addWidget(titre);
    layoutPrincipal->addWidget(sousTitre);

    // ── Indicateurs clés ──────────────────────────────────────────────────
    QHBoxLayout* layoutIndicateurs = new QHBoxLayout;
    layoutIndicateurs->setSpacing(18);

    QFrame* carteS = creerIndicateur("Solde actuel",    "1 245 000 FCFA", "#0057B8");
    QFrame* carteSM = creerIndicateur("Solde moyen",    "980 000 FCFA",   "#16A34A");
    QFrame* carteDM = creerIndicateur("Dépense max",    "320 000 FCFA",   "#DC2626");
    QFrame* carteTE = creerIndicateur("Taux d'épargne", "22.4 %",         "#7C3AED");

    // On garde les refs pour pouvoir les mettre à jour plus tard
    labelSoldeActuel = carteS->findChildren<QLabel*>().last();
    labelSoldeMoyen  = carteSM->findChildren<QLabel*>().last();
    labelDepenseMax  = carteDM->findChildren<QLabel*>().last();
    labelTauxEpargne = carteTE->findChildren<QLabel*>().last();

    layoutIndicateurs->addWidget(carteS);
    layoutIndicateurs->addWidget(carteSM);
    layoutIndicateurs->addWidget(carteDM);
    layoutIndicateurs->addWidget(carteTE);

    layoutPrincipal->addLayout(layoutIndicateurs);

    // ── Courbe du solde (pleine largeur) ──────────────────────────────────
    graphiqueCourbe = new GraphiqueCourbe;
    QFrame* carteCourbe = creerCarteGraphique("Évolution du solde", graphiqueCourbe, 220);
    layoutPrincipal->addWidget(carteCourbe);

    // ── Camembert + Histogramme côte à côte ───────────────────────────────
    QHBoxLayout* layoutBas = new QHBoxLayout;
    layoutBas->setSpacing(18);

    graphiqueCamembert   = new GraphiqueCamembert;
    graphiqueHistogramme = new GraphiqueHistogramme;

    QFrame* carteCamembert   = creerCarteGraphique("Dépenses par catégorie", graphiqueCamembert, 200);
    QFrame* carteHistogramme = creerCarteGraphique("Recettes vs Dépenses",   graphiqueHistogramme, 200);

    layoutBas->addWidget(carteCamembert,   1);
    layoutBas->addWidget(carteHistogramme, 1);

    layoutPrincipal->addLayout(layoutBas);
}

void FenetreStatistiques::appliquerStyle()
{
    setStyleSheet(
        "QWidget {"
        "   background: #F4F7FB;"
        "   font-family: 'Segoe UI';"
        "   color: #0F172A;"
        "}"

        "QLabel { background: transparent; }"

        "QLabel#titre {"
        "   color: #0057B8;"
        "   font-size: 32px;"
        "   font-weight: 900;"
        "}"

        "QLabel#sousTitre {"
        "   color: #6B7280;"
        "   font-size: 15px;"
        "}"

        "QFrame#carteGraphique {"
        "   background: white;"
        "   border: 1px solid #D9E2EC;"
        "   border-radius: 18px;"
        "}"

        "QLabel#titreCarte {"
        "   color: #1F2937;"
        "   font-size: 15px;"
        "   font-weight: 800;"
        "}"

        "QFrame#carteIndicateur {"
        "   background: white;"
        "   border: 1px solid #D9E2EC;"
        "   border-radius: 16px;"
        "}"

        "QLabel#labelIndicateur {"
        "   color: #6B7280;"
        "   font-size: 13px;"
        "   font-weight: 600;"
        "}"

        "QLabel#valeurIndicateur {"
        "   font-size: 22px;"
        "   font-weight: 900;"
        "}"
    );
}

void FenetreStatistiques::chargerDonneesTest()
{
    // Courbe — soldes mensuels (FCFA)
    QVector<double> soldes = {
        820000, 950000, 870000, 1100000, 1050000, 980000,
        1150000, 1200000, 1080000, 1300000, 1245000, 1245000
    };
    QVector<QString> moisCourbe = {
        "Jan","Fév","Mar","Avr","Mai","Jun",
        "Jul","Aoû","Sep","Oct","Nov","Déc"
    };
    graphiqueCourbe->setDonnees(soldes, moisCourbe);

    // Camembert — catégories de dépenses
    QVector<QString> categories = { "Alimentation", "Transport", "Logement", "Loisirs", "Santé" };
    QVector<double>  partsCat   = { 35.0, 20.0, 25.0, 12.0, 8.0 };
    graphiqueCamembert->setDonnees(categories, partsCat);

    // Histogramme — recettes vs dépenses sur 6 mois
    QVector<double>  recettes = { 500000, 620000, 480000, 700000, 650000, 720000 };
    QVector<double>  depenses = { 380000, 410000, 390000, 450000, 420000, 475000 };
    QVector<QString> moisHist = { "Jul","Aoû","Sep","Oct","Nov","Déc" };
    graphiqueHistogramme->setDonnees(recettes, depenses, moisHist);
}

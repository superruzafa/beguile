#define BEGUILE_LANG_ES
#include <beguile.h>

#ifndef Caracteristica
#error Beguile compiled without Spanish support!
#endif

volatile int i;

FeatureRunner

Caracteristica ("Un ejemplo en español")
    Antecedentes
        Dado(i = 10)
    FinAntecedentes

    Escenario ("Al cuadrado")
        Cuando (i *= i)
        Entonces (i deberia_ser(100))
    FinEscenario
FinCaracteristica

EndFeatureRunner

#ifdef BEGUILE_LANG_ES

#define Caracteristica(feature_name)            BEGUILE_FEATURE("Característica", feature_name)
#define FinCaracteristica                       BEGUILE_ENDFEATURE

#define Como(role)                              BEGUILE_FEATURE_INTRO("Como", role)
#define Quiero(feature)                         BEGUILE_FEATURE_INTRO("Quiero", feature)
#define Para_poder(benefit)                     BEGUILE_FEATURE_INTRO("Para poder", benefit)

#define Antecedentes                            BEGUILE_BACKGROUND("Antecedentes")
#define FinAntecedentes                         BEGUILE_ENDBACKGROUND

#define Escenario(scenario_name)                BEGUILE_SCENARIO("Escenario", scenario_name)
#define FinEscenario                            BEGUILE_ENDSCENARIO

#define Dado(...)                               BEGUILE_STEP("Dado",     #__VA_ARGS__, __VA_ARGS__)
#define Dada(...)                               BEGUILE_STEP("Dada",     #__VA_ARGS__, __VA_ARGS__)
#define Dados(...)                              BEGUILE_STEP("Dados",    #__VA_ARGS__, __VA_ARGS__)
#define Dadas(...)                              BEGUILE_STEP("Dadas",    #__VA_ARGS__, __VA_ARGS__)
#define Cuando(...)                             BEGUILE_STEP("Cuando",   #__VA_ARGS__, __VA_ARGS__)
#define Entonces(...)                           BEGUILE_STEP("Entonces", #__VA_ARGS__, __VA_ARGS__)
#define Y(...)                                  BEGUILE_STEP("Y",        #__VA_ARGS__, __VA_ARGS__)
#define Pero(...)                               BEGUILE_STEP("Pero",     #__VA_ARGS__, __VA_ARGS__)

#define deberia_ser_igual_a(x)                  BEGUILE_ASSERT_SHOULD_BE_EQUAL_TO(x)
#define deberia_ser(x)                          BEGUILE_ASSERT_SHOULD_BE_EQUAL_TO(x)
#define no_deberia_ser_igual_a(x)               BEGUILE_ASSERT_SHOULD_NOT_BE_EQUAL_TO(x)
#define no_deberia_ser(x)                       BEGUILE_ASSERT_SHOULD_NOT_BE_EQUAL_TO(x)
#define deberia_ser_menor_que(x)                BEGUILE_ASSERT_SHOULD_BE_LESS_THAN(x)
#define deberia_ser_menor_o_igual_a(x)          BEGUILE_ASSERT_SHOULD_BE_LESS_OR_EQUAL_THAN(x)
#define deberia_ser_mayor_que(x)                BEGUILE_ASSERT_SHOULD_BE_GREATER_THAN(x)
#define deberia_ser_mayor_o_igual_a(x)          BEGUILE_ASSERT_SHOULD_BE_GREATER_OR_EQUAL_THAN(x)
#define deberia_ser_nulo                        BEGUILE_ASSERT_SHOULD_BE_NULL
#define no_deberia_ser_nulo                     BEGUILE_ASSERT_SHOULD_NOT_BE_NULL

#define BEGUILE_MSG_OK                          "BIEN"
#define BEGUILE_MSG_FAIL                        "FALLO"

#define BEGUILE_MSG_SUMMARY_FEATURES            "%d características"
#define BEGUILE_MSG_SUMMARY_SCENARIOS           "%d escenarios"
#define BEGUILE_MSG_SUMMARY_STEPS               "%d pasos"
#define BEGUILE_MSG_SUMMARY_ALL_PASSED          "todos pasaron"
#define BEGUILE_MSG_SUMMARY_FAILED              "%d fallaron"

#define BEGUILE_MSG_COULD_NOT_PIPE              "No se pudo crear la tubería del escenario"
#define BEGUILE_MSG_COULD_NOT_FORK              "No se pudo bifurcar el subproceso del escenario"

#endif


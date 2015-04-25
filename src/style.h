#define BEGUILE_STYLE_RESET                 "\x1b[0m"
#define BEGUILE_STYLE_BOLD                  "\x1b[1m"
#define BEGUILE_STYLE_ITALIC                "\x1b[3m"
#define BEGUILE_STYLE_UNDERLINE             "\x1b[4m"
#define BEGUILE_STYLE_BLINK                 "\x1b[5m"
#define BEGUILE_STYLE_STRIKETHROUGH         "\x1b[9m"
#define BEGUILE_STYLE_FOREGROUND_BLACK      "\x1b[30m"
#define BEGUILE_STYLE_FOREGROUND_RED        "\x1b[31m"
#define BEGUILE_STYLE_FOREGROUND_GREEN      "\x1b[32m"
#define BEGUILE_STYLE_FOREGROUND_YELLOW     "\x1b[33m"
#define BEGUILE_STYLE_FOREGROUND_BLUE       "\x1b[34m"
#define BEGUILE_STYLE_FOREGROUND_MAGENTA    "\x1b[35m"
#define BEGUILE_STYLE_FOREGROUND_CYAN       "\x1b[36m"
#define BEGUILE_STYLE_FOREGROUND_WHITE      "\x1b[37m"
#define BEGUILE_STYLE_FOREGROUND_DEFAULT    "\x1b[38m"
#define BEGUILE_STYLE_BACKGROUND_BLACK      "\x1b[40m"
#define BEGUILE_STYLE_BACKGROUND_RED        "\x1b[41m"
#define BEGUILE_STYLE_BACKGROUND_GREEN      "\x1b[42m"
#define BEGUILE_STYLE_BACKGROUND_YELLOW     "\x1b[43m"
#define BEGUILE_STYLE_BACKGROUND_BLUE       "\x1b[44m"
#define BEGUILE_STYLE_BACKGROUND_MAGENTA    "\x1b[45m"
#define BEGUILE_STYLE_BACKGROUND_CYAN       "\x1b[46m"
#define BEGUILE_STYLE_BACKGROUND_WHITE      "\x1b[47m"
#define BEGUILE_STYLE_BACKGROUND_DEFAULT    "\x1b[49m"

#define BEGUILE_STYLE_KEYWORD(keyword)                  BEGUILE_STYLE_BOLD keyword BEGUILE_STYLE_RESET
#define BEGUILE_STYLE_FEATURE(feature_keyword)          BEGUILE_STYLE_KEYWORD(feature_keyword)
#define BEGUILE_STYLE_BACKGROUND(background_keyword)    BEGUILE_STYLE_KEYWORD(background_keyword)
#define BEGUILE_STYLE_SCENARIO(scenario_keyword)        BEGUILE_STYLE_KEYWORD(scenario_keyword)
#define BEGUILE_STYLE_STEP(step_keyword)                BEGUILE_STYLE_FOREGROUND_YELLOW step_keyword BEGUILE_STYLE_RESET

#define BEGUILE_STYLE_SUCCESS(message)                  BEGUILE_STYLE_FOREGROUND_GREEN message BEGUILE_STYLE_RESET
#define BEGUILE_STYLE_FAILURE(message)                  BEGUILE_STYLE_FOREGROUND_RED message BEGUILE_STYLE_RESET


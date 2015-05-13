#define BEGUILE_PRINT(...) (beguile_global_vars.output_enabled ? printf(__VA_ARGS__) : 0)
#define BEGUILE_FLUSH() (beguile_global_vars.output_enabled ? fflush(stdout) : 0)

#define beguile_enable_pretty_print() beguile_global_vars.pretty_print_enabled = 1
#define beguile_disable_pretty_print() beguile_global_vars.pretty_print_enabled = 0

void beguile_pretty_print(char *string)
{
    char *str = string;
    if (beguile_global_vars.pretty_print_enabled) {
        while (*str != '\0') {
            if (*str == ' ' || *str == '_' || *str == '(' || *str == ')') {
                while (*str != '\0' && (*str == ' ' || *str == '_' || *str == '(' || *str == ')')) ++str;
                if (*str != '\0') BEGUILE_PRINT(" ");
            } else {
                BEGUILE_PRINT("%c", *str);
                ++str;
            }
        }
    } else {
        BEGUILE_PRINT("%s", string);
    }
}

#define beguile_enable_output() beguile_global_vars.output_enabled = 1
#define beguile_disable_output() beguile_global_vars.output_enabled = 0

#define BEGUILE_EOL() BEGUILE_PRINT("\n")

#define BEGUILE_CONCAT(a, b) a ## b

#define BEGUILE_INDENT_1()  BEGUILE_PRINT("  ")
#define BEGUILE_INDENT_2()  BEGUILE_PRINT("    ")
#define BEGUILE_INDENT_3()  BEGUILE_PRINT("      ")


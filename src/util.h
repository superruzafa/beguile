#define BEGUILE_PRINT(...)  printf(__VA_ARGS__)
#define BEGUILE_FLUSH fflush(stdout);

#define BEGUILE_EOL BEGUILE_PRINT("\n")

#define BEGUILE_CONCAT(a, b) a ## b

#define BEGUILE_INDENT_1    BEGUILE_PRINT("  ")
#define BEGUILE_INDENT_2    BEGUILE_PRINT("    ")
#define BEGUILE_INDENT_3    BEGUILE_PRINT("      ")


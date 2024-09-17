#include <stdio.h>
#include "ExpressionParser/ExpressionParser.h"

int main(void)
{
    //"x exp x ln 2 * - x 6 ^ 3 * +"; // ez más
    //const char* expr = "x * exp(x) - x^6 * 3 + 2 * ln(x)";
    //const char* expr = "sin(1.57)";
    const char* expr = "(5 + x) * 2";

    Token* ex = expression_parse(expr);
    expression_print(ex); printf("\n");
    printf("%g\n", expression_evaluate(ex, 1.0));
    expression_free(ex);

    return 0;
}
#include <stdio.h>
#include "expression_parser/expression_parser.h"

int main(void)
{
    char expr[] = "x exp x ln 2 * - x 6 ^ 3 * +";

    Node* ex = expression_parse(expr);
    printf("%g\n", expression_evaluate(ex, 1.0));
    expression_free(ex);

    return 0;
}
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "turtle-ast.h"
#include "turtle-lexer.h"
#include "turtle-parser.h"

int main() {
    srand(time(NULL) ^ (getpid() << 16));

    struct ast root;
    const int ret = yyparse(&root);

    if (ret != 0) {
        return ret;
    }

    yylex_destroy();
    assert(root.unit);

    // ici on vérifie qu'il n'y a pas de procedure imbriquée
    check_procedure_recurs(root.unit, false);

    struct context ctx;
    context_create(&ctx);

    ast_eval(&root, &ctx);
    ast_print(&root);

    ast_destroy(&root);
    context_destroy(&ctx);

    return ret;
}

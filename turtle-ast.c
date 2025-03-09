#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793

struct ast_node *make_expr_value(double value) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_VALUE;
  node->u.value = value;
  return node;
}

struct ast_node *make_expr_name(char *name) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_NAME;
    node->u.name = name;
    return node;
}

struct ast_node *make_expr_binop(const char op, struct ast_node *left, struct ast_node *right) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_BINOP;
    node->u.op = op;
    node->children_count = 2;
    node->children[0] = left;
    node->children[1] = right;
    return node;
}

struct ast_node *make_expr_unop(const char op, struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_UNOP;
    node->u.op = op;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

struct ast_node *make_cmd_forward(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_FORWARD;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}

struct ast_node *make_cmd_backward(struct ast_node *expr) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_BACKWARD;
    node->children_count = 1;
    node->children[0] = expr;
    return node;
}


struct ast_node *make_func_cos(const double value) {
    struct ast_node *value_node = calloc(1, sizeof(struct ast_node));
    value_node->kind = KIND_EXPR_VALUE;
    value_node->u.value = value;
    value_node->children_count = 0;

    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_COS;
    node->children_count = 1;
    node->children[0] = value_node;
    return node;
}
struct ast_node *make_func_sin(const double value) {
    struct ast_node *value_node = calloc(1, sizeof(struct ast_node));
    value_node->kind = KIND_EXPR_VALUE;
    value_node->u.value = value;
    value_node->children_count = 0;

    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_SIN;
    node->children_count = 1;
    node->children[0] = value_node;
    return node;
}
struct ast_node *make_func_tan(const double value) {
    struct ast_node *value_node = calloc(1, sizeof(struct ast_node));
    value_node->kind = KIND_EXPR_VALUE;
    value_node->u.value = value;
    value_node->children_count = 0;

    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_TAN;
    node->children_count = 1;
    node->children[0] = value_node;
    return node;
}
struct ast_node *make_func_sqrt(const double value) {
    struct ast_node *value_node = calloc(1, sizeof(struct ast_node));
    value_node->kind = KIND_EXPR_VALUE;
    value_node->u.value = value;
    value_node->children_count = 0;

    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_SQRT;
    node->children_count = 1;
    node->children[0] = value_node;
    return node;
}
struct ast_node *make_func_random(const double min, const double max) {
    struct ast_node *min_node = calloc(1, sizeof(struct ast_node));
    min_node->kind = KIND_EXPR_VALUE;
    min_node->u.value = min;
    min_node->children_count = 0;

    struct ast_node *max_node = calloc(1, sizeof(struct ast_node));
    max_node->kind = KIND_EXPR_VALUE;
    max_node->u.value = max;
    max_node->children_count = 0;

    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_RANDOM;
    node->children_count = 2;
    node->children[0] = min_node;
    node->children[1] = max_node;
    return node;
}

void ast_destroy(struct ast *self) {

}

/*
 * context
 */

void context_create(struct context *self) {

}

/*
 * eval
 */

void ast_eval(const struct ast *self, struct context *ctx) {

}

/*
 * print
 */

void ast_print(const struct ast *self) {

}

#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793

struct ast_node *make_cmd_up() {
    struct ast_node *node = malloc(sizeof(struct ast_node));

    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_UP;
    node->children_count = 0;
    node->children[0] = NULL;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_down() {
    struct ast_node *node = malloc(sizeof(struct ast_node));

    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_DOWN;
    node->children_count = 0;
    node->children[0] = NULL;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_home() {
    struct ast_node *node = malloc(sizeof(struct ast_node));

    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_HOME;
    node->children_count = 0;
    node->children[0] = NULL;

    node->next = NULL;
    return node;
}

struct ast_node *make_expr_value(const double value) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_EXPR_VALUE;
    node->u.value = value;
    node->children_count = 0;
    node->children[0] = NULL;

    node->next = NULL;
    return node;
}

struct ast_node *make_expr_name(char *name) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_EXPR_NAME;
    node->u.name = name;
    node->children_count = 0;
    node->children[0] = NULL;

    node->next = NULL;
    return node;
}

struct ast_node *make_expr_binop(const char op, struct ast_node *left, struct ast_node *right) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_EXPR_BINOP;
    node->u.op = op;
    node->children_count = 2;
    node->children[0] = left;
    node->children[1] = right;

    node->next = NULL;
    return node;
}

struct ast_node *make_expr_unop(const char op, struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_EXPR_UNOP;
    node->u.op = op;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_forward(struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_FORWARD;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_backward(struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_BACKWARD;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}


struct ast_node *make_func_cos(struct ast_node *arg) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_COS;
    node->children_count = 1;
    node->children[0] = arg;

    node->next = NULL;
    return node;
}

struct ast_node *make_func_sin(struct ast_node *arg) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_SIN;
    node->children_count = 1;
    node->children[0] = arg;

    node->next = NULL;
    return node;
}

struct ast_node *make_func_tan(struct ast_node *arg) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_TAN;
    node->children_count = 1;
    node->children[0] = arg;

    node->next = NULL;
    return node;
}

struct ast_node *make_func_sqrt(struct ast_node *arg) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_SQRT;
    node->children_count = 1;
    node->children[0] = arg;

    node->next = NULL;
    return node;
}

struct ast_node *make_func_random(struct ast_node *min, struct ast_node *max) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_RANDOM;
    node->children_count = 2;
    node->children[0] = min;
    node->children[1] = max;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_left(struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_LEFT;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}
struct ast_node *make_cmd_right(struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_RIGHT;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}
struct ast_node *make_cmd_heading(struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_HEADING;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}
struct ast_node *make_cmd_position(struct ast_node *x, struct ast_node *y) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_POSITION;
    node->children_count = 2;
    node->children[0] = x;
    node->children[1] = y;

    node->next = NULL;
    return node;
}
struct ast_node *make_cmd_color(struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_COLOR;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}
struct ast_node *make_cmd_print(struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_PRINT;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_block(struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));

    node->kind = KIND_CMD_BLOCK;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}
struct ast_node *make_cmd_set(struct ast_node *name, struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_CMD_SET;
    node->u.name = name->u.name;
    node->children_count = 1;
    node->children[1] = name;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_repeat(struct ast_node *how_many, struct ast_node *block) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_CMD_REPEAT;
    node->children_count = 2;
    node->children[0] = how_many;
    node->children[1] = block;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_proc(struct ast_node *name, struct ast_node *block) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_CMD_PROC;
    node->u.name = name->u.name;
    node->children_count = 2;
    node->children[0] = name;
    node->children[1] = block;

    node->next = NULL;
    return node;
}
struct ast_node *make_cmd_call(struct ast_node *name) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_CMD_CALL;
    node->u.name = name->u.name;
    node->children_count = 1;
    node->children[0] = name;

    node->next = NULL;
    return node;
}
struct ast_node *make_color_expr(struct ast_node *r, struct ast_node *g, struct ast_node *b) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_COLOR;
    node->children_count = 3;
    node->children[0] = r;
    node->children[1] = g;
    node->children[2] = b;

    node->next = NULL;
    return node;
}
struct ast_node *make_color_keyword(const char *keyword) {
    double r, g, b;
    if (strcmp(keyword, "white") == 0) {
        r = g = b = 255.0;
    } else if (strcmp(keyword, "gray") == 0) {
        r = g = b = 128.0;
    } else if (strcmp(keyword, "red") == 0) {
        r = 255.0;
        g = 0.0;
        b = 0.0;
    } else if (strcmp(keyword, "green") == 0) {
        r = 0.0;
        g = 255.0;
        b = 0.0;
    } else if (strcmp(keyword, "blue") == 0) {
        r = 0.0;
        g = 0.0;
        b = 255.0;
    } else if (strcmp(keyword, "yellow") == 0) {
        r = 255.0;
        g = 255.0;
        b = 0.0;
    } else if (strcmp(keyword, "cyan") == 0) {
        r = 0.0;
        g = 255.0;
        b = 255.0;
    } else if (strcmp(keyword, "magenta") == 0) {
        r = 255.0;
        g = 0.0;
        b = 255.0;
    } else {
        // Black case, at this point we cannot have another keyword than 'black' because the keyword are hard-coded in the lexer.
        r = g = b = 0.0;
    }
    struct ast_node *color_nodes = calloc(3, sizeof(struct ast_node));
    struct ast_node red_node = color_nodes[0], green_node = color_nodes[1], blue_node = color_nodes[2];

    for (int i = 0; i < 3; ++i) {
        color_nodes[i].kind = KIND_EXPR_VALUE;
        color_nodes[i].children_count = 0;
        color_nodes[i].next = NULL;
    }

    red_node.u.value = r;
    green_node.u.value = g;
    blue_node.u.value = b;

    return make_color_expr(&red_node, &green_node, &blue_node);
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

/**
 * print
 * TODO : real implementation
 */
void ast_print(const struct ast *self) {
    const struct ast_node *node = self->unit;
    while (node) {
        switch (node->kind) {
            case KIND_CMD_SIMPLE:
                printf("Command: %d\n", node->u.cmd);
                break;
            case KIND_EXPR_VALUE:
                printf("Value: %f\n", node->u.value);
                break;
            case KIND_EXPR_NAME:
                printf("Name: %s\n", node->u.name);
                break;
            case KIND_EXPR_BINOP:
                printf("Binary Op: %c\n", node->u.op);
                break;
            case KIND_EXPR_UNOP:
                printf("Unary Op: %c\n", node->u.op);
                break;
            case KIND_EXPR_FUNC:
                printf("Function: %d\n", node->u.func);
                break;
            default: break;
        }
        node = node->next;
    }
}

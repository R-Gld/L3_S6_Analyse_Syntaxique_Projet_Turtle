#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846
#define SQRT2 1.41421356237309504880
#define SQRT3 1.7320508075688772935

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
    node->u.name = strdup(name->u.name);
    node->children_count = 2;
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
    node->u.name = strdup(name->u.name);
    node->children_count = 2;
    node->children[0] = name;
    node->children[1] = block;

    node->next = NULL;
    return node;
}
struct ast_node *make_cmd_call(struct ast_node *name) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    node->kind = KIND_CMD_CALL;
    node->u.name = strdup(name->u.name);
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
    struct ast_node *red_node = malloc(sizeof(struct ast_node));
    struct ast_node *green_node = malloc(sizeof(struct ast_node));
    struct ast_node *blue_node = malloc(sizeof(struct ast_node));

    if (!red_node || !green_node || !blue_node) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    red_node->kind = KIND_EXPR_VALUE;
    red_node->u.value = r;
    red_node->children_count = 0;
    red_node->next = NULL;

    green_node->kind = KIND_EXPR_VALUE;
    green_node->u.value = g;
    green_node->children_count = 0;
    green_node->next = NULL;

    blue_node->kind = KIND_EXPR_VALUE;
    blue_node->u.value = b;
    blue_node->children_count = 0;
    blue_node->next = NULL;
    return make_color_expr(red_node, green_node, blue_node);
}


void node_stack_push(struct node_stack *self, struct ast_node *node) {
    if(self->size >= self->capacity) {
        self->capacity *= 2;
        struct ast_node **new_stack = realloc(self->stack, self->capacity * sizeof(struct ast_node *));
        if(!new_stack) {
            perror("realloc (3)");
            exit(EXIT_FAILURE);
        }
        self->stack = new_stack;
    }
    self->stack[self->size++] = node;
}

/**
 * Free the ast.
 *
 * Here we could have chosen a classic recursive destruction function of the tree, but we learn in the project of
 * "théorie des langages" in the 5th semester that if the tree is huge, it could cause a stack overflow.
 * So we use a stack to destroy the tree. A bit more complex that in cpp, but pretty cool.
 *
 * @param self the AST to destroy
 */
void ast_destroy(const struct ast *self) {
    struct node_stack stack;
    stack.capacity = 8;
    stack.size = 0;
    stack.stack = calloc(stack.capacity, sizeof(struct ast_node *));

    node_stack_push(&stack, self->unit);

    while (stack.size > 0) {
        struct ast_node *current_node = stack.stack[--stack.size]; // pop
        if (current_node->next != NULL) {
            node_stack_push(&stack, current_node->next);
        }
        for (int i = 0; i < current_node->children_count; ++i) {
            struct ast_node *child = current_node->children[i];
            if (child != NULL) {
                node_stack_push(&stack, child);
            }
        }

        // Free the name of the node because of the strdup used here and in the lexer.
        if (current_node->kind == KIND_EXPR_NAME ||
            current_node->kind == KIND_CMD_SET ||
            current_node->kind == KIND_CMD_PROC ||
            current_node->kind == KIND_CMD_CALL)
        {
            free(current_node->u.name);
        }

        free(current_node);
    }

    free(stack.stack);
}

/*
 * context
 */

void context_create(struct context *self) {
    self->x = 0.0;
    self->y = 0.0;
    self->up = false;
    self->angle = 0.0; // set default angle to 0 degrees toward north.
}

/*
 * eval
 */
void ast_eval(const struct ast *self, struct context *ctx) {

}

/**
 * TODO make an iterative version of this.
 * @param node the AST node to print
 * @param indent the indentation level
 */
static void print_ast_internal(const struct ast_node *node, const int indent) {
    if (!node) return;

    // Imprimer l'indentation
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }

    // Afficher le type et le contenu du nœud
    switch (node->kind) {
        case KIND_CMD_SIMPLE:
            printf("CMD: ");
            switch (node->u.cmd) {
                case CMD_UP:       printf("up"); break;
                case CMD_DOWN:     printf("down"); break;
                case CMD_HOME:     printf("home"); break;
                case CMD_FORWARD:  printf("forward"); break;
                case CMD_BACKWARD: printf("backward"); break;
                case CMD_LEFT:     printf("left"); break;
                case CMD_RIGHT:    printf("right"); break;
                case CMD_HEADING:  printf("heading"); break;
                case CMD_POSITION: printf("position"); break;
                case CMD_COLOR:    printf("color"); break;
                case CMD_PRINT:    printf("print"); break;
                default:           printf("unknown cmd");
            }
            break;
        case KIND_CMD_REPEAT:
            printf("repeat:");
            break;
        case KIND_CMD_BLOCK:
            printf("block:");
            break;
        case KIND_CMD_PROC:
            printf("proc: %s", node->u.name);
            break;
        case KIND_CMD_CALL:
            printf("call: %s", node->u.name);
            break;
        case KIND_CMD_SET:
            printf("set: %s", node->u.name);
            break;
        case KIND_EXPR_VALUE:
            printf("value: %f", node->u.value);
            break;
        case KIND_EXPR_NAME:
            printf("name: %s", node->u.name);
            break;
        case KIND_EXPR_BINOP:
            printf("binop: %c", node->u.op);
            break;
        case KIND_EXPR_UNOP:
            printf("unop: %c", node->u.op);
            break;
        case KIND_EXPR_FUNC:
            printf("func: ");
            switch (node->u.func) {
                case FUNC_COS:     printf("cos"); break;
                case FUNC_SIN:     printf("sin"); break;
                case FUNC_TAN:     printf("tan"); break;
                case FUNC_SQRT:    printf("sqrt"); break;
                case FUNC_RANDOM:  printf("random"); break;
                default:           printf("unknown func");
            }
            break;
        default:
            printf("unknown node type");
    }
    printf("\n");

    for (size_t i = 0; i < node->children_count; i++) {
        if (node->children[i]) {
            print_ast_internal(node->children[i], indent + 1);
        }
    }
    if (node->next) {
        print_ast_internal(node->next, indent);
    }
}

void ast_print(const struct ast *self) {
    print_ast_internal(self->unit, 0);
}


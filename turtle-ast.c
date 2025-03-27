#include "turtle-ast.h"

#include <assert.h>
#include <errno.h>
#include <fenv.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846
#define SQRT2 1.41421356237309504880
#define SQRT3 1.7320508075688772935

void check_malloc(const void *pointer) {
    if (pointer == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
}

void create_variable(char* name, const double value, struct context *ctx) {
    struct ast_node *name_node = make_expr_name(name);
    struct ast_node *value_node = make_expr_value(value);
    node_list_push(&ctx->variables, make_cmd_set(name_node, value_node));
}


struct ast_node *make_cmd_up() {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_UP;
    node->children_count = 0;
    node->children[0] = NULL;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_down() {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_DOWN;
    node->children_count = 0;
    node->children[0] = NULL;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_home() {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_HOME;
    node->children_count = 0;
    node->children[0] = NULL;

    node->next = NULL;
    return node;
}

struct ast_node *make_expr_value(const double value) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_EXPR_VALUE;
    node->u.value = value;
    node->children_count = 0;
    node->children[0] = NULL;

    node->next = NULL;
    return node;
}

struct ast_node *make_expr_name(char *name) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_EXPR_NAME;
    node->u.name = name;
    node->children_count = 0;
    node->children[0] = NULL;

    node->next = NULL;
    return node;
}

struct ast_node *make_expr_binop(const char op, struct ast_node *left, struct ast_node *right) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

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
    check_malloc(node);

    node->kind = KIND_EXPR_UNOP;
    node->u.op = op;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_forward(struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_FORWARD;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_backward(struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_BACKWARD;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}


struct ast_node *make_func_cos(struct ast_node *arg) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_COS;
    node->children_count = 1;
    node->children[0] = arg;

    node->next = NULL;
    return node;
}

struct ast_node *make_func_sin(struct ast_node *arg) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_SIN;
    node->children_count = 1;
    node->children[0] = arg;

    node->next = NULL;
    return node;
}

struct ast_node *make_func_tan(struct ast_node *arg) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_TAN;
    node->children_count = 1;
    node->children[0] = arg;

    node->next = NULL;
    return node;
}

struct ast_node *make_func_sqrt(struct ast_node *arg) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_EXPR_FUNC;
    node->u.func = FUNC_SQRT;
    node->children_count = 1;
    node->children[0] = arg;

    node->next = NULL;
    return node;
}

struct ast_node *make_func_random(struct ast_node *min, struct ast_node *max) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

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
    check_malloc(node);

    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_LEFT;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}
struct ast_node *make_cmd_right(struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_RIGHT;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}
struct ast_node *make_cmd_heading(struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_HEADING;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}
struct ast_node *make_cmd_position(struct ast_node *x, struct ast_node *y) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_POSITION;
    node->children_count = 2;
    node->children[0] = x;
    node->children[1] = y;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_print(struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_PRINT;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_block(struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);


    node->kind = KIND_CMD_BLOCK;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_set(struct ast_node *name, struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_CMD_SET;
    node->u.name = strdup(name->u.name);
    node->children_count = 2;
    node->children[0] = name;
    node->children[1] = expr;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_repeat(struct ast_node *how_many, struct ast_node *block) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_CMD_REPEAT;
    node->children_count = 2;
    node->children[0] = how_many;
    node->children[1] = block;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_proc(struct ast_node *name, struct ast_node *block) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

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
    check_malloc(node);

    node->kind = KIND_CMD_CALL;
    node->u.name = strdup(name->u.name);
    node->children_count = 1;
    node->children[0] = name;

    node->next = NULL;
    return node;
}

struct ast_node *make_cmd_color(struct ast_node *expr) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

    node->kind = KIND_CMD_SIMPLE;
    node->u.cmd = CMD_COLOR;
    node->children_count = 1;
    node->children[0] = expr;

    node->next = NULL;
    return node;
}

struct ast_node *make_color_expr(struct ast_node *r, struct ast_node *g, struct ast_node *b) {
    struct ast_node *node = malloc(sizeof(struct ast_node));
    check_malloc(node);

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
        r = g = b = 1.0;
    } else if (strcmp(keyword, "gray") == 0) {
        r = g = b = 0.5;
    } else if (strcmp(keyword, "red") == 0) {
        r = 1.0;
        g = 0.0;
        b = 0.0;
    } else if (strcmp(keyword, "green") == 0) {
        r = 0.0;
        g = 1.0;
        b = 0.0;
    } else if (strcmp(keyword, "blue") == 0) {
        r = 0.0;
        g = 0.0;
        b = 1.0;
    } else if (strcmp(keyword, "yellow") == 0) {
        r = 1.0;
        g = 1.0;
        b = 0.0;
    } else if (strcmp(keyword, "cyan") == 0) {
        r = 0.0;
        g = 1.0;
        b = 1.0;
    } else if (strcmp(keyword, "magenta") == 0) {
        r = 1.0;
        g = 0.0;
        b = 1.0;
    } else {
        // ici keyword est forcément = "black" parce que ya pas d'autres KW_ de définis dans le .l
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


void node_list_push(struct node_list *self, struct ast_node *node) {
    if(self->size >= self->capacity) {
        self->capacity *= 2;
        struct ast_node **new_stack = realloc(self->list, self->capacity * sizeof(struct ast_node *));
        if(!new_stack) {
            perror("realloc (3)");
            exit(EXIT_FAILURE);
        }
        self->list = new_stack;
    }
    self->list[self->size++] = node;
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
    struct node_list stack;
    node_list_init(&stack);

    node_list_push(&stack, self->unit);

    while (stack.size > 0) {
        struct ast_node *current_node = stack.list[--stack.size]; // pop
        if (current_node->next != NULL) {
            node_list_push(&stack, current_node->next);
        }
        for (size_t i = 0; i < current_node->children_count; ++i) {
            struct ast_node *child = current_node->children[i];
            if (child != NULL) {
                node_list_push(&stack, child);
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

    free(stack.list);
}

/*
 * context
 */
void context_create(struct context *self) {
    self->x = 0.0;
    self->y = 0.0;
    self->up = false;
    self->angle = 0.0; // set default angle to 0 degrees toward north.
    // Set the default color to black
    self->color[0] = 0;
    self->color[1] = 0;
    self->color[2] = 0;
    node_list_init(&self->procedures);
    node_list_init(&self->variables);

    create_variable("PI", PI, self);
    // create_variable("SQRT2", SQRT2, self);
    // create_variable("SQRT3", SQRT3, self);
}

void context_destroy(const struct context *self) {
    free(self->procedures.list);

    for (size_t i = 0; i < self->variables.size; ++i) {
        struct ast_node *set_node = self->variables.list[i];

        free(set_node->children[0]);
        free(set_node->children[1]);

        free(set_node->u.name);
        free(set_node);
    }

    free(self->variables.list);
}

void node_list_init(struct node_list *list) {
    list->capacity = 16;
    list->size = 0;
    list->list = calloc(list->capacity, sizeof(struct ast_node *));
    if (list->list == NULL) {
        perror("calloc on node_list_init");
        exit(EXIT_FAILURE);
    }
}

/**
 *
 * @param name the name of the variable to add
 * @param ctx the context to add the variable to
 * @return the ast_node corresponding to the variable if it exists, NULL otherwise
 */
struct ast_node *get_variable(const struct ast_node* name, const struct context *ctx) {
    const struct node_list *vars = &ctx->variables;
    for (size_t i = 0; i < vars->size; ++i) {
        if (strcmp(name->u.name, vars->list[i]->u.name) == 0) {
            return vars->list[i]->children[1]; // expr is stored at index 1.
        }
    }
    return NULL;
}

struct ast_node *get_procedure(const struct ast_node* name, const struct context *ctx) {
    const struct node_list *procs = &ctx->procedures;
    for (size_t i = 0; i < procs->size; ++i) {
        if (strcmp(name->u.name, procs->list[i]->u.name) == 0) {
            return procs->list[i]->children[1]; // block is stored at index 1.
        }
    }
    return NULL;
}

/*
 * eval
 */
void ast_eval(const struct ast *self, struct context *ctx) {
    eval_cmd(self->unit, ctx);
}

void move_to(struct context *ctx, const double x, double y) {
    if (ctx->up) {
        printf("MoveTo %f %f\n", x, y);
    } else {
        printf("LineTo %f %f\n", x, y);
    }
    if (x < -500 || x > 500 || y < -500 || y > 500) {
        fprintf(stderr, "Warning, the coordinates (%f, %f) are out of bounds.\n", x, y);
    }
    ctx->x = x;
    ctx->y = y;
}

/**
 *
 * @param node the AST node to evaluate Should have a kind of KIND_EXPR_*
 * @param ctx the context to use for the evaluation
 * @return the value of the expression / the content of the variable.
 */
double eval_expr(const struct ast_node *node, struct context *ctx) {
    switch (node->kind) {
        case KIND_EXPR_VALUE:
            return node->u.value;
        case KIND_EXPR_NAME: {
            struct ast_node *var_expr = get_variable(node, ctx);
            if (var_expr == NULL) {
                fprintf(stderr, "Error, the variable '%s' is not defined\n", node->u.name);
                exit(EXIT_FAILURE);
            }
            return eval_expr(var_expr, ctx);
        }
        case KIND_EXPR_BINOP: {
            const double left = eval_expr(node->children[0], ctx);
            const double right = eval_expr(node->children[1], ctx);
            switch (node->u.op) {
                case '+': return left + right;
                case '-': return left - right;
                case '*': return left * right;
                case '/':
                    if (right == 0) {
                        fprintf(stderr, "Error, dividing by zero.\n");
                        exit(EXIT_FAILURE);
                    }
                    return left / right;
                case '^': {
                    // via pow(3), modf(3), math_error(7), fetextexcept(3)
                    double blc;
                    if (left < 0
                        && modf(right, &blc) != 0.0)    { fprintf(stderr, "Error, the base (%f) is negative, the exponent (%f) must be an integer.\n", left, right); exit(EXIT_FAILURE); }
                    if (left == 0.0 && right <= 0.0)    { fprintf(stderr, "Error, for a base set to 0, the exponent must be > 0 (%f).\n", right); exit(EXIT_FAILURE); }

                    // clear errors.
                    feclearexcept(FE_ALL_EXCEPT);
                    errno = 0;
                    const double value = pow(left, right);
                    if (errno != 0) {
                        if (fetestexcept(FE_DIVBYZERO))     { fprintf(stderr, "Error: Division by zero occurred in pow() (base: %f; exponent: %f).\n", left, right); exit(EXIT_FAILURE); }
                        if (fetestexcept(FE_INVALID))       { fprintf(stderr, "Error: Invalid operation occurred in pow() (base: %f; exponent: %f).\n", left, right); exit(EXIT_FAILURE); }
                        if (fetestexcept(FE_OVERFLOW))      { fprintf(stderr, "Error: Overflow occurred in pow() (base: %f; exponent: %f).\n", left, right); exit(EXIT_FAILURE); }
                        if (fetestexcept(FE_UNDERFLOW))     { fprintf(stderr, "Error: Underflow occurred in pow() (base: %f; exponent: %f).\n", left, right); exit(EXIT_FAILURE); }
                    }
                    return value;
                }
                default:
                    fprintf(stderr, "Error, binary operator '%c' not supported\n", node->u.op);
                    exit(EXIT_FAILURE);
            }
        }
        case KIND_EXPR_UNOP: {
            const double val = eval_expr(node->children[0], ctx);
            switch (node->u.op) {
                case '-': return -val;
                default:
                    fprintf(stderr, "Error, unary operator '%c' not supported\n", node->u.op);
                    exit(EXIT_FAILURE);
            }
        }
        case KIND_EXPR_FUNC: {
            switch (node->u.func) {
                case FUNC_SIN: {
                    const double angle = eval_expr(node->children[0], ctx);

                    // clear errors.
                    feclearexcept(FE_ALL_EXCEPT);
                    errno = 0;

                    const double value = sin(deg_to_rad(angle)); // sin take radians in parameter, not degrees. Cf man 3 sin
                    if (errno != 0 && fetestexcept(FE_INVALID)) {
                        fprintf(stderr, "Error, x is an infinity, implies a domain error (value in degrees: %f).\n", angle); exit(EXIT_FAILURE);
                   }
                    return value;
                }
                case FUNC_COS: {
                    const double angle = eval_expr(node->children[0], ctx);

                    // clear errors.
                    feclearexcept(FE_ALL_EXCEPT);
                    errno = 0;

                    const double value = cos(deg_to_rad(angle)); // sin take radians in parameter, not degrees. Cf man 3 sin
                    if (errno != 0 && fetestexcept(FE_INVALID)) {
                        fprintf(stderr, "Error, x is an infinity, implies a domain error (value in degrees: %f).\n", angle); exit(EXIT_FAILURE);
                    }
                    return value;
                }
                case FUNC_TAN: {
                    const double angle = eval_expr(node->children[0], ctx);

                    // clear errors.
                    feclearexcept(FE_ALL_EXCEPT);
                    errno = 0;

                    const double value = tan(deg_to_rad(angle)); // sin take radians in parameter, not degrees. Cf man 3 sin
                    if (errno != 0) {
                        if (fetestexcept(FE_INVALID))  { fprintf(stderr, "Error, %f is an infinity, implies a domain error.\n", angle); exit(EXIT_FAILURE); }
                        if (fetestexcept(FE_OVERFLOW)) { fprintf(stderr, "Error, %f is too big, creating an overflow.", angle); exit(EXIT_FAILURE); }
                    }
                    return value;
                }
                case FUNC_SQRT: {
                    // man sqrt(3)
                    const double val = eval_expr(node->children[0], ctx);
                    if (val < 0) {
                        fprintf(stderr, "Error, the sqrt of '%f' is not defined.\n", val);
                        exit(EXIT_FAILURE);
                    }
                    return sqrt(val);
                }
                case FUNC_RANDOM: {
                    const double min = eval_expr(node->children[0], ctx);
                    const double max = eval_expr(node->children[1], ctx);
                    if (min > max) { // on aurait pu swap les deux valeurs mais il faut print une erreur :/
                        fprintf(stderr, "Error, the two values of the random function are inverted (%f > %f).\n", min, max);
                        exit(EXIT_FAILURE);
                    }
                    const double range = max - min;
                    const double rnd = (double) rand() / RAND_MAX;
                    return min + rnd * range;
                }
                default:
                    fprintf(stderr, "Internal function unknown.\n");
                    exit(EXIT_FAILURE);
            }
        }
        default:
            fprintf(stderr, "expr type invalid.\n");
            exit(EXIT_FAILURE);
    }
}

void check_procedure_recurs(const struct ast_node *node, const bool in_proc) {
    if (node == NULL) return;

    if (node->kind == KIND_CMD_PROC) {
        if (in_proc) {
            fprintf(stderr, "Error, you can't define a procedure inside of another procedure (%s).\n", node->u.name);
            exit(EXIT_FAILURE);
        }
        check_procedure_recurs(node->children[1], true);
    } else {
        for (size_t i = 0; i < node->children_count; ++i) {
            check_procedure_recurs(node->children[i], in_proc);
        }
    }
    check_procedure_recurs(node->next, in_proc);
}


/**
 *
 * @param node the node to evaluate
 * @param ctx the context to use for the evaluation
 */
void eval_cmd(struct ast_node *node, struct context *ctx) {

    while (node) {
        switch (node->kind) {
            case KIND_CMD_SIMPLE:

                switch (node->u.cmd) {
                    case CMD_UP:

                        ctx->up = true;
                        break;
                    case CMD_DOWN:

                        ctx->up = false;
                        break;
                    case CMD_HOME:

                        move_to(ctx, 0, 0);
                        ctx->angle = 0;
                        break;
                    case CMD_FORWARD: {

                        const double distance = eval_expr(node->children[0], ctx);
                        const double angle_rad = deg_to_rad(ctx->angle);
                        const double new_x = ctx->x + distance * sin(angle_rad);
                        const double new_y = ctx->y - distance * cos(angle_rad);
                        move_to(ctx, new_x, new_y);
                        break;
                    }
                    case CMD_BACKWARD: {

                        const double distance = eval_expr(node->children[0], ctx);
                        const double angle_rad = deg_to_rad(ctx->angle);
                        const double new_x = ctx->x - distance * sin(angle_rad);
                        const double new_y = ctx->y + distance * cos(angle_rad);
                        move_to(ctx, new_x, new_y);
                        break;
                    }
                    case CMD_LEFT: {

                        const double angle = eval_expr(node->children[0], ctx);
                        ctx->angle -= angle;
                        break;
                    }
                    case CMD_RIGHT: {

                        const double angle = eval_expr(node->children[0], ctx);
                        ctx->angle += angle;
                        break;
                    }
                    case CMD_HEADING: {

                        const double angle = eval_expr(node->children[0], ctx);
                        ctx->angle = angle;
                        break;
                    }
                    case CMD_POSITION: {

                        const bool tmp_up = ctx->up;
                        ctx->up = true;
                        const double new_x = eval_expr(node->children[0], ctx);
                        const double new_y = eval_expr(node->children[1], ctx);
                        move_to(ctx, new_x, new_y);
                        ctx->up = tmp_up;
                        break;
                    }
                    case CMD_COLOR: {
                        const double r = eval_expr(node->children[0], ctx);
                        const double g = eval_expr(node->children[1], ctx);
                        const double b = eval_expr(node->children[2], ctx);
                        ctx->color[0] = r;
                        ctx->color[1] = g;
                        ctx->color[2] = b;
                        printf("Color %f %f %f\n", r, g, b);
                        break;
                    }
                    case CMD_PRINT: {
                        const double val = eval_expr(node->children[0], ctx);
                        fprintf(stderr, "print => %f\n", val);
                        break;
                    }
                    default:
                        fprintf(stderr, "Error, simple command unknown.\n");
                        exit(EXIT_FAILURE);
                }
                break;
            case KIND_CMD_REPEAT: {
                const int count = (int) floor(eval_expr(node->children[0], ctx));
                for (int i = 0; i < count; ++i) {
                    eval_cmd(node->children[1], ctx);
                }
                break;
            }
            case KIND_CMD_BLOCK:

                eval_cmd(node->children[0], ctx);
                break;
            case KIND_CMD_SET: {

                const double value = eval_expr(node->children[1], ctx);
                struct ast_node *value_fig = make_expr_value(value);
                // Ici, on fige la valeur de value à l'instant t en l'évaluant et arès on recréer un cmd_set dans la node_list.
                struct ast_node *var = get_variable(node->children[0], ctx);
                if (var == NULL) {
                    node_list_push(&ctx->variables, make_cmd_set(node->children[0], value_fig));
                } else {
                    // Ici, on met à jour la valeur dans la variable.
                    var->children[1] = value_fig;
                }
                break;
            }
            case KIND_CMD_PROC: {

                if (get_procedure(node->children[0], ctx) == NULL) {
                    node_list_push(&ctx->procedures, node);
                } else {
                    fprintf(stderr, "Error, procedure '%s' already defined.\n", node->children[0]->u.name);
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case KIND_CMD_CALL: {

                struct ast_node *proc = get_procedure(node->children[0], ctx);
                if (proc == NULL) {
                    fprintf(stderr, "Error, the procedure '%s' is not defined.\n", node->children[0]->u.name);
                    exit(EXIT_FAILURE);
                }
                eval_cmd(proc, ctx);
                break;
            }
            case KIND_EXPR_VALUE:
            case KIND_EXPR_NAME:
            case KIND_EXPR_BINOP:
            case KIND_EXPR_BLOCK:
            case KIND_EXPR_FUNC:
            case KIND_EXPR_UNOP:
                eval_expr(node, ctx);
                break;
            default:
                fprintf(stderr, "Error, command type unknown\n");
                exit(EXIT_FAILURE);
        }
        node = node->next;
    }
}

/**
 * TODO make an iterative version of this.
 * @param node the AST node to print
 * @param indent the indentation level
 */
void print_ast_internal(const struct ast_node *node, const int indent) {
    if (!node) return;

    // Imprimer l'indentation
    for (int i = 0; i < indent; i++) {
        fprintf(stderr, "  ");
    }

    // Afficher le type et le contenu du nœud
    switch (node->kind) {
        case KIND_CMD_SIMPLE:
            fprintf(stderr, "CMD: ");
            switch (node->u.cmd) {
                case CMD_UP:       fprintf(stderr, "up"); break;
                case CMD_DOWN:     fprintf(stderr, "down"); break;
                case CMD_HOME:     fprintf(stderr, "home"); break;
                case CMD_FORWARD:  fprintf(stderr, "forward"); break;
                case CMD_BACKWARD: fprintf(stderr, "backward"); break;
                case CMD_LEFT:     fprintf(stderr, "left"); break;
                case CMD_RIGHT:    fprintf(stderr, "right"); break;
                case CMD_HEADING:  fprintf(stderr, "heading"); break;
                case CMD_POSITION: fprintf(stderr, "position"); break;
                case CMD_COLOR:    fprintf(stderr, "color"); break;
                case CMD_PRINT:    fprintf(stderr, "print"); break;
                default:           fprintf(stderr, "unknown cmd");
            }
            break;
        case KIND_CMD_REPEAT:
            fprintf(stderr, "repeat:");
            break;
        case KIND_CMD_BLOCK:
            fprintf(stderr, "block:");
            break;
        case KIND_CMD_PROC:
            fprintf(stderr, "proc: %s", node->u.name);
            break;
        case KIND_CMD_CALL:
            fprintf(stderr, "call: %s", node->u.name);
            break;
        case KIND_CMD_SET:
            fprintf(stderr, "set: %s", node->u.name);
            break;
        case KIND_EXPR_VALUE:
            fprintf(stderr, "value: %f", node->u.value);
            break;
        case KIND_EXPR_NAME:
            fprintf(stderr, "name: %s", node->u.name);
            break;
        case KIND_EXPR_BINOP:
            fprintf(stderr, "binop: %c", node->u.op);
            break;
        case KIND_EXPR_UNOP:
            fprintf(stderr, "unop: %c", node->u.op);
            break;
        case KIND_EXPR_FUNC:
            fprintf(stderr, "func: ");
            switch (node->u.func) {
                case FUNC_COS:     fprintf(stderr, "cos"); break;
                case FUNC_SIN:     fprintf(stderr, "sin"); break;
                case FUNC_TAN:     fprintf(stderr, "tan"); break;
                case FUNC_SQRT:    fprintf(stderr, "sqrt"); break;
                case FUNC_RANDOM:  fprintf(stderr, "random"); break;
                default:           fprintf(stderr, "unknown func");
            }
            break;
        default: break;
    }
    fprintf(stderr, "\n");

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

double deg_to_rad(const double deg) {
    return deg * PI / 180.0;
}
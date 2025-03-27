#ifndef TURTLE_AST_H
#define TURTLE_AST_H

#include <stddef.h>
#include <stdbool.h>

// simple commands
enum ast_cmd {
  CMD_UP,
  CMD_DOWN,
  CMD_RIGHT,
  CMD_LEFT,
  CMD_HEADING,
  CMD_FORWARD,
  CMD_BACKWARD,
  CMD_POSITION,
  CMD_HOME,
  CMD_COLOR,
  CMD_PRINT,
};

// internal functions
enum ast_func {
  FUNC_COS,
  FUNC_SIN,
  FUNC_TAN,
  FUNC_SQRT,
  FUNC_RANDOM,
};

// kind of a node in the abstract syntax tree
enum ast_kind {
  KIND_CMD_SIMPLE,
  KIND_CMD_REPEAT,
  KIND_CMD_BLOCK,
  KIND_CMD_PROC,
  KIND_CMD_CALL,
  KIND_CMD_SET,

  KIND_EXPR_FUNC,
  KIND_EXPR_VALUE,
  KIND_EXPR_UNOP,
  KIND_EXPR_BINOP,
  KIND_EXPR_BLOCK,
  KIND_EXPR_NAME,
};

#define AST_CHILDREN_MAX 3

// a node in the abstract syntax tree
struct ast_node {
  enum ast_kind kind; // kind of the node

  union {
    enum ast_cmd cmd;   // kind == KIND_CMD_SIMPLE
    double value;       // kind == KIND_EXPR_VALUE, for literals
    char op;            // kind == KIND_EXPR_BINOP or kind == KIND_EXPR_UNOP, for operators in expressions
    char *name;         // kind == KIND_EXPR_NAME, the name of procedures and variables
    enum ast_func func; // kind == KIND_EXPR_FUNC, a function
  } u;

  size_t children_count;  // the number of children of the node
  struct ast_node *children[AST_CHILDREN_MAX];  // the children of the node (arguments of commands, etc)
  struct ast_node *next;  // the next node in the sequence
};

struct ast_node *make_cmd_up();
struct ast_node *make_cmd_down();
struct ast_node *make_cmd_home();
struct ast_node *make_expr_value(double value);
struct ast_node *make_expr_name(char *name);
struct ast_node *make_expr_binop(char op, struct ast_node *left, struct ast_node *right);
struct ast_node *make_expr_unop(char op, struct ast_node *expr);
struct ast_node *make_func_cos(struct ast_node *arg);
struct ast_node *make_func_sin(struct ast_node *arg);
struct ast_node *make_func_tan(struct ast_node *arg);
struct ast_node *make_func_sqrt(struct ast_node *arg);
struct ast_node *make_func_random(struct ast_node *min, struct ast_node *max);
struct ast_node *make_cmd_forward(struct ast_node *expr);
struct ast_node *make_cmd_backward(struct ast_node *expr);
struct ast_node *make_cmd_left(struct ast_node *expr);
struct ast_node *make_cmd_right(struct ast_node *expr);
struct ast_node *make_cmd_heading(struct ast_node *expr);
struct ast_node *make_cmd_position(struct ast_node *x, struct ast_node *y);
struct ast_node *make_cmd_print(struct ast_node *expr);
struct ast_node *make_cmd_block(struct ast_node *expr);
struct ast_node *make_cmd_set(struct ast_node *name, struct ast_node *expr);
struct ast_node *make_cmd_repeat(struct ast_node *how_many, struct ast_node *block);
struct ast_node *make_cmd_proc(struct ast_node *name, struct ast_node *block);
struct ast_node *make_cmd_call(struct ast_node *name);

struct ast_node *make_cmd_color(struct ast_node *expr);
struct ast_node *make_color_expr(struct ast_node *r, struct ast_node *g, struct ast_node *b);
struct ast_node *make_color_keyword(const char *keyword);

// root of the abstract syntax tree
struct ast {
  struct ast_node *unit;
};

/**
 * Can be used as a stack by using node_list_push and pop with list.list[--list.size];
 */
struct node_list { // 8 + 8 + 8 = 24 bytes
  struct ast_node **list;
  size_t capacity;
  size_t size;
};
void node_list_push(struct node_list *self, struct ast_node *node);
void node_list_init(struct node_list *list);

void add_variable(const struct ast_node *var, struct node_list *self);

// do not forget to destroy properly! no leaks allowed!
void ast_destroy(const struct ast *self);

struct context {
  double x;
  double y;
  double angle;
  bool up;
  double color[3];

  struct node_list variables;
  struct node_list procedures;
};

// create an initial context
void context_create(struct context *self);

void context_destroy(const struct context *self);

// print the tree as if it was a Turtle program
void ast_print(const struct ast *self);

void print_ast_internal(const struct ast_node *node, int indent);
// evaluate the tree and generate some basic primitives
void ast_eval(const struct ast *self, struct context *ctx);

void move_to(struct context *ctx, double x, double y);
double eval_expr(const struct ast_node *node, struct context *ctx);

void check_procedure_recurs(const struct ast_node *node, bool in_proc);

void eval_cmd(struct ast_node *node, struct context *ctx);

double deg_to_rad(double deg);

struct ast_node *get_variable(const struct ast_node* name, const struct context *ctx);
struct ast_node *get_procedure(const struct ast_node* name, const struct context *ctx);
#endif /* TURTLE_AST_H */

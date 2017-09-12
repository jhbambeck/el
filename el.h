#ifndef EL_H
#define EL_H
enum arith_op
{
    op_add,
    op_sub,
    op_div,
    op_rem
};

enum rel_op
{
    op_lt,
    op_gt,
    op_eq
};

enum logical_op
{
    op_and,
    op_or
};

enum num_expr_kind
{
    ek_int,
    ek_arg,
    ek_arith,
    ek_if
};

enum bool_expr_kind
{
    ek_bool,
    ek_rel,
    ek_logic
};

struct prog;
struct bool_expr;
struct num_expr;

struct prog
{
    prog(int n, num_expr* e) : args(n), body(e)
    { }

    int args;
    num_expr* body;
};

//num_expr structs

struct num_expr
{
    num_expr(num_expr_kind k) : kind(k)
    { }

    num_expr_kind kind;
};

struct int_lit : num_expr
{
    int_lit(int n) : num_expr(ek_int), val(n)
    { }

    int val;
};

struct arg_expr : num_expr
{
    arg_expr(int n) : num_expr(ek_arg), arg(n)
    { }

    int arg;
};

struct arith_expr : num_expr
{
    arith_expr(arith_op op, num_expr* l, num_expr* r)
    : num_expr(ek_arith), op(op), lhs(l), rhs(r)
    { }

    arith_op op;
    num_expr* lhs;
    num_expr* rhs;
};

struct if_expr : num_expr
{
    if_expr(bool_expr* t, num_expr* p, num_expr* f)
    : num_expr(ek_if), test(t), pass(p), fail(f)
    { }

    bool_expr* test;
    num_expr* pass;
    num_expr* fail;
};

//bool_expr structs

struct bool_expr
{
    bool_expr(bool_expr_kind k) : kind(k)
    { }

    bool_expr_kind kind;
};

struct bool_lit : bool_expr
{
    bool_lit(bool b) : bool_expr(ek_bool), val(b)
    { }

    bool val;
};

struct rel_expr : bool_expr
{
    rel_expr(rel_op op, num_expr* e1, num_expr* e2)
    : bool_expr(ek_bool), op(op), lhs(e1), rhs(e2)
    { }

    rel_op op;
    num_expr* lhs;
    num_expr* rhs;
};

struct logical_expr : bool_expr
{
    logical_expr(logical_op op, bool_expr* e1, bool_expr* e2)
    : bool_expr(ek_logic), op(op), lhs(e1), rhs(e2)
    { }

    logical_op op;
    bool_expr* lhs;
    bool_expr* rhs;
};

//Algorithms

int height(num_expr* e);
int height(bool_expr* e);

#endif // EL_H

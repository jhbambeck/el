#include "el.h"
# include <algorithm>

//num_expr height

int height_int(int_lit* e)
{
    return 0;
}

int height_arg(arg_expr* e)
{
    return 0;
}

int height_arith(arith_expr* e)
{
    return 1 + std::max(height(e->lhs), height(e->rhs));
}

int height_if(if_expr* e)
{
    return 1 + std::max(
    {
        height(e->test),
        height(e->pass),
        height(e->fail)
    });
}

int height(num_expr* e)
{
    switch(e->kind)
    {
    case ek_int:
        return height_int(static_cast<int_lit*>(e));
    case ek_arg:
        return height_arg(static_cast<arg_expr*>(e));
    case ek_arith:
        return height_arith(static_cast<arith_expr*>(e));
    case ek_if:
        return height_if(static_cast<if_expr*>(e));
    }
}

//bool_expr height

int height_bool(bool_lit* e)
{
    return 0;
}

int height_rel(rel_expr* e)
{
    return 1 + std::max(height(e->lhs), height(e->rhs));
}

int height_logical(logical_expr* e)
{
    return 1 + std::max(height(e->lhs), height(e->rhs));
}

int height(bool_expr* e)
{
    switch(e->kind)
    {
    case ek_bool:
        return height_bool(static_cast<bool_lit*>(e));
    case ek_rel:
        return height_rel(static_cast<rel_expr*>(e));
    case ek_logic:
        return height_logical(static_cast<logical_expr*>(e));
    }
}

//max args

int max_args_int(int_lit* e)
{
    return 0;
}

int max_args_arg(arg_expr* e)
{
    return 1;
}

int max_args_arith(arith_expr* e)
{
    return max_args(e->lhs) + max_args(e->rhs);
}

int max_args_if(if_expr* e)
{
    return max_args(e->test) + std::max(max_args(e->pass), max_args(e->fail));
}

int max_args(num_expr* e)
{
    switch(e->kind)
    {
    case ek_int:
        return max_args_int(static_cast<int_lit*>(e));
    case ek_arg:
        return max_args_arg(static_cast<arg_expr*>(e));
    case ek_arith:
        return max_args_arith(static_cast<arith_expr*>(e));
    case ek_if:
        return max_args_if(static_cast<if_expr*>(e));
    }
}

int max_args_bool(bool_lit* e)
{
    return 0;
}

int max_args_rel(rel_expr* e)
{
    return max_args(e->rhs) + max_args(e->lhs);
}

int max_args_logical(logical_expr* e)
{
    return max_args(e->rhs) + max_args(e->lhs);
}

int max_args(bool_expr* e)
{
    switch(e->kind)
    {
    case ek_bool:
        return max_args_bool(static_cast<bool_lit*>(e));
    case ek_rel:
        return max_args_rel(static_cast<rel_expr*>(e));
    case ek_logic:
        return max_args_logical(static_cast<logical_expr*>(e));
    }
}

//min args

int min_args_int(int_lit* e)
{
    return 0;
}

int min_args_arg(arg_expr* e)
{
    return 1;
}

int min_args_arith(arith_expr* e)
{
    return min_args(e->lhs) + min_args(e->rhs);
}

int min_args_if(if_expr* e)
{
    return min_args(e->test) + std::min(min_args(e->pass), min_args(e->fail));
}

int min_args(num_expr* e)
{
    switch(e->kind)
    {
    case ek_int:
        return min_args_int(static_cast<int_lit*>(e));
    case ek_arg:
        return min_args_arg(static_cast<arg_expr*>(e));
    case ek_arith:
        return min_args_arith(static_cast<arith_expr*>(e));
    case ek_if:
        return min_args_if(static_cast<if_expr*>(e));
    }
}

int min_args_bool(bool_lit* e)
{
    return 0;
}

int min_args_rel(rel_expr* e)
{
    return min_args(e->rhs) + min_args(e->lhs);
}

int min_args_logical(logical_expr* e)
{
    return min_args(e->rhs) + min_args(e->lhs);
}

int min_args(bool_expr* e)
{
    switch(e->kind)
    {
    case ek_bool:
        return min_args_bool(static_cast<bool_lit*>(e));
    case ek_rel:
        return min_args_rel(static_cast<rel_expr*>(e));
    case ek_logic:
        return min_args_logical(static_cast<logical_expr*>(e));
    }
}



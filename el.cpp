#include "el.h"
# include <algorithm>

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

int height(bool_expr* e)
{
    return 0;
}

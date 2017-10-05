#include "fold_algos.h"

num_expr* fold_int(int_lit* e)
{
    return e;
}

num_expr* fold_arg(arg_expr* e)
{
    return e;
}

num_expr* fold_arith(arith_expr* e)
{
    e->lhs = fold(e->lhs);
    e->rhs = fold(e->rhs);
    if((e->lhs->kind == ek_int) && (e->rhs->kind == ek_int))
    {
        int_lit* templ = static_cast<int_lit*>(e->lhs);
        int_lit* tempr = static_cast<int_lit*>(e->rhs);
        num_expr* r;
        switch(e->op)
        {
        case op_add:
            r = new int_lit(templ->val + tempr->val);
            break;
        case op_sub:
            r = new int_lit(templ->val - tempr->val);
            break;
        case op_mul:
            r = new int_lit(templ->val * tempr->val);
            break;
        case op_div:
            r = new int_lit(templ->val / tempr->val);
            break;
        case op_rem:
            r = new int_lit(templ->val % tempr->val);
            break;
        }
        return r;
    }
    return e;
}

num_expr* fold_if(if_expr* e)
{
    e->pass = fold(e->pass);
    e->fail = fold(e->fail);
    e->test = fold(e->test);
    if(e->test->kind == ek_bool)
    {
        bool_lit* tempt = static_cast<bool_lit*>(e->test);
        if(tempt->val == true)
        {
            return e->pass;
        }
        else
        {
            return e->fail;
        }
    }
    return e;
}

num_expr* fold(num_expr* e)
{
    switch(e->kind)
    {
    case ek_int:
        return fold_int(static_cast<int_lit*>(e));
        break;
    case ek_arg:
        return fold_arg(static_cast<arg_expr*>(e));
        break;
    case ek_arith:
        return fold_arith(static_cast<arith_expr*>(e));
        break;
    case ek_if:
        return fold_if(static_cast<if_expr*>(e));
        break;
    }
}

bool_expr* fold_bool(bool_expr* e)
{
    return e;
}

bool_expr* fold_logical(logical_expr* e)
{
    e->lhs = fold(e->lhs);
    e->rhs = fold(e->rhs);
    if((e->rhs->kind == ek_bool) && (e->lhs->kind == ek_bool))
    {
        bool_lit* templ = static_cast<bool_lit*>(e->lhs);
        bool_lit* tempr = static_cast<bool_lit*>(e->rhs);
        bool_lit* r;
        switch(e->op)
        {
        case op_or:
            if((templ->val == true) || (tempr->val == true))
                r = new bool_lit(true);
            else r = new bool_lit(false);
            break;
        case op_and:
            if((templ->val == true) && (tempr->val == true))
                r = new bool_lit(true);
            else r = new bool_lit(false);
            break;
        }
        return r;
    }
    return e;
}

bool_expr* fold_rel(rel_expr* e)
{
    e->lhs = fold(e->lhs);
    e->rhs = fold(e->rhs);
    if((e->lhs->kind == ek_int) && (e->rhs->kind == ek_int))
    {
        int_lit* templ = static_cast<int_lit*>(e->lhs);
        int_lit* tempr = static_cast<int_lit*>(e->rhs);
        bool_expr* r;
        bool r_val = false;
        switch(e->op)
        {
        case op_lt:
            if(templ->val < tempr->val) r_val = true;
            break;
        case op_gt:
            if(templ->val > tempr->val) r_val = true;
            break;
        case op_eq:
            if(templ->val == tempr->val) r_val = true;
            break;
        }
        r = new bool_lit(r_val);
        return r;
    }
    return e;
}

bool_expr* fold(bool_expr* e)
{
    switch(e->kind)
    {
    case ek_bool:
        return fold_bool(static_cast<bool_lit*>(e));
        break;
    case ek_rel:
        return fold_rel(static_cast<rel_expr*>(e));
        break;
    case ek_logic:
        return fold_logical(static_cast<logical_expr*>(e));
        break;
    }
}


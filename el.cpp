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

//num_expr evaluator

answer eval_int(int_lit* e)
{
    return answer(e->val);
}

answer eval_arg(arg_expr* e)
{
    return answer(e->arg);
}

answer eval_arith(arith_expr* e)
{
    answer ans_lhs = eval(e->lhs);
    answer ans_rhs = eval(e->rhs);
    if((ans_lhs.kind == int_ans) && (ans_rhs.kind == int_ans))
    {
    switch(e->op)
    {
    case op_add:
        return answer(ans_lhs.n + ans_rhs.n);
    case op_sub:
        return answer(ans_lhs.n - ans_rhs.n);
    case op_mul:
        return answer(ans_lhs.n * ans_rhs.n);
    case op_div:
        return answer(ans_lhs.n / ans_rhs.n);
    case op_rem:
        return answer(ans_lhs.n % ans_rhs.n);
    }
    }

    else return answer(error);
}

answer eval_if(if_expr* e)
{
    answer test_ans = eval(e->test);
    if(test_ans.kind == int_ans)
    {
       if(test_ans.n == 0) return eval(e->fail);
       else return eval(e->pass);
    }
}

answer eval(num_expr* e)
{
    switch(e->kind)
    {
    case ek_int:
        return eval_int(static_cast<int_lit*>(e));
    case ek_arg:
        return eval_arg(static_cast<arg_expr*>(e));
    case ek_arith:
        return eval_arith(static_cast<arith_expr*>(e));
    case ek_if:
        return eval_if(static_cast<if_expr*>(e));
    }
}

//bool_expr evaluator

answer eval_bool(bool_lit* e)
{
    if(e->val) return answer(1);
    else return answer(0);
}

answer eval_rel(rel_expr* e)
{
    answer ans_lhs = eval(e->lhs);
    answer ans_rhs = eval(e->rhs);
    if((ans_lhs.kind == int_ans) && (ans_rhs.kind == int_ans))
    {
    switch(e->op)
    {
    case op_lt:
        if(ans_lhs.n < ans_rhs.n) return answer(1);
        else return answer(0);
    case op_gt:
        if(ans_lhs.n > ans_rhs.n) return answer(1);
        else return answer(0);
    case op_eq:
        if(ans_lhs.n == ans_rhs.n) return answer(1);
        else return answer(0);
    }
    }
    else return answer(error);
}

answer eval_logic(logical_expr* e)
{
    answer ans_lhs = eval(e->lhs);
    answer ans_rhs = eval(e->rhs);
    if((ans_lhs.kind == int_ans) && (ans_rhs.kind == int_ans))
    {
    switch(e->op)
    {
    case op_and:
        if(ans_lhs.n == 1 && ans_rhs.n == 1) return answer(1);
        else return answer(0);
    case op_or:
        if(ans_lhs.n==1 || ans_rhs.n==1) return answer(1);
        else return answer(0);
    }
    }
    else return answer(error);
}

answer eval(bool_expr* e)
{
    switch(e->kind)
    {
    case ek_bool:
        return eval_bool(static_cast<bool_lit*>(e));
    case ek_rel:
        return eval_rel(static_cast<rel_expr*>(e));
    case ek_logic:
        return eval_logic(static_cast<logical_expr*>(e));

    }
}

std::ostream& operator<<(std::ostream& os, const answer& ans)
    {
        if(ans.kind == int_ans) os << ans.n;
        else os << ans.e;
        return os;
    }

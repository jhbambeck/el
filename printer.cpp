#include "printer.h"

void printer::print_int_lit(int_lit* e)
{
    //std::cout << "print_int_lit\n";
    os << e->val;
}

void printer::print_arg_expr(arg_expr* e)
{
    //std::cout << "print_arg_expr\n";
    os << "(arg " << e->ix << ")";
}

void printer::print_arith_expr(arith_expr* e)
{
    //std::cout << "print_arith_expr\n";
    os << "(";
    switch(e->op)
    {
    case op_add:
        os << "+ ";
        break;
    case op_sub:
        os << "- ";
        break;
    case op_mul:
        os << "* ";
        break;
    case op_div:
        os << "/ ";
        break;
    case op_rem:
        os << "% ";
        break;
    }
    print_num_expr(e->lhs);
    os << " ";
    print_num_expr(e->rhs);
    os << ")";
}

void printer::print_if_expr(if_expr* e)
{
    //std::cout << "print_if_expr\n";
    os << "(if ";
    print_bool_expr(e->test);
    os << " ";
    print_num_expr(e->pass);
    os << " ";
    print_num_expr(e->fail);
    os << ")";
}

void printer::print_num_expr(num_expr* e)
{
    //std::cout<<"print_num_expr\n";
    switch(e->kind)
    {
    case ek_int:
        print_int_lit(static_cast<int_lit*>(e));
        break;
    case ek_arg:
        print_arg_expr(static_cast<arg_expr*>(e));
        break;
    case ek_arith:
        print_arith_expr(static_cast<arith_expr*>(e));
        break;
    case ek_if:
        print_if_expr(static_cast<if_expr*>(e));
        break;
    }
}

void printer::print_bool_lit(bool_lit* e)
{
    //std::cout << "print_bool_lit\n";
    if(e->val == true) os << "true";
    else os << "false";
}

void printer::print_rel_expr(rel_expr* e)
{
    //std::cout << "print_rel_expr\n";
    os << "(";
    switch(e->op)
    {
    case op_lt:
        os << "< ";
        break;
    case op_gt:
        os << "> ";
        break;
    case op_eq:
        os << "= ";
        break;
    }
    print_num_expr(e->lhs);
    os << " ";
    print_num_expr(e->rhs);
    os << ")";
}

void printer::print_logical_expr(logical_expr* e)
{
    //std::cout << "print_logical_expr\n";
    os << "( ";
    switch(e->op)
    {
    case op_and:
        os << "and ";
        break;
    case op_or:
        os << "or ";
        break;
    }
    os << " ";
    print_bool_expr(e->lhs);
    os << " ";
    print_bool_expr(e->rhs);
    os << " )";
}

void printer::print_bool_expr(bool_expr* e)
{
    //std::cout << "print_bool_expr\n";
    switch(e->kind)
    {
    case ek_bool:
        print_bool_lit(static_cast<bool_lit*>(e));
        break;
    case ek_rel:
        print_rel_expr(static_cast<rel_expr*>(e));
        break;
    case ek_logic:
        print_logical_expr(static_cast<logical_expr*>(e));
        break;
    }
}

std::ostream& operator<<(std::ostream& os, num_expr* numex)
{
    //std::cout << "overloaded operator\n";
    printer print(os);
    print.print_num_expr(numex);
    return os;
}

std::ostream& operator<<(std::ostream& os, bool_expr* boolex)
{
    //std::cout << "overloaded operator\n";
    printer print(os);
    print.print_bool_expr(boolex);
    return os;
}

std::ostream& operator<<(std::ostream& os, const answer& ans)
{
    if(ans.kind == int_ans) os << ans.n;
    else os << ans.e;
    return os;
}

#include <iostream>
#include "el.h"

int main()
{
    //(= (arg1) (arg2))
    auto *e1 = new rel_expr
    {
        op_eq,
        new arg_expr {1},
        new arg_expr {2}
    };

    //(if (< (arg 1) 0) -1 1)
    auto* e2 = new if_expr(
        new rel_expr(
            op_lt,
            new arg_expr(1),
            new int_lit(0)
        ),
        new int_lit(-1),
        new int_lit(1)
    );

    //(+ N N)
    auto* e3 = new arith_expr(
        op_add,
        new int_lit(3),
        new int_lit(4)
    );
    std::cout << height(e1) << std::endl;
    std::cout << height(e2) << std::endl;
    std::cout << height(e3) << std::endl;
    return 0;
}

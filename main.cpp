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

    auto* e4 = new if_expr
    (
     new bool_lit(true),
     new arg_expr(4),
     new int_lit(5)
     );
    //std::cout << "height e1: " << height(e1) << std::endl;
    //std::cout << "height e2: " << height(e2) << std::endl;
    //std::cout << "height e3: " << height(e3) << std::endl;
    //std::cout << "height e4: " << height(e4) << std::endl;
    //std::cout << "max args e1: " << max_args(e1) << std::endl;
    //std::cout << "max args e2: " << max_args(e2) << std::endl;
    //std::cout << "max args e3: " << max_args(e3) << std::endl;
    //std::cout << "max args e4: " << max_args(e4) << std::endl;
    //std::cout << "min args e1: " << min_args(e1) << std::endl;
    //std::cout << "min args e2: " << min_args(e2) << std::endl;
    //std::cout << "min args e3: " << min_args(e3) << std::endl;
    //std::cout << "min args e4: " << min_args(e4) << std::endl;
    //auto* p1 = new prog(3, e4);
    //auto* p2 = new prog(0, e2);
    std::cout << eval(e1) << std::endl;
    std::cout << eval(e2) << std::endl;
    std::cout << eval(e3) << std::endl;
    std::cout << eval(e4) << std::endl;
    return 0;
}

#include <iostream>
#include "el.h"
#include "fold_algos.h"
#include "printer.h"

int main()
{
    //(= (arg1) (arg2))
    bool_expr *e1 = new rel_expr
    {
        op_eq,
        new arg_expr {1, 1},
        new arg_expr {2, 1}
    };

    //(if (< (arg 1) 0) -1 1)
    num_expr* e2 = new if_expr(
        new rel_expr(
            op_lt,
            new arg_expr(1, 1),
            new int_lit(0)
        ),
        new int_lit(-1),
        new int_lit(1)
    );

    //(+ 3 4)
    num_expr* e3 = new arith_expr(
        op_add,
        new int_lit(3),
        new int_lit(4)
    );

    //(if true 4 5)
    num_expr* e4 = new if_expr
    (
     new bool_lit(true),
     new arg_expr(4, 1),
     new int_lit(5)
     );

     //height testing
     /*
     {
        std::cout << "height e1: " << height(e1) << std::endl;
        std::cout << "height e2: " << height(e2) << std::endl;
        std::cout << "height e3: " << height(e3) << std::endl;
        std::cout << "height e4: " << height(e4) << std::endl;
     }
     */

     //min/max args testing
     /*
     {
        std::cout << "max args e1: " << max_args(e1) << std::endl;
        std::cout << "max args e2: " << max_args(e2) << std::endl;
        std::cout << "max args e3: " << max_args(e3) << std::endl;
        std::cout << "max args e4: " << max_args(e4) << std::endl;
        std::cout << "min args e1: " << min_args(e1) << std::endl;
        std::cout << "min args e2: " << min_args(e2) << std::endl;
        std::cout << "min args e3: " << min_args(e3) << std::endl;
        std::cout << "min args e4: " << min_args(e4) << std::endl;
        auto* p1 = new prog(3, e4);
        auto* p2 = new prog(0, e2);
     }
     */

    std::cout << e1 << std::endl;
    std::cout << e2 << std::endl;
    std::cout << e3 << std::endl;
    std::cout << e4 << std::endl << std::endl;

    e1 = fold(e1);
    e2 = fold(e2);
    e3 = fold(e3);
    e4 = fold(e4);

    std::cout << e1 << std::endl;
    std::cout << e2 << std::endl;
    std::cout << e3 << std::endl;
    std::cout << e4 << std::endl;


    return 0;
}

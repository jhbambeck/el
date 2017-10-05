#ifndef PRINTER_H
#define PRINTER_H
#include <iostream>
#include "el.h"



class printer
{
private:
    std::ostream& os;

    void print_int_lit(int_lit*);
    void print_arg_expr(arg_expr*);
    void print_arith_expr(arith_expr*);
    void print_if_expr(if_expr*);

    void print_bool_lit(bool_lit*);
    void print_rel_expr(rel_expr*);
    void print_logical_expr(logical_expr*);

public:
    printer(std::ostream& os1) : os(os1)
        { }

    void print_num_expr(num_expr*);
    void print_bool_expr(bool_expr*);
};

std::ostream& operator<<(std::ostream&, num_expr*);
std::ostream& operator<<(std::ostream&, bool_expr*);
std::ostream& operator<<(std::ostream&, const answer&);

#endif // PRINTER_H

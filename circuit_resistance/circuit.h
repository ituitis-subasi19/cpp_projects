#pragma once
#include "resistor.h"

struct circuit{
    resistor *head;
    void create();
    void add_resistor(const char&, const double&);
    void remove_resistor(const char&, const double&);
    void delete_resistor(resistor*, resistor*);
    void circuit_info();
    void clear();
};
#pragma once

struct resistor{
    char group;
    double value;
    int quantity;
    resistor *next;
    void build_resistor(const char&, const double&);
    void copy_resistor(const char&, const double&, const int&);
};
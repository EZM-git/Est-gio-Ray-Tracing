#ifndef INTERVAL_H
#define INTERVAL_H
#include <limits>

const double infinity = std::numeric_limits<double>::infinity();

class interval {
    public:
        double min, max;


        interval() : min(+infinity), max(-infinity) {} // Não existe intervalo inicialmente.

        interval(double min, double max) : min(min), max(max) {}

        double size() const {
            return max - min;
        }

        bool contains(double x) const {
            return min <= x && x <= max;
        }

        bool surrounds(double x) const {
            return min < x && x < max;
        }

        double clamp(double x) const {
            if (x < min) return min;
            if (x > max) return max;
            return x;
        } // ter ctz q vai ta entre [0, 1]

        static const interval empty, universe;
};

// Constantes estáticas
// Dois estados fundamentais da matemática e da computação gráfica
const interval interval::empty      = interval(+infinity, -infinity); // O conjunto vazio
const interval interval::universe  = interval(-infinity, +infinity); // O conjunto de todos os números reais

#endif
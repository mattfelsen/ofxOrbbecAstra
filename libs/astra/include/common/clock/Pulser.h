#ifndef PULSER_H
#define PULSER_H

#include "Stopwatch.h"
#include <string>

namespace astra { namespace clock {

    class Pulser
    {
    public:
        Pulser();
        ~Pulser();

        void set_period(double period);
        double get_period();

        void start();
        void stop();

        void pause();
        bool is_pulse();
        void reset();

    private:
        Stopwatch m_swatch;
        std::string m_swatchName;

        double m_period{0.0};
    };
}}


#endif /* PULSER_H */
#ifndef TIMER_HPP
# define TIMER_HPP

# include <sys/time.h>

class Timer
{
    private:
        struct timeval  _tp;
        long int        _start;
        long int        _stop;

    public:
        Timer(void);
        Timer(const Timer& other);
        ~Timer();

        Timer&    operator=(const Timer& other);

        void    start(void);
        void    stop(void);
        long int    get_stop() const;
};

#endif
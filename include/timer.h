#ifndef H_TIMER
#define H_TIMER
class Timer {
    private:
        unsigned long prev;
        unsigned long interval;
        bool immediately;
    public:    
        explicit Timer(const unsigned long interval, bool immediately=false);
        explicit Timer(const int interval, bool immediately=false);
        bool tick(const unsigned long nowMillis);
};
#endif

#ifndef IMP_TIMER_H
#define IMP_TIMER_H


class Imp_Timer
{
    public:
        Imp_Timer();
        virtual ~Imp_Timer();

        void start();
        void stop();
        void paused();
        void unpaused();

        int get_ticks();

        bool is_paused();
        bool is_started();

    private:
        int start_tick ;
        int paused_tick;
        bool is_paused_;
        bool is_started_;
};

#endif // IMP_TIMER_H

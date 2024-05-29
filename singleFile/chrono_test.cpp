#include <iostream>
#include <typeinfo>
#include <ctime>
#include <chrono>   
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

void timingus(size_t us)
{
    auto start = std::chrono::system_clock::now();
    while (1) 
    {
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (duration.count() > us) break;
    }
}

void do_something(void) 
{
//     for (int i = 1000, a = 0; i >= 0; --i) {
//        for (int j = 1000; j >= 0; --j) {
//            for (int k = 100; k >= 0; --k) {
//                ++a;
//            }
//        }
//    }
    // usleep(1000);
    // sleep(1);
    timingus(1000000);

}
void func1(void) 
{
   clock_t start = clock();
   do_something();
   clock_t end = clock();
   std::cout << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
}

void func2(void)
{
    auto start = std::chrono::system_clock::now();
    do_something();
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << (double)(duration.count()) * std::chrono::microseconds::period::num / 
        std::chrono::microseconds::period::den  << "s" << std::endl;
}

void func3(void)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    do_something();
    gettimeofday(&end, NULL);
    std::cout << (end.tv_sec + end.tv_usec / pow(10, 6)) - 
            (start.tv_sec + start.tv_usec / pow(10, 6)) << std::endl;
}

void func4(void)
{
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    do_something();
    clock_gettime(CLOCK_REALTIME, &end);
    std::cout << (end.tv_sec + end.tv_nsec / pow(10, 9)) - 
            (start.tv_sec + start.tv_nsec / pow(10, 9)) << std::endl;
}
int main()
{
    void (*p[])(void) = {func1, func2, func3, func4};

    for (size_t i = 0; i < sizeof(p) / sizeof(p[0]); ++i) 
    {
        p[i]();
    }
    
    return 0;
}


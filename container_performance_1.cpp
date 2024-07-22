#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <deque>
#include <list>



using timer = std::chrono::system_clock;

template<class Container>
    void measure_complexity_on_container(unsigned N, std::mt19937 & G) {
        std::exponential_distribution<double> E(1.);
        auto start = timer::now();
        auto end = timer::now();
        std::chrono::duration<double>
            generation_time,
            counting_time,
            square_time,
            copy_time,
            sort_time,
            swap_time;
        {   
            // Generation of random values
            
            start = timer::now(); 
            Container c1(N);
            Container c2(N);
            generate(c1.begin(), c1.end(), [&]() { return E(G); });
            end = timer::now();
            generation_time = end - start;

            // Counting elements greater than 10

            start = timer::now();
            int n10 = std::count_if(c1.begin(), c1.end(), [](double x) { return (x > 10.); });
            end = timer::now();
            counting_time = end - start;

            // Squaring the first 100 elements: Note that the reference is important!
            start = timer::now();
            std::for_each(c1.begin(), c1.begin() + 100, [](double & x) { return x = x * x; });
            // Here, these two functions do the same thing, but there is likely a difference in terms of performance
            //std::transform(c1.begin(), c1.end(), c1.begin() + 100, [](double & x) { return x * x; });
            end = timer::now();
            square_time = end - start;

            // Copying the container to the second one
            start = timer::now();
            std::copy(c1.begin(), c1.end(), c2.begin());
            end = timer::now();
            copy_time = end - start;

            // Sorting
            start = timer::now();
            std::sort(c1.begin(), c1.begin() + N / 2, [](double & x1, double & x2) { return x1 < x2; });
            end = timer::now();
            sort_time = end - start;

            // Swapping the contents of the two containers
            start = timer::now();
            std::swap(c1, c2);
            end = timer::now();
            swap_time = end - start;

            std::cout << "Size: " << c1.size() << "\n";
            std::cout << "Generation time: " << generation_time.count() << "s.\n";
            std::cout << "Counting time: " << counting_time.count() << "s.\n";
            std::cout << "Square calculation time: " << square_time.count() << "s.\n";
            std::cout << "Copy time: " << copy_time.count() << "s (value: " << n10 << ")\n";
            std::cout << "Sort time: " << sort_time.count() << "s.\n";
            std::cout << "Swap time: " << swap_time.count() << "s.\n";
            std::cout << "----------------------------\n\n";
        }
};


template<>
        void measure_complexity_on_container<std::list<double>>(unsigned N, std::mt19937 & G) {
            using Container = std::list<double>;
                    std::exponential_distribution<double> E(1.);
        auto start = timer::now();
        auto end = timer::now();
        std::chrono::duration<double>
            generation_time,
            counting_time,
            square_time,
            copy_time,
            sort_time,
            swap_time;
        {   
            // Generation of random values
            
            start = timer::now(); 
            Container c1(N);
            Container c2(N);
            generate(c1.begin(), c1.end(), [&]() { return E(G); });
            end = timer::now();
            generation_time = end - start;

            // Counting elements greater than 10

            start = timer::now();
            int n10 = std::count_if(c1.begin(), c1.end(), [](double x) { return (x > 10.); });
            end = timer::now();
            counting_time = end - start;

            // Squaring the first 100 elements: Note that the reference is important!
            start = timer::now();
            auto It_position = c1.begin();
            std::advance(It_position,100);
            std::for_each(c1.begin(), It_position, [](double & x) { return x = x * x; });
            // Here, these two functions do the same thing, but there is likely a difference in terms of performance
            // std::transform(c1.begin(), c1.end(), It_position, [](double & x) { return x * x; });
            end = timer::now();
            square_time = end - start;

            // Copying the list to the second one
            start = timer::now();
            std::copy(c1.begin(), c1.end(), c2.begin());
            end = timer::now();
            copy_time = end - start;

 /*         // Sorting all elements
            start = timer::now();
            c1.sort();
            end = timer::now();
            sort_time = end - start;
         
            // Note : * For partial sorting, you cannot do this directly since it is not defined. 
               //     * You need to use another container, copy the elements, perform the sort, and then copy them back.
                    
 */
            // Swapping the contents of the two listes
            start = timer::now();
            std::swap(c1, c2);
            end = timer::now();
            swap_time = end - start;

            std::cout << "Size: " << c1.size() << "\n";
            std::cout << "Generation time: " << generation_time.count() << "s.\n";
            std::cout << "Counting time: " << counting_time.count() << "s.\n";
            std::cout << "Square calculation time: " << square_time.count() << "s.\n";
            std::cout << "Copy time: " << copy_time.count() << "s (value: " << n10 << ")\n";
            std::cout << "Sort time: NOT DEFINED \n";
            std::cout << "Swap time: " << swap_time.count() << "s.\n";
            std::cout << "----------------------------\n\n";
        }

        };

int main(){
    std::mt19937 G((time(nullptr)));
    const long int N = 10000000;
    std::cout << "*** Calculation with std::vector<double> ***\n";
    measure_complexity_on_container<std::vector<double>>(N,G);
    measure_complexity_on_container<std::vector<double>>(2 * N,G);
    measure_complexity_on_container<std::vector<double>>(4 * N,G);
    measure_complexity_on_container<std::vector<double>>(8 * N,G);

    std::cout << "*** Calculation avec std::deque<double> ***\n";
    measure_complexity_on_container<std::deque<double>>(N,G);
    measure_complexity_on_container<std::deque<double>>(2 * N,G);
    measure_complexity_on_container<std::deque<double>>(4 * N,G);
    measure_complexity_on_container<std::deque<double>>(8 * N,G);


    std::cout << "*** Calculation avec std::list<double> ***\n";
    measure_complexity_on_container<std::list<double>>(N,G);
    measure_complexity_on_container<std::list<double>>(2 * N,G);
    measure_complexity_on_container<std::list<double>>(4 * N,G);
    measure_complexity_on_container<std::list<double>>(8 * N,G);


    return 0;
}

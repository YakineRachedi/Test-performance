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

            for(int i = 0; i < N; i++){
                double x = E(G); // To avoid correlation, we store the random variable in a temporary variable.
                c1[i] = x;
            }
            end = timer::now();
            generation_time = end - start;

            // Counting elements greater than 10.
            start = timer::now(); 
            int n10 = 0;
            for(int i = 0; i < N; i++){
                if(c1[i] > 10.){
                    n10++;
                }
            }
            end = timer::now();
            counting_time = end - start;

            // Squaring the first 100 elements: Note that the reference is important!
            start = timer::now(); 
            for(int i = 0; i < 100; i++){
                c1[i] = c1[i] * c1[i];
            }
            end = timer::now();
            square_time = end - start;

            // Copying the container to the second one
            for(int i = 0; i < N; i++){
                c2[i] = c1[i];
            }

            // Sorting
            start = timer::now(); 
            for(int i = 0; i < N / 2; i++){
                int index_min = i;
                for(int j = i + 1; j < N / 2; j++){
                    if(c1[j] < c1[index_min]){
                        index_min = j;
                    }
                }
                if(i != index_min){
                    double temp = c1[i];
                    c1[i] = c1[index_min];
                    c1[index_min] = temp;
                }
                else{
                    continue;
                }
            }
            end = timer::now();
            sort_time = end - start;

            // Swapping the contents of the two containers
            start = timer::now();
            Container temp = c1;
            c1 = c2;
            c2 = temp;
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
                for (unsigned i = 0; i < N; ++i) {
                    c1.push_back(E(G));
                }
                end = timer::now();
                generation_time = end - start;

                // Counting elements greater than 10

                start = timer::now();
                int n10 = 0;
                for(const double & x : c1){
                    if(x > 10){
                        n10++;
                    }
                }
                end = timer::now();
                counting_time = end - start;

                // Squaring the first 100 elements
                start = timer::now();
                for (auto It = c1.begin(); It != c1.end(); ++It) {
                    *It = (*It) * (*It);
                }
                end = timer::now();
                square_time = end - start;

                // Copying the list to the second one
                start = timer::now();
                for(double & x : c1){
                    c2.push_back(x);
                }
                end = timer::now();
                copy_time = end - start;

                // Swapping the contents of the two listes
                start = timer::now();
                Container temp = c1;
                c1 = c2;
                c2 = temp;
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
    const long int N = 1000;
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

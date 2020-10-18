#include <customer.h>

bool cmp(Customer a, Customer b){
    return a.arrivalTime < b.arrivalTime;
}
void generate_customers(int n, std::queue <Customer> &customers_queue){
    std::vector <Customer> array;
    // H-Customers
    for(int i=0; i<n; ++i){
        Customer c;
        c.id = "H";
        c.arrivalTime = rand() % 60;
        c.serviceTime = rand() % 2 + 1;
        c.responseTime = 0;
        c.turnaroundTime = 0;
        c.waitingTime = 0;
        array.push_back(c);
    }
    // M-Customers
    for(int i=0; i<3*n; ++i){
        Customer c;
        c.id = "M";
        c.arrivalTime = rand() % 60;
        c.serviceTime = rand() % 3 + 2;
        c.responseTime = 0;
        c.turnaroundTime = 0;
        c.waitingTime = 0;
        array.push_back(c);
    }
    // L-Customers
    for(int i=0; i<6*n; ++i){
        Customer c;
        c.id = "L";
        c.arrivalTime = rand() % 60;
        c.serviceTime = rand() % 4 + 4;
        c.responseTime = 0;
        c.turnaroundTime = 0;
        c.waitingTime = 0;
        array.push_back(c);
    }
    std::sort(array.begin(), array.end(), cmp);
    for(auto i : array){
        customers_queue.push(i);
    }
}


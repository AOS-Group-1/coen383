#include <customer.h>

bool cmp(Customer a, Customer b){
    return a.arrivalTime < b.arrivalTime;
}
void generate_customers(int n, std::queue <Customer> &customers_queue, char customer_type){
    std::vector <Customer> array;
    // H-Customers
    if(customer_type == 'H')
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
    if(customer_type == 'M')
        for(int i=0; i<n; ++i){
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
    if(customer_type == 'L')
        for(int i=0; i<n; ++i){
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


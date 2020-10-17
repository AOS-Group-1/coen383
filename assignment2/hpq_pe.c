#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_JOBS 10

typedef struct {
    int id;
    float arrival_time;
    float service_time;
    int priority;
    float completed_time;
    float start_time;
    float response; // start_time - arrival_time
    float turnaround; // completion_time - arrival_time
    float wait; // turnaround - service_time
    float elapsed;
    int status; // -1 = Waiting 1 = Ready, 2 = Running, 3 = Done
} job_t;

void generate_job(job_t *job, int upper, int lower){
    //int seed = time(NULL);
    //srand(0);
    float arrival_time = (rand() % (upper-lower+1)) + lower;
    float service_time = rand() % 11;
    if(service_time == 0) service_time++;
    int priority = rand() % 5;
    if (priority == 0) priority++;

    job->arrival_time = arrival_time;
    job->service_time = service_time;
    job->priority = priority;
    job->completed_time = 0;
    job->start_time = 0;
    job->response = 0;
    job->turnaround = 0;
    job->wait = 0;
    job->elapsed = 0;
    job->status = -1;
}


void print_job(job_t *job){
    printf("%.1f, ", job->arrival_time);
    printf("%.1f, ", job->service_time);
    printf("%d\n", job->priority);
}

void sort_queue(job_t *queue, int n){
    // Bubble Sort the queue on Arrival Time
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++){
            if(queue[j+1].arrival_time <= queue[j].arrival_time){
                job_t tmp = queue[j];
                queue[j] = queue[j+1];
                queue[j+1] = tmp;
            }
        }
    }
}

job_t* check_idle(job_t **queue, int *add_jobs){
    int i = 0;
    job_t *tmp_queue;

    // Intra Idle Time
    while(1){
        if(i >= N_JOBS+(*add_jobs) || (*queue+i+1)->arrival_time > 99){
            break;
        }
        else if( (*queue+i+1)->arrival_time - ((*queue+i)->arrival_time + (*queue+i)->service_time) > 2){
            (*add_jobs)++;
            tmp_queue = (job_t *)malloc((*add_jobs + N_JOBS) * sizeof(job_t));
            generate_job(&tmp_queue[0], (*queue+i+1)->arrival_time-1, (*queue+i)->arrival_time + (*queue+i)->service_time + 2);
            for(int k = 1; k < *add_jobs + N_JOBS; k++){
                tmp_queue[k] = *(*queue+k-1);
            }
            sort_queue(tmp_queue, N_JOBS+(*add_jobs));
            free(*queue);
            queue = (job_t **)malloc((*add_jobs + N_JOBS) * sizeof(job_t));
            for(int k = 0; k < *add_jobs + N_JOBS; k++){
                queue[k] = &tmp_queue[k];
            }
            //i++;
        }
        else{ i++;
        }
    }
    return *queue;
}

void initialize_runq_pq(job_t **job, int njobs){
    for(int i = 0; i < njobs; ++i){
        job[i] = (job_t *)malloc(sizeof(job_t));
        job[i]->id = -1;
        job[i]->arrival_time = 0;
        job[i]->service_time = 0;
        job[i]->priority = 0;
        job[i]->completed_time = 0;
        job[i]->start_time = 0;
        job[i]->response = 0;
        job[i]->turnaround = 0;
        job[i]->wait = 0;
        job[i]->elapsed = 0;
        job[i]->status = 0;
    }
}

void initialize_runq(job_t *job, int njobs){
    for(int i = 0; i < njobs; ++i){
        job[i].id = -1;
        job[i].arrival_time = 0;
        job[i].service_time = 0;
        job[i].priority = 0;
        job[i].completed_time = 0;
        job[i].start_time = 0;
        job[i].response = 0;
        job[i].turnaround = 0;
        job[i].wait = 0;
        job[i].elapsed = 0;
        job[i].status = 0;
    }
}

// Round-Robin Simulation
void simulate(job_t *queue, int n_jobs, float *atp, float *att, float *awt, float *art){
    int completed_jobs = 0, running_jobs = 0, waiting = 0;
    int current_time = 0;
    job_t *run_q = (job_t *)malloc(n_jobs * sizeof(job_t));
    initialize_runq(run_q, n_jobs);

    run_q[0] = queue[0];

    while(completed_jobs < n_jobs){

        if(current_time > 300){
            printf("\n\n****ERROR****\n\n\n");
            break;
        }

        // Get Job at front of the queue
        int id = run_q[0].id;

        // If Arrived -> Ready
        if(current_time >= run_q[0].arrival_time && run_q[0].status == -1){
            run_q[0].status = 1;
        }
        // If Ready -> Running
        if(run_q[0].status == 1){
            run_q[0].status = 2;
            running_jobs++; // Back of the queue
            if(waiting > 0) waiting--;
            run_q[0].start_time = current_time;
        }
        // If Running
        if(run_q[0].status == 2){
            // Print Running Job
            printf("%c", id+65);
            run_q[0].elapsed++;
            current_time++;

            // Check if Done
            if(run_q[0].elapsed == run_q[0].service_time){
                run_q[0].status = 3;
                run_q[0].completed_time = current_time;
                running_jobs--;
                completed_jobs++;
                // Copy the rest to process queue
                queue[id] = run_q[0];
                // Shift Left
                for(int i = 0; i <= running_jobs+waiting; i++){
                    run_q[i] = run_q[i+1];
                }

            }
            // If Not Done & Other jobs in queue
            else if (running_jobs+waiting > 1){
                job_t tmp = run_q[0]; // Current Job
                // Shift left
                for(int i = 0; i < running_jobs+waiting; i++){
                    run_q[i] = run_q[i+1];
                }
                run_q[running_jobs+waiting-1] = tmp; // Put Current in the back
            }
        }
        // Increment Time if Idle
        if(running_jobs == 0){
            printf("-");
            current_time++;
        }

        // Put Jobs in Queue if they arrived
        for(int i = completed_jobs+running_jobs+waiting; i < n_jobs; i++){
            if(current_time >= queue[i].arrival_time && queue[i].status == -1) {
                // Shift right and move arrival in front
                for(int i = running_jobs+waiting; i > 0; --i){
                    run_q[i] = run_q[i-1];
                }
                waiting++;
                run_q[0] = queue[i];
            }
        }
    }

    float avg_rt = 0;
    float avg_tt = 0;
    float avg_wt = 0;

    // Calculate Statistics
    for(int i = 0; i < n_jobs; i++){
        queue[i].response = queue[i].start_time - queue[i].arrival_time;
        queue[i].turnaround = queue[i].completed_time - queue[i].arrival_time;
        queue[i].wait = queue[i].turnaround - queue[i].service_time;
        avg_rt += queue[i].response/n_jobs;
        avg_tt += queue[i].turnaround/n_jobs;
        avg_wt += queue[i].wait/n_jobs;
    }

    // Throughput  = # Jobs / Total Time
    float tp = (float)n_jobs/(float)current_time;
    printf("\n\n| Throughput: %.2f | Response: %.2f | Turnaround: %.2f | Wait: %.2f | \n", tp, avg_rt, avg_tt, avg_wt);

    *art += avg_rt;
    *att += avg_tt;
    *awt += avg_wt;
    *atp += tp;

    free(run_q);
}

void initialize_pq(job_t *queue, job_t **ppq1, job_t **ppq2, job_t **ppq3, job_t **ppq4, int n_jobs,
                   int *j1, int *j2, int *j3, int *j4){
    int i = 0, q1=0, q2=0, q3=0, q4=0, n = n_jobs;
    while(n_jobs--){
        if(queue[i].priority == 1){
            q1++;
        }
        else if(queue[i].priority == 2){
            q2++;
        }
        else if(queue[i].priority == 3){
            q3++;
        }
        else if(queue[i].priority == 4){
            q4++;
        }
        i++;
    }

    job_t *pq1 = NULL, *pq2 = NULL, *pq3 = NULL, *pq4 = NULL;
    if(q1 > 0){
        pq1 = (job_t*)malloc(q1 * sizeof(job_t));
        initialize_runq(pq1, q1);
    }
    if(q2 > 0){
        pq2 = (job_t*)malloc(q2 * sizeof(job_t));
        initialize_runq(pq2, q2);
    }
    if(q3 > 0){
        pq3 = (job_t*)malloc(q3 * sizeof(job_t));
        initialize_runq(pq3, q3);
    }
    if(q4 > 0){
        pq4 = (job_t*)malloc(q4 * sizeof(job_t));
        initialize_runq(pq4, q4);
    }

    i = 0, q1=0, q2=0, q3=0, q4=0;
    while(n--){
        if(queue[i].priority == 1){
            pq1[q1++] = queue[i];
        }
        else if(queue[i].priority == 2){
            pq2[q2++] = queue[i];
        }
        else if(queue[i].priority == 3){
            pq3[q3++] = queue[i];
        }
        else if(queue[i].priority == 4){
            pq4[q4++] = queue[i];
        }
        i++;
    }
    *ppq1 = pq1;
    *ppq2 = pq2;
    *ppq3 = pq3;
    *ppq4 = pq4;
    *j1 = q1;
    *j2 = q2;
    *j3 = q3;
    *j4 = q4;

}

job_t * get_hp_job_init(int *ct, job_t *pq1,job_t *pq2,job_t *pq3,job_t *pq4){
    int x = 0, i1=0, i2=0, i3=0, i4=0;
    while(1){
        if(pq1 != NULL && *ct >= pq1[i1].arrival_time){
            if(pq1[i1].status == -1){
                return &(pq1[i1]);
            }
            else i1++;
        }
        else if(pq2 != NULL && *ct >= pq2[i2].arrival_time){
            if(pq2[i2].status == -1){
                return &(pq2[i2]);
            }
            else i2++;

        }
        else if(pq3 != NULL && *ct >= pq3[i3].arrival_time){
            if(pq3[i3].status == -1){
                return &(pq3[i3]);
            }
            else i3++;

        }
        else if(pq4 != NULL && *ct >= pq4[i4].arrival_time){
            if(pq4[i4].status == -1){
                return &(pq4[i4]);
            }
            else i4++;
        }
        else{
            (*ct)++;
            printf("-");
        }
    }
}

int get_next_pq(int ct, job_t **run_q, job_t *pq, int *waiting, int running_jobs, int pmax, int pi){
    if(pi < pmax){
        if(ct >= pq[pi].arrival_time && pq[pi].status == -1) {
            // Shift right and move arrival in front
            for(int i = running_jobs+(*waiting); i > 0; --i){
                run_q[i] = run_q[i-1];
            }
            (*waiting)++;
            run_q[0] = &pq[pi];
            run_q[0]->status = 1; // Arrived and Ready to run
            return 1;
        }
    }
    return 0;
}

job_t * get_hp_job(int *ct, job_t **run_q, int n_jobs){
    job_t *front = run_q[0];

    for(int i=0; i<n_jobs; i++) {
        if (run_q[i]->priority == 1 && *ct >= run_q[i]->arrival_time
            && (run_q[i]->status == -1 || run_q[i]->status == 1 || run_q[i]->status == 2)) {
            front = run_q[i];
            // Shift right to the found process
            for (int k = i; k > 0; --k) {
                run_q[k] = run_q[k - 1];
            }
            return front;
        }
    }
    for(int i=0; i<n_jobs; i++) {
        if (run_q[i]->priority == 2 && *ct >= run_q[i]->arrival_time
            && (run_q[i]->status == -1 || run_q[i]->status == 1 || run_q[i]->status == 2)) {
            front = run_q[i];
            for (int k = i; k > 0; --k) {
                run_q[k] = run_q[k - 1];
            }
            return front;
        }
    }
    for(int i=0; i<n_jobs; i++) {
        if (run_q[i]->priority == 3 && *ct >= run_q[i]->arrival_time
            && (run_q[i]->status == -1 || run_q[i]->status == 1 || run_q[i]->status == 2)) {
            front = run_q[i];
            for (int k = i; k > 0; --k) {
                run_q[k] = run_q[k - 1];
            }
            return front;
        }
    }
    for(int i=0; i<n_jobs; i++) {
        if(run_q[i]->priority == 4 && *ct >= run_q[i]->arrival_time
                && (run_q[i]->status == -1 || run_q[i]->status == 1 || run_q[i]->status == 2)){
            front = run_q[i];
            for(int k=i; k>0; --k){
                run_q[k] = run_q[k-1];
            }
            return front;
        }
    }
    return front;
}

void calculate_single_hpq(int n, job_t *pq, int pn, float *atp, float *att, float *awt, float *art){
    float tp =0, avg_rt = 0, avg_tt = 0, avg_wt = 0;

    if(pn > 0){
        // Calculate Statistics
        for(int i = 0; i < pn; i++){
            pq[i].response = pq[i].start_time - pq[i].arrival_time;
            pq[i].turnaround = pq[i].completed_time - pq[i].arrival_time;
            pq[i].wait = pq[i].turnaround - pq[i].service_time;
            avg_rt += pq[i].response/pn;
            avg_tt += pq[i].turnaround/pn;
            avg_wt += pq[i].wait/pn;
        }
        // Throughput  = # Jobs / Completion Time of Last Job
        tp = (float)pn/(float)pq[pn-1].completed_time;
        printf("\nStats for Priority Queue: %d", n);
        printf("\n| Throughput: %.2f | Response: %.2f | Turnaround: %.2f | Wait: %.2f | \n", tp, avg_rt, avg_tt, avg_wt);
    }
    else{
        printf("\nNo Jobs with priority: %d\n", n);
    }

    *art += avg_rt;
    *att += avg_tt;
    *awt += avg_wt;
    *atp += tp;
}

// HPQ Simulation pre-emptive with RR
void simulate_hpq(job_t *queue, int n_jobs, float *atp, float *att, float *awt, float *art){
    int completed_jobs = 0, running_jobs = 0, waiting = 0;
    int current_time = 0, init=0, j1=0, j2=0, j3=0, j4=0;

    job_t *pq1 = NULL, *pq2 = NULL, *pq3 = NULL, *pq4 = NULL;
    job_t *run_q[n_jobs];
    initialize_runq_pq(run_q, n_jobs);
    initialize_pq(queue, &pq1, &pq2, &pq3, &pq4, n_jobs, &j1, &j2, &j3, &j4);

    while(completed_jobs < n_jobs){

        if(current_time > 300){
            printf("\n\n****ERROR****\n\n");
            break;
        }
        if(!init){
            init = 1;
            // Get First HP Job among all queues
            run_q[0] = get_hp_job_init(&current_time, pq1, pq2, pq3, pq4);
        }
        else{
            // Get Job from the queue with highest priority
            run_q[0] = get_hp_job(&current_time, run_q, n_jobs);
        }

        int id = run_q[0]->id;

        // If Arrived -> Ready
        if(current_time >= run_q[0]->arrival_time && run_q[0]->status == -1){
            run_q[0]->status = 1;
        }
        // If Ready -> Running
        if(run_q[0]->status == 1){
            run_q[0]->status = 2;
            running_jobs++; // Back of the queue
            if(waiting > 0) waiting--;
            run_q[0]->start_time = current_time;
        }
        // If Running
        if(run_q[0]->status == 2){
            // Print Running Job
            printf("%c", id+65);
            run_q[0]->elapsed++;
            current_time++;

            // Check if Done
            if(run_q[0]->elapsed == run_q[0]->service_time){
                run_q[0]->status = 3;
                run_q[0]->completed_time = current_time;
                running_jobs--;
                completed_jobs++;

                // Shift Left
                for(int i = 0; i <= running_jobs+waiting; i++){
                    run_q[i] = run_q[i+1];
                }

            }
            // If Not Done & Other jobs in queue
            else if (running_jobs+waiting > 1){
                job_t *tmp = run_q[0]; // Current Job
                // Shift Left
                for(int i = 0; i < running_jobs+waiting; i++){
                    run_q[i] = run_q[i+1];
                }
                run_q[running_jobs+waiting-1] = tmp; // Put Current in the back
            }
        }
        // Increment Time if Idle
        if(running_jobs == 0){
            printf("-");
            current_time++;
        }

        int pi=0;
        // Put next highest priority job in queue if it arrived
        while(1){
            if(get_next_pq(current_time, run_q, pq1, &waiting, running_jobs, j1, pi)) {
                break;
            }
            else if(get_next_pq(current_time, run_q, pq2, &waiting, running_jobs, j2, pi)){
                break;
            }
            else if(get_next_pq(current_time, run_q, pq3, &waiting, running_jobs, j3, pi)){
                break;
            }
            else if(get_next_pq(current_time, run_q, pq4, &waiting, running_jobs, j4, pi)){
                break;
            }
            else if (pi >= n_jobs){
                // No jobs arrived
                break;
            }
            else{
                pi++;
            }
        }
    }

    calculate_single_hpq(1, pq1, j1, &atp[0], &att[0], &awt[0], &art[0]);
    calculate_single_hpq(2, pq2, j2, &atp[1], &att[1], &awt[1], &art[1]);
    calculate_single_hpq(3, pq3, j3, &atp[2], &att[2], &awt[2], &art[2]);
    calculate_single_hpq(4, pq4, j4, &atp[3], &att[3], &awt[3], &art[3]);

}


int main(int argc, char **argv) {

    int seed = time(NULL);
    if(argc > 1){
        seed = atoi(argv[1]);
    }
    srand(seed);

    float runs = 0, total_jobs = 0;
    float atp = 0, att = 0, awt = 0, art = 0;
    float atpp[4] = {0,0,0,0}, attp[4] = {0,0,0,0}, awtp[4] = {0,0,0,0}, artp[4] = {0,0,0,0};

    while(runs < 5){
        //printf("Seed = %d\n", seed);

        // Create Queue
        job_t *queue = (job_t *)malloc(N_JOBS * sizeof(job_t));;
        for(int i = 0; i < N_JOBS; i++){
            generate_job(&queue[i], 99, 0);
        }

        sort_queue(queue, N_JOBS);

        // Fill intra idle times with jobs
        int add_jobs = 0;
        queue = check_idle(&queue, &add_jobs);

        printf("\n*************************************************\nQueue for HPQ pre-emptive Run: %d\n", (int)runs+1);
        printf("*************************************************\n");
        printf("Job | Arrival | Service | Priority\n");
        printf("*************************************************\n");
        for(int i = 0; i < N_JOBS + add_jobs; i++){
            queue[i].id = i;
            printf("%c : ", queue[i].id+65);
            print_job(&queue[i]);
        }

        printf("\n*************************************************\nStats for HPQ pre-emptive Run: %d\n", (int)runs+1);
        printf("*************************************************\n\n");
        simulate_hpq(queue, N_JOBS+add_jobs, atpp, attp, awtp, artp);
        total_jobs += N_JOBS+add_jobs;

        free(queue);
        runs++;
    }

    // Total Averages for each PQ
    printf("\n*************************************************\nAverages for all HPQ pre-emptive Runs:\n");
    printf("*************************************************\n");
    for(int i = 0; i < 4; i++){
        printf("Priority %d: ", i+1);
        printf("| Throughput: %2.2f | Response: %2.2f | Turnaround: %2.2f | Wait: %2.2f |\n",
               atpp[i]/runs, artp[i]/runs, attp[i]/runs, awtp[i]/runs);

    }

    printf("Avg Jobs: %.1f\n", total_jobs/runs);
    return 0;
}

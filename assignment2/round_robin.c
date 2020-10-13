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
            queue = (job_t *)malloc((*add_jobs + N_JOBS) * sizeof(job_t));
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
    printf("\nThroughput: %.2f\nResponse: %.2f\nTurnaround: %.2f\nWait: %.2f\n", tp, avg_rt, avg_tt, avg_wt);

    *art += avg_rt;
    *att += avg_tt;
    *awt += avg_wt;
    *atp += tp;

    free(run_q);
}


int main() {

    int seed = time(NULL);
    srand(seed);

    float runs = 0, total_jobs = 0;
    float atp = 0, att = 0, awt = 0, art = 0;

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

        printf("\n*************************************************\nQueue for Round Robin Run: %d\n", (int)runs+1);
        printf("*************************************************\n");
        printf("Job | Arrival | Service | Priority\n");
        printf("*************************************************\n");
        for(int i = 0; i < N_JOBS + add_jobs; i++){
            queue[i].id = i;
            printf("%c : ", queue[i].id+65);
            print_job(&queue[i]);
        }

        printf("\n*************************************************\nStats for Round Robin Run: %d\n", (int)runs+1);
        printf("*************************************************\n");
        simulate(queue, N_JOBS+add_jobs, &atp, &att, &awt, &art);
        total_jobs += N_JOBS+add_jobs;

        free(queue);
        runs++;
    }

    printf("\n*************************************************\nAverages for all Round Robin Runs:\n");
    printf("*************************************************\n");
    printf("\nThroughput: %.2f\nResponse: %.2f\nTurnaround: %.2f\nWait: %.2f\n", atp/runs, art/runs, att/runs, awt/runs);
    printf("Avg Jobs: %.1f\n", total_jobs/runs);

    return 0;
}

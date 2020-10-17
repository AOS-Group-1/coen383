#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


#define PROCESS_COUNT 30
#define RUNS_PER_ALGO 5
#define QUANTA 100

//Process
typedef struct {
    int process_id;
    float arrival_time;
    float burst_time;
    int priority;
    int age;
} process;


// MAIN Function
int main(int argc, char *argv[]){
	
    int seed = time(NULL);
	 if(argc > 1){
        seed = atoi(argv[1]);
    }
	 srand(seed); // guarantee consistency when debugging

    process proc_list[PROCESS_COUNT];
    int i;
    process *buff = malloc(PROCESS_COUNT * sizeof(process));

        //int seed = time(NULL);
        //srand(seed);

        //srand(0);
        for (i=0; i< RUNS_PER_ALGO; i++)
        {
            printf("%d\n", i);
            generate_process(buff);
            print_procs(buff);
            process b[PROCESS_COUNT];
            for(int j=0;j<PROCESS_COUNT;j++) {
               // a[j] = buff[j];
                b[j] = buff[j];
            }

            hpf_nonpreemptive(b);
        }
   
    return 0;

}

// Function to compare the arrival time of a process
int compare_arrival_times(const void * a, const void * b)
{
    process *p1 = (process*)a;
    process *p2 = (process*)b;
    float r = p1->arrival_time - p2->arrival_time;
    if (r>0) return 1;
    if (r<0) return -1;
    return r;
}

// Function to generate processes with random arrival time, burst time and priority
int generate_process(process *p)
{
    int pr;
    int i;
    float tmp;
    for(i=0; i<PROCESS_COUNT; i++)
    {
        p[i].process_id = i;

        tmp = rand() % 1000;
        tmp = tmp / 10;
        p[i].arrival_time = tmp;

        tmp = rand() % 101;
        tmp = tmp / 10;
        if (tmp < 1) tmp += 1;
        p[i].burst_time = tmp;

        pr = rand() % 5;
        if (pr == 0) pr += 1;
        p[i].priority = pr;
    }

    return 0;
}

// Function to print the processes in a buffer.
int print_procs(process *b){
    int i;
    printf("|   id    |   arvlTime |   runTime | priority|\n");
    printf("|-------------------------------------------------------------|\n");
    for (i=0; i<PROCESS_COUNT; i++){
        printf("|   %-7d|   %-7.1f|   %-7.1f|   %-7d|\n", \
            b[i].process_id,\
            b[i].arrival_time,\
            b[i].burst_time,\
            b[i].priority);

    }
    printf("--------------------------------------------------------------\n");

    return 0;
}

int last_q;

void print_statistics(process* ptr,int* fs,int* ls,int* done) {
    float avg_response_time = 0,
	  avg_turn_around_time = 0,
	  throughput = 0,
	  avg_waiting_time = 0;
    int processes = 0;
    float avg_rt[4] = {0};
    float avg_tat[4] = {0};
    float avg_wt[4] = {0};
    float th[4] = {0};
    int proc_count[4] = {0};
    for(int i=0;i<4;i++) {
		avg_rt[i] = 0; avg_tat[i] = 0;
		avg_wt[i] = 0; th[i] = 0;
		proc_count[i] = 0;
    }

    for(int i=0;i<PROCESS_COUNT;i++) 
		if(done[ptr[i].process_id]) {
			processes++;
			avg_response_time += fs[ptr[i].process_id] - ptr[i].arrival_time + 1;
			avg_turn_around_time += ls[ptr[i].process_id] - ptr[i].arrival_time + 1;
			assert((ls[ptr[i].process_id] - ptr[i].arrival_time + 1) >= ptr[i].burst_time);
			avg_waiting_time += (ls[ptr[i].process_id] - ptr[i].arrival_time + 1) - ptr[i].burst_time;

		
			int ix = ptr[i].priority - 1; // Get the array index
			proc_count[ix]++;
			avg_rt[ix] += fs[ptr[i].process_id] - ptr[i].arrival_time + 1;
			avg_tat[ix] += ls[ptr[i].process_id] - ptr[i].arrival_time + 1;
			avg_wt[ix] += (ls[ptr[i].process_id] - ptr[i].arrival_time + 1) - ptr[i].burst_time;
    }



    for(int i=0;i<4;i++) { 
		avg_rt[i] /= proc_count[i];
		avg_tat[i] /= proc_count[i];
		avg_wt[i] /= proc_count[i];
		th[i] = ((1.0*proc_count[i]) / (1.0*last_q));
    }

    printf("\n----Overall stats----\n");
    printf("Total completed processes: %d\n",processes);
    avg_response_time /= processes;
    avg_turn_around_time /= processes;
    avg_waiting_time /= processes;
    printf("Avg. Response time: %f\nAvg. Turn around-time: %f\nAvg. Waiting time: %f\n",avg_response_time,avg_turn_around_time,avg_waiting_time);
    throughput = (1.0*(processes))/(1.0*last_q);
    printf("Avg. throughput: %f\n",throughput);

    
    printf("\n--priority specific stats----\n");

    for(int i=0;i<4;i++) {
		printf("Priority %d:\n",i+1);
		printf("Avg. Response time: %f\nAvg. Turn around-time: %f\nAvg. Waiting time: %f\n",avg_rt[i],avg_tat[i],avg_wt[i]);
		printf("Avg. throughput: %f\n",th[i]);
    }
}


int hpf_nonpreemptive(process *ptr) {

    last_q = QUANTA;

    qsort(ptr, PROCESS_COUNT, sizeof(process), compare_arrival_times);
    process queue[4][PROCESS_COUNT];

    int idx[4] = {0,0,0,0}; // first available position in each queue
    int first_served[PROCESS_COUNT]; 
    int last_served[PROCESS_COUNT]; 
    int done[PROCESS_COUNT];

    // Initialize arrays
    for(int i=0;i<PROCESS_COUNT;i++) {
		first_served[i] = -1;
		last_served[i] = -1;
		done[i] = 0;
    }

    process* active_process = NULL;

    int x = 0; 
    for(int q=0;q<QUANTA + 50;q++) {

		if(q == QUANTA) { // process which cannot be served
			for(int i=0;i<4;i++) 
			for(int j=0;j<idx[i];j++) {
				if(first_served[queue[i][j].process_id] == -1) 
					queue[i][j].burst_time = -1.0;
			}
		}

		//  Handle aging - promote process to higher queue after age of 5 quanta


		// Age processes present in all queues (except queue 1)
		for(int i=1;i<4;i++) 
			for(int j=0;j<idx[i];j++) 
				if(queue[i][j].burst_time > 0) {
					queue[i][j].age++;
		}

		//see if any process should be assigned queue
		if(q < QUANTA) {
			while(x < PROCESS_COUNT && ptr[x].arrival_time <= q) {
				int pr = ptr[x].priority - 1;
				queue[pr][idx[pr]] = ptr[x];
				idx[pr]++;
				x++;
			}
		}

		for(int i=1;i<4;i++) {
			for(int j=0;j<idx[i];j++) 
			if(queue[i][j].burst_time > 0 && queue[i][j].age == 5) {
				if(active_process && active_process->process_id == queue[i][j].process_id) 
					continue; 
				queue[i-1][idx[i-1]] = queue[i][j]; // Insert process into higher priority queue
				queue[i-1][idx[i-1]].age = 0; 
				queue[i-1][idx[i-1]].priority--;
				printf("Process %d aged one priority up\n",queue[i-1][idx[i-1]].process_id);

				idx[i-1]++;
				queue[i][j].burst_time = -1;
			}
		}

		if(!active_process) {

			if(q >= QUANTA) { 
				last_q = q;
				break;
			}

			// iterate thorugh queues to find process to be assigned CPU
			int target_queue = -1;
			for(int i=0;i<4;i++) {
				for(int j=0;j<idx[i];j++) 
					if(queue[i][j].burst_time > 0.0) { // if burst_time <= 0.0 then the process has already completed
						target_queue = i;
						break;
					}
				if(target_queue != -1) 
					break;
			}
			if(target_queue == -1) {
				printf("No jobs to process at %d\n",q);
				continue;
			}
			int active_process_index = 0;
			while(active_process_index < idx[target_queue] && queue[target_queue][active_process_index].burst_time <= 0) {
				active_process_index++;
			}
			active_process = &(queue[target_queue][active_process_index]);
		} 

		if(first_served[active_process->process_id] == -1) 
			first_served[active_process->process_id] = q;
		last_served[active_process->process_id] = q;

		if(active_process->burst_time < 1.0) {
			printf("T %d: %d(%f,Priority: %d)   (CPU idle for %f quantum)\n",q,active_process->process_id,active_process->burst_time,active_process->priority,(1.0-(active_process->burst_time)));
		} else {
			printf("T %d: %d(%f,Priority: %d)\n",q,active_process->process_id,active_process->burst_time,active_process->priority);
		}

		active_process->burst_time -= 1.0;
		active_process->age = 0; // Process just serviced, reset age.
		if(active_process->burst_time <= 0) {
			done[active_process->process_id] = 1;
			active_process = NULL;
		}
    }

    print_statistics(ptr,first_served,last_served,done);
    return 0;
}

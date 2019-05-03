#include <signal.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "plantilla.c"


#define DEBUG 0
#define MAX PIPE_BUF
#define MAX_BUFFER_SIZE MAX
#define MAX_BUFFER_SIZE_INT MAX / sizeof(int)
#define MAX_VECTOR_SIZE_INT (MAX / (2 * sizeof(int))) - 1


FILE *data_file;
char *data_file_name;

int fd[2];
int producer_pid, consumer_pid;

int buffer_size = 0;

unsigned int sum_passangers = 0;
unsigned int sum_time = 0;
unsigned int sum_passenger_count = 0;

int bytes_written;
int bytes_read;


void productor() {
    if (consumer_pid != 0) {
        while (buffer_size < MAX_BUFFER_SIZE) {
            

            // Init of the data structure and 
            // allocating memory for the max size
            Data data;
            data.passenger_count   = malloc(sizeof(int) * MAX_VECTOR_SIZE_INT);
            data.trip_time_in_secs = malloc(sizeof(int) * MAX_VECTOR_SIZE_INT); 


            // The size of the data (in ints)
            int data_size  = get_data(&data, data_file, MAX_VECTOR_SIZE_INT);

            // The size of the block (in bytes)         
            int block_size = (1 + 2 * data_size) * sizeof(int);


            // Add the block size to the
            // buffer size counter
            buffer_size += block_size;


            // The block array
            int *block = malloc(block_size);

            if (DEBUG) {
                fprintf(stdout, "P: Writing %d bytes (%d ints) to fd[1]\n\n", block_size, 2 * data_size + 1);
                fprintf(stdout, "P: %d data points\n", block[0]);
            }

            // The first element of the block
            // is the size of the data (in ints)
            block[0] = data_size;


            // The next 2 * data_size elements
            // are the data tuples
            for (int i = 0; i < data_size; ++i) {
                block[1 + (2 * i)]      = data.passenger_count[i];
                block[1 + (2 * i) + 1]  = data.trip_time_in_secs[i];
            }


            // We write the full data block 
            // to the pipe, free the local
            // memory, and send a signal
            // to the costumer.
            bytes_written = write(fd[1], block, block_size);

            if (bytes_written == -1) {
                fprintf(stderr, "ERROR: Could not wrtie to pipe.");
                exit(1);
            }

            free(data.passenger_count);
            free(data.trip_time_in_secs);
            free(block);
            
            kill(consumer_pid, SIGUSR2);
        }
    }
}


void consumer() {
    while (buffer_size > 0) {
        int block_size_bytes;
        int data_size_bytes;
        int data_size;


        // Read the block size (in bytes),
        // init the local size variables,
        // and decrease the buffer size counter
        bytes_read = read(fd[0], &data_size, sizeof(int));
        
        if (bytes_read == -1) {
            fprintf(stderr, "ERROR: Could not read from pipe.\n");
            exit(1);
        }

        block_size_bytes = (2 * data_size + 1) * sizeof(int);
        data_size_bytes  = (2 * data_size) * sizeof(int);
        buffer_size     -= block_size_bytes;


        // Check if the producer has ended
        if (data_size == 0) {
            if (DEBUG)
                fprintf(stdout, "C: Finished.\n\n");

            fclose(data_file);

            // Give the wanted results,
            // and exit
            double passenger_avearge = (double) sum_passangers / (double) sum_passenger_count;
            double time_average      = (double) sum_time / (double) sum_passenger_count;

            fprintf(stdout, "Average passengers: %8.4f\n", passenger_avearge);
            fprintf(stdout, "Average time:       %8.4f\n", time_average);

            exit(0);
        }

        if (DEBUG)
            printf("C: The recieved block size is %d bytes (%d ints)\n", block_size_bytes, 2 * data_size + 1);


        // Allocate memory for the data block
        // and read it from the pipe
        int *block = malloc(data_size_bytes);
        bytes_read = read(fd[0], block, data_size_bytes);

        if (bytes_read == -1) {
            fprintf(stderr, "ERROR: Could not read from pipe.\n");
            exit(1);
        }

        // Make the pertinent 
        // calculations
        for (int i = 0; i < data_size; ++i) {
            sum_passangers += block[(2 * i)];
            sum_time += block[(2 * i) + 1];
            ++sum_passenger_count;
        }


        // Free the data block and
        // send a signal to the producer. 
        free(block);
        kill(producer_pid, SIGUSR1);
    }
}


int main(int argc, char *argv[]) {
    // Check correct number of
    // arguments
    if(argc != 2) {
        fprintf(stdout, "Usage:\n%s <file>\n", argv[0]);
        exit(1);
    }
    

    // Init the data file related
    // structures
    data_file_name = argv[1];
    data_file = fopen(data_file_name, "r");
    
    if (!data_file) {
        fprintf(stderr, "ERROR: Could not open '%s'.\n", data_file_name);
        exit(1);
    }


    // Init the handlers for the 
    // signals SIGUSR1 and SIGUSR2,
    // and the pipe
    signal(SIGUSR1, productor);
    signal(SIGUSR2, consumer);
    int pipe_return = pipe(fd);

    if (pipe_return == -1) {
        fprintf(stderr, "ERROR: Could not create pipe.");
        exit(1);
    }

    if (fork() != 0) {
        // Productor
        producer_pid = getpid();

        bytes_written = write(fd[1], &producer_pid, sizeof(int));

        if (bytes_written == -1) {
            fprintf(stderr, "ERROR: Could not write from pipe.\n");
            exit(1);
        }

        wait(NULL);
    } else {
        // Consumer
        consumer_pid = getpid();

        bytes_read = read(fd[0], &producer_pid, sizeof(int));
        
        if (bytes_read == -1) {
            fprintf(stderr, "ERROR: Could not read from pipe.\n");
            exit(1);
        }
        
        raise(SIGUSR1);
    }

    fclose(data_file);

    return 0;
}

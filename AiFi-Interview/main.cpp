// Robin Kalia
// robinkalia@berkeley.edu
//
// Full Stack Software Engineer Interview
// AiFi
//
// main.cpp: main function for instantiating AiFiMessager's streaming messages and sync message operations

#include "AiFiMessager.h"

#include <unistd.h>

bool Logger::DEBUG_FLAG_ = false;
bool Logger::WARN_FLAG_  = false;

void execute(int64_t testDuration, int64_t window, int64_t numSources, int64_t messageGenerationInterval, int64_t syncMessageOutputInterval, Logger& log) {
    AiFiMessager messager(window, numSources, messageGenerationInterval, syncMessageOutputInterval);

    try {
        log.info("Starting the AiFi Messager");
        log.info("The program will run for " + std::to_string(testDuration) + " seconds\n");
        messager.start();

        // Let this thread sleep for the time that we would like to see the operations
        // for streaming message and generating sync messages
        std::this_thread::sleep_for(std::chrono::seconds(testDuration));

        log.info("Terminating the 2 streaming message and sync-message generating threads");
        log.info("AiFi Messager program is ending. Goodbye!!!");
        messager.end();
    } catch (const std::exception& ex) {
        log.info("Caught Exception: Error |===> " + std::string(ex.what()));
    }
}


int32_t main (int32_t argc, char* argv[]) {
    // Command Line Arguments
    int64_t testDuration = 300;                 // Default 5 minutes/300 seconds for running the program
    int64_t window = 5;                         // Window size = 5 seconds
    int64_t messageGenerationInterval = 1;      // Message Generation Interval = 1 second
    int64_t syncMessageOutputInterval = 10;     // Interval between outputting syncMessage = 10 seconds
    int64_t numSources = 10;                    // Number of Sources = 10
    char *test_duration=nullptr, *window_size=nullptr, *message_generation_interval=nullptr, *sync_message_output_interval=nullptr, *num_sources=nullptr;
    std::string usage =
    "\n\n    Usage: ./AiFiMessager [-dh] [-t test_duration] [-w window_size] [-m message_generation_interval] [-s sync_message_output_interval] [-n num_sources] \n \
    [-d]: Debug Mode \n \
    [-h]: Help \n \
    [-m message_generation_interval]: Interval at which you want to generate the message stream. < Default: 1 second > \n \
    [-s sync_message_output_interval]: Interval at which you want to see the sync message output that will only display the timestamp and source of the sync messages. < Default: 10 seconds > \n \
    [-t test_duration]: Duration for which the program will run. < Default: 300 seconds > \n \
    [-w window_size]  : Size of the window over which you want to get the sync messages. Total Size: 2w -> [t-w,t+w] where t is the timestamp. < Default: 5 seconds >";

    int c;
    opterr = 0;
    Logger log;

    while ((c = getopt (argc, argv, "dht:w:m:n:s:")) != -1)
        switch (c)
        {
        case 'h':
            log.info(usage);
            return 0;
        case 'd':
            Logger::DEBUG_FLAG_ = true;
            break;
        case 't':
            test_duration = optarg;
            testDuration = std::stoi(test_duration);
            break;
        case 'w':
            window_size = optarg;
            window = std::stoi(window_size);
            break;
        case 'm':
            message_generation_interval = optarg;
            messageGenerationInterval = std::stoi(message_generation_interval);
            break;
        case 's':
            sync_message_output_interval = optarg;
            syncMessageOutputInterval = std::stoi(sync_message_output_interval);
            break;
        case 'n':
            num_sources = optarg;
            numSources = std::stoi(num_sources);
            break;
        case '?':
            log.error(usage);
            if ((optopt == 'd') || (optopt == 't') || (optopt == 'w') || (optopt == 'm') || (optopt == 'n') || (optopt == 's'))
                log.error("Option -" + std::to_string(optopt) + " requires an argument");
            else if (isprint (optopt))
                log.error("Unknown option '" + std::to_string(optopt) + "'");
            else
                log.error("Unknown option character '" + std::to_string(optopt) + "'");
            return 1;
        default:
            abort ();
        }

    for (int32_t index = optind; index < argc; index++)
        log.error("Non-option argument %s\n" + std::string(argv[index]));

    execute(testDuration, window, numSources, messageGenerationInterval, syncMessageOutputInterval, log);

    return 0;
}
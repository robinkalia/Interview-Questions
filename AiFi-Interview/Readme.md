This document contains the complete details regarding the behavior of the program and the way to run it.

========================================

Problem Statement::

Full Stack Engineer Written Exercise
Given an incoming stream of messages (defined below), generated from N different sources, your task is to implement a program that outputs the messages in a synchronized fashion. This is, the program needs to create new messages containing at most one message from each of the N sources in a given time-window (d-t, d+t) where t is the timestamp of a message and d is a delta setting the size of the window. For the sake of simplicity you can assume that a message has the following form:

```
message {
    timestamp float;
    body []byte;
    source int; # From 0 to N-1, specifies the source of the message
}

synched_message {
    timestamp []float;
    messages []message;
}
```

You can assume also that all the N sources are synchronized by the same network clock.

Deliverables
You can implement the program in any language of your choice. You should implement a program that streams the `messages` and the "synchronizer" creates and outputs `synched_messages`.

What are the caveats of your particular implementation? Assuming an incoming message rate, what is the worse case and best case scenario for your implementation?

Tests and/or visualization of the behaviour of the program would be a nice extra.

Please back up all your claims and guide us through your thought process by writing meaningful comments in your code.

========================================

Here is the Complete solution:-

1) Running the Program:

$ make all

This will generate the following executable: aifi
Along with the executable the following object files will be generated: Streamer.o, Synchronizer.o, AiFiMessager.o, main.o

To get idea about the command line arguments: $ ./aifi -h
For example:
Tue Apr  3 00:55:14 2018:: Usage: ./AiFiMessager [-dh] [-t test_duration] [-w window_size] [-m message_generation_interval] [-s sync_message_output_interval] [-n num_sources]
[-d]: Debug Mode
[-t test_duration]: Duration for which the program will run. < Default Value: 300 seconds >
[-w window_size]  : Size of the window over which you want to get the sync messages. Total Size: 2w -> [t-w,t+w] where t is the timestamp. < Default: 5 seconds >
[-m message_generation_interval]: Interval at which you want to generate the message stream. < Default value: 1 second >
[-s sync_message_output_interval]: Interval at which you want to see the sync message output that will only display the timestamp and source of the sync messages. < Default Value: 10 seconds >
[-n num_sources]: Number of sources. < Default Value: 10 >

PS: Instead of float as mentioned in the assignment I have made timestamp as int64_t for milliseconds [since epoch].

The program consists of 2 components: Generating the messages and Displaying the sync messages

In the default mode, you can only see the sync message every interval. In the debug mode, you will also see the messages that are continuously being generated every specific interval.
For example:
$ ./aifi -d
Tue Apr  3 00:27:15 2018:: Starting the AiFi Messager
Tue Apr  3 00:27:15 2018:: The program will run for 20 seconds

Tue Apr  3 00:27:16 2018:: Generated Message
Timestamp: 1522740436739
Source: 2
Body(Len=76): "0&,.#>#4%1<?27&.?87>."

Tue Apr  3 00:27:17 2018:: Generated Message
Timestamp: 1522740437740
Source: 0
Body(Len=38): "3))$)+<1+36"

Tue Apr  3 00:27:18 2018:: Generated Message
Timestamp: 1522740438740
Source: 7
Body(Len=256): "+4(@;:+*.<3=A#.<8#A#"=+75>&"+0')65(A";A!8;)>,)@9--/<.-&/$;59.3"+(.'1(?1"

Tue Apr  3 00:27:19 2018:: Generated Message
Timestamp: 1522740439744
Source: 8
Body(Len=221): "0272-#02<!3?2>(2##")=5?!<@-@A<@,9*''1;)1381#6(<A,3462"=7%"

Tue Apr  3 00:27:20 2018:: Sync Message:
Timestamps = [  1522740437740  1522740438740  1522740439744  ]
Sources = [  0  7  8  ]

In normal mode, you will only see debug messages.

./aifi -t 20
Tue Apr  3 00:53:48 2018:: Starting the AiFi Messager
Tue Apr  3 00:53:48 2018:: The program will run for 20 seconds

Tue Apr  3 00:54:08 2018:: Sync Message:
Timestamps = [  1522742044008  1522742045008  1522742046012  1522742048021  ]
Sources = [  7  4  5  8  ]

Tue Apr  3 00:54:18 2018:: Terminating the 2 streaming message and sync-message generating threads
Tue Apr  3 00:54:18 2018:: AiFi Messager program is ending. Goodbye!!!

You can find complete examples here: https://gist.github.com/robinkalia/2d0ac184d9bb2b2fdcef5f2090c98136



2) Program Details:

Here is an explanation of what I have done.

a) When the program starts, I spawn 2 additional threads, one for generating a message stream and other thread for displaying the sync message at a specific timestamp within a window, as in [t-w,t+w], where the messages inside sync message correspond to a single message per source for all specific sources generating messages within the time interval.

b) I use a thread safe message map that is shared by these 2 threads. The message stream generator thread [Think of it as a Producer] keeps on adding messages to message app every specific interval (default = 1 second). The other sync message generator thread reads [Think of it as a Consumer] this message map to generate a message stream every specific interval (default = 10 seconds). Since these 2 threads access messageMap simultaneously, I have made the message map thread-safe.



3) Discussion:

As per the doc I was asked these questions.

Q: What are the caveats of your particular implementation? Assuming an incoming message rate, what is the worse case and best case scenario for your implementation?

Ans. Given a timeline of 4-5 hours in which I had to solve this problem, my solution requires quite a lot of improvements.

a) Given the time scarcity, I could not write unit tests. I generally do Test Driven Development in my general work but given the time crunch, I had to pass out on unit tests.
b) I have tested my program for only 1 message stream generator thread (producer), but in reality there could be 10 such threads populating the message map. I need better stress testing of my producer threads to see, how the sync message generator performs.
c) I have tested my program for only 1 sync message generator thread (consumer), but in reality there could be 4 such threads for reading the message map that is being populated by 10 message stream generator (producer) threads at the same time. I need better stress testing of my stream message producer and message map consuming sync message threads to see, how the performance gets degraded in case of any potential readers(/consumers) or writers(/producers) starvation.
d) Since I don't have unit tests, I might have missed out on subtle and hidden bugs in my code.

At an incoming message rate of lets say 60 messages per second, here are the best and worst case scenarios.

Best Case Scenario: The sync message generation rate is a small fraction of the incoming message rate -> We can properly produce the sync messages without any bizarre results.
Worst Case Scenario:
a) Very high incoming message rate can result in memory leak or heap memory exhaustion eventually, so the program cannot run infinitely. It needs a mechanism for flusing out messages that are old and make sure that sync message generator does not keep attempt to get old messages from message map.
b) Sync Message generation rate is close or same or greater than incoming message generation rate. This will give really abrupt and useless results, since most of the generated sync messages will be frequent and quite often contain 1 element or empty or infact same and that case will not give any further informarion.

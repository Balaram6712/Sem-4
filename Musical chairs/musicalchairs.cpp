/*
 * Program: Musical chairs game with n players and m intervals.
 * Author:  Sai Balaram Korrapati, Krishna Pawan
 * Roll# :  ES18BTECH11011, CS18BTECH11008
 */
#include <stdlib.h>  /* for exit, atoi */
#include <iostream>  /* for fprintf */
#include <errno.h>   /* for error code eg. E2BIG */
#include <getopt.h>  /* for getopt */
#include <assert.h>  /* for assert */
#include <chrono>	/* for timers */
#include <condition_variable>
#include <mutex>
#include <vector>
#include <string.h>
#include <thread>
#include <fstream>
#define MAX 100000
/*
 * Forward declarations
 */
void usage(int argc, char *argv[]);
unsigned long long musical_chairs(int nplayers);

using namespace std;
 	//number of chairs
int lap = 0;	//number of laps
int count = 0;	//count of the chairs occupied
int chairs = 0;

int sit = 0;	//bools
int start = 0;
mutex player_lock;
mutex umpire_lock;

mutex sleep_lock_player;

condition_variable w1;
condition_variable w2;

int player_sleep_time[MAX] = {0};

int main(int argc, char *argv[])
{
    int c;
	int nplayers = 0;

    /* Loop through each option (and its's arguments) and populate variables */
    while (1) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"help",            no_argument,        0, 'h'},
            {"nplayers",         required_argument,    0, '1'},
            {0,        0,            0,  0 }
        };

        c = getopt_long(argc, argv, "h1:", long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
        case 0:
            cerr << "option " << long_options[option_index].name;
            if (optarg)
                cerr << " with arg " << optarg << endl;
            break;

        case '1':
            nplayers = atoi(optarg);
            break;

        case 'h':
        case '?':
            usage(argc, argv);

        default:
            cerr << "?? getopt returned character code 0%o ??n" << c << endl;
            usage(argc, argv);
        }
    }

    if (optind != argc) {
        cerr << "Unexpected arguments.\n";
        usage(argc, argv);
    }


	if (nplayers == 0) {
		cerr << "Invalid nplayers argument." << endl;
		return EXIT_FAILURE;
	}

    unsigned long long game_time;
	game_time = musical_chairs(nplayers);

    cout << "Time taken for the game: " << game_time << " us" << endl;

    exit(EXIT_SUCCESS);
}
/*
 * Show usage of the program
 */
void usage(int argc, char *argv[])
{
    cerr << "Usage:\n";
    cerr << argv[0] << "--nplayers <n>" << endl;
    exit(EXIT_FAILURE);
}

void umpire_main(int nplayers)
{
	string input;
	while(lap < nplayers)
	{
		
    	if(cin >> input)
    	{

        //cout << "input " << input << endl;

    	 if(input == "lap_start")
    	{
			count = 0;
			sit = 0;
    		
    	}
    	else if(input == "music_start")
    	{
    		start = 1;
    		w1.notify_all();
    	}	

    	else if(input== "umpire_sleep")
    	{
    		int ump_sleep;
    		cin >> ump_sleep;
    		this_thread::sleep_for(chrono::microseconds(ump_sleep));
    	}//umpire sleep
		
		else if(input == "player_sleep")
    	{
    		int id;
    		int sleep_time;
    		cin >> id;
    		cin >> sleep_time;
    		//unique_lock<mutex> pslck(sleep_lock_player);
    		player_sleep_time[id] = sleep_time;	//shared array
    		//pslck.unlock();
    	}//player sleep
		
		else if(input == "music_stop")
    	{
    		unique_lock<mutex> lck1(umpire_lock);
    		sit = 1;
    		w2.wait(lck1);
       	}
		
		else if(input == "lap_stop")
    	{
    		lap = lap + 1;
    		chairs = chairs - 1;
    		start = 0;
    		//cout << "lap " << lap << endl;
    		//cout << "chairs " << chairs << endl;
    		if(lap == nplayers-1)
    		{
    			w1.notify_one();
    		}//last lap last thread get chair and print and exits
    		
    	}	
       }

       else
       	break;
	}
    /* Add your code here */
	/* read stdin only from umpire */
	return;
}

void player_main(int plid)
{
	while(1)
	{

		 

		if(start)
		{
		if(player_sleep_time[plid] != 0)
		{
			this_thread::sleep_for(chrono::microseconds(player_sleep_time[plid]));
			player_sleep_time[plid] = 0;
		}
	    

        if(sit)
		{	
			unique_lock<mutex> plck(player_lock);
			count = count + 1;
			if(count > chairs )
			{
				cout << "======= lap# "<< lap + 1 << " ======="<<endl;
				cout << plid << " could not get chair" << endl;
				cout << "**********************" << endl;
				plck.unlock();
				w2.notify_one();
				break;
			} 
			w1.wait(plck);
		}
	    }

	    if(chairs == 0)
		{
			cout << "Winner is " << plid << endl;
			break;	
		}

		
	}
    /* Add your code here */
	/* synchronize stdouts coming from multiple players */
	return;
}

unsigned long long musical_chairs(int nplayers)
{
	auto t1 = chrono::steady_clock::now();//total time claculation
	// Spawn umpire thread.
    chairs = nplayers -1;
    thread ump(umpire_main,nplayers);
    thread players[nplayers];
    cout<<"Musical Chairs: "<<nplayers<<" player game with "<<nplayers-1<<" laps."<<endl;
  //  cout << "Musical Chairs: "<< nplayers << " player game with "<< nplayers-1 << " laps." << endl;
    for(int i=0;i<nplayers;i++)
    {	
    	players[i] = thread(player_main,i);//player thread
    }
    for(int i=0;i<nplayers;i++)
    {
   		players[i].join();	//joining threads
    } 
	ump.join();
    auto t2 = chrono::steady_clock::now();
    /* Add your code here */
	// Spawn n player threads.
    /* Add your code here */
	auto d1 = chrono::duration_cast<chrono::microseconds>(t2 - t1);
	return d1.count();
}
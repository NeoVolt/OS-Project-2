## OS-Project-2

To get the program to run, type ```make run FILE=<file_name>``` into the console. With the default file provided, ```make run FILE=input_1.txt``` will run banker's algorithm on that file. The first row of the file is the row for the current available system resources, and then every row afterwards is for a process, with the first set of comma separated values being for the maximum resources said process can use, and the second set being for the resources currently allocated to it. 

Example of the program running is provided in ```example.png```. This was ran on the Kent linux servers. 

Every method should be pretty self-explanatory in the code, I left a few comments here and there but it's fairly easy to tell what's going on. 

With the way I coded everything, it should be hypothetically possible to do processes with more than 3 resources, or to add/remove additional processes, as long as the number of resources is consistent between everything. That was beyond the scope of this project though, so I never tested it. 
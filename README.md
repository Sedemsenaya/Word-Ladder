Project 1 -- Word Ladder - Statement of the problem
Due Sep 1, 2023 by 11pm Points 70 Submitting a file upload File Types zip Available until Sep 1, 2023 at 11pm
This assignment was locked Sep 1, 2023 at 11pm.
Two words are neighbors if they differ by exactly one letter. Here is a few examples of words that are neighbors.

cold  cord
warm  worm
hand  band
By this definition, two words can only be neighbors if they have the same number of letters.

In this assignment, we'll use the word dictionary to mean a list of words. This has nothing to do with the dictionary data structure in some programming languages.

We can use a graph to represent the neighbor relation among the words in a dictionary as depicted below.

neighborGraph.png

We expect you to have been introduced to graph theory in your prerequisite discrete math class (SSU's CS 242 or the equivalent), but we will remind you of some common terms in graph theory and how they relate to this particular graph:

The graph has a line (an edge) between each pair of neighbor words (nodes).
A word may have zero or more neighbors. The word slow has no neighbors, fake has four neighbors, and cell has one neighbor.
The neighbor relation partitions the dictionary into several connected components. All of the words in a given connected component are mutually reachable by traveling along the graph edges. Words outside that component cannot reach any of the words inside it. In the above example, the dictionary has three connected components.
You can use the graph to determine if there is a path between two given words or not. For example, there is a path between words ball and cell (ball - bell - cell.) The path starts with ball and ends at cell. On the other hand, there is no path between words bell and made. This is because each of these two words belongs to a different connected component.
A path between two words is called a ladder. Each consecutive pair of words in a ladder differ by exactly one letter. For example, here is a ladder between the words made and rate:

made
fade
fake
fate
rate
Here is another one between the same pair of words:

made
fade
fake
fate
kate
rate
Can you find other ladders between these two words?

Project Statement
For this assignment, you will write a C++ program that reads a dictionary of words and determines whether there is a ladder between pairs of words. If a ladder for a pair of words exists, your program finds and prints it. As we discussed above, there may be multiple ladders between two words. Your program may print any one of them. If no ladder exists between a pair of words, your program will report that.

Input/Output
The command-line input to your program will be the names of two files. One contains the dictionary, one word per line, and the other contains a number of lines, each of which contains a pair of words. For each pair of words, your program either prints a ladder between them, if one exists, or it prints a message indicating the absence of one.

For example, let suppose the dictionary contains the following words.

fake
lake
tate
kate
cell
ball
bate
made
rate
fade
bell
fate
wall
slow
and the second file contains the following pair of words.

fate kate
cell fate
lake bate
wall cell
Then, your program would print the following output

A ladder for the pair fate and kate is:
fate
kate

No ladder for the pair cell and fate exists.
A ladder for the pair lake and bate is:
lake
fake
fate
rate
kate
tate
bate

A ladder for the pair wall and cell is:
wall
ball
bell
cell
Again, any one of the multiple ladders between between words lake and bate is an acceptable answer.

The dictionary file will contain a collection of 4-letter words, one per line. The start-target file will have a number of lines, each of which would contain a 4-letter word followed by one space, followed by a second 4-letter word.

If you use CLion to develop your application, you should use Run->Edit Configuration and make it so that your program takes the names of the two input files as arguments. The first argument should be the name of the file that contains the dictionary and the second argument should be the name of the input file that contains pairs of words, just as depicted in the previous example.

Where to start
Start with this partial solution Download Start with this partial solution. It include the definition of data type Dictionary, whose constructor accepts the name of the input file as an argument. Here are a few steps...

Unzip this file, open it with CLion, and run it (you will learn how to do that in the lab.) This is a partial solution, so the output is will be minimal. Take a note of how arguments are passed to the application and received in the main function. 
main.cpp should open both input files (the dictionary and the file that contains the start-end pairs) to make sure that they exist. The main function in the CLion project that you have downloaded demonstrate how to open and input file and what to do in case the file doesn't exist. 
Finish function readStartTargetWords in main.cpp. It is intended to open the start-target file, read and store each pair of start-target words in an instance of "std::pair", add each pair to a vector, and return the vector. In the solution that I have provided, this function opens the input file but it doesn't read from it. That is left for you to do. The code in that function also demonstrates how to create tuples and add them to a vector. The idea here is that you make sure that you are able to identify each of the start and target words and to detect the end-of-file when all the input pairs have been read. The main function calls readStartTargetWords and stores the vector that it returns. main.cpp already includes the code to print the contents of the vector that readStartTargetWords returns.
Write the necessary code to read the dictionary input file and store it in array "words" in Dictionary.cpp and write the code for "printDictionary()" to print the words to the standard output. Test "printDictionary()"  before you continue. By the way, this function is only for testing your code that reads and stores the dictionary. It is not used when you attempt to find a ladder between two words. Also, in order to test this function, can comment out other the functions that you haven't implemented in Dictionary. On the other hand, if you only call functions that you have implemented, your code should compile and run. 
Write Dictionary functions size, member, positionalDiff, and idxOfSuccessorWordFrom. Test each one of them before you go on to the next to make sure that they work.
Write the pathFromTo of Dictionary. In the next section, under A Backtracking Algorithm, provides some insight into how to write this function. If there is a path between the start and the target words, This function finds it and returns the words on the path in a vector. If there is no path, it just returns an empty vector.
A few notes...

It is not a good idea to have the constructor of a class to open a file for input as the file might not exist. If that is the case, then the class can not be initialized. Therefore, in the main function, before we create an instance of this class, I have made sure that the input file exists by opening it first. If the file opens with no errors, then I close it and create an instance of Dictionary with the file name as an argument to its constructor.
We could have broken up Dictionary into two classes, one that strictly maintains the dictionary and one that finds paths between the start and target words. If you were to do that, which functions would you keep in Dictionary and which ones would you move to the second class?
A Backtracking Algorithm
Let's try to find a path between the start word, "lake" and the target word, "bate". To do so, we first find "lake", the start word, in the dictionary at index 1 and push it on the stack. Then, we search for a successor for it in the dictionary by starting from the first word (index 0) in the dictionary and once we find it, we push it on the stack. It so happens that "fake", the first word in the dictionary, is a successor to "lake". Once we push it on the stack, the stack would contain:

lake, 1
fake, 0
We search for a successor for "lake" next. It happens to be "fade" at index 9. We push that on the stack. The stack now will contain:

lake, 1
fake, 0
fade, 9
So far, we have a ladder from "lake" to "fade". We will have to continue until we find the target word and push that on the stack. To find a successor for "fade", we, just as always, start with the first word in the dictionary, trying to find a word that differs from "fade" only in one letter. "fake" happens to fulfill that requirement. However, "fake" is already on the stack and if we were to push it again on the stack, we will fall into an infinite loop. Therefore, as we try to find a successor for the last word that we add to the stack, we will have to avoid words that are already on the stack. 

There are different ways that we can avoid falling into an infinite loop of this type. One way is to have a Boolean array that parallels the dictionary (we called this array "used" in the definition of Dictionary and we will use this word in this discussion as well.) Whenever we add a word from dictionary to the stack, we set the element in "used" that corresponds to it to truth value, True. 

Initially, all elements of "used" will be set to False. Given the three words that we have on the stack, by this point, we have to have set elements 1, 0, and 9 of "used" to True. Therefore, when we try to find a successor for "fade", we will not choose "lake" as its "used" element is set to True.

In general, we start to find a successor for the last word that we push on the stack from the beginning of dictionary, avoiding those whose "used" elements are True. We end up with two cases:

We find a success for the top element of the stack. In this case, we push the successor word and its index in the dictionary to the stack.
We do not find a successor for the top element of the stack in the dictionary. (This will happen for example if you continue to find a successor for "fade". The successor is "made" at index 7 of the dictionary. Now, there is no successor for "made" in the dictionary.) When that happens, you will have to backtrack. That is, you will have to discard the last word on the stack and try to find a different successor, if one exists, for the word that is now on top of the stack. 
If at any point, the stack becomes empty, that means there is not path between the start and the target words. 

In this discussion, I have mentioned that you find a successor for a word by starting from index 0 of the dictionary. However, if you backtrack, you shouldn't start from index zero to find a successor for the word that is now at the top of the stack. Instead, you should use the index of the element that you popped from the stack. Can you figure out why?

What to turn in
Make sure that your solution compiles and runs on blue.cs. You will lose a significant number of points if your solution doesn't work on blue.cs even when it works on your computer.

You should read the sections of the course syllabus entitled Programming Projects and Policy on Collaboration.

Zip the directory (folder) that contains all your files, including the input files, and upload it via Canvas. Make sure to include the requirement README file as specified in the course syllabus in the Programming Projects section.

How do we test your submission
Suppose that the name of the zip file that you have submitted is MySolution.zip and that it is the zip of a folder called MySolution. We run the following command in a shell window where we have stored your MySolution.zip.

unzip MySolution.zip
cd MySolution
g++ -std=c++20 *.cpp -o ladder.x
./ladder.x nameOfDictionaryFile nameOfStartTargetFile
A few notes...

You should include the input files that you used to test your solution in the directory that you submit even though we will use our own input files.
The command that we use assumes that all .cpp files are part of your solution. Make sure that the directory that you submit only contains .cpp and .hpp files that you have used in your solution.
In the statement of this project, we provided a sample dictionary and a list of star- target-words. The output of your solution should be identical to what we have provided for those input files.
Please make sure that you are able to run your program as above on blue.cs before you submit your solution. 
 


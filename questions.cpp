//Author: Fangshan
#include <iostream>
#include "simpio.h"
using namespace std;

void skip(istream& input, string& line);

bool playQuestionGame(istream& input) {
    bool result = true;
    string line;
    getline(input, line);
    
    if (line[0] == 'Q') {
        string question = line.substr(2);
        bool ans = getYesOrNo(question);
        if (ans) {
            result = playQuestionGame(input);  //if yes, simply go on to the next question/answer
        } else {
            string str = line;
            getline(input, str);
            skip(input, str);                 //if no, skip until the last line of yes child is reached
            result = playQuestionGame(input);
        }

    } else {
        string answer = line.substr(2);
        answer += "?";
        string p = "Are you thinking of: ";
        p += answer;
        result = getYesOrNo(p);
        if (result) {
            cout << "Hooray, I win!" << endl;
        } else {
            cout << "Drat, I lost." << endl;
        }
        return result;
    }
    return result;
}

/* Help skip an entire body of contents:
 * 1. A question: skip the yes child of the question, and then the no child;
 * 2. An answer : simply stay on this line.
 * After skipping:
 * reach the last line of the body
 */
void skip(istream& input, string& line) {
    if (line[0] == 'Q') {         //A question: skip the question

        //YES
        getline(input, line);
        //do something for the yes child
        if (line[0] == 'Q') {
            skip(input, line);
        } /* else {
        do_nothing();
        } */

        getline(input, line);  //jump to no child

        //NO
        //do exactly the same thing!
        skip(input, line);

    } /* else {                   //An answer: simply stay on the line
        do_nothing();
    } */
}

/*
This is the skip function with comments removed.
void skip(istream& input, string& line) {
    if (line[0] == 'Q') {
        getline(input, line);
        if (line[0] == 'Q') {
            skip(input, line);
        }
        getline(input, line);
        skip(input, line);
    }
}
*/

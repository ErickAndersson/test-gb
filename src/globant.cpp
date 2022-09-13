/* 
* * * * * * * * * * * * * * * * * * * * * * * *
* Resolución de problema de pasantía Globant. *
* * * * * * * * * * * * * * * * * * * * * * * *
* * * * * * * Erick Andersson * * * * * * * * *
* * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <string>
#include <list>
#include "TEPConfig.h"

using namespace std;

void fill(string & output, string cl, string lastPrefix){
    if(lastPrefix != ""){
        output.append(lastPrefix + "." + cl);
    }
    else{
        output.append(cl);
    }
}

void parseJson(string input, string & output, int & it, string lastPrefix){
    string currentLine;
    string prefix;
    bool finished = false;
    it++;

    while(it < input.length() && !finished){
    switch(input[it]){
        case '}': //End path.
            if(it<input.length()){
                if(input[it+1] == ',' || input[it+1] == '}'){
                    currentLine.append("\n");
                }
            }
            if((currentLine!="") && (currentLine!="\n")){ //Only add relevant information
                fill(output, currentLine, lastPrefix);
                currentLine="";
            }
            finished = true; //Needed for stoping recursion
            break;
        case '"': //Start of possible prefix found
            prefix=""; //Reset it
            it++; //Advance
            while(input[it]!='"'){
                prefix.push_back(input[it]);
                it++;
            }
            if((input[it+1] == ':') && (input[it+2] == '{')){ //Both true for prefix of a nested loop
                it++; //Jump over the ':'
                if(lastPrefix!=""){
                    prefix = lastPrefix + "." + prefix; //For nested prefixes
                }
            }
            else{
                currentLine.append(prefix);
            }
            break;
        case '{': //Nested path
            parseJson(input, output, it, prefix);
            it--; //Going back and forward later
            break;
        case ':':
            currentLine.append("=");
            break;
        case ',':
            if((currentLine!="") && (currentLine!="\n")){ //Only add relevant information
                currentLine.append("\n");
                fill(output, currentLine, lastPrefix);
                currentLine="";
            }
            break;
        default:
            currentLine.push_back(input[it]);
            break;
    }
    it++;
    }
}

/*
Ejemplo enunciado:
{ 
    “a”: true, 
    “b”: { 
        “b1”: “hello”, 
        “b2”: 3.5 
        }, 
    “c”: 3
}

Test1:
{
    "a":{
        "b":{
            "c":1,
            "d":2,
            "e":3
        }
    },
    "g":1
}

Test2:
{
    "a":{
        "b":{
            "c":3
        }
    }
}

Test3:
{
    "a":{
        "c":1,
        "d":2,
        "e":3
    },
    "g":1
}

Test4:
{
    "a":true,
    "b":{
        "b1":"hola",
        "b2":{
            "d":"uwu"
        },
        "b3":27
    },
    "c":3
}

test5:
{ 
    “a”: true, 
    “b”: 3,
    “c”: { 
        “c1”: “hello”, 
        “c2”: 3.5 
        }
}

test6:
{
    "isbn": "123-456-222",  
    "author": 
    {
        "lastname": "Doe",
        "firstname": "Jane"
    },
    "editor": 
    {
        "lastname": "Smith",
        "firstname": "Jane"
    },
    "title": "The Ultimate Database Study Guide",  
    "category": "Technology"
}
*/

int main() {
    //Print of version number
    cout << "Version " << TEP_VERSION_MAJOR << "." << TEP_VERSION_MINOR << endl;
    cout << endl;

    //Input must be without spaces and on a single line.
    string enunciado = "{\"a\":true,\"b\":{\"b1\":\"hello\",\"b2\":3.5},\"c\":3}";
    string test1 = "{\"a\":{\"b\":{\"c\":1,\"d\":2,\"e\":3}},\"g\":1}";
    string test2 = "{\"a\":{\"b\":{\"c\":3}}}";
    string test3 = "{\"a\":{\"c\":1,\"d\":2,\"e\":3},\"g\":1}";
    string test4 = "{\"a\":true,\"b\":{\"b1\":\"hola\",\"b2\":{\"d\":\"uwu\"},\"b3\":27},\"c\":3}";
    string test5 = "{\"a\":true,\"b\":3,\"c\":{\"c1\":\"hello\",\"c2\":3.5}}";
    string test6 = "{\"isbn\":\"123-456-222\",\"author\":{\"lastname\":\"Doe\",\"fisrtname\":\"Jane\"},\"editor\":{\"lastname\":\"Smith\",\"fisrtname\":\"Jane\"},\"title\":\"The Ultimate Database Study Guide\",\"category\":\"Technology\"}";

    string output;
    string prefix;
    int it = 0;

    
    bool ok = true; 
    
    do
    {
        cout << "Select the test case you want to use (from 0 to 6)" << endl;
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 0:
            cout << "Input:" << endl; 
            cout << enunciado << endl;
            parseJson(enunciado, output, it, prefix);
            ok = true;
            break;
        case 1:
            cout << "Input:" << endl; 
            cout << test1 << endl;
            parseJson(test1, output, it, prefix);
            ok = true;
            break;
        case 2:
            cout << "Input:" << endl; 
            cout << test2 << endl;
            parseJson(test2, output, it, prefix);
            ok = true;
            break;
        case 3:
            cout << "Input:" << endl; 
            cout << test3 << endl;
            parseJson(test3, output, it, prefix);
            ok = true;
            break;
        case 4:
            cout << "Input:" << endl; 
            cout << test4 << endl;
            parseJson(test4, output, it, prefix);
            ok = true;
            break;
        case 5:
            cout << "Input:" << endl; 
            cout << test5 << endl;
            parseJson(test5, output, it, prefix);
            ok = true;
            break;
        case 6:
            cout << "Input:" << endl; 
            cout << test6 << endl;
            parseJson(test6, output, it, prefix);
            ok = true;
            break;    
        default:
            cout << "Incorrect choice, select again." << endl;
            ok = false;
            break;
        }
    } while (!ok);

    cout << "Output:" << endl;
    cout << output << endl;
    cin.get();
    
    return 0;
}
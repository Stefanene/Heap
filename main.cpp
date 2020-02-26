#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>

using namespace std;

int main() {
  //variables
  char input[10];
  ifstream file;
  int count = 0;  //number of chars
  int modif[100];
  for (int i = 0; i < 100; i++) {
    modif[i] = 0;
  }  //clear char* array
  //program
  cout << "=========================" << endl;
  cout << "Welcome to my Heap program." << endl;
  bool run = true;
  while (run) {
    cout << endl << "You can: heap, quit." << endl;
    cin.get(input, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    if (strcmp(input, "heap") == 0) {
      cout << "=========Entered========" << endl;
      cout << "How would you like to input? file or type:" << endl;
      cin.get(input, 10);
      cin.clear();
      cin.ignore(10000, '\n');
      if (strcmp(input, "file") == 0) {
	file.open("C:\\cygwin64\\home\\Stefan Ene\\Heap\\heap.txt");
	if (!file) {
	  cout << "Unable to open file heap.txt" << endl;
	  exit(1);   // call system to stop
	}
	//read from file

	file.close();  //close file
      }
      else if (strcmp(input, "type") == 0) {
	cout << "Enter numbers separated by space:" << endl;
	char in[100000];
	cin.get(in, 100000);
	cin.clear();
	cin.ignore(1000000, '\n');
	//parse input by spaces
	int l = 0;  //keeps track of # of chars before space
	for (int i = 0; i < strlen(in); i++) {
	  if (in[i] == ' ') {
	    if (l == 1) {
	      int temp = 0;
	      cout << in[i-1] -'0';
	      temp = in[i-1] - '0';
	      modif[count] = temp;
	      count++;
	      l = 0;
	    } else {
	      int temp = 0;
	      for (int a = 0; a < l; a++) {
		cout << in[i-l+a] - '0';
		temp = 10 * temp + (in[i-l+a] - '0');
	      }
	      modif[count] = temp;
	      count++;
	      l = 0;
	    }
	  } else {
	    int temp = 0;
	    l++;
	    if (i == strlen(in) - 1) {  //last possible pair of chars
	      for (int a = 0; a < l; a++) {
		cout << in[i+a+1-l] - '0';
		temp = 10 * temp + (in[i+a+1-l] - '0');
	      }
	      modif[count] = temp;
	      count++;
	    }
	  }
	}
      }
      cout << endl;
      for (int i = 0; i < count; i++) {
	cout << modif[i] << endl;
      }
      //create heap tree
      char** heap = new char*[count+1];  //it's a linear tree yoooo
      
    }
    else if (strcmp(input, "quit") == 0) {
      cout << endl << "Thank you for using my program!" << endl;
      cout << "=========================" << endl;
      run = false;
    }
    else {
      cout << endl << "Invalid input. Try again." << endl;
    }
  }
  return 0;
}

/*Heap by Stefan Ene
  This program creates a max heap tree using a typed or a file input
  Works Cited: reading in from a file from Omar Nassar
               C++ file references from http://www.fredosaurus.com/notes-cpp/io/readtextfile.html
 */

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

//functions
void parse(char* in, int* modif, int &count);
void buildHeap(int* modif, int* heap, int size);
int getMax(int* array);
void printHeap(int* heap, int size);
void deleteHeap(int* heap, int size);

int main() {
  //variables
  char inp[10];
  char fileName[30];
  char input[10000];
  int count = 0;  //number of chars
  int modif[100];
  for (int i = 0; i < 100; i++) {
    modif[i] = 0;  //clear int array
  }
  //program
  cout << "=========================" << endl;
  cout << "Welcome to my Heap program." << endl;
  bool run = true;
  while (run) {
    for (int c = 0; c < 100; c++) {
      modif[c] = 0; //clear array
    }
    count = 0;  //clear array size index
    cout << endl << "You can: heap, quit." << endl;
    cin.get(inp, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    if (strcmp(inp, "heap") == 0) {
      cout << "=========Entered========" << endl;
      cout << "How would you like to input? file or type:" << endl;
      cin.get(inp, 10);
      cin.clear();
      cin.ignore(10000, '\n');
      if (strcmp(inp, "file") == 0) {
	//Credit Omar Nassar for this chunk of code
	cout << endl << "What is the name of the file?" << endl << ">> ";
	cin.get(fileName, 30);
	cin.clear();
	cin.ignore(100000, '\n');
	streampos size;
	ifstream file(fileName, ios::in | ios::binary | ios::ate);
	if (file.is_open()) {
	  size = file.tellg();
	  file.seekg(0, ios::beg);
	  file.read(input, size);
	  file.close();
	  parse(input, modif, count);  //parse input to modif array
	  cout << "IN: ";
	  for (int i = 0; i < 100; i++) {
	    if (modif[i] == 0) break;
	    cout << modif[i] << " ";
	  }
	  cout << endl;
	}
      }
      else if (strcmp(inp, "type") == 0) {
	cout << "Enter numbers separated by space:" << endl;
	char in[100000];
	cin.get(in, 100000);
	cin.clear();
	cin.ignore(1000000, '\n');
	//parse input by spaces
	parse(in, modif, count);  //parse input to modif array
	cout << ">> IN: ";
	for (int i = 0; i < 100; i++) {
	  if (modif[i] == 0) break;
	  cout << modif[i] << " ";
	}
	cout << endl;      
      }
      else {
	cout << "Invalid input type. Try again." << endl;
      }
      //create heap tree
      int heap[101];  //it's a linear tree yoooo
      for (int c = 0; c < 101; c++) {
	heap[c] = 0;  //clear array
      }
      //get size of modif array
      int siz = 0;
      for (int i = 0; i < 100; i++) {
	if(modif[i] != 0) {
	  siz++;
	} else break;
      }
      buildHeap(modif, heap, siz);
      cout << "=======Heap=Built=======" << endl;
      for (int i = 1; i < 101; i++) {
	if (heap[i] == 0) break;
	cout << heap[i] << " ";
      }
      cout << endl;
      printHeap(heap, siz);
      cout << "=====Heap=Deletion======" << endl;
      deleteHeap(heap, siz);
    }
    else if (strcmp(inp, "quit") == 0) {
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

void parse(char* in, int* modif, int &count) {
  int l = 0;  //keeps track of # of chars before space
  for (int i = 0; i < strlen(in); i++) {
    if (in[i] == ' ') {
      if (l == 1) {
	int temp = 0;
	temp = in[i-1] - '0';
	modif[count] = temp;
	count++;
	l = 0;
      } else {
	int temp = 0;
	for (int a = 0; a < l; a++) {
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
	  temp = 10 * temp + (in[i+a+1-l] - '0');
	}
	modif[count] = temp;
	count++;
      }
    }
  } 
}

void buildHeap(int* modif, int* heap, int size) {
  int curr = 1;
  //set index at 1 to largest int
  heap[1] = modif[getMax(modif)];  //largest set at index 1
  modif[getMax(modif)] = 0;
  while(curr <= size) {
    //check if out of nums
    if(heap[2*curr] == 0) {  //if right child is empty
      //fill right child with next max int
      heap[2*curr] = modif[getMax(modif)];
      modif[getMax(modif)] = 0;
      //now fill left chile with next
      heap[2*curr+1] = modif[getMax(modif)];
      modif[getMax(modif)] = 0;
    } else {  //if right child filled
      //fill left child with next max int
      heap[2*curr+1] = modif[getMax(modif)];
      modif[getMax(modif)] = 0;
    }
    curr++;
  }
}

int getMax(int* array) {
  int i;
  for (int l = 0; l < 100; l++) {
    if (array[l] >= array[i]) {
      i = l;
    }
  }
  return i;
}

void printHeap(int* heap, int size) {
  for(int i = 1; i <= size/2; i++) {
    if(heap[i] != 0) {
      cout << endl << heap[i];
    }
    if (heap[i*2] != 0) {
      cout << "---R:" << heap[i*2];
    }
    if(heap[i*2+1] != 0) {
      cout << " & L:" << heap[i*2+1] << endl;
    }
  }
}

void deleteHeap(int* heap, int size) {
  for (int i = 1; i <= size; i++) {
    cout << heap[i] << " ";
    heap[i] = 0;
  }
  cout << endl;
}

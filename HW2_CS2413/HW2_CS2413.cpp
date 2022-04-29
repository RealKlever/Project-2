#include <iostream>

using namespace std;

// used to empty a given string A of length n
void emptyString(char* A, int n) {
	for (int i = 0; i < n; i++) {
		A[i] = '\0';
	}
}

// copy a string A to B of length n
void stringCopy(char* A, int n, char* B) {
	for (int i = 0; i < n; i++) {
		B[i] = A[i];
	}
}

// return the length of a given string A
int stringLength(char* A) {
	int size = 0;
	while (A[size] != '\0') size++;
	return size; //size is the last index position
}

class myString;

class myString {
	friend ostream& operator << (ostream& s, myString& A);
protected:
	char* strArray;
	int size;
	void strCpy(char* A, char* B, int n);
public:
	myString();
	myString(char* inpStr);
	myString(myString& B);
	int Size();
	char* getWord();
	bool operator == (myString& B);
	bool operator > (myString& B);
	bool operator < (myString& B);
	myString& operator = (myString& B);
	myString& operator = (char* B);
};

// outputs a given string A
ostream& operator << (ostream& s, myString& A) {
	s << A.strArray;
	return s;
}

// default constructor - initializes with a NULL as the first character
myString::myString() {
	size = 0;
	strArray = new char[1];
	strArray[0] = '\0';
}

// non default constructor - initialize object with an existing string
myString::myString(char* inpStr) {
	int i = 0;
	while (inpStr[i] != '\0')
		i++;
	size = i;
	strArray = new char[size];
	emptyString(strArray, size + 1);
	for (int j = 0; j < size; j++)
		strArray[j] = inpStr[j];
}

// non default constructor - initialize object with an existing mystring object
myString::myString(myString& B) {
	delete[] strArray;
	strArray = NULL;
	size = B.size;
	strArray = new char[size];
	emptyString(strArray, size + 1);
	stringCopy(B.strArray, size, strArray);
}

// getter for string of myString
char* myString::getWord()
{
	return strArray;
}

// getter for size of myString
int myString::Size() {
	return size;
}

// overloading = operator - initialize object with an existing string
myString& myString::operator = (char* B) {

	// Gets the size of B and sets strArray to it
	size = stringLength(B);
	strArray = new char[size];

	stringCopy(B, size, strArray);

	return *this;
}

// overloading = operator - initialize object with an existing myString object
myString& myString::operator = (myString& B) {

	size = B.size;
	strArray = new char[size];

	emptyString(strArray, size + 1);
	stringCopy(B.strArray, size, strArray);

	return *this;
}

// checking if two myString objects are the same - return true or false
bool myString::operator == (myString& B) {

	if (this->strArray == B.strArray)
		return true;

	return false;
}

// comparison of myString A if less than myString B - return true or false
bool myString::operator < (myString& B) {

	int thisSize = 0;
	int bSize = 0;

	for (int i = 0; i < this->size; i++)
	{
		thisSize += this->strArray[i];
	}

	for (int i = 0; i < B.size; i++)
	{
		bSize += B.strArray[i];
	}

	if (thisSize < bSize)
		return true;

	return false;
}

// comparison of myString A if greater than myString B - return true or false
bool myString::operator > (myString& B) {

	int thisSize = 0;
	int bSize = 0;

	for (int i = 0; i < this->size; i++)
	{
		thisSize += this->strArray[i];
	}

	for (int i = 0; i < B.size; i++)
	{
		bSize += B.strArray[i];
	}

	if (thisSize > bSize)
		return true;

	return false;
}

// get one URL from redirected input and return it as a string
char* getNextURL() {
	char* str = new char[50]; //assumes a max URL size of 50
	emptyString(str, 50);

	char c;
	int i = 0;
	//read until the next white space or line-break 
	//modify the following line of code, so that the function returns only the URLs (i.e., it ignores everything that does not start with http:// or https:// )
	while (!cin.eof()) {
		cin.get(c);
		if (!cin.eof()) {
			if ((c != '\n') && (c != ' ')) {
				if (((c >= 'a') && (c <= 'z')) ||
					((c >= 'A') && (c <= 'Z')) ||
					((c >= '0') && (c <= '9')) ||
					(c >= ':') || (c >= '/') || (c >= '.') || (c >= '_'))
					str[i++] = c;
			}
			else if ((c == '\n') && (i > 0))
				return str;
			else if ((c == ' ') && (i > 0))
				return str;
		}
	}
	if (i > 0) return str;
	else return NULL;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class setOfURLs {
private:
	int binarySearchAndInsert(myString& u);
protected:
	myString* _URLs;
	int* _frequencies;
	int _size;

public:
	setOfURLs();
	setOfURLs(int numOfWords);

	myString* get_Words();
	int* get_Freq();
	int get_size();

	void setSize(int i);

	void addURL(myString& u);//insert word w into the array _URLs - keep it sorted alphabetically
	void sortFreq(); //sort words array based on frequency
	void sortURLs(); //sort words array alphabetically
	void display(); //print word followed by a colon followed by a single space and frequencuy
	setOfURLs* removeURLs(myString* URLsToFilterOut, int numURLsToFilterOut); //URLsToFilterOut from _URLs array
	~setOfURLs();
};

// default constructor - initializes with no URLs
setOfURLs::setOfURLs()
{
	_size = 0;
	_URLs = new myString[0];
	_frequencies = new int[0];
}

// non default constructor - initializes with a known number of URLs
setOfURLs::setOfURLs(int numOfWords)
{
	_size = numOfWords;
	_URLs = new myString[numOfWords];
	_frequencies = new int[numOfWords];
}

// getter for the array of URLs of the setOfURLs
myString* setOfURLs::get_Words()
{
	return _URLs;
}

// getter for the array of frequencies of the setOfURLs
int* setOfURLs::get_Freq()
{
	return _frequencies;
}

// getter for the size of the setOfURLs
int setOfURLs::get_size()
{
	return _size;
}

// store the value of the size of the setOfURLs
void setOfURLs::setSize(int i)
{
	_size = i;
}

// print the set of URLs in dictionary format (i.e., in alphabetical order)
void setOfURLs::display()
{
	this->sortURLs();

	for (int i = 0; i < _URLs->Size(); i++)
	{
		cout << _URLs[i] << endl;
	}
}

// sort the _URLs and _frequencies arrays, based on the frequencies
void setOfURLs::sortFreq()
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = i + 1; j < _size; j++)
		{
			if (_frequencies[i] > _frequencies[j])
			{
				myString temp = _URLs[i];
				_URLs[i] = _URLs[j];
				_URLs[j] = temp;

				int temp2 = _frequencies[i];
				_frequencies[i] = _frequencies[j];
				_frequencies[j] = temp2;
			}
		}
	}
}

// sort the _URLs and _frequencies arrays, alphabetically
void setOfURLs::sortURLs()
{
	for (int i = 0; i < _URLs->Size(); i++)
	{
		for (int j = i + 1; j < _URLs->Size(); j++)
		{
			if (_URLs[i].operator>(_URLs[j]))
			{
				myString temp = _URLs[i];
				_URLs[i] = _URLs[j];
				_URLs[j] = temp;

				int temp2 = _frequencies[i];
				_frequencies[i] = _frequencies[j];
				_frequencies[j] = temp2;
			}
		}
	}
}

// remove from the setOfURLs object, the URLs that have to be filtered out 
setOfURLs* setOfURLs::removeURLs(myString* URLsToFilterOut, int numURLsToFilterOut)
{
	int removed = 0;

	for (int i = 0; i < _URLs->Size(); i++)
	{
		if (URLsToFilterOut->operator==(_URLs[i]))
		{
			_URLs[i]; // THIS IS WHERE YOU LAST LEFT OFF
		}
	}

	return NULL;
}

// search for a given URL in _URLs - if found, update the setOfURLs object accordingly, if not, return the position where the URL has to be inserted
int setOfURLs::binarySearchAndInsert(myString& wordToFind)
{

	// TODO

	return NULL;
}

// method to store URLs to the setOfURLs object
void setOfURLs::addURL(myString& newWord)
{
	// TODO
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class URLLinks {

	friend ostream& operator << (ostream& s, URLLinks& A);

protected:
	myString URL;
	int numLinks;
	URLLinks** hyperLinks;

public:
	URLLinks();
	URLLinks(myString& x, int n);
	~URLLinks();

	int getNumLinks();
	URLLinks* getHyperLink(int i);
	myString& getURL();

	void addSite(myString& t);
	void addNeighbor(URLLinks& link);
	void setNeighbors(int nei);
};

// add the information about URL A to the output stream s 
ostream& operator << (ostream& s, URLLinks& A)
{
	//TODO
}

// create an empty URLLinks object
URLLinks::URLLinks()
{
	//TODO
}

// create a URLLinks object for URL x with n neighbors
URLLinks::URLLinks(myString& x, int n)
{
	//TODO
}

// return the URL of the URLLinks object
myString& URLLinks::getURL()
{
	//TODO
}

// returm the number of links of the URLLinks object
int URLLinks::getNumLinks()
{
	//TODO
}

// return a URLLinks object
URLLinks* URLLinks::getHyperLink(int i)
{
	//TODO
}

// destructor fot the URLLinks class
URLLinks::~URLLinks()
{
	//TODO
}

// store t as the URL of the URLLinks object
void URLLinks::addSite(myString& t)
{
	//TODO
}

// store the number of neighboring URLs of the specific URL, and create the space needed to store these URLs in the future
void URLLinks::setNeighbors(int nei)
{
	//TODO
}

// store the neighboring URLs of the specific URL
void URLLinks::addNeighbor(URLLinks& link)
{
	//TODO
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {

	int numURLsToFilterOut;
	char* url;
	myString* urlString;
	int numPages;
	int pageNo;
	int numNeighbors;
	int neighbor;


	// read the first number from the file that contains the number of URLs that have to be filtered out
	cin >> numURLsToFilterOut;
	cout << "Number of URLs to filter out: " << numURLsToFilterOut << endl;
	myString* URLsToFilterOutList = new myString[numURLsToFilterOut];

	// read the URLs that have to be filtered out
	for (int i = 0; i < numURLsToFilterOut; i++)
	{
		url = getNextURL();
		URLsToFilterOutList[i] = url; //calls the overloaded = operator on myString class
	}

	// Read a text containing URLs and store the in the setOfURLs instance
	setOfURLs* mySetOfURLs = new setOfURLs();

	url = getNextURL(); //first read the next URL as an array of characters

	while (url != NULL)
	{
		urlString = new myString(url); //create a myString object with the URL just read
		(*mySetOfURLs).addURL(*urlString); //add URL to mySetOfURLs
		url = getNextURL();
	}

	// this should display each URL along with its frequency;
	// note that because you are using binary search and insert, the URLs in the setOfURLs instance will be sorted alphabetically
	cout << endl;
	cout << "Input display:" << endl;
	(*mySetOfURLs).display();

	(*mySetOfURLs).sortFreq();
	cout << endl;
	cout << "mySetOfURLs - Sorted based on frequency:" << endl;
	(*mySetOfURLs).display();

	(*mySetOfURLs).sortURLs();
	cout << endl;
	cout << "mySetOfURLs - Sorted alphabetically:" << endl;
	(*mySetOfURLs).display();

	setOfURLs* newSetOfURLs = (*mySetOfURLs).removeURLs(URLsToFilterOutList, numURLsToFilterOut);
	cout << endl;
	cout << "newSetOfURLs - Sorted alphabetically:" << endl;
	(*newSetOfURLs).display();

	(*newSetOfURLs).sortFreq();
	cout << endl;
	cout << "newSetOfURLs - Sorted based on frequency:" << endl;
	(*newSetOfURLs).display();

	// read the number of URLs that follow
	cin >> numPages;
	cout << "Number of webpages: " << numPages << endl;

	// create the myLinkStructure array to store all URLLink objects
	URLLinks* myLinkStructure = new URLLinks[numPages];
	for (int i = 0; i < numPages; i++)
	{
		// read all URLs and store them in the myLinkStructure array of URLLink objects
	}

	// store the neighbors/hyperlinks of each page/URL
	for (int i = 0; i < numPages; i++)
	{
		cin >> pageNo >> numNeighbors;
		myLinkStructure[i].setNeighbors(numNeighbors);
		for (int j = 0; j < numNeighbors; j++)
		{
			cin >> neighbor;
			myLinkStructure[pageNo].addNeighbor((myLinkStructure[neighbor]));
		}
	}


	cout << "~~~Webpages and the links they contain:" << endl;
	// display all URLLink objects using the overloaded << operator (see sample output file)

	cout << "~~~Webpages and the number and URL of pages that contain links to them:" << endl;
	// display all the incoming nodes here (see sample output file)



	// TODO : implement the destructors
	// delete [] URLsToFilterOutList;
	// delete mySetOfURLs;
	// delete newSetOfURLs;

	delete[] myLinkStructure;

	return 0;

}

#include <iostream>

using namespace std;

// used to empty a given string A of length n
void emptyString(char* A, int n) {
	for (int i = 0; i < n; i++) {
		// \0 means an empty character
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
	strArray = new char[size + 1];
	emptyString(strArray, size + 1);
	for (int j = 0; j < size; j++)
		strArray[j] = inpStr[j];
}

// non default constructor - initialize object with an existing mystring object
myString::myString(myString& B) {
	//delete[] strArray;
	strArray = NULL;
	size = B.size;
	strArray = new char[size + 1];
	emptyString(strArray, size + 1);
	stringCopy(B.strArray, size, strArray);
}

// getter for string of myString
char* myString::getWord()
{
	return strArray;
}

// getter for size of the string
int myString::Size() {
	return size;
}

// overloading = operator - initialize object with an existing string
myString& myString::operator = (char* B) {

	// Gets the size of B and sets strArray to it plus an empty character
	size = stringLength(B);
	strArray = new char[size + 1];

	// Emptys the the array then copys B to it
	emptyString(strArray, size + 1);
	stringCopy(B, size, strArray);

	return *this;
}

// overloading = operator - initialize object with an existing myString object
myString& myString::operator = (myString& B) {

	// Gets the size of B and sets strArray to it plus an empty character
	size = B.size;
	strArray = new char[size + 1];

	// Emptys the the array then copys B to it
	emptyString(strArray, size + 1);
	stringCopy(B.strArray, size, strArray);

	return *this;
}

// checking if two myString objects are the same - return true or false
bool myString::operator == (myString& B) {

	// If the strings are not equal in size then they cannot be the same so returns false
	if (this->size != B.size)
		return false;
	else
	{
		for (int i = 0; i < this->size; i++)
		{
			// If a character does not match then return false
			if (this->strArray[i] != B.strArray[i])
				return false;
		}
	}

	return true;
}

// comparison of myString A if less than myString B - return true or false
bool myString::operator < (myString& B) {

	// Gets the size of the smallest strArray
	int minSize = min(B.size, this->size);

	for (int i = 0; i < minSize; i++)
	{
		// If the characters at i are the same then it continues through the loop, if ascii at this is less then B, returns true
		if (B.strArray[i] == this->strArray[i])
			continue;

		// Checks to see if the character for this is less then the character at B
		return (this->strArray[i] - B.strArray[i]) < 0;
	}

	if (this->Size() < B.Size())
		return true;
	else
		return false;
}

// comparison of myString A if greater than myString B - return true or false
bool myString::operator > (myString& B) {

	// Gets the size of the smallest array
	int minSize = min(B.size, this->size);

	for (int i = 0; i < minSize; i++)
	{
		// If the characters at i are the same then it continues through the loop, if ascii at this is greater then B, returns true
		if (B.strArray[i] == this->strArray[i])
			continue;

		// Checks to see if the character for this is greater then the character at B
		return (this->strArray[i] - B.strArray[i]) > 0;
	}

	if (this->Size() > B.Size())
		return true;
	else
		return false;
}

// get one URL from redirected input and return it as a string
char* getNextURL() {

	char* str = new char[100]; //assumes a max URL size of 50
	emptyString(str, 100);

	char c;
	int i = 0;
	bool isWebsite = false;

	//read until the next white space or line-break 
	while (!cin.eof()) {
		cin.get(c);
		if (!cin.eof()) {
			if ((c != '\n') && (c != ' ')) {
				if (((c >= 'a') && (c <= 'z')) ||
					((c >= 'A') && (c <= 'Z')) ||
					((c >= '0') && (c <= '9')) ||
					(c >= ':') || (c >= '/') || (c >= '.') || (c >= '_') || (c >= '$'))
					str[i++] = c;
			} 
			else if (((c == '\n') || (c == ' ')) && (i > 0) && isWebsite) // If it is a new line or spacce and isWebsite is true and i > 0 it will return the current str
				return str;
			else if (((c == '\n') || (c == ' ')) && (i > 0))
			{
				if (str[0] == '$' && str[1] == '$' && str[2] == '$' && str[3] == '$')
					return NULL;

				emptyString(str, 50);
				i = 0;
				continue;
			}


			// Checks to see if it is a real website with http:// or https://
			if (str[0] == 'h' && str[1] == 't' && str[2] == 't' && str[3] == 'p' && str[4] == ':' && str[5] == '/' && str[6] == '/')
				isWebsite = true;
			if (str[0] == 'h' && str[1] == 't' && str[2] == 't' && str[3] == 'p' && str[4] == 's' && str[5] == ':' && str[6] == '/' && str[7] == '/')
				isWebsite = true;
		}
	}

	if (i > 0) 
		return str;
	else
		return NULL;
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class setOfURLs {
private:
	int binarySearchAndInsert(myString& u);
	int binarySearch(myString* arr, int start, int end, myString find);
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
	cout << "mySetOfURLs: " << this->get_size() << endl;

	for (int i = 0; i < _size; i++)
	{
		cout << _URLs[i] << ": " << _frequencies[i] << endl;
	}

	cout << endl;
}

// sort the _URLs and _frequencies arrays, based on the frequencies
void setOfURLs::sortFreq()
{
	// Bubble Sort
	for (int i = 0; i < _size - 1; i++)
	{
		for (int j = 0; j < _size - i - 1; j++)
		{
			if (_frequencies[j] > _frequencies[j + 1])
			{
				myString temp = _URLs[j];
				_URLs[j] = _URLs[j + 1];
				_URLs[j + 1] = temp;

				int temp2 = _frequencies[j];
				_frequencies[j] = _frequencies[j + 1];
				_frequencies[j + 1] = temp2;
			}
		}
	}
}

// sort the _URLs and _frequencies arrays, alphabetically
void setOfURLs::sortURLs()
{
	// Bubble Sort
	for (int i = 0; i < _size - 1; i++)
	{
		for (int j = 0; j < _size - i - 1; j++)
		{
			if (_URLs[j] > _URLs[j + 1])
			{
				myString temp = _URLs[j];
				_URLs[j] = _URLs[j + 1];
				_URLs[j + 1] = temp;

				int temp2 = _frequencies[j];
				_frequencies[j] = _frequencies[j + 1];
				_frequencies[j + 1] = temp2;
			}
		}
	}
}

// remove from the setOfURLs object, the URLs that have to be filtered out 
setOfURLs* setOfURLs::removeURLs(myString* URLsToFilterOut, int numURLsToFilterOut)
{
	for (int i = 0; i < numURLsToFilterOut; i++)
	{
		int index = 0;

		// If the URL at i is not in _URLs then it continues the for loop
		if (binarySearchAndInsert(URLsToFilterOut[i]) == -1)
			continue;

		// Arrays to put the arrays we do not remove in
		myString* removedURLs = new myString[_size - 1];
		int* removedFreq = new int[_size - 1];

		for (int j = 0; j < _size; j++)
		{
			// If the URL at j equals a URL that we need to remove we continue with the for loop
			if (_URLs[j] == URLsToFilterOut[i])
				continue;

			removedURLs[index] = _URLs[j];
			removedFreq[index++] = _frequencies[j];
		}

		_URLs = removedURLs;
		_frequencies = removedFreq;
		this->setSize(_size - 1);
	}

	return this;
}

// search for a given URL in _URLs - if found, update the setOfURLs object accordingly, if not, return the position where the URL has to be inserted
int setOfURLs::binarySearchAndInsert(myString& wordToFind)
{
	return binarySearch(_URLs, 0, _size - 1, wordToFind);
}

int setOfURLs::binarySearch(myString* arr, int start, int end, myString find)
{
	// Gets the middle of the array
	if (end >= start) {
		int mid = start + (end - start) / 2;

		// Checks to see if the element needed is in the middle
		if (arr[mid] == find)
			return mid;

		// If element the is smaller than the middle then it can only be present in the left subarray
		if (arr[mid] > (find))
			return binarySearch(arr, start, mid - 1, find);

		// If it is not in the left subarray, then it is in the right
		return binarySearch(arr, mid + 1, end, find);
	}

	// Returns -1 if the element cannot be found
	return -1;
}


// method to store URLs to the setOfURLs object
void setOfURLs::addURL(myString& newWord)
{
	int size = _size + 1;

	// Initialze empty arrays
	int* copyFreq = new int[size];
	myString* copyURLs = new myString[size];

	// Puts info from the actual arrays into the copys
	for (int i = 0; i < _size; i++)
	{
		copyURLs[i] = _URLs[i];
		copyFreq[i] = _frequencies[i];
	}

	// If newWord could not be found in _URLs, then it adds it and the frequency
	if (binarySearchAndInsert(newWord) == -1)
	{
		copyURLs[size - 1] = newWord;
		copyFreq[size - 1] = 1;

		_URLs = copyURLs;
		_frequencies = copyFreq;
		this->setSize(size++);
	}
	else
	{
		// Increases the frequency at the place where the newWord is
		_frequencies[binarySearchAndInsert(newWord)]++;
	}

	sortURLs();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class URLLinks {

	friend ostream& operator << (ostream& s, URLLinks& A);

protected:
	myString URL;
	int numLinks;
	int nextLink;
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
	s << A.getURL() << ": " << endl;

	for (int i = 0; i < A.getNumLinks(); i++)
		cout << "** " << A.getHyperLink(i)->getURL() << endl;
	
	return s;
}

// create an empty URLLinks object
URLLinks::URLLinks()
{
	hyperLinks = new URLLinks * [0];
	URL = new char[0];
	numLinks = 0;
	nextLink = 0;
}

// create a URLLinks object for URL x with n neighbors
URLLinks::URLLinks(myString& x, int n)
{
	hyperLinks = new URLLinks * [n];
	URL = x;
	numLinks = n;
	nextLink = 0;
}

// return the URL of the URLLinks object
myString& URLLinks::getURL()
{
	return URL;
}

// returm the number of links of the URLLinks object
int URLLinks::getNumLinks()
{
	return numLinks;
}

// return a URLLinks object
URLLinks* URLLinks::getHyperLink(int i)
{
	return hyperLinks[i];
}

// destructor fot the URLLinks class
URLLinks::~URLLinks()
{
	delete[] hyperLinks;
}

// store t as the URL of the URLLinks object
void URLLinks::addSite(myString& t)
{
	URL = t;
}

// store the number of neighboring URLs of the specific URL, and create the space needed to store these URLs in the future
void URLLinks::setNeighbors(int nei)
{
	numLinks = nei;
	hyperLinks = new URLLinks * [nei];
	nextLink = 0;
}

// store the neighboring URLs of the specific URL
void URLLinks::addNeighbor(URLLinks& link)
{
	hyperLinks[nextLink++] = &link;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

URLLinks** increaseByOne(URLLinks** arr, int size)
{
	URLLinks** copy = new URLLinks * [size + 1];

	for (int i = 0; i < size; i++)
	{
		copy[i] = arr[i];
	}

	return copy;
}

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

	 //read the URLs that have to be filtered out
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
		myLinkStructure[i] = *new URLLinks(*new myString(getNextURL()), 0);
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
	for (int i = 0; i < numPages; i++)
	{
		cout << myLinkStructure[i] << endl;
	}

	cout << "~~~Webpages and the number and URL of pages that contain links to them:" << endl;
	for (int i = 0; i < numPages; i++)
	{
		// Loops thtough all the webpages
		URLLinks* outerLink = &myLinkStructure[i];
		int nextLink = 0;
		URLLinks** allLinks = new URLLinks * [nextLink];

		for (int j = 0; j < numPages; j++)
		{
			URLLinks& innerLink = myLinkStructure[j];

			for (int k = 0; k < innerLink.getNumLinks(); k++)
			{
				// If the two links match, it increases the size of the array and adds the innerLink
				if (outerLink->getURL() == innerLink.getHyperLink(k)->getURL())
				{
					allLinks = increaseByOne(allLinks, nextLink);
					allLinks[nextLink++] = &innerLink;
				}
			}
		}

		cout << outerLink->getURL() << ": " << nextLink << endl;
		for (int x = 0; x < nextLink; x++)
		{
			cout << "** " << allLinks[x]->getURL() << endl;
		}
		cout << endl;
	}

	 /*delete [] URLsToFilterOutList;
	 delete mySetOfURLs;
	 delete newSetOfURLs;*/

	delete[] myLinkStructure;

	return 0;

}

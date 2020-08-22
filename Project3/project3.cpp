// Preprocessor Directives
// Include Statements
#include <iostream>

using namespace std;


// Classes
template <class DT>
class GLRow
{
    protected:
        DT* _info;
        int _next;
        int _down;
    public:
        GLRow(); // Default Constructor
        GLRow(DT& newInfo);
        GLRow(GLRow<DT>& anotherOne); // Copy Constructor
        ~GLRow(); // Destructor

        int getNext();
        int getDown();
        DT* getInfo();
        void setNext(int n);
        void setDown(int d);
        void setInfo(DT& x);

        GLRow<DT>& operator=(GLRow<DT>& anotherOne); // A deep copy
};

// GLRow Constructors and Destructor
template <class DT>
GLRow<DT>::GLRow()
{
    // Initialize variables
    _info = NULL;
    _next = -1;
    _down = -1;
}

template <class DT>
GLRow<DT>::GLRow(DT& newInfo)
{
    // Initialize variables
    _info = new DT(newInfo);
    _next = -1;
    _down = -1;
}

template <class DT>
GLRow<DT>::GLRow(GLRow<DT>& anotherOne)
{
    // A copy constructor, so deep copy all of the values over
    if(anotherOne._info == NULL)
        _info = NULL;
    else
        _info = new DT(*anotherOne.getInfo());

    // Copy over the next and down values
    _next = anotherOne.getNext();
    _down = anotherOne.getDown();
}

template <class DT>
GLRow<DT>::~GLRow()
{
    // Delete _info and set to null
    if(_info != NULL)
    {
        delete _info;
        _info = NULL;
    }
}

// GLRow Methods
template <class DT>
int GLRow<DT>::getNext()
{
    // Return the next index
    return _next;
}

template <class DT>
int GLRow<DT>::getDown()
{
    // Return the down index
    return _down;
}

template <class DT>
DT* GLRow<DT>::getInfo()
{
    // First check if info is empty, if so return null?
    if(_info == NULL)
    {
        return NULL;
    }

    // Return the info of the row
    return _info;
}

template <class DT>
void GLRow<DT>::setNext(int n)
{
    // Set next to the parameter value
    _next = n;
}

template <class DT>
void GLRow<DT>::setDown(int d)
{
    // Set down to the parameter value
    _down = d;
}

template <class DT>
void GLRow<DT>::setInfo(DT& x)
{
    // Set the info to the parameter value as a pointer
    _info = new DT(x);
}

// GLRow Overloaded Operators
template <class DT>
GLRow<DT>& GLRow<DT>::operator=(GLRow<DT>& anotherOne)
{
    // Perform a deep copy on anotherOne and copy over to this instance
    _info = new DT(*anotherOne.getInfo());
    _next = anotherOne.getNext();
    _down = anotherOne.getDown();
}

template <class DT>
ostream& operator<<(ostream& os, GLRow<DT>& oneRow)
{
    // Output the data of oneRow
    os << *oneRow.getInfo();
    return os;
}



template <class DT>
class ArrayGLL
{
    protected:
        GLRow<DT>* myGLL;
        int maxSize; // Max size of the array of GLRows
        int firstElement;
        int firstFree;

        void displayHelper(int index); // A utility method to help with display
        int findHelper(DT& key, int index); // A utility method to help with find()
        void displayPathHelper(DT& key, int index); // A utility method for findDisplayPath()
        int sizeHelper(int index); // A utility method to help with size()
    public:
        ArrayGLL(); // Default Constructor
        ArrayGLL(int size);
        ArrayGLL(ArrayGLL<DT>& anotherOne); // Copy Constructor
        ~ArrayGLL();

        void display(); // Display in parenthesis format
        int find(DT& key); // Return the index position where you find the element key / -1 if not found
        void findDisplayPath(DT& key); // As travelling throughout the tree, print the values of nodes encountered
        int noFree(); // Return number of free locations, need to follow _next and get free locations
        int size(); // Return number of elements stored
        int parentPos(DT& key); // Provide location of the parent of element key in array
        int getMaxSize();
        int getFirstFree();
        int getFirstElement();
        void setFirstFree(int pos);
        void setFirstElement(int pos);

        GLRow<DT>& operator[](int pos); // Return GLRow that's in position pos in the array
        ArrayGLL<DT>& operator=(ArrayGLL<DT>& anotherOne);
};

// ArrayGLL Constructors and Destructor
template <class DT>
ArrayGLL<DT>::ArrayGLL()
{
    // Initialize variables
    // Need to set myGLL to NULL since we don't have a size
    myGLL = NULL;
    maxSize = 0;
    firstElement = -1;
    firstFree = -1;
}

template <class DT>
ArrayGLL<DT>::ArrayGLL(int size)
{
    // Set variables
    myGLL = new GLRow<DT>[size];
    maxSize = size;
    firstElement = -1;
    firstFree = -1;
}

template <class DT>
ArrayGLL<DT>::ArrayGLL(ArrayGLL<DT>& anotherOne)
{
    // Copy Constructor, copy all values over
    myGLL = new GLRow<DT>[anotherOne.getMaxSize()];
    maxSize = anotherOne.getMaxSize();
    firstElement = anotherOne.getFirstElement();
    firstFree = anotherOne.getFirstFree();

    for(int i = 0; i < anotherOne.getMaxSize(); i++)
    {
        myGLL[i] = anotherOne.myGLL[i];
    }
}

template <class DT>
ArrayGLL<DT>::~ArrayGLL()
{
    // Delete myGLL and set to NULL
    if(myGLL != NULL)
    {
        delete[] myGLL;
        myGLL = NULL;
    }
}

// ArrayGLL Methods
template <class DT>
void ArrayGLL<DT>::display()
{
    // Display in full parenthesized format
    // Will use a helper method and recursion
    displayHelper(firstElement);

}

template <class DT>
void ArrayGLL<DT>::displayHelper(int index)
{
    // First check base cases
    if(index == -1)
        return;

    // Output the data in this cell
    cout << myGLL[index] << " ";

    // Output next and down (with down first)
    if(myGLL[index].getDown() != -1)
    {
        cout << "(";
        displayHelper(myGLL[index].getDown());
        cout << ")";
    }

    if(myGLL[index].getNext() != -1)
        displayHelper(myGLL[index].getNext());
}

template <class DT>
int ArrayGLL<DT>::find(DT& key)
{
    // Need to use a recursive search but we can't because the find method doesn't exist within GLRow class
    // Return -1 if not found
    return findHelper(key, firstElement);
}

template <class DT>
int ArrayGLL<DT>::findHelper(DT& key, int index)
{
    if(index == -1)
        return -1;
    else if(*(myGLL[index].getInfo()) == key)
        return index;
    else
    {
        int t = findHelper(key, myGLL[index].getNext());

        if(t > -1)
            return t;
        else
            return findHelper(key, myGLL[index].getDown());
    }
}

template <class DT>
void ArrayGLL<DT>::findDisplayPath(DT& key)
{
    displayPathHelper(key, firstElement);
}

template <class DT>
void ArrayGLL<DT>::displayPathHelper(DT& key, int index)
{
    if(index == -1)
        return;

    cout << myGLL[index] << " ";

    // Check if this index is the key we are looking for
    if(*myGLL[index].getInfo() == key)
        return;
    else
    {
        // Go onto the down and next paths
        displayPathHelper(key, myGLL[index].getDown());

        displayPathHelper(key, myGLL[index].getNext());
    }
}

template <class DT>
int ArrayGLL<DT>::noFree()
{
    // Variables
    int numFree = 0;
    bool allFreeFound = false;
    int check = firstFree;

    while(!allFreeFound)
    {
        if(myGLL[check].getNext() == -1)
        {
            numFree++;
            allFreeFound = true;
        }
        else
        {
            check = myGLL[check].getNext();
            numFree++;
        }
    }

    return numFree;
}

template <class DT>
int ArrayGLL<DT>::size()
{
    return sizeHelper(firstElement);
}

template <class DT>
int ArrayGLL<DT>::sizeHelper(int index)
{
    if(index == -1)
        return 0;
    if(myGLL[index].getInfo() == NULL)
        return 0;

    return (1 + sizeHelper(myGLL[index].getNext()) + sizeHelper(myGLL[index].getDown()));
}

template <class DT>
int ArrayGLL<DT>::parentPos(DT& key)
{
    cout << "Not Implemented" << endl;
    return -1;
}

template <class DT>
int ArrayGLL<DT>::getMaxSize()
{
    return maxSize;
}

template <class DT>
int ArrayGLL<DT>::getFirstFree()
{
    // Return the firstFree element
    return firstFree;
}

template <class DT>
int ArrayGLL<DT>::getFirstElement()
{
    // Return the firstElement
    return firstElement;
}

template <class DT>
void ArrayGLL<DT>::setFirstFree(int pos)
{
    // Set firstFree to be the parameter
    firstFree = pos;
}

template <class DT>
void ArrayGLL<DT>::setFirstElement(int pos)
{
    // Set firstElement to be the parameter
    firstElement = pos;
}

// ArrayGLL Overloaded Operators
template <class DT>
GLRow<DT>& ArrayGLL<DT>::operator[](int pos)
{
    // Get the element from the pos index in the myGLL array
    return myGLL[pos];
}

template <class DT>
ArrayGLL<DT>& ArrayGLL<DT>::operator=(ArrayGLL<DT>& anotherOne)
{
    // Copy all values of anotherOne over
    myGLL = new GLRow<DT>[anotherOne.getMaxSize()];
    maxSize = anotherOne.getMaxSize();
    for(int i = 0; i < maxSize; i++)
    {
        myGLL[i] = anotherOne[i];
    }

    firstElement = anotherOne.getFirstElement();
    firstFree = anotherOne.getFirstFree();
}

template <class DT>
ostream& operator<<(ostream& os, ArrayGLL<DT>& oneGLL)
{
    for(int i = 0; i < oneGLL.getMaxSize(); i++)
        os << oneGLL[i] << " ";

    return os;
}


// Main Function
// Start of Program Logic
int main()
{
    // Variables
    int noElements, value, next, down, parentPos;
    int pos = -1;
    int keyValue;
    int tempValue = 0;

    int rowVal = 0;
    GLRow<int> oneRow(rowVal);

    // Get input of number of elements
    cin >> noElements;

    // Initialize a statically defined ArrayGLL object
    ArrayGLL<int> firstGLL(noElements);

    // Get values for all GLRows in ArrayGLL
    for(int i = 0; i < noElements; i++)
    {
        cin >> value >> next >> down;
        oneRow.setInfo(value);
        oneRow.setNext(next);
        oneRow.setDown(down);
        firstGLL[i] = oneRow;
    }

    firstGLL.setFirstFree(8);
    firstGLL.setFirstElement(2);

    cout << firstGLL << endl;
    firstGLL.display();
    cout << endl;

    ArrayGLL<int>* secondGLL = new ArrayGLL<int>(firstGLL);

    int firstInfo = 600, secondInfo = 700;
    (*secondGLL)[1].setInfo(firstInfo);
    (*secondGLL)[2].setInfo(secondInfo);

    cout << *secondGLL << endl;
    (*secondGLL).display();
    cout << endl;

    keyValue = 700;
    pos = (*secondGLL).find(keyValue);
    if(pos != -1)
    {
        cout << (*secondGLL)[pos] << endl;
        (*secondGLL).findDisplayPath(keyValue);
        cout << endl;
    }

    parentPos = (*secondGLL).parentPos(keyValue);
    if(parentPos != -1)
    {
        cout << (*secondGLL)[parentPos] << endl;
    }

    cout << (*secondGLL).size() << endl;
    cout << (*secondGLL).noFree() << endl;

    delete secondGLL;

    return 0;
}
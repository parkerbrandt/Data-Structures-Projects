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
    void deleteInfo();

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

template <class DT>
void GLRow<DT>::deleteInfo()
{
    if(_info != NULL)
        delete _info;
    _info = NULL;
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
    int arraySize;

    void displayHelper(int index); // A utility method to help with display
    int findHelper(DT& key, int index); // A utility method to help with find()
    void displayPathHelper(DT& key, int index); // A utility method for findDisplayPath()
    int sizeHelper(int index); // A utility method to help with size()
    int parentPosHelper(DT& key, int index);
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
    void insertAChild(DT& parent, DT& child);
    void removeANode(DT& node);
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
    firstElement = 0;
    firstFree = 0;
}

template <class DT>
ArrayGLL<DT>::ArrayGLL(int size)
{
    // Set variables
    myGLL = new GLRow<DT>[size];
    maxSize = size;
    firstElement = 0;
    firstFree = 0;
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
        cout << ") ";
    }

    if(myGLL[index].getNext() != -1)
        displayHelper(myGLL[index].getNext());
}

template <class DT>
int ArrayGLL<DT>::find(DT& key)
{
    // Need to use a recursive search but we can't because the find method doesn't exist within GLRow class
    // Return -1 if not found
    // First check if array is empty with size(), if so just return -1
    if(size() == 0)
        return -1;

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
        displayPathHelper(key, myGLL[index].getNext());

        displayPathHelper(key, myGLL[index].getDown());
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
    return parentPosHelper(key, firstElement);
}

template <class DT>
int ArrayGLL<DT>::parentPosHelper(DT& key, int index)
{
    int next = myGLL[index].getNext();
    int down = myGLL[index].getDown();

    // Check if this index is the parent of the key
    if((*myGLL[next].getInfo()) == key || (*myGLL[down].getInfo()) == key)
        return index;
    else if((*myGLL[next].getInfo()) == -1 && (*myGLL[down].getInfo()) == -1)
        return -1;
    else
    {
        if(parentPosHelper(key, next) == -1)
            return parentPosHelper(key, down);
        else
            return parentPosHelper(key, next);
    }
}

template <class DT>
void ArrayGLL<DT>::insertAChild(DT& parent, DT& child)
{
    // GLRow to be added
    GLRow<DT> rowToAdd(child);

    // First, need to do a find on parent
    int parentIndex = find(parent);

    // If parentIndex returns -1, this will be the root
    if(parentIndex == -1)
    {
        // Make the child the root
        // Add to array at index 0/firstElement
        myGLL[firstElement] = rowToAdd;
        return;
    }

    // Insert index
    int childIndex = size();
    firstFree++;

    if(myGLL[childIndex].getInfo() != NULL)
       childIndex = firstFree;

    // Add child to the array
    myGLL[childIndex] = rowToAdd;
    myGLL[childIndex].setDown(-1);
    myGLL[childIndex].setNext(-1);

    // Adjust parents _down and _next values
    // Need to check if parent's _down is already occupied
    if(myGLL[parentIndex].getDown() == -1)
    {
        // Adjust parent's down index
        myGLL[parentIndex].setDown(childIndex);
    }
    else
    {
        // Add to parent's down, but also need a temp down variable
        int tempDown = myGLL[parentIndex].getDown();
        myGLL[parentIndex].setDown(childIndex);

        // Set tempDown to be the next location of childIndex
        myGLL[childIndex].setNext(tempDown);
    }
}

template <class DT>
void ArrayGLL<DT>::removeANode(DT& node)
{
    // First, need to do a find
    int index = find(node);

    // Check if this is a leaf node (_down is -1)
    if(myGLL[index].getDown() == -1)
    {
        if(myGLL[index].getNext() == -1)
        {
            // Can simply delete this info
            int newInfo = -1;
            myGLL[index].setInfo(newInfo);
            return;
        }
        else
        {
            // Copy contents of _next into this
            int nextIndex = myGLL[index].getNext();
            myGLL[index].setInfo((*myGLL[nextIndex].getInfo()));
            myGLL[index].setNext(myGLL[nextIndex].getNext());

            // Delete the nextIndex
            int newInfo = -1;
            myGLL[nextIndex].setInfo(newInfo);
        }
    }
    else
    {
        // Not a leaf node
        // Replace with left most child in subtree
        // Keep going down tree until _down = -1
        int testIndex = index;
        int parentIndex = index;
        while(myGLL[testIndex].getDown() != -1)
        {
            parentIndex = testIndex;
            testIndex = myGLL[testIndex].getDown();
        }

        // Now test index should be the left most child
        // Replace index with testIndex and delete the testIndex
        myGLL[index].setInfo((*myGLL[testIndex].getInfo()));

        // Need to update parent index's down value to not point to that anymore
        // First will check if index had a next
        if(myGLL[testIndex].getNext() != -1)
        {
            myGLL[parentIndex].setDown(myGLL[testIndex].getNext());
        }
        else
        {
            myGLL[parentIndex].setDown(-1);
        }

        int newInfo = -1;
        myGLL[testIndex].setInfo(newInfo);
    }
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
    for(int i = 0; i < oneGLL.size(); i++)
        os << oneGLL[i] << " ";

    return os;
}


// Main Function
// Start of Program Logic
int main()
{
    // Variables
    int noElements;
    char command;
    int inputNum1, inputNum2;
    ArrayGLL<int>* firstGLL;

    // Get the number of elements from the user
    cin >> noElements;
    cout << "The size of the array is " << noElements << endl;

    // Initialize firstGLL
    firstGLL = new ArrayGLL<int>(noElements);

    // Continue to take in user input
    while(!cin.eof())
    {
        // Get the command
        cin >> command;

        // Check which command that is
        switch(command)
        {
            case 'D':
            {
                // Call the display method
                (*firstGLL).display();
                cout << endl;
                break;
            }

            case 'F':
            {
                // Call the find method
                // Output the index where it was found
                // First, need to get the key for what num we're looking for
                cin >> inputNum1;

                //Output the index where it was found
                cout << "The element " << inputNum1 << " is found at index: " << (*firstGLL).find(inputNum1) << endl;

                break;
            }

            case 'I':
            {
                // Perform an insert
                // Need to get two numbers, first will be a parent and second will be the actual number
                // If the parent = -1, it is the root of the tree
                cin >> inputNum1 >> inputNum2;

                (*firstGLL).insertAChild(inputNum1, inputNum2);
                cout << "Element inserted" << endl;

                break;
            }

            case 'P':
            {
                // Get the parent position
                // Get the number of the parent position
                cin >> inputNum1;

                cout << "Not Implemented" << endl;
                // cout << "The parent of " << inputNum1 << " is " << endl;
                // cout << (*firstGLL).parentPos(inputNum1);

                break;
            }

            case 'R':
            {
                // Remove a node
                // Get the element to remove
                cin >> inputNum1;

                (*firstGLL).removeANode(inputNum1);
                cout << "Element removed" << endl;

                break;
            }

            default:
                break;
        }
    }

    return 0;
}
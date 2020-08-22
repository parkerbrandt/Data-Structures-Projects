/*
 * Project 2 by Parker Brandt
 * ID: 113521131
 */

// Preprocessor Directives
#include <iostream>

using namespace std;


// Function Prototypes
double squareroot(double var);
double roundNum(double var);

// Exception Classes
class Exception : exception
{
    public:
        // Constructors
        Exception();
};

Exception::Exception() {}

class LineSegmentException : public Exception
{
    public:
        // Constructors
        LineSegmentException();
};

LineSegmentException::LineSegmentException() {}

class SegmentsException : public Exception
{
    public:
        // Constructors
        SegmentsException();
};

SegmentsException::SegmentsException() {}


// Classes
template <class DT>
class Point
{
    protected:
        DT x; // x-coordinate value
        DT y; // y-coordinate value
    public:
        // Constructors
        Point();
        Point(DT xvalue, DT yvalue);

        // Methods
        void setLocation(DT xvalue, DT yvalue); // sets x = xvalue and y = yvalue
        double getXValue(); // returns x value of the object
        double getYValue(); // returns y value of the object
};

// Constructors
template <class DT>
Point<DT>::Point()
{
    // Initialize x and y to 0
    x = 0.0;
    y = 0.0;
}

template <class DT>
Point<DT>::Point(DT xvalue, DT yvalue)
{
    // Initialize variables
    x = xvalue;
    y = yvalue;
}

// Methods
template <class DT>
void Point<DT>::setLocation(DT xvalue, DT yvalue)
{
    // Set the variables
    x = xvalue;
    y = yvalue;
}

template <class DT>
double Point<DT>::getXValue()
{
    // Return the x value
    return x;
}

template <class DT>
double Point<DT>::getYValue()
{
    // Return the y value
    return y;
}

// Overloaded operators
template <class DT>
ostream& operator<<(std::ostream& os, Point<DT> otherPoint)
{
    // Display the coordinates of the point
    os << "(" << roundNum(otherPoint.getXValue()) << ", " << roundNum(otherPoint.getYValue()) << ")";
    return os;
}



template <class DT>
class LineSegment
{
    protected:
        Point<DT> P1;
        Point<DT> P2;
    public:
        // Constructors
        LineSegment();
        LineSegment(Point<DT> one, Point<DT> two);

        // Methods
        double length(); // returns length of the line segment
        Point<DT> midpoint(); // returns midpoint of the line segment
        Point<DT> xIntercept(); // returns x intercept of the line segment
        Point<DT> yIntercept(); // returns y intercept of the line segment
        double slope(); // returns the slope of the line segment
        bool itIntersects(LineSegment<DT> L); // finds if this line segment object intersects with the one inputted
        Point<DT> intersectionPoint(LineSegment<DT> L); // returns the intersection point with another line segment
        bool isParallel(LineSegment<DT> L);
        void displayEquation(); // displays the equation of the line segment in y=m*x+b format
        Point<DT> getPoint1(); // returns the first point of the line segment
        Point<DT> getPoint2(); // returns the second point of the line segment
};

// Constructors
template <class DT>
LineSegment<DT>::LineSegment() {}

template <class DT>
LineSegment<DT>::LineSegment(Point<DT> one, Point<DT> two)
{
    // Initialize variables
    P1 = one;
    P2 = two;
}

// Methods
template <class DT>
double LineSegment<DT>::length()
{
    // Variables
    double length = 0.0;

    // Use the distance formula to determine length between the two points
    // d = sqrt( (x2-x1)^2 + (y2-y1)^2 )
    double xComp = (P2.getXValue() - P1.getXValue()) * (P2.getXValue() - P1.getXValue());
    double yComp = (P2.getYValue() - P1.getYValue()) * (P2.getYValue() - P1.getYValue());

    double squareLength = xComp + yComp;

    // get the square root
    length = squareroot(squareLength);

    return length;
}

template <class DT>
Point<DT> LineSegment<DT>::midpoint()
{
    // Variables
    Point<DT> midpoint;
    double midx, midy;

    try
    {
        if(length() == 0)
        {
            throw LineSegmentException();
        }

        // Get line segment point values
        double p1x = P1.getXValue(), p1y = P1.getYValue(), p2x = P2.getXValue(), p2y = P2.getYValue();

        // Determine the coordinates for the midpoint
        midx = (p1x + p2x) / 2;
        midy = (p1y + p2y) / 2;

        midpoint.setLocation(midx, midy);
    }
    catch(LineSegmentException& e)
    {
        // Output the error message
        cout << "Length is 0" << endl;
    }

    return midpoint;
}

template <class DT>
Point<DT> LineSegment<DT>::xIntercept()
{
    // Variables
    Point<DT> intercept;

    // Equation for x intercept is given by x1 - y1 * (x2 - x1)/(y2 - y1)
    double xCoord = P1.getXValue() - (P1.getYValue() * (P2.getXValue() - P1.getXValue())/(P2.getYValue() - P1.getYValue()));

    // Set the coordinates of the intercept
    intercept.setLocation(xCoord, 0);

    return intercept;
}

template <class DT>
Point<DT> LineSegment<DT>::yIntercept()
{
    // Variables
    Point<DT> intercept;

    // Can use point slope formula: y- y1 = m(x - x1)
    // By reconfiguring the equation we can get the y-intercept as y1 - mx1
    // The coordinates will be (0, y1-mx1)
    // Doesn't matter if I use Point1 or Point2, so I'll just use Point1
    double yCoord = P1.getYValue() - (slope() * P1.getXValue());

    // Set the coordinates of the intercept
    intercept.setLocation(0, yCoord);

    return intercept;
}

template <class DT>
double LineSegment<DT>::slope()
{
    // Variables
    double slope;
    double x1 = P1.getXValue(), x2 = P2.getXValue();
    double y1 = P1.getYValue(), y2 = P2.getYValue();

    slope = (y2 - y1) / (x2 - x1);

    return slope;
}

template <class DT>
bool LineSegment<DT>::itIntersects(LineSegment<DT> L)
{
    // Use formula from reference paper
    // Variables
    double x1 = P1.getXValue(), y1 = P1.getYValue();
    double x2 = P2.getXValue(), y2 = P2.getYValue();
    double x3 = L.getPoint1().getXValue(), y3 = L.getPoint1().getYValue(); // Would refer to the point Q1 in the reference paper
    double x4 = L.getPoint2().getXValue(), y4 = L.getPoint2().getYValue(); // Would refer to point Q2

    // Make sure first, that they are not parallel, thus not being the same line segment
    // Either they are parallel, and won't ever touch, or they are the same line
    if(isParallel(L))
        return false;

    // Calculate values to determine if they intersect
    // These values are derived from the coordinates of the points, and the cross product provided in the reference
    // Created the vector values from the reference paper by subtracting the second values from the first values and
    // substituting those into the cross product (Ex. Vector P1P2 = <x2 - x1, y2 - y1>)
    double d1 = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1); // P1P2 x P1Q1
    double d2 = (x2 - x1)*(y4 - y1) - (x4 - x1)*(y2 - y1); // P1P2 x P1Q2
    double d3 = (x4 - x3)*(y1 - y3) - (x1 - x3)*(y4 - y3); // Q1Q2 x Q1P1
    double d4 = (x4 - x3)*(y2 - y1) - (x2 - x1)*(y4 - y3); // Q1Q2 x P1P2

    // Check the d values to determine if the line segments intersect
    // All values multiplied need to be less than 0
    return d1 * d2 <= 0 && d3 * d4 <= 0;
}

template <class DT>
Point<DT> LineSegment<DT>::intersectionPoint(LineSegment<DT> L)
{
    // Variables
    Point<DT> interPoint;
    double interX, interY;
    double m1, c1, m2, c2;

    // Using the formula from the reference paper
    // this line segment will be y = m1x + c1
    // L will be y = m2x + c2
    // Formula: x = (c2-c1)/(m1-m2) | y = (c1m2 - c2m1)/(m2 - m1)
    m1 = slope();
    c1 = yIntercept().getYValue();

    m2 = L.slope();
    c2 = L.yIntercept().getYValue();

    // Initialize the x and y values for the intersection point
    interX = (c2 - c1) / (m1 - m2);
    interY = (c1 * m2 - c2 * m1) / (m2 - m1);

    // Set the values for the object
    interPoint.setLocation(interX, interY);

    return interPoint;
}

template <class DT>
bool LineSegment<DT>::isParallel(LineSegment<DT> L)
{
    // Variables
    double mySlope = roundNum(slope());
    double otherSlope = roundNum(L.slope());

    // Check if the slopes are equal
    if(mySlope == otherSlope)
    {
        // The slopes are equal, so they are parallel
        return true;
        // Need to check for slight error due to rounding errors that may occur
    }
    else if(mySlope == (otherSlope + 0.01) || mySlope == (otherSlope - 0.01))
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class DT>
void LineSegment<DT>::displayEquation()
{
    // Variables
    double m = roundNum(slope());
    double b = roundNum(yIntercept().getYValue());

    cout << "y=" << m << "*x+" << b;
}

template <class DT>
Point<DT> LineSegment<DT>::getPoint1()
{
    return P1;
}

template <class DT>
Point<DT> LineSegment<DT>::getPoint2()
{
    return P2;
}

// Overloaded Operators
template <class DT>
ostream& operator<<(ostream& os, LineSegment<DT> otherSegment)
{
    // Output the y=m*x+b format of the line segment
    double slope = roundNum(otherSegment.slope());
    double yIntercept = roundNum(otherSegment.yIntercept().getYValue());

    os << "y=" << slope << "*x+" << yIntercept;
    return os;
}



template <class DT>
class Segments
{
    protected:
        LineSegment<DT>* segments;
        int count;
        int maxSize;
    public:
        // Constructors
        Segments();
        Segments(int size);
        ~Segments();

        // Methods
        void setSize(int size);
        void addLineSegment(LineSegment<DT> L);
        void removeLineSegment(LineSegment<DT> L);
        int sizeOfArray();
        LineSegment<DT> getSegment(int index); // Retrieves a specific line segment from segments at a specific index
        Segments<DT> aClosedPolygon();
        Segments<DT> findAPolygon(Point<DT> startPoint, LineSegment<DT> lineSegments[]);
        Segments<DT> findAllIntersects(LineSegment<DT>& LS);
        double distance(Point<DT> p, LineSegment<DT> ls);
        LineSegment<DT>& findClosest(Point<DT>& aPoint);
};

// Constructors
template <class DT>
Segments<DT>::Segments()
{
    // No parameters, so we set everything to 0 or NULL
    segments = NULL;
    count = 0;
    maxSize = 0;
}

template <class DT>
Segments<DT>::Segments(int size)
{
    segments = new LineSegment<DT>[size];
    count = 0;
    maxSize = size;
}

template <class DT>
Segments<DT>::~Segments()
{
    delete[] segments;
}

// Methods
template <class DT>
void Segments<DT>::setSize(int size)
{
    segments = new LineSegment<DT>[size];
    count = 0;
    maxSize = size;
}

template <class DT>
void Segments<DT>::addLineSegment(LineSegment<DT> L)
{
    // Add the line segment to segments
    segments[count] = L;

    // Add one to the count variable
    count++;
}

template <class DT>
void Segments<DT>::removeLineSegment(LineSegment<DT> L)
{
    // First make sure there aren't no elements in the array
    if(count == 0)
        return;

    for(int i = 0; i < count; i++)
    {
        // Check to see if we found the right LineSegment by checking x and y values
        LineSegment<DT> testSegment = segments[i];

        if(L.getPoint1().getXValue() == testSegment.getPoint1().getXValue() && L.getPoint1().getYValue() == testSegment.getPoint1().getYValue())
        {
            if(L.getPoint2().getXValue() == testSegment.getPoint2().getXValue() && L.getPoint2().getYValue() == testSegment.getPoint2().getYValue())
            {
                // Create a new array to hold values
                LineSegment<DT>* newSegments = new LineSegment<DT>[maxSize];

                // Check if i = 0
                if (i == 0)
                {
                    // Can straight copy the other values over
                    for(int j = 1; j < count; j++)
                    {
                        newSegments[j - 1] = segments[j];
                    }

                    delete[] segments;
                    segments = newSegments;
                    count--;

                    return;
                }

                // Move all values except for the one we want to remove
                // Works if i > 1
                int j = 0;
                for(j = 0; j < i; j++)
                {
                    newSegments[j] = segments[j];
                }

                for(int k = j + 1; k < count; k++)
                {
                    newSegments[k] = segments[k];
                }

                // Delete segments then reinitialize it
                delete[] segments;
                segments = newSegments;
                count--;

                // We're done, so we can return
                return;
            }
        }
    }
}

template <class DT>
int Segments<DT>::sizeOfArray()
{
    return count;
}

template <class DT>
LineSegment<DT> Segments<DT>::getSegment(int index)
{
    // Return the specific line segment
    return segments[index];
}

template <class DT>
Segments<DT> Segments<DT>::aClosedPolygon() {}

template <class DT>
Segments<DT> Segments<DT>::findAllIntersects(LineSegment<DT>& LS)
{
    // Variables
    Segments<DT> intersectSegments = Segments<DT>(maxSize);

    // Iterate through segments array and see if if the LineSegments intersect
    for(int i = 0; i < count; i++)
    {
        LineSegment<DT> testSegment = segments[i];

        if(LS.itIntersects(testSegment))
            intersectSegments.addLineSegment(testSegment);
    }

    return intersectSegments;
}

template <class DT>
double Segments<DT>::distance(Point<DT> p, LineSegment<DT> ls)
{
    // Variables
    double x0, y0, m, c;
    double denominator, numerator;
    double distance;

    // Get values from the parameters
    x0 = p.getXValue();
    y0 = p.getYValue();
    m = ls.slope();
    c = ls.yIntercept().getYValue();

    denominator = squareroot(1 + (m * m));
    numerator = (m*x0) - y0 + c;

    if(numerator < 0)
        numerator *= -1;

    distance = numerator / denominator;

    return distance;
}

template <class DT>
LineSegment<DT>& Segments<DT>::findClosest(Point<DT> &aPoint)
{
    // Variables
    double smallestDist;
    int smallestIndex;

    // First get the first line segment in segments and test that to initialize
    smallestDist = distance(aPoint, segments[0]);
    smallestIndex = 0;

    for(int i = 1; i < count; i++)
    {
        if(distance(aPoint, segments[i]) < smallestDist)
        {
            smallestDist = distance(aPoint, segments[i]);
            smallestIndex = i;
        }
    }

    return segments[smallestIndex];
}

// Overloaded Operators
template <class DT>
ostream& operator<<(ostream& os, Segments<DT> segments)
{
    for(int i = 0; i < segments.sizeOfArray(); i++)
    {
        os << "Line Segment " << i + 1 << ":" << endl;
        os << segments.getSegment(i).getPoint1();

        os << ",";
        os << segments.getSegment(i).getPoint2() << endl;

        os << "Slope:" << roundNum(segments.getSegment(i).slope()) << endl;

        os << "Midpoint:" << segments.getSegment(i).midpoint() << endl;

        os << "X Intercept:" << roundNum(segments.getSegment(i).xIntercept().getXValue()) << endl;

        os << "Y Intercept:" << roundNum(segments.getSegment(i).yIntercept().getYValue()) << endl;

        os << "Length:" << roundNum(segments.getSegment(i).length()) << endl;

        os << segments.getSegment(i);
        os << endl;
    }

    return os;
}



// Main Function
// Start of Program Logic
int main()
{
    // Variables
    char command;
    int noOfSegments;

    // Get the first line of input, which will have the max number of line segments
    cin >> noOfSegments;

    // Create a Segments object
    Segments<double> *segments = new Segments<double>(noOfSegments);

    while(cin >> command)
    {
        switch(command)
        {
            case 'A':
            {
                // Add a line segment
                // Variables for the line segment
                double x1, y1, x2, y2;

                // Read input for each of the points
                cin >> x1 >> y1 >> x2 >> y2;

                // Create the two point objects and line segment object to be added
                Point<double> point1 = Point<double>(x1, y1);
                Point<double> point2 = Point<double>(x2, y2);

                LineSegment<double> segment = LineSegment<double>(point1, point2);

                // Add to the segments object
                segments->addLineSegment(segment);

                cout << "Line segment added" << endl << endl;

                break;
            }

            case 'R':
            {
                // Remove a line segment
                // Variables
                double x1, y1, x2, y2;

                try
                {
                    // Read in the points
                    cin >> x1 >> y1 >> x2 >> y2;

                    // Loop through segments to find if there is a line segment that matches
                    bool foundMatch = false;

                    for(int i = 0; i < noOfSegments; i++)
                    {
                        LineSegment<double> testSegment = segments->getSegment(i);

                        if(x1 == testSegment.getPoint1().getXValue() && y1 == testSegment.getPoint1().getYValue())
                        {
                            if(x2 == testSegment.getPoint2().getXValue() && y2 == testSegment.getPoint2().getYValue())
                            {
                                // Found a match
                                // Need to remove the found segment
                                foundMatch = true;

                                // Create a line segment and pass it to segments to remove it
                                LineSegment<double> removeSegment = LineSegment<double>(Point<double>(x1, y1), Point<double>(x2, y2));
                                segments->removeLineSegment(removeSegment);
                            }
                        }
                    }

                    if(!foundMatch)
                    {
                        throw SegmentsException();
                    }

                    cout << "Line segment removed" << endl << endl;
                }
                catch(SegmentsException& e)
                {
                    cout << "Exception,line segment not found" << endl << endl;
                }

                break;
            }

            case 'D':
            {
                // Display the segments object
                cout << *segments << endl;

                break;
            }

            case 'P':
            {
                cout << "Polygon not implemented." << endl;

                break;
            }

            case 'I':
            {
                // Variables for line segment thats intersected with
                double x1, y1, x2, y2;

                // Read in the values
                cin >> x1 >> y1 >> x2 >> y2;

                // Form a LineSegment Object
                LineSegment<double> testSegment = LineSegment<double>(Point<double>(x1, y1), Point<double>(x2, y2));

                // Find all of the intersects
                Segments<double> intersectSegments = segments->findAllIntersects(testSegment);

                if(intersectSegments.sizeOfArray() == 0)
                {
                    cout << "NO INTERSECTING LINE SEGMENTS" << endl;
                }
                else
                {

                    // cout << intersectSegments;
                    // Output the equations of the line segments
                    cout << "The lines segments intersecting with the given line segment are:" << endl;

                    for(int i = 0; i < intersectSegments.sizeOfArray(); i++)
                    {
                        LineSegment<double> testSegment1 = intersectSegments.getSegment(i);
                        LineSegment<double> testSegment2 = segments->getSegment(i);

                        // Check if the points match
                        if(testSegment1.getPoint1().getXValue() == testSegment2.getPoint1().getXValue() && testSegment1.getPoint1().getYValue() == testSegment2.getPoint1().getYValue())
                        {
                            if(testSegment1.getPoint2().getXValue() == testSegment2.getPoint2().getXValue() && testSegment1.getPoint2().getYValue() == testSegment2.getPoint2().getYValue())
                            {
                                cout << "Line segment " << i + 1 << endl;
                            }
                        }
                    }

                    cout << endl;
                }

                break;
            }

            case 'C':
            {
                // Variables for the point that will be inputted
                double x, y;

                // Get values
                cin >> x >> y;

                // Create a point object
                Point<double> testPoint = Point<double>(x, y);

                // Find the closest line segment
                LineSegment<double> closestSegment = segments->findClosest(testPoint);

                // Match the Line Segment with one in segments
                int index = 0;
                for(int i = 0; i < segments->sizeOfArray(); i++)
                {
                    LineSegment<double> testSegment = segments->getSegment(i);

                    // Check points to make sure it is the right segment
                    if(closestSegment.getPoint1().getXValue() == testSegment.getPoint1().getXValue() && closestSegment.getPoint1().getYValue() == testSegment.getPoint1().getYValue())
                    {
                        if(closestSegment.getPoint2().getXValue() == testSegment.getPoint2().getXValue() && closestSegment.getPoint2().getYValue() == testSegment.getPoint2().getYValue())
                        {
                            index = i;
                        }
                    }
                }

                // Output the line segment
                cout << "The Line segment closest to the given point is:Line segment " << index + 1 << endl;
                break;
                break;
            }

            default:
                cout << "Invalid command" << endl;
                break;
        }
    }

    delete segments;

    return 0;
}


// Function Declarations
double squareroot(double var)
{
    // Variables
    double eps = 1e-10;
    double k = var;
    double l = 0.0, r, mid;

    if (k >= 1)
    {
        r = k;
    }

    if (k < 1)
    {
        r = 1;
    }


    while (l-k/l > eps || l-k/l < -eps)
    {
        mid = l + (r - l) /2 ;

        if (mid < k / mid)
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }

    return l;
}

double roundNum(double var)
{
    // Variables
    double rndnum;
    double num2 = var * 100;
    int num3 = (int)num2;
    double dec3 = num2 - num3;

    if ((dec3*10) >= 5)
    {
        rndnum = ((int)((var)*100))/100.00 + 0.01;
    }
    else
    {
        rndnum = ((int)((var)*100))/100.00;
    }

    return rndnum;
}
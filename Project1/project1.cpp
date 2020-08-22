/**
 * CS 2413 Project 1
 * By Parker Brandt (bran0107)
 */

// Preprocessor Directives
#include <iostream>
using namespace std;

// Function Prototypes
double squareroot(double var);
double roundNum(double var);

// Classes
class Point {
	protected:
		double x; // x-coordinate value
		double y; // y-coordinate value
	public:
		Point(); // Default constructor
		Point(double xvalue, double yvalue); // overridden constructor
		void setLocation(double xvalue, double yvalue); // set x=xvalue and y=yvalue
		double getXValue(); // returns the x of the object
		double getYValue(); // returns the y of the object
		void display(); // Print (0.0, 0.0) with coordinates of the point
};

// Point Methods
Point::Point() {
	// Initialize x and y to 0
	x = 0.0;
	y = 0.0;
}

Point::Point(double xvalue, double yvalue) {
	// Initialize Variables
	x = xvalue;
	y = yvalue;
}

void Point::setLocation(double xvalue, double yvalue) {
	// Set variables
	x = xvalue;
	y = yvalue;
}

double Point::getXValue() {
	// Return the x value
	return x;
}

double Point::getYValue() {
	// Return the y value
	return y;
}

void Point::display() {
	// Display the coordinates of the Point
	cout << "(" << roundNum(x) << ", " << roundNum(y) << ")";
}



class LineSegment {
	protected:
		Point P1;
		Point P2;
	public:
		LineSegment(); // Default constructor
		LineSegment(Point one, Point two); // Overridden constructor
		double length(); // returns the length of the line segment
		Point midpoint(); // returns the midpoint of the line segment
		Point xIntercept(); // returns the x-intercept of the line segment
		Point yIntercept(); // returns the y-intercept of the line segment
		double slope(); // returns the slope of the line segment
		bool itIntersects(LineSegment L); // finds if this line segment intersects with another line segment
		Point intersectionPoint(LineSegment L);
		bool isParallel(LineSegment L); // checks if the two line segments are parallel by checking their slopes
		void displayEquation(); // displays the equation in the form of y = mx + b
		Point getPoint1(); // returns the first point of the line segment
		Point getPoint2(); // returns the second point of the line segment
};

// LineSegment Methods
LineSegment::LineSegment() {}

LineSegment::LineSegment(Point one, Point two) {
	// Initialize the points of the line segment
	P1 = one;
	P2 = two;
}

double LineSegment::length() {
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

Point LineSegment::midpoint() {
	// Variables
	Point midpoint;
	double midx, midy;

	// Get line segment point values
	double p1x = P1.getXValue(), p1y = P1.getYValue(), p2x = P2.getXValue(), p2y = P2.getYValue();

	// Determine the coordinates for the midpoint
	midx = (p1x + p2x) / 2;
	midy = (p1y + p2y) / 2;

	midpoint.setLocation(midx, midy);

	return midpoint;
}

Point LineSegment::xIntercept() {
	// Variables
	Point intercept;

	// Equation for x intercept is given by x1 - y1 * (x2 - x1)/(y2 - y1)
	double xCoord = P1.getXValue() - (P1.getYValue() * (P2.getXValue() - P1.getXValue())/(P2.getYValue() - P1.getYValue()));

	// Set the coordinates of the intercept
	intercept.setLocation(xCoord, 0);

	return intercept;
}

Point LineSegment::yIntercept() {
	// Variables
	Point intercept;

	// Can use point slope formula: y- y1 = m(x - x1)
	// By reconfiguring the equation we can get the y-intercept as y1 - mx1
	// The coordinates will be (0, y1-mx1)
	// Doesn't matter if I use Point1 or Point2, so I'll just use Point1
	double yCoord = P1.getYValue() - (slope() * P1.getXValue());

	// Set the coordinates of the intercept
	intercept.setLocation(0, yCoord);

	return intercept;
}

double LineSegment::slope() {
	// Variables
	double slope;
	double x1 = P1.getXValue(), x2 = P2.getXValue();
	double y1 = P1.getYValue(), y2 = P2.getYValue();

	slope = (y2 - y1) / (x2 - x1);

	return slope;
}

bool LineSegment::itIntersects(LineSegment L) {
	// Use formula from reference paper
	// Variables
	double x1 = P1.getXValue(), y1 = P1.getYValue();
	double x2 = P2.getXValue(), y2 = P2.getYValue();
	double x3 = L.getPoint1().getXValue(), y3 = L.getPoint1().getYValue();
	double x4 = L.getPoint2().getXValue(), y4 = L.getPoint2().getYValue();

	// Calculate values to determine if they intersect
	// These values are derived from the coordinates of the points, and the cross product provided in the reference
	double d1 = (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1);
	double d2 = (x2 - x1)*(y4 - y1) - (x4 - x1)*(y2 - y1);
	double d3 = (x4 - x3)*(y1 - y3) - (x1 - x3)*(y4 - y3);
	double d4 = (x4 - x3)*(y2 - y1) - (x2 - x1)*(y4 - y3);

	// Check the d values to determine if the line segments intersect
	// All values need to be less than 0
	if(d1 * d2 <= 0 && d3 * d4 <= 0) {
		// All values were less than or equal to 0
		return true;
	} else {
		// One value was greater than 0
		return false;
	}
}

Point LineSegment::intersectionPoint(LineSegment L) {
	// Variables
	Point interPoint;
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

bool LineSegment::isParallel(LineSegment L) {
	// Variables
	double mySlope = slope();
	double otherSlope = L.slope();

	// Check if the slopes are equal
	if(mySlope == otherSlope) {
		// The slopes are equal, so they are parallel
		return true;
	} else {
		return false;
	}
}

void LineSegment::displayEquation() {
	// Variables
	double m = roundNum(slope());
	double b = roundNum(yIntercept().getYValue());

	// printf("m*x + b", m, b);
	cout << "y=" << m << "*x+" << b;
}

Point LineSegment::getPoint1() {
	return P1;
}

Point LineSegment::getPoint2() {
	return P2;
}



class Intervals {
	protected:
		LineSegment* segments;
		int count;
		int maxSize;
	public:
		Intervals(); // Sets segments to NULL, count to 0, and maxSize to 0
		Intervals(int size); // overridden constructor
		void setSize(int size); // if overridden constructor is not initially called, this method will be used
		void addLineSegment(LineSegment L);
		LineSegment getSegment(int index); // Retrieves a specific line segment from segments at a specific index
		void display(); // Displays all line segments stored
};

// Intervals methods
Intervals::Intervals() {
	// No parameters, so we set everything to 0 or NULL
	segments = NULL;
	count = 0;
	maxSize = 0;
}

Intervals::Intervals(int size) {
	segments = new LineSegment[size];
	count = 0; // no line segments in the interval
	maxSize = size;
}

void Intervals::setSize(int size) {
	segments = new LineSegment[size];
	count = 0;
	maxSize = size;
}

void Intervals::addLineSegment(LineSegment L) {
	// Add the line segment to segments
	segments[count] = L;

	// Add one to the count variable
	count++;
}

LineSegment Intervals::getSegment(int index) {
	// Return the specific line segment
	return segments[index];
}

void Intervals::display() {
	// Go through all of the LineSegments and display info
	for(int i = 0; i < count; i++) {
		cout << "Line Segment " << i + 1 << ":" << endl;
		//cout << "P1 = ";
		segments[i].getPoint1().display();

		//cout << " P2 = ";
		cout << ",";
		segments[i].getPoint2().display();
		cout << endl;

		cout << "Slope:" << roundNum(segments[i].slope()) << endl;

		cout << "Midpoint:";
		segments[i].midpoint().display();
		cout << endl;

		cout << "X Intercept:" << roundNum(segments[i].xIntercept().getXValue());
		cout << endl;

		cout << "Y Intercept:" << roundNum(segments[i].yIntercept().getYValue());
		cout << endl;

		cout << "Length:" << roundNum(segments[i].length()) << endl;

		segments[i].displayEquation();
		cout << endl;
	}
}


/**
 * Main Function
 * Start of Program Logic
 */
int main()
{
	// Variables
	Intervals intervals;
	int noOfSegments;

	// Get the number of segments
	cin >> noOfSegments;

	// Initialize intervals
	intervals.setSize(noOfSegments);

	// Go through a loop and read information about each segment
	for(int i = 0; i < noOfSegments; i++)
	{
		// Variables
		double p1x, p1y, p2x, p2y;

		cin >> p1x;

		cin >> p1y;

		cin >> p2x;

		cin >> p2y;

		// Create two new Point objects
		Point point1(p1x, p1y);
		Point point2(p2x, p2y);

		// Create a new LineSegment
		LineSegment segment(point1, point2);

		// Add the line segment to the intervals
		intervals.addLineSegment(segment);
	}

	// Display all of the line segments
	intervals.display();

	// Determine all intersecting lines
	for(int i = 0; i < noOfSegments; i++) {
		// Get the line segment
		LineSegment testSegment = intervals.getSegment(i);

		for (int j = 0; j < noOfSegments; j++) {
			// Do not test against self
			if(i < j) {
				// Get the segment we'll be comparing against
				LineSegment compare = intervals.getSegment(j);

				// See if the two segments intersect
				if(testSegment.itIntersects(compare)) {
					// Get the intersection point
					Point interPt = testSegment.intersectionPoint(compare);

					// Print the place in the array that the intersecting lines are
					cout << "The line segments compared are segments[" << i << "] and segments[" << j << "]: ";
					cout << "Intersection Point :";
					interPt.display();
					cout << endl;
				}
				else if(testSegment.isParallel(compare)) {
					cout << "The line segments compared are segments[" << i << "] and segments[" << j << "]: ";
					cout << "Lines are Parallel" << endl;
				}
				else if(!testSegment.isParallel(compare) && !testSegment.itIntersects(compare)) {
					cout << "The line segments compared are segments[" << i << "] and segments[" << j << "]: ";
					cout << "Not Parallel and not Intersecting" << endl;
				}
			}
		}
	}


	return 0;
}


// Function Declarations
double squareroot(double var) {
	// Variables
	double eps = 1e-10;
	double k = var;
	double l = 0.0, r, mid;

	if (k >= 1) {
		r = k;
	}

	if (k < 1)  {
        r = 1;
	}


	while (l-k/l > eps || l-k/l < -eps) {
		mid = l + (r - l) /2 ;

		if (mid < k / mid) {
			l = mid;
		} else {
			r = mid;
		}
	}

	return l;
}

double roundNum(double var) {
	double value = (int)(var * 100.0);
	return (double)value / 100.0;
}

//Linear Fit
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
    int i, j, k, n;
    cout << "\nEnter the no. of data pairs to be entered:\n"; //To find the size of arrays
    cin >> n;
    double a, b;
    double y[] = {39343, 46205, 37731, 43525, 39891, 56642, 60150, 54445, 64445, 57189, 63218, 55794, 56957, 57081, 61111, 67938, 66029, 83088, 81363, 93940, 91738, 98273, 101302, 113812, 109431, 105582, 116969, 112635, 122391, 121872};
    double x[] = {1.1, 1.3, 1.5, 2, 2.2, 2.9, 3, 3.2, 3.2, 3.7, 3.9, 4, 4, 4.1, 4.5, 4.9, 5.1, 5.3, 5.9, 6, 6.8, 7.1, 7.9, 8.2, 8.7, 9, 9.5, 9.6, 10.3, 10.5};
    // cout << "\nEnter the x-axis values:\n"; //Input x-values
    // for (i = 0; i < n; i++)
    //     cin >> x[i];
    // cout << "\nEnter the y-axis values:\n"; //Input y-values
    // for (i = 0; i < n; i++)
    //     cin >> y[i];
    double xsum = 0, x2sum = 0, ysum = 0, xysum = 0; //variables for sums/sigma of xi,yi,xi^2,xiyi etc
    for (i = 0; i < n; i++)
    {
        xsum = xsum + x[i];           //calculate sigma(xi)
        ysum = ysum + y[i];           //calculate sigma(yi)
        x2sum = x2sum + pow(x[i], 2); //calculate sigma(x^2i)
        xysum = xysum + x[i] * y[i];  //calculate sigma(xi*yi)
    }
    a = (n * xysum - xsum * ysum) / (n * x2sum - xsum * xsum);     //calculate slope
    b = (x2sum * ysum - xsum * xysum) / (x2sum * n - xsum * xsum); //calculate intercept
    double y_fit[n];                                               //an array to store the new fitted values of y
    for (i = 0; i < n; i++)
        y_fit[i] = a * x[i] + b; //to calculate y(fitted) at given x points
    cout << "S.no" << setw(5) << "x" << setw(19) << "y(observed)" << setw(19) << "y(fitted)" << endl;
    cout << "-----------------------------------------------------------------\n";
    for (i = 0; i < n; i++)
        cout << i + 1 << "." << setw(8) << x[i] << setw(15) << y[i] << setw(18) << y_fit[i] << endl; //print a table of x,y(obs.) and y(fit.)
    cout << "\nThe linear fit line is of the form:\n\n"
         << a << "x + " << b << endl; //print the best fit line
    double x1;
    cout << "Enter the value at which the response is to be predicted ";
    cin >> x1;
    cout << "The predicted value is " << a * x1 + b << endl;
    cout << "[ ";
    for (int i = 0; i < 30; i++)
    {
        cout << y[i] << " ,";
    }
    cout << " ]" << endl;
    return 0;
}
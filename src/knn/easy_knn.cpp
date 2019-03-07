#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int val;
    double x, y;
    double dist;
};

bool compare(Point a, Point b)
{
    return (a.dist < b.dist);
}

int test_the_point(Point arr[], int n, int k, Point p)
{
    for (int i = 0; i < n; i++)
        arr[i].dist =
            sqrt((arr[i].x - p.x) * (arr[i].x - p.x) +
                 (arr[i].y - p.y) * (arr[i].y - p.y));

    sort(arr, arr+n, compare);

    int freq1 = 0;
    int freq2 = 0;
    for (int i = 0; i < k; i++)
    {
        if (arr[i].val == 0)
            freq1++;
        else if (arr[i].val == 1)
            freq2++;
    }

    return (freq1 > freq2 ? 0 : 1);
}
int main()
{
    int n=16;
    Point arr[n];
    float  valx[n]={1,2,3,3,1.5,7,6,3.8,3,5.6,4,3.5,2,2,2,1};
    float valy[n]={12,5,3,26,9,2,1,3,10,4,2,8,11,5,9,7};
    for (int x = 0; x< n; x++)
    {
        arr[x].x = valx[x];
        arr[x].y = valy[x];
    }
    int a,b;
    cout << "Enter the checking point - a ";
	cin >> a;
	cout << "Enter the checking point - b ";
	cin >> b;
    Point p;
    p.x = a;
    p.y = b;
    int k;
    cout<< "Enter the K ";
    cin >> k;
    printf ("The result "
            " is %d.\n", test_the_point(arr, n, k, p));
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

// Function to calculate the value of y
// y = poly[0] + x*poly[1] + x^2*poly[2] + ...
int calculate_Y(int x, vector<int> &poly)
{
    int y = 0;
    int temp = 1;
    for (auto coeff : poly)
    {
        y = (y + (coeff * temp)) % 997; // Include modulus for safety
        temp = (temp * x) % 997;        // Include modulus for safety
    }
    return y;
}

// Function to perform the secret sharing algorithm and encode the given secret
void secret_sharing(int S, vector<pair<int, int>> &points, int N, int K)
{
    vector<int> poly(K);
    poly[0] = S;

    for (int j = 1; j < K; ++j)
    {
        int p = 0;
        while (p == 0)
            p = (rand() % 997);
        poly[j] = p;
    }

    for (int j = 1; j <= N; ++j)
    {
        int x = j;
        int y = calculate_Y(x, poly);
        points[j - 1] = {x, y};
    }
}

// This structure is used for fraction part handling multiplication and addition of fraction
struct fraction
{
    int num, den;
    fraction(int n, int d) : num(n), den(d) {}

    void reduce_fraction()
    {
        int gcd = __gcd(num, den);
        num /= gcd;
        den /= gcd;
    }

    fraction operator*(fraction f)
    {
        fraction temp(num * f.num, den * f.den);
        temp.reduce_fraction();
        return temp;
    }

    fraction operator+(fraction f)
    {
        fraction temp(num * f.den + den * f.num, den * f.den);
        temp.reduce_fraction();
        return temp;
    }
};

// Function to generate the secret back from the given points
int Generate_Secret(int x[], int y[], int M)
{
    fraction ans(0, 1);
    for (int i = 0; i < M; ++i)
    {
        fraction l(y[i], 1);
        for (int j = 0; j < M; ++j)
        {
            if (i != j)
            {
                fraction temp(-x[j], x[i] - x[j]);
                l = l * temp;
            }
        }
        ans = ans + l;
    }
    return ans.num % 997; // Return the secret modulo 997
}

// Function to encode and decode the given secret
void operation(int S, int N, int K)
{
    vector<pair<int, int>> points(N);
    secret_sharing(S, points, N, K);

    cout << "Secret is divided into " << N << " Parts:\n";
    for (int i = 0; i < N; ++i)
    {
        cout << "Point (" << points[i].first << ", " << points[i].second << ")\n";
    }

    cout << "We can generate the Secret from any " << K << " Parts.\n";

    int M = K; // Use K points to retrieve the secret
    int *x = new int[M];
    int *y = new int[M];

    // Get the first K points to retrieve the secret
    for (int i = 0; i < M; ++i)
    {
        x[i] = points[i].first;
        y[i] = points[i].second;
    }

    cout << "Our Secret Code is: " << Generate_Secret(x, y, M) << endl;

    // Clean up
    delete[] x;
    delete[] y;
}

// Driver Code
int main()
{
    int S = 65; // Secret to share
    int N = 4;  // Total number of points
    int K = 2;  // Minimum points required to reconstruct the secret

    operation(S, N, K);
    return 0;
}

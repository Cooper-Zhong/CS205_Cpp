#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX_TRIANGLES = 100;
const double tolerance = 0.1;

struct Triangle
{
    // To be completed
    double side1;
    double side2;
    double side3;
};

struct TriangleDictionary
{
    Triangle triangles[MAX_TRIANGLES];
    int triangle_count;
};

double getSide3(double side1, double side2, double angle)
{
    return sqrt(side1 * side1 + side2 * side2 - 2 * side1 * side2 * cos(angle * M_PI / 180));
}

bool isequal(double a, double b)
{
    return fabs(a - b) <= tolerance;
}

void addTriangle(TriangleDictionary *dict, double side1, double side2, double angle)
{
    // To be completed
    // -> is the same as (*dict).triangle_count, access the member through pointer
    // check if the sum of the two sides is greater than the third side
    double side3 = getSide3(side1, side2, angle);
    if (side1 + side2 <= side3 || side1 + side3 <= side2 || side2 + side3 <= side1)
    {
        return;
    }
    dict->triangles[dict->triangle_count] = Triangle();
    dict->triangles[dict->triangle_count].side1 = side1;
    dict->triangles[dict->triangle_count].side2 = side2;
    dict->triangles[dict->triangle_count].side3 = side3;
    dict->triangle_count++;
}

bool isSimilar(const Triangle &triangle, double side1, double side2, double side3)
{
    // To be completed
    // sort the sides
    double t1[] = {side1, side2, side3};
    double t2[] = {triangle.side1, triangle.side2, triangle.side3};
    sort(t2, t2 + 3);
    sort(t1, t1 + 3);
    // check if the ratio of the sides are the same
    bool sideRatio = isequal(t1[0] / t2[0], t1[1] / t2[1]) && isequal(t1[1] / t2[1], t1[2] / t2[2]) && isequal(t1[2] / t2[2], t1[0] / t2[0]);
    return sideRatio;
}

bool searchSimilar(TriangleDictionary *dict, double side1, double side2, double angle)
{
    double side3 = sqrt(side1 * side1 + side2 * side2 - 2 * side1 * side2 * cos(angle * M_PI / 180));
    for (int i = 0; i < dict->triangle_count; ++i)
    {
        if (isSimilar(dict->triangles[i], side1, side2, side3))
        {
            return true;
        }
    }
    return false;
}

int main()
{
    int n;
    // printf("Enter the number of operations (n): ");
    scanf("%d", &n);

    char **actions = (char **)malloc(n * sizeof(char *));
    double **parameters = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < n; ++i)
    {
        actions[i] = (char *)malloc(15 * sizeof(char));
        parameters[i] = (double *)malloc(3 * sizeof(double));
    }

    for (int i = 0; i < n; ++i)
    {
        // printf("Enter operation #%d: ", i + 1);
        scanf("%s", actions[i]);
        if (strcmp(actions[i], "addTriangle") == 0 || strcmp(actions[i], "searchSimilar") == 0)
        {
            scanf("%lf %lf %lf", &parameters[i][0], &parameters[i][1], &parameters[i][2]);
        }
    }

    TriangleDictionary triangleDictionary;
    triangleDictionary.triangle_count = 0;

    for (int i = 0; i < n; ++i)
    {
        if (strcmp(actions[i], "TriangleDictionary") == 0)
        {
            // Do nothing
        }
        else if (strcmp(actions[i], "addTriangle") == 0)
        {
            addTriangle(&triangleDictionary, parameters[i][0], parameters[i][1], parameters[i][2]);
        }
        else if (strcmp(actions[i], "searchSimilar") == 0)
        {
            int result = searchSimilar(&triangleDictionary, parameters[i][0], parameters[i][1], parameters[i][2]);
            printf(result ? "true\n" : "false\n");
        }
    }
}

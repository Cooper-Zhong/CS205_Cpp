//#include <iostream>
//#include <cmath>
//
//using namespace std;
//
//const int MAX_TRIANGLES = 100;
//
//struct Triangle {
//    // To be completed
//};
//
//struct TriangleDictionary {
//    Triangle triangles[MAX_TRIANGLES];
//    int triangle_count;
//};
//
//void addTriangle(TriangleDictionary* dict, double side1, double side2, double angle) {
//    // To be completed
//}
//
//bool isSimilar(const Triangle& triangle, double side1, double side2, double side3) {
//// To be completed
//}
//
//bool searchSimilar(TriangleDictionary* dict, double side1, double side2, double angle) {
//    double side3 = sqrt(side1 * side1 + side2 * side2 - 2 * side1 * side2 * cos(angle * M_PI / 180));
//    for (int i = 0; i < dict->triangle_count; ++i) {
//        if (isSimilar(dict->triangles[i], side1, side2, side3)) {
//            return true;
//        }
//    }
//    return false;
//}
//
//int main() {
//    int n;
//    // printf("Enter the number of operations (n): ");
//    scanf("%d", &n);
//
//    char** actions = (char**)malloc(n * sizeof(char*));
//    double** parameters = (double**)malloc(n * sizeof(double*));
//
//    for (int i = 0; i < n; ++i) {
//        actions[i] = (char*)malloc(15 * sizeof(char));
//        parameters[i] = (double*)malloc(3 * sizeof(double));
//    }
//
//    for (int i = 0; i < n; ++i) {
//        // printf("Enter operation #%d: ", i + 1);
//        scanf("%s", actions[i]);
//        if (strcmp(actions[i], "addTriangle") == 0 || strcmp(actions[i], "searchSimilar") == 0) {
//            scanf("%lf %lf %lf", &parameters[i][0], &parameters[i][1], &parameters[i][2]);
//        }
//    }
//
//    TriangleDictionary triangleDictionary;
//    triangleDictionary.triangles = NULL;
//    triangleDictionary.triangle_count = 0;
//
//    for (int i = 0; i < n; ++i) {
//        if (strcmp(actions[i], "TriangleDictionary") == 0) {
//            // Do nothing
//        } else if (strcmp(actions[i], "addTriangle") == 0) {
//            addTriangle(&triangleDictionary, parameters[i][0], parameters[i][1], parameters[i][2]);
//        } else if (strcmp(actions[i], "searchSimilar") == 0) {
//            int result = searchSimilar(&triangleDictionary, parameters[i][0], parameters[i][1], parameters[i][2]);
//            printf(result ? "true\n" : "false\n");
//        }
//    }
//}

#include <stdio.h>
#include <stdlib.h>

// 定义多项式的结构体
typedef struct {
    double coefficient;
    double exponent;
} Polynomial;

// 函数声明
void readPolynomial(Polynomial *poly, int size);
void savePolynomialToFile(Polynomial *poly, int size, char *filename);
void addPolynomials(Polynomial *poly1, int size1, Polynomial *poly2, int size2, Polynomial **result, int *resultSize);
void subtractPolynomials(Polynomial *poly1, int size1, Polynomial *poly2, int size2, Polynomial **result, int *resultSize);

int main() {
    int size1, size2, resultSize;
    Polynomial *poly1, *poly2, *result;
    char filename[20];

    // 输入第一个多项式
    printf("请输入第一个多项式的项数：");
    scanf("%d", &size1);
    poly1 = (Polynomial *) malloc(size1 * sizeof(Polynomial));
    printf("请输入第一个多项式的每项的系数和指数：\n");
    readPolynomial(poly1, size1);

    // 输入第二个多项式
    printf("请输入第二个多项式的项数：");
    scanf("%d", &size2);
    poly2 = (Polynomial *) malloc(size2 * sizeof(Polynomial));
    printf("请输入第二个多项式的每项的系数和指数：\n");
    readPolynomial(poly2, size2);

    // 将多项式保存到文件中
    printf("请输入要保存多项式的文件名：");
    scanf("%s", filename);
    savePolynomialToFile(poly1, size1, filename);
    savePolynomialToFile(poly2, size2, filename);

    // 计算两个多项式的和
    addPolynomials(poly1, size1, poly2, size2, &result, &resultSize);
    printf("\n加法结果：\n");
    for (int i = 0; i < resultSize; i++) {
        printf("%.2fx^%.2f ", result[i].coefficient, result[i].exponent);
        if (i < resultSize - 1)
            printf("+ ");
    }
    printf("\n");

    // 计算两个多项式的差
    subtractPolynomials(poly1, size1, poly2, size2, &result, &resultSize);
    printf("\n减法结果：\n");
    for (int i = 0; i < resultSize; i++) {
        printf("%.2fx^%.2f ", result[i].coefficient, result[i].exponent);
        if (i < resultSize - 1&&result[i+1].coefficient>=0)
            printf("+ ");
    }
    printf("\n");

    // 释放内存
    free(poly1);
    free(poly2);
    free(result);

    return 0;
}

// 读取多项式的系数和指数
void readPolynomial(Polynomial *poly, int size) {
    for (int i = 0; i < size; i++) {
        printf("第%d项：\n", i + 1);
        printf("系数：");
        scanf("%lf", &(poly[i].coefficient));
        printf("指数：");
        scanf("%lf", &(poly[i].exponent));
    }
}

// 将多项式保存到文件中
void savePolynomialToFile(Polynomial *poly, int size, char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("打开文件失败。\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%.2fx^%.2f ", poly[i].coefficient, poly[i].exponent);
        if (i < size - 1)
            fprintf(file, "+ ");
    }
    fprintf(file, "\n");

    fclose(file);
}

// 计算两个多项式的和
void addPolynomials(Polynomial *poly1, int size1, Polynomial *poly2, int size2, Polynomial **result, int *resultSize) {
    int maxSize = size1 + size2;
    *result = (Polynomial *) malloc(maxSize * sizeof(Polynomial));
    *resultSize = 0;

    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (poly1[i].exponent > poly2[j].exponent) {
            (*result)[k++] = poly1[i++];(*resultSize)++;
            //printf("%lf\n",poly1[i].exponent);
        } else if (poly1[i].exponent < poly2[j].exponent) {
            (*result)[k++] = poly2[j++];(*resultSize)++;
            //printf("%lf\n",poly2[i].exponent);
        } else {
            (*result)[k].coefficient = poly1[i].coefficient + poly2[j].coefficient;
            (*result)[k].exponent = poly1[i].exponent;
            i++;
            j++;
            k++;
            (*resultSize)++;
        }
    }

    while (i < size1) {
        (*result)[k++] = poly1[i++];
        (*resultSize)++;
    }

    while (j < size2) {
        (*result)[k++] = poly2[j++];
        (*resultSize)++;
    }
}

// 计算两个多项式的差
void subtractPolynomials(Polynomial *poly1, int size1, Polynomial *poly2, int size2, Polynomial **result, int *resultSize) {
    int maxSize = size1 + size2;
    *result = (Polynomial *) malloc(maxSize * sizeof(Polynomial));
    *resultSize = 0;

    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (poly1[i].exponent > poly2[j].exponent) {
            (*result)[k++] = poly1[i++];
            (*resultSize)++;
        } else if (poly1[i].exponent < poly2[j].exponent) {
            (*result)[k].coefficient = -poly2[j].coefficient;
            (*result)[k].exponent = poly2[j].exponent;
            j++;
            k++;
            (*resultSize)++;
        } else {
            (*result)[k].coefficient = poly1[i].coefficient - poly2[j].coefficient;
            (*result)[k].exponent = poly1[i].exponent;
            i++;
            j++;
            k++;
            (*resultSize)++;
        }
    }

    while (i < size1) {
        (*result)[k++] = poly1[i++];
        (*resultSize)++;
    }

    while (j < size2) {
        (*result)[k].coefficient = -poly2[j].coefficient;
        (*result)[k].exponent = poly2[j].exponent;
        j++;
        k++;
        (*resultSize)++;
    }
}


#include <stdio.h>
#include <stdlib.h>

// �������ʽ�Ľṹ��
typedef struct {
    double coefficient;
    double exponent;
} Polynomial;

// ��������
void readPolynomial(Polynomial *poly, int size);
void savePolynomialToFile(Polynomial *poly, int size, char *filename);
void addPolynomials(Polynomial *poly1, int size1, Polynomial *poly2, int size2, Polynomial **result, int *resultSize);
void subtractPolynomials(Polynomial *poly1, int size1, Polynomial *poly2, int size2, Polynomial **result, int *resultSize);

int main() {
    int size1, size2, resultSize;
    Polynomial *poly1, *poly2, *result;
    char filename[20];

    // �����һ������ʽ
    printf("�������һ������ʽ��������");
    scanf("%d", &size1);
    poly1 = (Polynomial *) malloc(size1 * sizeof(Polynomial));
    printf("�������һ������ʽ��ÿ���ϵ����ָ����\n");
    readPolynomial(poly1, size1);

    // ����ڶ�������ʽ
    printf("������ڶ�������ʽ��������");
    scanf("%d", &size2);
    poly2 = (Polynomial *) malloc(size2 * sizeof(Polynomial));
    printf("������ڶ�������ʽ��ÿ���ϵ����ָ����\n");
    readPolynomial(poly2, size2);

    // ������ʽ���浽�ļ���
    printf("������Ҫ�������ʽ���ļ�����");
    scanf("%s", filename);
    savePolynomialToFile(poly1, size1, filename);
    savePolynomialToFile(poly2, size2, filename);

    // ������������ʽ�ĺ�
    addPolynomials(poly1, size1, poly2, size2, &result, &resultSize);
    printf("\n�ӷ������\n");
    for (int i = 0; i < resultSize; i++) {
        printf("%.2fx^%.2f ", result[i].coefficient, result[i].exponent);
        if (i < resultSize - 1)
            printf("+ ");
    }
    printf("\n");

    // ������������ʽ�Ĳ�
    subtractPolynomials(poly1, size1, poly2, size2, &result, &resultSize);
    printf("\n���������\n");
    for (int i = 0; i < resultSize; i++) {
        printf("%.2fx^%.2f ", result[i].coefficient, result[i].exponent);
        if (i < resultSize - 1&&result[i+1].coefficient>=0)
            printf("+ ");
    }
    printf("\n");

    // �ͷ��ڴ�
    free(poly1);
    free(poly2);
    free(result);

    return 0;
}

// ��ȡ����ʽ��ϵ����ָ��
void readPolynomial(Polynomial *poly, int size) {
    for (int i = 0; i < size; i++) {
        printf("��%d�\n", i + 1);
        printf("ϵ����");
        scanf("%lf", &(poly[i].coefficient));
        printf("ָ����");
        scanf("%lf", &(poly[i].exponent));
    }
}

// ������ʽ���浽�ļ���
void savePolynomialToFile(Polynomial *poly, int size, char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("���ļ�ʧ�ܡ�\n");
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

// ������������ʽ�ĺ�
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

// ������������ʽ�Ĳ�
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


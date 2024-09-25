#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 假設這是 layer 結構體的定義
typedef struct
{
    int binary;
    int numload;
    int n;
    int c;
    int groups;
    int size;
    float *biases;
    int batch_normalize;
    int dontloadscales;
    float *scales;
    float *rolling_mean;
    float *rolling_variance;
    float *weights;
    int flipped;
} layer;

// 假設這是 load_convolutional_weights 函式的定義
void load_convolutional_weights(layer l, FILE *fp);

int main()
{
    // 初始化 layer 變數
    layer l;
    l.binary = 0;
    l.numload = 0;
    l.n = 64;
    l.c = 3;
    l.groups = 1;
    l.size = 3;
    l.biases = (float *)malloc(l.n * sizeof(float));
    l.batch_normalize = 1;
    l.dontloadscales = 0;
    l.scales = (float *)malloc(l.n * sizeof(float));
    l.rolling_mean = (float *)malloc(l.n * sizeof(float));
    l.rolling_variance = (float *)malloc(l.n * sizeof(float));
    l.weights = (float *)malloc((l.c / l.groups * l.n * l.size * l.size) * sizeof(float));
    l.flipped = 0;

    // 打開權重檔案
    FILE *fp = fopen("weights_file.bin", "rb");
    if (!fp)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // 調用 load_convolutional_weights 函式
    load_convolutional_weights(l, fp);

    // 關閉檔案
    fclose(fp);

    // 釋放分配的記憶體
    free(l.biases);
    free(l.scales);
    free(l.rolling_mean);
    free(l.rolling_variance);
    free(l.weights);

    return 0;
}
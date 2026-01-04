#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXTRIX_TYPE float
#define COLS_SIZE 1024
#define ROWS_SIZE 1024

typedef struct maxtrix
{
    uint32_t cols, rows;
    MAXTRIX_TYPE *data;
} maxtrix_t;


maxtrix_t maxtrix_create(uint32_t cols, uint32_t rows);
/* ~2700 ms*/
MAXTRIX_TYPE maxtrix_sum_optimize(const maxtrix_t *input);
/* ~5000 ms*/
MAXTRIX_TYPE maxtrix_sum_no_optimize(const maxtrix_t *input);

void maxtrix_mul(maxtrix_t *output, const maxtrix_t *input_1, const maxtrix_t *input_2);

int main() 
{

    maxtrix_t a = maxtrix_create(ROWS_SIZE, COLS_SIZE);
    maxtrix_t b = maxtrix_create(ROWS_SIZE, COLS_SIZE);
    maxtrix_t c = maxtrix_create(ROWS_SIZE, COLS_SIZE);

    for (size_t i = 0; i < ROWS_SIZE*COLS_SIZE; i++)
    {
        a.data[i] = i/(float)100;
        b.data[i] = i/(float)100;
    }

    float sum = 0;
    for (size_t i = 0; i < 10; i++)
    {
        //sum += maxtrix_sum_optimize(&a);
        maxtrix_mul(&c, &a, &b);
    }
    printf("%f\n", sum);

    free(a.data);
}

maxtrix_t maxtrix_create(uint32_t cols, uint32_t rows)
{
    maxtrix_t maxtrix;
    maxtrix.cols = cols;
    maxtrix.rows = rows;
    if (cols == 0 && rows == 0)
    {
        maxtrix.data = NULL;
        return maxtrix;
    }

    maxtrix.data = (MAXTRIX_TYPE *)calloc(cols * rows, sizeof(MAXTRIX_TYPE));
    return maxtrix;
}


MAXTRIX_TYPE maxtrix_sum_optimize(const maxtrix_t *input)
{
    MAXTRIX_TYPE sum = 0;

    if (input == NULL)
        return sum;
    
    for(uint32_t row = 0; row < input->rows; row++)
    {
        for (uint32_t col = 0; col < input->cols; col++)
        {
            sum += input->data[col + row*input->cols];            
        }
    }
}


MAXTRIX_TYPE maxtrix_sum_no_optimize(const maxtrix_t *input)
{
    MAXTRIX_TYPE sum = 0;

    if (input == NULL)
        return sum;

    for (uint32_t col = 0; col < input->cols; col++)
    {
        for(uint32_t row = 0; row < input->rows; row++)
        {
            sum += input->data[col + row*input->cols];            
        }
    }
}

void maxtrix_mul(maxtrix_t *output, const maxtrix_t *input_1, const maxtrix_t *input_2)
{
    if((input_1->rows != input_2->cols) || (input_1->cols != input_2->rows))
        return;

    output->rows = input_1->rows;
    output->cols = input_2->cols;

    memset(output->data, 0, output->cols*output->rows*sizeof(MAXTRIX_TYPE));

    for (size_t row = 0; row < output->rows; row++)
    {
        for (size_t col = 0; col < output->cols; col++)
        {
           for(size_t col_1 = 0; col_1 < input_1->cols; col_1++)
           {
            output->data[col + row*output->cols] += input_1->data[col_1 + row*input_1->cols]*input_2->data[col + col_1*input_2->cols];
           }
        }
    }
}
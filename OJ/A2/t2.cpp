// PREPEND BEGIN
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

struct Data
{
    int *entry;
    size_t row, col;
    size_t ref_cnt;

    Data(size_t row, size_t col) : row(row), col(col), ref_cnt(0)
    {
        entry = new int[row * col]{};
    }

    ~Data()
    {
        delete[] entry;
    }
};

struct Matrix
{
    Data *data;      // the ptr pointing to the entries
    size_t start;    // the starting index of ROI
    size_t row, col; // the shape of ROI

    Matrix() : data(nullptr), start(0), row(0), col(0) {}

    ~Matrix()
    {
        if (!data)
            return;
        if (!--data->ref_cnt)
            delete data;
    }
};

void print_matrix(Matrix &mat)
{
    for (size_t r = 0; r < mat.row; r++)
    {
        size_t head = mat.start + r * mat.data->col;
        for (size_t c = 0; c < mat.col; c++)
            cout << mat.data->entry[head + c] << ' ';
        cout << '\n';
    }
    cout << endl;
}
// PREPEND END

// TEMPLATE BEGIN
void unload_data(Matrix &mat)
{
    // TODO
    // Noted that `mat.data` could be `nullptr` here
    if (mat.data == nullptr)
        return;
    mat.data->ref_cnt--;
    if (mat.data->ref_cnt == 0)
    {
        delete mat.data;
    }
    mat.data = nullptr;
    mat.start = 0;
    mat.row = 0;
    mat.col = 0;
}

void load_data(Matrix &mat, Data *data, size_t start, size_t row, size_t col)
{
    // TODO
    unload_data(mat);
    mat.data = data;
    mat.start = start;
    mat.row = row;
    mat.col = col;
    if (data != nullptr)
        data->ref_cnt++;
}

void shallow_copy(Matrix &dest, Matrix &src)
{
    // TODO
    unload_data(dest);
    load_data(dest, src.data, src.start, src.row, src.col);
}

void deep_copy(Matrix &dest, Matrix &src)
{
    // TODO
    unload_data(dest);
    if (src.data == nullptr)
        return;

    Data *data = new Data(src.row, src.col); // new data
    for (size_t i = 0; i < src.row; i++)
    {
        size_t head = src.start + i * src.data->col; // ROI
        for (size_t j = 0; j < src.col; j++)
        {
            data->entry[head + j] = src.data->entry[head + j];
        }
    }
    load_data(dest, data, src.start, src.row, src.col);
}

bool equal_matrix(Matrix &a, Matrix &b)
{
    // TODO
    if (a.row != b.row || a.col != b.col)
        return false;
    if (a.data == b.data && a.start == b.start) // point to the same data
        return true;
    if (a.data == nullptr || b.data == nullptr)
        return false;
    for (size_t i = 0; i < a.row; i++)
    {
        int head1 = a.start + i * a.data->col;
        int head2 = b.start + i * b.data->col;
        for (size_t j = 0; j < a.col; j++)
        {
            if (a.data->entry[head1 + j] != b.data->entry[head2 + j])
                return false;
        }
    }
    return true;
}

void add_matrix(Matrix &dest, Matrix &a, Matrix &b)
{
    // TODO
    unload_data(dest);
    Data *data = new Data(a.row, a.col);

    for (size_t i = 0; i < a.row; i++)
    {
        size_t head1 = a.start + i * a.data->col;
        size_t head2 = b.start + i * b.data->col;
        for (size_t j = 0; j < a.col; j++)
        {
            data->entry[i * a.col + j] = a.data->entry[head1 + j] + b.data->entry[head2 + j];
        }
    }
    load_data(dest, data, 0, a.row, a.col);
}

void minus_matrix(Matrix &dest, Matrix &a, Matrix &b)
{
    // TODO
    unload_data(dest);
    Data *data = new Data(a.row, a.col);

    for (size_t i = 0; i < a.row; i++)
    {
        size_t head1 = a.start + i * a.data->col;
        size_t head2 = b.start + i * b.data->col;
        for (size_t j = 0; j < a.col; j++)
        {
            data->entry[i * a.col + j] = a.data->entry[head1 + j] - b.data->entry[head2 + j];
        }
    }
    load_data(dest, data, 0, a.row, a.col);
}

void multiply_matrix(Matrix &dest, Matrix &a, Matrix &b)
{
    // TODO
    unload_data(dest);
    Data *data = new Data(a.row, b.col);

    for (size_t i = 0; i < a.row; i++)
    {
        size_t head1 = a.start + i * a.data->col;

        for (size_t j = 0; j < b.col; j++)
        {
            int sum = 0;
            for (size_t k = 0; k < a.col; k++)
            {
                size_t head2 = b.start + k * b.data->col;
                sum += a.data->entry[head1 + k] * b.data->entry[head2 + j];
            }
            data->entry[i * data->col + j] = sum;
        }
    }
    load_data(dest, data, 0, a.row, b.col);
}
// TEMPLATE END

// APPEND BEGIN
void test()
{
    // Sample code on how to use your library
    Data *da = new Data(3, 2), *db = new Data(2, 3);
    for (size_t i = 0; i < 6; i++)
        da->entry[i] = db->entry[i] = i;

    Matrix a, b, c;
    load_data(b, db, 0, 2, 3);
    print_matrix(a);
    /*
        0 1
        2 3
        4 5
    */
    print_matrix(b);
    /*
        0 1 2
        3 4 5
    */

    multiply_matrix(c, a, b);
    print_matrix(c);
    /*
        3 4 5
        9 14 19
        15 24 33
    */

    Matrix d, e, f, g;
    shallow_copy(d, c); // d, c -> (the same) data
    deep_copy(e, c);    // e->data have the exactly same content with c->ROI(data) with e.data.shape = c.ROI.shape
                        // but their addresses are different and ref_cnts possibly differ
    load_data(f, c.data, 1, 3, 2);
    print_matrix(f);
    /*
        4 5
        14 19
        24 33
    */
    add_matrix(b, a, f); // notice that the original b.data->ref_cnt becomes 0 and should be deleted
    print_matrix(b);
    /*
        4 6
        16 22
        28 38
    */

    cout << a.data->ref_cnt << ' ' << b.data->ref_cnt << ' '
         << c.data->ref_cnt << ' ' << d.data->ref_cnt << ' '
         << e.data->ref_cnt << ' ' << f.data->ref_cnt << endl;
    /*
        1 1 3 3 1 3
    */
}

int main()
{
    test();
    return 0;
}
// APPEND END
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct PandoraBox
{
    int item_count; // Number of items stored in the PandoraBox.
    int *item_size; // Array of item sizes in bytes.
    int total_size; // Total size of items in bytes.
    void *data;     // A type-agnostic pointer to store data.
} Panbox;

/*
A PandoraBox capable of storing various data types within a continuous memory space.

- item_count: Number of items stored in this box.
- item_size: An array of integers; item_size[i] represents the size (in bytes) of the i-th item in the box.
- data: A type-agnostic pointer, enabling interpretation of different data types by reading segments with varying
lengths.
*/

/*=+=+=+=+=+=+=+=+=+=+=Your code starts from here=+=+=+=+=+=+=+=+=+=+=*/

void *mycpy(void *dst, const void *src, size_t size)
{
    unsigned char *d = (unsigned char *)dst; // regard address as a unsigned char pointer
    const unsigned char *s = (const unsigned char *)src;

    for (size_t i = 0; i < size; i++)
        d[i] = s[i]; // copy byte by byte

    return dst;
}
/*
Function: See memcpy in <string.h>

Notes:
- It is not a must to implement this function, but with it you can implement the following functions more easily.
*/

void *myset(void *dst, int n, size_t size)
{
    unsigned char *d = (unsigned char *)dst; // regard address as a unsigned char pointer

    for (size_t i = 0; i < size; i++)
        d[i] = n;

    return dst;
}
/*
Function: See memset in <string.h>

Notes:
- It is not a must to implement this function, but with it you can implement the following functions more easily.
*/

Panbox *create(int item_count, int item_size[])
{
    if (item_count < 0)
        return NULL;
    if (item_count > 0 && item_size == NULL)
        return NULL;

    Panbox *panbox = (Panbox *)malloc(sizeof(Panbox));
    if (panbox == NULL) // allocate failed
        return NULL;

    int sum = 0;
    // total size
    for (size_t i = 0; i < item_count; i++)
    {
        if (item_size[i] <= 0) // size should be positive
        {
            free(panbox);
            return NULL;
        }
        sum += item_size[i];
    }
    // allocate memory for item_size
    panbox->item_size = (int *)malloc(item_count * sizeof(int));
    if (panbox->item_size == NULL) // allocate failed
    {
        free(panbox);
        return NULL;
    }

    mycpy(panbox->item_size, item_size, item_count * sizeof(int)); // copy item_size to panbox->item_size

    panbox->item_count = item_count;
    panbox->total_size = sum;
    // allocate memory for data
    panbox->data = (void *)malloc(sum);
    if (panbox->data == NULL) // allocate failed
    {
        free(panbox->item_size);
        free(panbox);
        return NULL;
    }
    myset(panbox->data, 0, sum); // set all data to 0
    return panbox;
}
/*
Function: Create an empty PandoraBox with specified item counts and their respective sizes.

Parameters:
- item_count: The number of items to be stored in the PandoraBox.
- item_size: An array specifying the size (in bytes) of each item.

Returns:
A pointer to the created PandoraBox.

Note:
- You CAN create a Panbox with no initial items, i.e., item_count=0 and item_size=NULL.
- However, negative item_count is not supported, and item_size should not be NULL when item_count is non-zero.
- The size of any item should be positive.
- Make sure that the memory newly allocated is filled with 0s.
- You should return NULL immediately if any failure happens.
- Good news: GuTao guarantees that [item_size, item_size+item_count-1] is allocated in advance, unless item_size is NULL.
*/

void append(Panbox *panbox, void *value, int width)
{
    if (panbox == NULL || value == NULL || width <= 0)
        return;
    panbox->item_size = (int *)realloc(panbox->item_size, (panbox->item_count + 1) * sizeof(int)); // add one more item (int)
    if (panbox->item_size == NULL)                                                                 // allocate failed
        return;
    panbox->item_size[panbox->item_count] = width;                            // the size of the new item
    panbox->data = (void *)realloc(panbox->data, panbox->total_size + width); // more space for data
    if (panbox->data == NULL)                                                 // allocate failed
        return;
    // append data to the end of the box
    unsigned char *target = (unsigned char *)panbox->data;
    target += panbox->total_size;
    mycpy(target, value, width);
    panbox->total_size += width;
    panbox->item_count++;
}
/*
Function: Extend the memory of the PandoraBox to append an item.

Parameters:
- panbox: A pointer to the PandoraBox.
- value: A pointer to the data to be added to the PandoraBox.
- width: The size of the data in value (in bytes).

Note:
- You should not append this item if any failure happens.
- Good news: GuTao guarantees that [value, value+width-1] is allocated in advance, unless value is NULL.
*/

void write(Panbox *panbox, int item_id, void *value, int width)
{
    if (item_id < 0 || item_id >= panbox->item_count || value == NULL || width <= 0)
        return;
    if (width > panbox->item_size[item_id]) // the item size cannot hold all data in value
        return;
    // calculate the address of the item
    unsigned char *addr = (unsigned char *)panbox->data; // unit: byte
    int offset = 0;
    for (size_t i = 0; i < item_id; i++)
    {
        offset += panbox->item_size[i];
    }
    addr += offset;
    // write data
    mycpy(addr, value, width); // at lower address

    int diff = panbox->item_size[item_id] - width;

    // padded
    if (diff > 0)
    {
        unsigned char padding = 0xFF;
        padding = ((unsigned char *)value)[width - 1] & 0x80; // highest bit
        myset(addr + width, padding, diff);
    }
}
/*
Function: COPY the data stored in 'value' into the segment of the item with index item_id in the PandoraBox.

Parameters:
- panbox: A pointer to the PandoraBox.
- item_id: The index of the item in the PandoraBox where data will be written.
- value: A pointer to the data that needs to be written to the PandoraBox.
- width: The size of the data in value (in bytes).

Notes:
- If 'item_id' is out of valid bounds, the data won't be written.
- If the item size cannot hold all data in value, the data won't be written.
- If the width of value is smaller than the item size, the data will be placed in the lower address and padded with the highest bit.
- Example: inserting a 1-byte value into a 2-byte item: (0x7f -> 0x007f), (0xf7 -> 0xfff7).
- The item_size should not change in this function.
- You should not write the item if any failure happens.
- Good news: GuTao guarantees that [value, value+width-1] is allocated in advance, unless value is NULL.
*/

void *read(Panbox *panbox, int item_id)
{
    if (item_id < 0 || item_id >= panbox->item_count)
        return NULL;
    // find address
    unsigned char *addr = (unsigned char *)panbox->data; // unit: byte
    int offset = 0;
    for (size_t i = 0; i < item_id; i++)
    {
        offset += panbox->item_size[i];
    }
    addr += offset;
    // copy data
    void *data = (void *)malloc(panbox->item_size[item_id]);
    if (data == NULL) // allocate failed
        return NULL;
    mycpy(data, addr, panbox->item_size[item_id]);
    return data;
}
/*
Function: COPY the item with index item_id from the PandoraBox into a newly allocated memory, and return a pointer to
this memory.

Parameters:
- panbox: A pointer to the PandoraBox.
- item_id: The index of the item in the PandoraBox that should be read.

Returns:
A pointer to the newly allocated memory containing a copy of the specified item.

Notes:
- You should return NULL immediately if any failure happens.
*/

void destroy(Panbox *panbox)
{
    if (panbox == NULL)
        return;
    if (panbox->data != NULL)
        free(panbox->data);
    if (panbox->item_size != NULL)
        free(panbox->item_size);
    free(panbox);
    panbox = NULL;
}
/*
Function: Deallocate the memory associated with the PandoraBox and its data.

Parameters:
- panbox: A pointer to the PandoraBox that should be destroyed.

Notes:
- This function should be used when the PandoraBox is no longer needed to prevent memory leak.
- You should check before freeing a pointer.
*/

void printc(void *value, int width)
{
    if (value == NULL || width <= 0)
        return;
    // print data
    unsigned char *data = (unsigned char *)value;
    for (size_t i = 0; i < width; i++)
    {
        unsigned char temp = data[i];
        if (temp >= 33 || temp == 127) // ignore
            continue;
        if (temp >= 128)
        {
            // negative
            printf("- ");
            continue;
        }
        printf("%c ", (char)temp);
    }
    printf("\n");
}
/*
Function: Print every 1 byte (char) in [value, value+width-1] as a character, split by a space.

Notes:
- Good news: GuTao guarantees that [value, value+width-1] is allocated in advance, unless value is NULL.
- If the value of the byte is in [0, 32] or equals to 127(Del), do not print anything(they are special characters).
- e.g., for an empty box with all 0, the destroy of this box will invoke printc(), but should not print anything.
- If the value of the byte is negative, print '-' instead.
- You should return immediately if any failure happens.
- Please print a `\n` before returning, unless you print nothing in this function.
*/

void printx(void *value, int width)
{
    if (value == NULL || width <= 0)
        return;

    unsigned char *data = (unsigned char *)value;
    printf("0x");
    for (size_t i = 0; i < width; i++)
    {
        unsigned char temp = data[i];
    }
}
/*
Function: Print the value in [value, value+width-1] as a single hexadecimal, in format of 0x12345678.

Notes:
- Good news: GuTao guarantees that [value, value+width-1] is allocated in advance, unless value is NULL.
- You should return immediately if any failure happens.
- If the highest byte is less than 0x10, please output a leading 0, e.g., 0x0514.
- Leading zeros are OK, if *(value) = 0x000f, width = 2, then print 0x000f. (print even number of characters)
- Please print a `\n` before returning, unless you print nothing in this function.
*/

void hex2byte(void *dst, char *hex)
{
    return;
}
/*
Function: For the given hex string "0x12345678", write 0x12345678 into dst.

Notes:
- The length of hex might be ODD, make sure to put all data into dst. For example, "0xfff"(12 bits) should be stored
using 2 bytes as 0x0fff(different from write(), just add a padding 0 here).
- You should return immediately if any failure happens.
*/

/*=+=+=+=+=+=+=+=+=+=+=Your code ends here=+=+=+=+=+=+=+=+=+=+=*/

void show_info(Panbox *p)
{
    if (p != NULL)
    {
        printf("%d\n", p->item_count);
        for (int i = 0; i < p->item_count; i++)
        {
            printf("%d ", p->item_size[i]);
        }
        printf("\n");
    }
    else
    {
        printf("NULL\n");
    }
}
/*
Function: Display the basic information of given PandoraBox

Implemented by GuTao.
*/

Panbox *p = NULL;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        char op;
        scanf(" %c", &op);
        switch (op)
        {
        case 'C':
        {
            int item_count;
            scanf("%d", &item_count);
            int *item_size = (int *)malloc(item_count * sizeof(int));
            for (int i = 0; i < item_count; i++)
            {
                scanf("%d", &item_size[i]);
            }
            p = create(item_count, item_size);
            free(item_size);
            break;
        }
        case 'D':
        {
            if (p != NULL)
            {
                for (int i = p->item_count - 1; i >= 0; i--)
                {
                    void *data = read(p, i);
                    if (data != NULL)
                    {
                        printc(data, p->item_size[i]);
                    }
                }
            }
            destroy(p);
            break;
        }
        case 'A':
        {
            int len;
            scanf("%d", &len);
            char *hex_str = (char *)malloc(len + 1);
            scanf("%s", hex_str);
            int num_of_byte = (strlen(hex_str) - 1) / 2;
            void *data = (void *)malloc(num_of_byte);
            hex2byte(data, hex_str);
            append(p, data, num_of_byte);
            free(hex_str);
            free(data);
            break;
        }
        case 'W':
        {
            int item_id;
            scanf("%d", &item_id);
            int len;
            scanf("%d", &len);
            char *hex_str = (char *)malloc(len + 1);
            scanf("%s", hex_str);
            int num_of_byte = (strlen(hex_str) - 1) / 2;
            void *data = (void *)malloc(num_of_byte);
            hex2byte(data, hex_str);
            write(p, item_id, data, num_of_byte);
            free(hex_str);
            free(data);
            break;
        }
        case 'R':
        {
            int item_id;
            scanf("%d", &item_id);
            int is_printc;
            scanf("%d", &is_printc);
            void *data = read(p, item_id);
            if (data != NULL)
            {
                if (is_printc)
                {
                    printc(data, p->item_size[item_id]);
                }
                else
                {
                    printx(data, p->item_size[item_id]);
                }
            }
            break;
        }
        case 'Q':
        {
            show_info(p);
            break;
        }
        default:
        {
            break;
        }
        }
    }
    return 0;
}

/*
Main function implemented by GuTao, you cannot rewrite one for yourself.

- Just for you to understand how the functions you implement would be invoked.
- Not exact the main function to test on OJ, this one does not check your error handling.
- You can test your functions on your PC with your own main().
- You may want to hack with your own main function, but this won't help you AC :)
*/
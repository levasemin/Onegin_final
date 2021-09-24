#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/*!
 * struct for describe sentence with his start and end
 */
struct strings
        {
            char *start;
            char *end;
        };

/*!
 * my qsort
 * @param pointer to first of sorting elements
 * @param count_elements count of elements in array
 * @param size size of element
 * @param comparator comparator for determining more element
 */
void my_qsort(void *pointer, size_t count_elements, size_t size, int (* comparator) (const void *, const void *));

/*!
 * sort function, that is called from my_qsort
 * @param data  pointer to data
 * @param left left border of data array
 * @param right right border of data array
 * @param size size of array element
 * @param comparator comparator for determining more element
 */
void sort(void *pointer, long long left, long long right, size_t size, int (* comparator) (const void *, const void *));

/*!
 * function for sort, that iterates over and replace elements
 * @param data array of elements
 * @param left left border of array
 * @param right right border of array
 * @param size size of array element
 * @param comparator for sorting by start of string
 * @return
 */
long long partition(char *data, long long left, long long right, size_t size, int (* comparator) (const void *, const void *));

/*!
 * swap permutation of elements of arbitrary size
 * @param first_pointer pointer to first element
 * @param second_pointer pointer to second element
 */
void swap(void *first_pointer, void *second_pointer, size_t size);

/*!
 * comparator for sorting by start of string
 * @param element1 pointer to struct strings of first string
 * @param element2 pointer to struct strings of second string
 * @return more than 0 if first is more than second, 0 if they are same, less 0 if second is more
 */
int start_comparator(const void *element1, const void *element2);

/*!
 * comparator for special sorting by end of string
 * @param element1 pointer to struct strings of first string
 * @param element2 pointer to struct strings of second string
 * @return more than 0 if first is more than second, 0 if they are same, less 0 if second is more
 */
int back_comparator(const void *element1, const void *element2);

/*!
 * function make array with struct strings elements
 * @warning you need to be sure that you have enough free memory for array of elements
 * @param string pointer to array of char
 * @param count_string count of string, it is count of element array of structs
 * @return pointer to first element of strings array
 */
strings * get_strings_data(char *string, size_t count_string);

/*!
 * function count '\n' in string
 * @param string pointer to string
 * @return count of '\n'
 */
size_t get_count_string(char *string);

/*!
 * @param file pointer to file
 * @return size of file in bytes
 */
size_t get_file_size(FILE *file);

/*!
 * read file with memory allocation for char elements from file
 * @warning you need be sure, that you have free memory for allocation for elements from file
 * @param file pointer to file
 * @return pointer to start of first element
 */
char* read_file(FILE *file);

/*!
 * writing array of struct strings in file
 * @param data pointer to first struct strings
 * @param count_elements count of elements in array
 * @param file the file to write to
 */
void write_in_file(strings *data, long count_elements, FILE *file);
#include "onegin.h"

void my_qsort(void *pointer, size_t count_elements, size_t size, int (* comparator) (const void *, const void *))
{
    assert(pointer != nullptr);
    assert(count_elements > 0);
    assert(size > 0);
    assert(comparator != nullptr);

    sort(pointer, 0, count_elements, size, comparator);
}

void sort(void *pointer, long long left, long long right, size_t size, int (* comparator) (const void *, const void *))
{
    assert(pointer != nullptr);
    assert(left < right);
    assert(size > 0);
    assert(comparator != nullptr);

    if (right - left < 2)
    {
        return;
    }

    char *data = (char *) pointer;

    long long last = partition(data, left, right, size, comparator);

    sort(data, last, right, size, comparator);
    sort(data, left, last,  size, comparator);
}

long long partition(char *data, long long left, long long right, size_t size,
                    int (* comparator) (const void *, const void *))
{
    assert(data != nullptr);
    assert(left < right);
    assert(size > 0);
    assert(comparator != nullptr);

    long long middle = (left + right) / 2;

    swap(data + left * size, data + middle * size, size);

    long long last = left;

    for (long long i = left + 1; i < right; ++i)
    {
        if (comparator(data + i * size, data + left * size) < 0)
        {
            ++last;
            swap(data + last * size, data + i * size, size);
        }
    }

    swap(data + last * size, data + left * size, size);

    if (last == left)
    {
        ++last;
    }

    return last;
}

void swap(void *first_pointer, void *second_pointer, size_t size)
{
    assert(first_pointer != nullptr);
    assert(second_pointer != nullptr);
    assert(size > 0);

    long long *source_long = (long long *) first_pointer;
    long long *destination_long = (long long *) second_pointer;

    long long el_long = 0;

    for (; size >= sizeof(long long); size -= sizeof(long long))
    {
        el_long = *source_long;

        *source_long = *destination_long;
        *destination_long = el_long;

        ++source_long;
        ++destination_long;
    }

    int *source_int = (int *) source_long; // TODO:
    int *destination_int = (int *) destination_long;

    int el_int = 0;

    for (; size >= sizeof(int); size -= sizeof(int))
    {
        el_int = *source_int;

        *source_int = *destination_int;
        *destination_int = el_int;

        ++source_int;
        ++destination_int;
    }

    char *source_char = (char *) source_int;
    char *destination_char = (char *) destination_int;

    char el_char = 0;

    for (; size >= sizeof(char); size-= sizeof(char))
    {
        el_char = *source_char;

        *source_char = *destination_char;
        *destination_char = el_char;

        ++source_char;
        ++destination_char;
    }
}

int start_comparator(const void *element1, const void *element2)
{
    assert(element1 != nullptr);
    assert(element2 != nullptr);

    const strings *str1 = (strings*)element1;
    const strings *str2 = (strings*)element2;
    char *str1_start = str1->start;
    char *str2_start = str2->start;

    while ((tolower(*str1_start) == tolower(*str2_start) && (str1_start < str1->end) && (str2_start < str2->end))
           || (!isalpha(*str1_start) && (str1_start < str1->end))
           || (!isalpha(*str2_start) && (str2_start < str2->end)))
    {
        if (tolower(*str1_start) == tolower(*str2_start))
        {
            ++str1_start;
            ++str2_start;
        }
        else
        {
            if (!isalpha(*str1_start))
            {
                ++str1_start;
            }

            if (!isalpha(*str2_start))
            {
                ++str2_start;
            }
        }
    }

    return tolower(*str1_start) - tolower(*str2_start);
}

int back_comparator(const void *element1, const void *element2)
{
    assert(element1 != nullptr);
    assert(element2 != nullptr);

    const strings *str1 = (strings*)element1;
    const strings *str2 = (strings*)element2;

    char *str1_end = str1->end;
    char *str2_end = str2->end;

    while (tolower((*str1_end) == tolower(*str2_end) && (str2_end > str2->start) && (str1_end > str1->start))
           || (!isalpha(*str1_end) && (str1_end > str1->start))
           || (!isalpha(*str2_end) && (str2_end > str2->start)))
    {
        if (tolower(*(str1_end)) == tolower(*(str2_end)))
        {
            --str1_end;
            --str2_end;
        }
        else
        {
            if (!isalpha(*str1_end))
            {
                --str1_end;
            }

            if (!isalpha(*str2_end))
            {
                --str2_end;
            }
        }
    }

    return tolower(*str1_end) - tolower(*str2_end);
}

strings * get_strings_data(char *string, size_t count_string)
{
    assert(string != nullptr);
    assert(count_string > 0);

    strings *data = (strings *) calloc(count_string, sizeof(strings));
    assert(data);

    for (int i = 0; i < count_string; ++i)
    {
        data[i].start = string;

        data[i].end = strchr(string, '\n');
        string = data[i].end + 1;
    }

    return data;
}

//FIXME: Sublime Text 3 + Far Manager 3

size_t get_count_string(char *string)
{
    assert(string != nullptr);

    size_t count_string = 1;

    while ((string = strchr(string, '\n')) != nullptr)
    {
        ++string;
        ++count_string;
    }

    return count_string;
}

size_t get_file_size(FILE *file)
{
    assert(file != nullptr);

    fseek(file, 0L, SEEK_END);

    int file_size = ftell(file);

    fseek(file, 0L, SEEK_SET);

    return file_size;
}

char* read_file(FILE *file)
{
    assert(file != nullptr);

    size_t file_size = get_file_size(file);

    char *string = (char *)calloc((file_size + 1), sizeof(char));
    assert(string != nullptr);

    size_t count_elements = fread(string, sizeof(char), file_size, file);

    string[count_elements] = '\n';

    return string;
}

void write_in_file(strings *data, long count_elements, FILE *file)
{
    assert(data != nullptr);
    assert(file != nullptr);

    for (int i = 0; i < count_elements; i++)
    {
        fwrite(data[i].start, sizeof(char), data[i].end - data[i].start + 1, file);
    }
}

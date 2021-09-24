#include "onegin.h"

const char* file_name        = "C:\\Users\\levce\\CLionProjects\\Onegin\\hamlet.txt";
const char* sorted_file_name = "C:\\Users\\levce\\CLionProjects\\Onegin\\sorted_hamlet.txt";

int main()
{
    FILE *file = fopen(file_name, "r");
    assert(file);

    char* string = read_file(file);

    size_t count_string = get_count_string(string) - 1;

    strings *data = get_strings_data(string, count_string);

    FILE *sorted_file = fopen(sorted_file_name, "w");
    assert(sorted_file);


    my_qsort(data, count_string, sizeof(strings), start_comparator);

    write_in_file(data, count_string, sorted_file);


    my_qsort(data, count_string, sizeof(strings), back_comparator);

    write_in_file(data, count_string, sorted_file);


    fclose(sorted_file);
}
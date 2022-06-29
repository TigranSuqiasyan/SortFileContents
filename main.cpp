#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

const int count = 1000;

std::vector<std::string> files{"f_0.txt", "f_1.txt", "f_2.txt", "f_3.txt", "f_4.txt"};

template <typename T>
void merge(std::vector<T> &vec, int start, int end){
    std::vector<T> temp(vec.size());
    int mid = start + (end - start) / 2;
    int start_1 = start;
    int end_1 = mid;
    int start_2 = mid + 1;
    int end_2 = end;
    int index = start;
    while ((start_1 <= end_1) && (start_2 <= end_2)){
        if (vec[start_1] < vec[start_2])
            temp[index++] = vec[start_1++];
        else
            temp[index++] = vec[start_2++];
    }
    while(start_1 <= end_1)
        temp[index++] = vec[start_1++];
    while(start_2 <= end_2)
        temp[index++] = vec[start_2++];
    for(int i{start}; i <= end; ++i){
        vec[i] = temp[i];
    }
}

template <typename T>
void merge_sort(std::vector<T> &vec, int start, int end){
    if (start < end){
        int mid = start + (end - start) / 2;
        merge_sort(vec, start, mid);
        merge_sort(vec, mid + 1, end);
        merge(vec, start, end);
    }
}

void write_randoms_on_file(const std::string& filename){
    srand(time(0));
    std::fstream file;
    file.open(filename);
    if(file.is_open()){
        int number{};
        for(int i{}; i < count; ++i){
            number = rand() % 100;
            file.write((char*)&number, sizeof(int));
        }
    }
}

void split_contentes_on_files(const std::string& filename){
    std::vector<int> numbers;
    int number{};
    std::fstream file(filename);
    while(!file.eof()){
        file.read((char*)&number, sizeof(int));
        numbers.push_back(number);
    }
    file.close();
    for(int i{}; i < files.size(); ++i){
        file.open(files[i], std::ios::out);
        for(int j = i * count / 5; j < (i + 1) * count / 5; ++j)
        {
            file.write((char*)&numbers[j], sizeof(int));
        }
        file.close();
    }
}

void sort_file(const std::string& filename){
    int number{};
    std::vector<int> numbers;
    std::fstream file(filename, std::ios::in);
    if(file.is_open()){
        while(!file.eof()){
            file.read((char*)&number, sizeof(int));
            numbers.push_back(number);
        }
    }
    merge_sort(numbers, 0, numbers.size());
    file.close();
    file.open(filename, std::ios::out);
    if(file.is_open()){
        int size = numbers.size();
        for(int i{}; i < size; ++i){
            file.write((char*)&numbers[i], sizeof(int));
        }
    }
    file.close();
}

int main(){
    write_randoms_on_file("test.txt");
    split_contentes_on_files("test.txt");
    for(int i{}; i < files.size(); ++i){
        sort_file(files[i]);
    }
    
}
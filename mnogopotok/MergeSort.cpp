#include <iostream>
#include <vector>
#include <thread>
#include <functional>

class MergeSort 
{
    public:
        void Sort(std::vector<int>& array) 
        {
            if (array.size() <= 1) return;
            std::vector<int> aux(array.size());
            Sort(array, aux, 0, array.size() - 1);
        }

    private:
        void Sort(std::vector<int>& array, std::vector<int>& aux, int low, int high) 
        {
            if (low >= high) return;
            int mid = low + (high - low) / 2;
            Sort(array, aux, low, mid);
            Sort(array, aux, mid + 1, high);
            Merge(array, aux, low, mid, high);
        }

        void Merge(std::vector<int>& array, std::vector<int>& aux, int low, int mid, int high) 
        {
            for (int k = low; k <= high; k++) 
            {
                aux[k] = array[k];
            }

            int i = low, j = mid + 1;
            for (int k = low; k <= high; k++) 
            {
                if (i > mid) 
                {
                    array[k] = aux[j++];
                }
                else if (j > high) {
                    array[k] = aux[i++];
                }
                else if (aux[j] < aux[i]) 
                {
                    array[k] = aux[j++];
                }
                else 
                {
                    array[k] = aux[i++];
                }
            }
        }
    };

    int main() 
    {
        setlocale(LC_ALL, "RUS");
        std::vector<int> array(10);
        std::cout << "Введите 10 чисел: ";
        for (int i = 0; i < 10; ++i) 
        {
            std::cin >> array[i];
        }

        MergeSort mergeSort;

        auto sortFunction = [&mergeSort](std::vector<int>& arr) 
        {
            mergeSort.Sort(arr);
        };

        std::thread mergeSortThread(sortFunction, std::ref(array));

        mergeSortThread.join();

        std::cout << "Отсортированный массив: ";
        for (const int& num : array) 
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        return 0;
    }
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

enum SortType
{
    Shell,
    Hibbard,
    Sedgewick
};

void sortTest();
void timeTest();
void caseTest();

template <typename T>
void printSortTime(std::vector<T>& arr, SortType sortType);


template <typename T>
void shellSort(std::vector<T>& arr, SortType sortType);
int changeGap(int gap, SortType sortType);

template <typename T>
bool isSorted(std::vector<T> arr);


int main()
{
    std::cout << "Sort test: " << '\n';
    sortTest();
    std::cout << '\n' << "Time test: " << '\n';
    timeTest();
    std::cout << '\n' << "Worst cases test: " << '\n';
    caseTest();

    return 0;
}

void sortTest()
{
    std::vector<int> arr{};
    std::vector<int> randomArr{};

    for (size_t i = 0; i < 12; i++)
    {
        randomArr.push_back(rand());
    }

    arr = randomArr;
    shellSort(arr, SortType::Shell);
    std::cout << std::boolalpha << isSorted(arr) << '\n';

    arr = randomArr;
    shellSort(arr, SortType::Hibbard);
    std::cout << std::boolalpha << isSorted(arr) << '\n';

    arr = randomArr;
    shellSort(arr, SortType::Sedgewick);
    std::cout << std::boolalpha << isSorted(arr) << std::endl;
}


void timeTest()
{
    std::vector<int> arr{};
    std::vector<int> randomArr{};

    for (size_t i = 0; i < 48; i++)
    {
        std::cout << '\n' << 1024 * (i + 1) << " elements" << '\n' << '\n';

        for (size_t j = 0; j < 1024; j++)
        {
            randomArr.push_back(rand());
        }

        arr = randomArr;
        printSortTime(arr, SortType::Shell);

        arr = randomArr;
        printSortTime(arr, SortType::Hibbard);

        arr = randomArr;
        printSortTime(arr, SortType::Sedgewick);
    }

    std::cout << std::endl;
}

void caseTest()
{
    const size_t TEST_LENGTH = 1024 * 128;

    std::vector<int> arr1;
    std::vector<int> arr2;
    std::vector<int> arr3;

    for (size_t i = 0; i < TEST_LENGTH; i++)
    {
        arr1.push_back(i);
        arr2.push_back(i);
        arr3.push_back(i);
    }

    std::cout << "Worst case: ";
    printSortTime(arr1, SortType::Shell);
    printSortTime(arr2, SortType::Hibbard);
    printSortTime(arr3, SortType::Sedgewick);
    std::cout << '\n';

    arr1.clear();
    arr2.clear();
    arr3.clear();

    std::mt19937 gen;
    std::uniform_int_distribution<int> dist(0, TEST_LENGTH);

    for (size_t i = 0; i < TEST_LENGTH; i++)
    {
        arr1.push_back(rand());
        arr2.push_back(rand());
        arr3.push_back(rand());
    }

    std::cout << "Medium case: ";
    printSortTime(arr1, SortType::Shell);
    printSortTime(arr2, SortType::Hibbard);
    printSortTime(arr3, SortType::Sedgewick);
    std::cout << '\n';

    arr1.clear();
    arr2.clear();
    arr3.clear();

    for (size_t i = 0; i < TEST_LENGTH; i++)
    {
        arr1.push_back(TEST_LENGTH - i - 1);
        arr2.push_back(TEST_LENGTH - i - 1);
        arr3.push_back(TEST_LENGTH - i - 1);
    }

    std::cout << "BestCase case: ";
    printSortTime(arr1, SortType::Shell);
    printSortTime(arr2, SortType::Hibbard);
    printSortTime(arr3, SortType::Sedgewick);
}

template <typename T>
void printSortTime(std::vector<T>& arr, SortType sortType)
{
    std::string sortName{};

    switch (sortType)
    {
    case Shell:
        sortName = "Shell";
        break;
    case Hibbard:
        sortName = "Hibbard";
        break;
    case Sedgewick:
        sortName = "Sedgewick";
        break;
    default:
        sortName = "";
        break;
    }

    auto start = std::chrono::high_resolution_clock::now();
    shellSort(arr, SortType::Sedgewick);
    auto end = std::chrono::high_resolution_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << sortName << " " << delta << " milliseconds" << '\n';

}

template <typename T> 
void shellSort(std::vector<T>& arr, SortType sortType)
{
    size_t swapCount = 0;

    size_t length = arr.size();
    size_t gap = 1;

    if (length == 0)
    {
        return;
    }

    if (sortType == SortType::Shell)
    {
        gap = length / 2;
    }
    else if (sortType == SortType::Hibbard)
    {
        while (gap < length / 2)
        {
            gap = gap * 2 + 1;
        }
    }
    else if (sortType == SortType::Sedgewick)
    {
        while (gap < length)
        {
            gap = 4 * gap + 3;
        }
    }

    while (gap > 0)
    {
        for (size_t i = gap; i < length; i++)
        {
            T key = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] < key)
            {
                swapCount++;
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = key;
        }
        gap = changeGap(gap, sortType);
    }

    std::cerr << swapCount;
}

int changeGap(int gap, SortType sortType)
{
    int result = gap;

    switch (sortType)
    {
    case Shell:
        result = gap / 2;
        break;
    case Hibbard:
        result = (gap - 1) / 2;
        break;
    case Sedgewick:
        result = gap / 2;
        break;
    default:
        result = 0;
        break;
    }

    return result;
}

template <typename T>
bool isSorted(std::vector<T> arr)
{
    size_t length = arr.size();

    for (size_t i = 0; i < length - 1 ; i++)
    {
        if (arr[i] < arr[i + 1])
        {
            return false;
        }
    }

    return true;
}

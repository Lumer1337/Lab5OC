#include <iostream>
#include <fstream>

class Stack {
private:
    int* array;
    int size;
    int topIndex;

public:
    Stack() {
        size = 10;
        array = new int[size];
        topIndex = -1;
    }

    ~Stack() {
        delete[] array;
    }

    void push(int element) {
        if (topIndex == size - 1) {
            int* newArray = new int[size * 2];
            for (int i = 0; i < size; i++) {
                newArray[i] = array[i];
            }
            delete[] array;
            array = newArray;
            size *= 2;
        }
        topIndex++;
        array[topIndex] = element;
    }

    int pop() {
        if (topIndex == -1) {
            std::cerr << "Stack is empty." << std::endl;
            return -1;
        }
        int element = array[topIndex];
        topIndex--;
        return element;
    }

    int peek() {
        if (topIndex == -1) {
            std::cerr << "Stack is empty." << std::endl;
            return -1;
        }
        return array[topIndex];
    }

    bool isEmpty() {
        return (topIndex == -1);
    }

    void loadFromFile(std::string filename) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Error opening file.");
        }
        delete[] array;
        file >> size;
        array = new int[size];
        file >> topIndex;
        for (int i = 0; i <= topIndex; i++) {
            file >> array[i];
        }
        file.close();
    }

    void saveToFile(std::string filename) {
        std::ofstream file(filename);
        if (!file.good()) {
            file.open(filename, std::ios::out);
        }
        file << size << std::endl;
        file << topIndex << std::endl;
        for (int i = 0; i <= topIndex; i++) {
            file << array[i] << std::endl;
        }
        file.close();
    }
};

int main() {
    Stack myStack;
    myStack.push(1);
    myStack.push(2);
    myStack.push(3);
    myStack.saveToFile("myStack.txt");
    myStack.loadFromFile("myStack.txt");

    std::cout << "Stack after saving to file(321): " << std::endl;
    std::cout << myStack.pop() << std::endl;
    std::cout << myStack.pop() << std::endl;
    std::cout << myStack.pop() << std::endl;

    myStack.push(4);
    myStack.push(5);
    myStack.push(6);

    myStack.saveToFile("myStack.txt");
    myStack.loadFromFile("myStack.txt");

    std::cout << "Stack after loading from file(654): " << std::endl;
    std::cout << myStack.pop() << std::endl;
    std::cout << myStack.pop() << std::endl;
    std::cout << myStack.pop() << std::endl;


    std::cout << "Stack after loading from file(-1-1-1): " << std::endl;
    myStack.saveToFile("myStack.txt");
    myStack.loadFromFile("myStack.txt");
    std::cout << myStack.pop() << std::endl;
    std::cout << myStack.pop() << std::endl;
    std::cout << myStack.pop() << std::endl;

    return 0;
}
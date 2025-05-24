#include <iostream>
#include <regex>
#include <cstring>
#include <string>


const int MaxLength{300};  

double countCoefficient(char*); //  считаем коэфф. гласн./согл.
void inputString(char*);
void addWord(char*&, const char*);  // добавляем слово к строке


int main() {
    
    char* string = new char[MaxLength];
    inputString(string);
    
    std::regex word_regex(R"([a-zA-Z]+)");
    auto words_begin = std::cregex_iterator(string, string + strlen(string), word_regex);
    auto words_end = std::cregex_iterator();
    
    std::cout << "Found words: ";  
    double coefMax = 0;
    char* result = nullptr;
    
    for (auto i = words_begin; i != words_end; ++i) { // ищем слова,сост. из лат. алфавита
        
        std::cmatch match = *i; 
        int wordLength = match.length();  
        char* buffer = new char[wordLength + 1];
        strcpy(buffer, match.str().c_str()); 
        
        double coef = countCoefficient(buffer);  
        
        if (coef > coefMax) { // если коэфф.>предыдущего, то удаляем старые слова и записываем новые
            coefMax = coef;
            delete[] result;  
            result = new char[wordLength + 1];
            strcpy(result, match.str().c_str());
        }
        else if (coef == coefMax) { //если коэфф.=предыдущего, то   добвляем слово в конец + пробел
            addWord(result, match.str().c_str()); //match.str() возвращает std::string
        }
        
        
        delete[] buffer;  
    }
    
    std::cout << "\n->Result: " << (result ? result : "No words found") << std::endl;
    
    delete[] string;
    delete[] result;
    return 0;
}

void inputString(char* string) {
    std::cout << "Enter a string whose length does not exceed 300 characters" << '\n';
    std::cout << "->";
    std::cin.getline(string, MaxLength);
}

double countCoefficient(char* word) {
    int32_t length = strlen(word);
    if (length == 0){
        return 0;  
    }  
    
    const char* vowels = "aeiouyAEIOUY";
    int32_t vowelsCounter = 0;  
    
    for (int32_t i = 0; i < length; ++i) {
        if (strchr(vowels, word[i]) != nullptr) {  
            ++vowelsCounter;
        }
    }
    
    if (vowelsCounter == 0){
        return 0;  
    } 
    return static_cast<double>(vowelsCounter) / length;
}

void addWord(char*& word, const char* addWord) {  
    int lengthWord = strlen(word);
    int lengthAddWord = strlen(addWord);
    int newLength = lengthWord + lengthAddWord + 2;  
    
    char* buffer = new char[newLength];
    strcpy(buffer, word);
    buffer[lengthWord] = ' ';
    buffer[lengthWord + 1] = '\0';  
    strcat(buffer, addWord);
    
    delete[] word; // читстим память, чтобы не было утечки и потом присваеваем указателю word адрес buffer
    word = buffer; 
}


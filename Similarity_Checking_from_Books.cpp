#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <cmath> // Added for mathematical functions if needed

const int NUM_BOOKS = 60; // Adjusted to match the actual number of files
const int TOP_WORDS = 100;
const std::unordered_set<std::string> EXCLUDED_WORDS = {"a", "and", "an", "of", "in", "the"};

// Function to clean and normalize words
std::string normalizeWord(const std::string & word) {
    std::string result;
    for (char ch : word) {
        if (std::isalnum(ch)) {
            result += std::toupper(ch);
        }
    }
    return result;
}

// Function to read file and compute word frequencies
std::unordered_map<std::string, int> computeWordFrequency(const std::string &filename) {
    std::unordered_map<std::string, int> wordCount;
    std::ifstream file(filename);
    std::string word;

    if (file.is_open()) {
        while (file >> word) {
            word = normalizeWord(word);
            if (!word.empty() && EXCLUDED_WORDS.find(word) == EXCLUDED_WORDS.end()) {
                wordCount[word]++;
            }
        }
        file.close();
    }
    return wordCount;
}

// Function to get top 100 words and normalize frequencies
std::unordered_map<std::string, double> getTopNormalizedWords(const std::unordered_map<std::string, int> &wordCount) {
    std::vector<std::pair<std::string, int>> wordList(wordCount.begin(), wordCount.end());

    // Use explicit types in the lambda for sorting
    std::sort(wordList.begin(), wordList.end(), [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
        return a.second > b.second;
    });

    if (wordList.size() > TOP_WORDS) wordList.resize(TOP_WORDS);

    double totalWords = 0;
    for (const auto &[word, freq] : wordList) {
        totalWords += freq;
    }

    std::unordered_map<std::string, double> topWords;
    for (const auto &[word, freq] : wordList) {
        topWords[word] = freq / totalWords;
    }
    return topWords;
}

// Function to compute similarity score between two books
double computeSimilarity(const std::unordered_map<std::string, double> &words1, const std::unordered_map<std::string, double> &words2) {
    double similarity = 0.0;
    for (const auto &[word, freq] : words1) 
    {
        if (words2.find(word) != words2.end()) 
        {
            similarity += freq * words2.at(word); // Fixed to multiply frequencies for similarity
        }
    }
    return similarity;
}

int main() {
    std::vector<std::string> filenames = {  
         "/mnt/data/Book-Txt/Book-Txt/Cats by Moncrif.txt",
    "/mnt/data/Book-Txt/Book-Txt/Foxes Book of Martyrs Part 1.txt",
    "/mnt/data/Book-Txt/Book-Txt/Foxes Book of Martyrs Part 2.txt",
    "/mnt/data/Book-Txt/Book-Txt/Foxes Book of Martyrs Part 3.txt",
    "/mnt/data/Book-Txt/Book-Txt/Foxes Book of Martyrs Part 4.txt",
    "/mnt/data/Book-Txt/Book-Txt/Foxes Book of Martyrs Part 5.txt",
    "/mnt/data/Book-Txt/Book-Txt/Foxes Book of Martyrs Part 6.txt",
    "/mnt/data/Book-Txt/Book-Txt/Gerards Herbal Vol.1.txt",
    "/mnt/data/Book-Txt/Book-Txt/Gerards Herbal Vol.2.txt",
    "/mnt/data/Book-Txt/Book-Txt/Gerards Herbal Vol.3.txt",
    "/mnt/data/Book-Txt/Book-Txt/Gerards Herbal Vol.4.txt",
    "/mnt/data/Book-Txt/Book-Txt/Gil Blas.txt",
    "/mnt/data/Book-Txt/Book-Txt/Gossip in a Library.txt",
    "/mnt/data/Book-Txt/Book-Txt/Hudibras.txt",
    "/mnt/data/Book-Txt/Book-Txt/King of the Beggars.txt",
    "/mnt/data/Book-Txt/Book-Txt/Knocknagow.txt",
    "/mnt/data/Book-Txt/Book-Txt/Les Chats par Moncrif.txt",
    "/mnt/data/Book-Txt/Book-Txt/Lives and Anecdotes of Misers.txt",
    "/mnt/data/Book-Txt/Book-Txt/Lives and Love And Madness.txt",
    "/mnt/data/Book-Txt/Book-Txt/Lives and The Memoirs of Laetitia Pilkington V 1.txt", 
    "/mnt/data/Book-Txt/Book-Txt/Lives and The Memoirs of Laetitia Pilkington V 2.txt",
    "/mnt/data/Book-Txt/Book-Txt/Lives and The Memoirs of Laetitia Pilkington V 3.txt",
    "/mnt/data/Book-Txt/Book-Txt/Lives and Memoirs of Mrs. Margaret Leeson.txt",
    "/mnt/data/Book-Txt/Book-Txt/Monro his Expedition.txt",
    "/mnt/data/Book-Txt/Book-Txt/Mrs. Beeton Book of Household Management.txt",
    "/mnt/data/Book-Txt/Book-Txt/Out Of The Hurly-Burly.txt",
    "/mnt/data/Book-Txt/Book-Txt/Percys Reliques.txt",
    "/mnt/data/Book-Txt/Book-Txt/Pompey The Little.txt",
    "/mnt/data/Book-Txt/Book-Txt/Radical Pamphlets from the English Civil War.txt",
    "/mnt/data/Book-Txt/Book-Txt/Scepsis Scientifica.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Anatomy of Melancholy Part 1.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Anatomy of Melancholy Part 2.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Anatomy of Melancholy Part 3.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Complete Cony-Catching.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Consolation of Philosophy.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Covent Garden Calendar.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Devil on Two Sticks.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Diary of a Lover of Literature.txt",
    "/mnt/data/Book-Txt/Book-Txt/The History of Ireland - Geoffrey Keatin.txt", 
    "/mnt/data/Book-Txt/Book-Txt/The History of the Human Heart.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Ingoldsby Legends.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Life Of Beau Nash.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Life of John Buncle by Thomas.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Life of of King Richard third.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Life of Pico Della Mirandola.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Martyrdom of Man.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Masterpiece of Aristotle.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Memoris of Count Boruwlaski.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Metamorphosis of Ajax.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Newgate Calendar - Supplement 3.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Newgate Calendar  Supplement .txt",
    "/mnt/data/Book-Txt/Book-Txt/The Newgate Calendar  Supplement 2.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Newgate Calendar V 1.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Newgate Calendar V 2.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Newgate Calendar V 3.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Newgate Calendar V 4.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Newgate Calendar V 5.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Newgate Calendar V 6.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Poems of Ossian.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Poetical Works of John Skelton.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Protestant Reformation.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Real Story of John Carteret Pilkington.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Rowley Poems.txt",
    "/mnt/data/Book-Txt/Book-Txt/The Silver Fox.txt",
    };

    std::vector<std::unordered_map<std::string, double>> normalizedWordFreqs(NUM_BOOKS);

    // Process each file to get top normalized word frequencies
    for (int i = 0; i < NUM_BOOKS; ++i) {
        auto wordCount = computeWordFrequency(filenames[i]);
        normalizedWordFreqs[i] = getTopNormalizedWords(wordCount);
    }

    // Create similarity matrix
    std::vector<std::vector<double>> similarityMatrix(NUM_BOOKS, std::vector<double>(NUM_BOOKS, 0.0));
    for (int i = 0; i < NUM_BOOKS; ++i) {
        for (int j = i + 1; j < NUM_BOOKS; ++j) {
            double similarity = computeSimilarity(normalizedWordFreqs[i], normalizedWordFreqs[j]);
            similarityMatrix[i][j] = similarity;
            similarityMatrix[j][i] = similarity;
        }
    }

    // Output the similarity matrix
    for (const auto &row : similarityMatrix) {
        for (double value : row) {
            std::cout << std::fixed << std::setprecision(2) << value << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

#include "FileAVL.hpp"
#include "File.hpp"
#include "FileTrie.hpp"
// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp


/**
 * @brief Helper function for in-order traversal to find files within the given range.
 * 
 * @param node The current node in the AVL tree.
 * @param min The lower bound of the file size range.
 * @param max The upper bound of the file size range.
 * @param result The vector to store pointers to files within the range.
 */
inline void queryHelper(Node* node, size_t min, size_t max, std::vector<File*>& result) {
    if (!node) return; // Base case: null node

    size_t fileSize = node->size_;

    // Traverse left subtree if potential valid files exist
    if (fileSize >= min) {
        queryHelper(node->left_, min, max, result);
    }

    // Include all files in the current node if their file size is within the range
    if (fileSize >= min && fileSize <= max) {
        // Iterate through all files in the current node
        for (File* file : node->files_) {
            result.push_back(file);  // Add the file to the result vector
        }
    }

    // Traverse right subtree if potential valid files exist
    if (fileSize <= max) {
        queryHelper(node->right_, min, max, result);
    }
}




/**
 * @brief Retrieves all files in the FileAVL whose file sizes are within [min, max]
 * 
 * @param min The min value of the file size query range.
 * @param max The max value of the file size query range.
 * @return std::vector<File*> storing pointers to all files in the tree within the given range.
 * @note If the query interval is in descending order (ie. the given parameters min >= max), 
        the interval from [max, min] is searched (since max >= min)
 */
std::vector<File*> FileAVL::query(size_t min, size_t max) {
    std::vector<File*> result;

    // Normalize the range to ensure [min, max]
    if (min > max) std::swap(min, max);

    // Start the recursive query
    queryHelper(root_, min, max, result);

    return result;
}




// FileTrie Implementation

// // Constructor: Initializes the trie with the root node
// FileTrie::FileTrie() {
//     head = new FileTrieNode();  // Root node representing the empty string
// }

// Adds a file to the trie
void FileTrie::addFile(File* f) {



}

// Searches for files with a given prefix
std::unordered_set<File*> FileTrie::getFilesWithPrefix(const std::string& prefix) const {
    std::unordered_set<File*> result;

    // Convert the prefix to lowercase for case-insensitive matching
    std::string lowerPrefix = prefix;
    for (auto& c : lowerPrefix) {
        c = std::tolower(c);
    }

    // Traverse the trie to find the node corresponding to the last character of the prefix
    FileTrieNode* currentNode = head;
    for (char c : lowerPrefix) {
        // If the node doesn't exist, return an empty result
        if (currentNode->next.find(c) == currentNode->next.end()) {
            return result;
        }
        
        // Move to the child node
        currentNode = currentNode->next[c];
    }

    // At this point, currentNode is the node corresponding to the last character of the prefix
    // All files starting with this prefix are in currentNode->matching
    result = currentNode->matching;
    return result;
}

// Destructor: Clean up the dynamically allocated memory
FileTrie::~FileTrie() {
    // Use a helper function to recursively delete all nodes
    std::function<void(FileTrieNode*)> deleteNode = [&](FileTrieNode* node) {
        for (auto& child : node->next) {
            deleteNode(child.second);  // Recursively delete child nodes
        }
        delete node;  // Delete the current node
    };

    deleteNode(head);  // Start deletion from the root node
}
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
    if (fileSize >= min) 
    {
        queryHelper(node->left_, min, max, result);
    }

    // Include the current node if its file size is within range
    if (fileSize >= min && fileSize <= max) 
    {
        File* test = node->files_.front();
        result.push_back(test);
    }
    // Traverse right subtree if potential valid files exist
    if (fileSize <= max) 
    {
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
    queryHelper(root, min, max, result);

    return result;
}


//-----FileTrie Implementation

    // Default constructor
FileTrie::FileTrie()
{

};

    // Add file, ignore case
void FileTrie::addFile(File* f)
{

};

        // Search
std::unordered_set<File*> FileTrie::getFilesWithPrefix(const std::string& prefix) const
{

};

    // Destructor
FileTrie::~FileTrie()
{

};
#include <vector>

template <typename T>
std::vector<std::vector<T>> splitVector(const std::vector<T>& data, size_t numParts) {
    std::vector<std::vector<T>> result;
    size_t dataSize = data.size();
    size_t chunkSize = dataSize / numParts;
    size_t startIndex = 0;

    for (size_t i = 0; i < numParts; ++i) {
        size_t endIndex = startIndex + chunkSize;
        if (i == numParts - 1) {
            // Assign the remaining elements to the last part
            endIndex = dataSize;
        }
        result.emplace_back(data.begin() + startIndex, data.begin() + endIndex);
        startIndex = endIndex;
    }

    return result;
}
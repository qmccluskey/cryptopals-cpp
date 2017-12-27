#ifndef INFO_HPP_
#define INFO_HPP_

#include <vector>

namespace wecrypt {
    float score_english(const std::vector<unsigned char> &buffer);

    int hamming_distance(
            const std::vector<unsigned char> &buffer_a,
            const std::vector<unsigned char> &buffer_b);

    // get average hamming distance between pairs of adjacent blocks
    // returns -1 if block_size is more than half of the buffer size
    float avg_hamming_distance(
            const std::vector<unsigned char> &buffer,
            const unsigned int block_size);
}

#endif // INFO_HPP_

#include <iostream>
#include <string>

#include "challenges/s02c11-ecb-cbc-oracle.hpp"
#include "utils/utils.hpp"
#include "wecrypt/wecrypt.hpp"

const std::string s02::c11::challenge_arg("s02c11");

int s02::c11::ecb_cbc_oracle(int argc, char **argv) {
    if (argc != 2) {
        std::cerr
            << "usage: "
            << argv[0] << " "
            << s02::c11::challenge_arg
            << std::endl;
        return 1;
    }

    auto cipher_mode = wecrypt::random_ecb_cbc_encrypt_oracle(
            wecrypt::aes_pkcs7_encrypt);
    switch (cipher_mode) {
        case wecrypt::cipher_mode::cbc:
            std::cout << "oracle guessed cbc" << std::endl;
            break;
        case wecrypt::cipher_mode::ecb:
            std::cout << "oracle guessed ecb" << std::endl;
            break;
        case wecrypt::cipher_mode::error:
            std::cout << "error with oracle" << std::endl;
            break;
    }

    return 0;
}

#include <algorithm>
#include <memory>
#include <vector>

#include "wecrypt/aes.hpp"
#include "wecrypt/cipher-mode.hpp"
#include "wecrypt/padding.hpp"


namespace wecrypt {
    const encryption_profile aes_pkcs7_encrypt = {
        wecrypt::aes_encrypt,
        wecrypt::pkcs7_pad,
        aes_block_size
    };

    const decryption_profile aes_pkcs7_decrypt = {
        wecrypt::aes_decrypt,
        wecrypt::pkcs7_unpad,
        aes_block_size
    };

    std::shared_ptr<std::vector<unsigned char>> ecb_encrypt(
            const encryption_profile &profile,
            const std::vector<unsigned char> &buffer,
            const std::vector<unsigned char> &key) {
        auto padded_buffer = profile.pad(buffer, profile.block_size);

        auto ciphertext = std::make_shared<std::vector<unsigned char>>(padded_buffer->size());

        for (unsigned int i = 0; i < padded_buffer->size(); i += profile.block_size) {
            auto ciphertext_block = profile.encrypt(
                    std::vector<unsigned char>(
                        padded_buffer->begin() + i,
                        padded_buffer->begin() + i + profile.block_size),
                    key);
            if (!ciphertext_block) {
                return nullptr;
            }

            for (unsigned int j = 0; j < ciphertext_block->size(); j++) {
                (*ciphertext)[i + j] = (*ciphertext_block)[j];
            }
        }

        return ciphertext;
    }

    std::shared_ptr<std::vector<unsigned char>> ecb_decrypt(
            const decryption_profile &profile,
            const std::vector<unsigned char> &buffer,
            const std::vector<unsigned char> &key) {
        if (buffer.size() % profile.block_size != 0) {
            return nullptr;
        }

        auto plaintext = std::make_shared<std::vector<unsigned char>>(buffer.size());

        for (unsigned int i = 0; i < buffer.size(); i += profile.block_size) {
            auto plaintext_block = profile.decrypt(
                    std::vector<unsigned char>(
                        buffer.begin() + i,
                        buffer.begin() + i + profile.block_size),
                    key);
            if (!plaintext_block) {
                return nullptr;
            }

            for (unsigned int j = 0; j < plaintext_block->size(); j++) {
                (*plaintext)[i + j] = (*plaintext_block)[j];
            }
        }

        bool ok = profile.unpad(*plaintext, profile.block_size);
        if (!ok) {
            return nullptr;
        }

        return plaintext;
    }
}
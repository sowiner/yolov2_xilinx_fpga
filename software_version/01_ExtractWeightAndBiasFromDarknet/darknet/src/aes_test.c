#include <stdio.h>
#include <string.h>
#include "aes.h"

int main()
{
    // 定義密鑰和初始化向量
    unsigned char key[32] = {0}; // 256-bit key
    unsigned char iv[16] = {0};  // 128-bit IV for CTR mode

    // 定義輸入和輸出資料
    unsigned char plaintext[16] = "Hello, World!";
    unsigned char ciphertext[16];
    unsigned char decryptedtext[16];

    // 初始化上下文
    aes256ctx ctx;
    aes256_ecb_keyexp(&ctx, key);

    // 加密資料
    aes256_ecb(ciphertext, plaintext, 1, &ctx);

    // 解密資料
    aes256_ecb(decryptedtext, ciphertext, 1, &ctx);

    // 釋放上下文
    aes256_ctx_release(&ctx);

    // 輸出結果
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%02x", ciphertext[i]);
    }
    printf("\nDecrypted text: %s\n", decryptedtext);

    return 0;
}
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "aes.h" // 假設你有一個 AES 庫

int main()
{
    FILE *file;
    uint8_t buffer[16];
    uint8_t ciphertext[16];
    uint8_t key[16] = {0}; // 這裡應該填入你的 AES 金鑰
    aes128ctx ctx;
    size_t bytesRead;

    // 開啟二進位檔案
    file = fopen("input.bin", "rb");
    if (file == NULL)
    {
        perror("無法打開檔案");
        return 1;
    }

    // 讀取 16 位元組的數據塊
    bytesRead = fread(buffer, 1, 16, file);
    if (bytesRead != 16)
    {
        if (feof(file))
        {
            printf("已到達檔案結尾\n");
        }
        else if (ferror(file))
        {
            perror("讀取檔案時發生錯誤");
        }
        fclose(file);
        return 1;
    }

    // 初始化 AES-128 ECB 加密上下文
    aes128_ecb_keyexp(&ctx, key);
    aes128_ecb(ciphertext, buffer, 1, &ctx);

    // 輸出加密後的數據塊
    printf("加密後的數據塊: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    // 關閉檔案
    fclose(file);
    return 0;
}